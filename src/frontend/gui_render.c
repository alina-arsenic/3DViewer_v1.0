#include "gui_main.h"

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int shader_compiler(GLuint *shaderProgram, char *infoLog) {
    int code = 0;

    // Build and compile our shader program
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;

    // Check for compile time errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        code = 1;
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    }

    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        code = 1;
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    }

    // Link shaders
    *shaderProgram = glCreateProgram();
    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glLinkProgram(*shaderProgram);

    // Check for linking errors
    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        code = 1;
        glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return code;
}

void buffer_binder(GLuint *VAO) {
    
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Left  
         0.5f, -0.5f, 0.0f, // Right 
         0.0f,  0.5f, 0.0f  // Top   
    };

    GLuint VBO;
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // Unbind VAO
}
