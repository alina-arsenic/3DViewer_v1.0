#version 330 core

in vec3 lightPos;
in vec3 FragPos;
in vec3 Normal;

out vec4 color;

void main() {
    vec3 lightColor = vec3(1.0f, 0.7f, 0.7f);
    vec3 objectColor = vec3(0.2f, 0.7f, 0.7f);

    float ambientStrength = 0.7f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    color = vec4(result, 1.0f);
}