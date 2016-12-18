#version 330 core

struct Light {
    vec3 position;
//  vec3 direction;

//  float cutOff;
//  float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 color;
//    float ambient;
//    float specular;
};

in vec3 FragPos;
in vec3 Normal;

out vec4 color;

uniform Light light;
uniform vec3 viewPos;
uniform vec3 objectColor;
//uniform vec3 lightPos;
//uniform vec3 lightColor;

void main()
{
    // Ambient
    float ambientStrength = 0.08f;
    vec3 ambient = ambientStrength * light.color;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light.color;

    // Attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 result = (ambient + diffuse + specular) * attenuation * objectColor;
    color = vec4(result, 1.0f);
}
