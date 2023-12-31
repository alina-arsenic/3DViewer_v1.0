#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 lightPos;
out vec3 FragPos;  
out vec3 Normal;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0f);
    lightPos = vec3(position) * vec3(1.3f, 0.7f, 1.5f);
    FragPos = vec3(model * vec4(position, 1.0f));
    Normal = normal;
}
