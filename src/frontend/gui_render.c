#include "gui_main.h"

GLchar *getFileBuffer(char *path) {
    FILE *file = fopen(path, "r");
    GLchar *buffer = 0;
    long length; int code = 0;

    if (file) {
        fseek(file, 0, SEEK_END);
        length = ftell (file);
        fseek(file, 0, SEEK_SET);
        buffer = malloc(length+1);
        if (buffer) fread (buffer, 1, length, file);
        else code = 1;
        fclose(file);
        buffer[length] = '\0';
    } else {
        code = 1;
    }
    if (code == 1) buffer = 0;
    return buffer;
}

int shadersInit(render_data *render, GLchar *infoLog) {

    int code = 0;
    GLchar *vertex_buffer = getFileBuffer("shaders/vertex.glsl");
    GLchar *fragment_buffer = getFileBuffer("shaders/fragment.glsl");
    if (vertex_buffer == 0 || fragment_buffer == 0) {
        code = 1;
        strcat(infoLog, "Error reading shader files");
    } else {
        const GLchar *vertexShaderSource = vertex_buffer;
        const GLchar *fragmentShaderSource = fragment_buffer;

        // Vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // Check for compile time errors
        GLint success;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            code = 1;
            glGetShaderInfoLog(vertexShader, LOG_LEN, NULL, infoLog);
        }

        // Fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // Check for compile time errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            code = 1;
            glGetShaderInfoLog(fragmentShader, LOG_LEN, NULL, infoLog);
        }

        // Link shaders
        render->shaderProgram = glCreateProgram();
        glAttachShader(render->shaderProgram, vertexShader);
        glAttachShader(render->shaderProgram, fragmentShader);
        glLinkProgram(render->shaderProgram);
        // Check for linking errors
        glGetProgramiv(render->shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            code = 1;
            glGetShaderInfoLog(render->shaderProgram, LOG_LEN, NULL, infoLog);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    return code;
}

int modelLoad(model *model) {
    int code = 0;
    model->scene = 0;
    model->scene = aiImportFile(model->path, aiProcessPreset_TargetRealtime_MaxQuality);
    if (model->scene == 0) {
        code = 1;
        strcat(model->infoLog, "Error loading model from file");
    }
    return code;
}

void init_minmax(model *model, C_STRUCT aiVector3D v) {
    model->max.x = v.x;
    model->min.x = v.x;
    model->max.y = v.y;
    model->min.y = v.y;
    model->max.z = v.z;
    model->min.z = v.z;
}

void minmax(model *model, C_STRUCT aiVector3D v) {
    max(model->max.x, v.x);
    max(model->max.y, v.y);
    max(model->max.z, v.z);

    min(model->min.x, v.x);
    min(model->min.y, v.y);
    min(model->min.z, v.z);
}

void countVerticesAndFaces(model *model) {
    unsigned int faces = 0, vertices = 0;
    for (unsigned int i = 0; i < model->scene->mNumMeshes; i++) {
        struct aiMesh *mesh = model->scene->mMeshes[i];
        vertices += mesh->mNumVertices;
        faces += mesh->mNumFaces;
    }
    model->vertices_count = vertices;
    model->faces_count = faces;
}

int buffersInit(model *model) {

    int code = 0;

    glGenVertexArrays(1, &model->VAO);
    glGenBuffers(1, &model->VBO);
    glGenBuffers(1, &model->EBO);

    glBindVertexArray(model->VAO);
    countVerticesAndFaces(model);

    GLfloat vertices[model->vertices_count * 3 * 2];
    verticesInit(model, vertices);
    glBindBuffer(GL_ARRAY_BUFFER, model->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint indices[model->faces_count * 3];
    indicesInit(model, indices);
    utilityInit(model);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct aiVector3D)*2, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct aiVector3D)*2, (GLvoid*)(sizeof(struct aiVector3D)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
    glBindVertexArray(0);  // Unbind VAO

    return code;
}

void verticesInit(model *model, GLfloat *vertices) {
    init_minmax(model, model->scene->mMeshes[0]->mVertices[0]);
    unsigned int count = 0;
    for (unsigned int j = 0; j < model->scene->mNumMeshes; j++) {
        struct aiMesh *mesh = model->scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            minmax(model, mesh->mVertices[i]);
            vertices[count] = mesh->mVertices[i].x;
            vertices[count+1] = mesh->mVertices[i].y;
            vertices[count+2] = mesh->mVertices[i].z;
            vertices[count+3] = mesh->mNormals[i].x;
            vertices[count+4] = mesh->mNormals[i].y;
            vertices[count+5] = mesh->mNormals[i].z;
            count += 6;
        }
    }
}

void indicesInit(model *model, GLuint *indices) {
    unsigned int count = 0;
    unsigned int shift = 0;
    for (unsigned int j = 0; j < model->scene->mNumMeshes; j++) {
        struct aiMesh *mesh = model->scene->mMeshes[j];
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            indices[count] = mesh->mFaces[i].mIndices[0] + shift;
            indices[count+1] = mesh->mFaces[i].mIndices[1] + shift;
            indices[count+2] = mesh->mFaces[i].mIndices[2] + shift;
            count += 3;
        }
        shift += mesh->mNumVertices;
    }
}

void utilityInit(model *model) {
    double delta_x = model->max.x - model->min.x;
    double delta_y = model->max.y - model->min.y;
    double delta_z = model->max.z - model->min.z;
    double delta_max = (delta_x > delta_y) ? delta_x : delta_y;
    if (delta_z > delta_max) delta_max = delta_z;

    model->trans.x = 0;
    model->trans.y = -(model->max.y + model->min.y) / 2;
    model->trans.z = delta_max * -1.5;

    model->center.x = 0;
    model->center.y = -(model->max.y + model->min.y) / 2;
    model->center.z = -(model->max.z + model->min.z) / 2;

    model->scale = delta_max / 50;

}

void modelDraw(render_data *render) {

    double buf_x_r = gtk_adjustment_get_value(render->ctrls->rotat_x.adj);
    double buf_y_r = gtk_adjustment_get_value(render->ctrls->rotat_y.adj);
    double buf_z_r = gtk_adjustment_get_value(render->ctrls->rotat_z.adj);

    double buf_scale = gtk_adjustment_get_value(render->ctrls->scale.adj);

    double buf_x_t = gtk_adjustment_get_value(render->ctrls->trans_x.adj);
    double buf_y_t = gtk_adjustment_get_value(render->ctrls->trans_y.adj);
    double buf_z_t = gtk_adjustment_get_value(render->ctrls->trans_z.adj);

    vec3 base_vec = {0.0f, 0.0f, 0.0f};

    mat4 model;
    glm_translate_make(model, base_vec);

    vec3 x_rotation_vec = {0.0f, 1.0f, 0.0f};
    vec3 y_rotation_vec = {-1.0f, 0.0f, 0.0f};
    vec3 z_rotation_vec = {0.0f, 0.0f, 1.0f};

    vec3 center_vec = {render->model->center.x, -render->model->center.y, -render->model->center.z};
    glm_translate(model, center_vec);

    glm_rotate(model, (GLfloat)buf_x_r / -50.0f, x_rotation_vec);
    glm_rotate(model, (GLfloat)buf_y_r / -50.0f, y_rotation_vec);
    glm_rotate(model, (GLfloat)buf_z_r / -50.0f, z_rotation_vec);

    center_vec[0] *= -1; center_vec[1] *= -1; center_vec[2] *= -1;
    glm_translate(model, center_vec);


    mat4 view;
    glm_translate_make(view, base_vec);
    //printf("%lf %lf %lf\n", render->model->trans.x, render->model->trans.y, render->model->trans.z);
    vec3 trans_vec = {render->model->trans.x + buf_x_t * render->model->scale,
                      render->model->trans.y + buf_y_t * render->model->scale,
                    ((render->model->trans.z + buf_z_t * render->model->scale)) / (0.5 + buf_scale / 20)};
    glm_translate(view, trans_vec);

    mat4 projection;
    glm_translate_make(projection, base_vec);
    glm_perspective(45.0f, (GLfloat)render->width/render->height, 0.1f, 2000.0f, projection);

    GLint modelLoc = glGetUniformLocation(render->shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat *)model);
    
    GLint viewLoc = glGetUniformLocation(render->shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat *)view);

    GLint projectionLoc = glGetUniformLocation(render->shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (const GLfloat *)projection);

    // Draw our first triangle
    glUseProgram(render->shaderProgram);

    glBindVertexArray(render->model->VAO);
    glDrawElements(GL_TRIANGLES, render->model->faces_count * 3, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

}
