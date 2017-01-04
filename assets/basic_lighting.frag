#version 330 core

struct PointLight {
    vec3 color;
    vec3 position;
    float constant;
    float linear;
    float quadratic;

    float ambient;// to generalize
    float diffuse;
    float specular;
};

struct SpotLight {
    vec3 color;
    vec3 position;
    vec3 direction;
    float cutoff;
    float outer_cutoff;

    float constant;
    float linear;
    float quadratic;

    float ambient;// to generalize
    float diffuse;
    float specular;
};

#define NR_POINT_LIGHTS 6
#define NR_SPOT_LIGHTS 0

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform sampler2D material_diffuse;   // cannot be in struct
uniform sampler2D material_specular;  // cannot be in struct
uniform float material_shininess;     // cannot be in struct
uniform PointLight pointLights[NR_POINT_LIGHTS + 1];
uniform SpotLight spotLights[NR_SPOT_LIGHTS + 1];

// // Calculates the color when using a directional light.
// vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
// {
//     vec3 lightDir = normalize(-light.direction);
//     // Diffuse shading
//     float diff = max(dot(normal, lightDir), 0.0);
//     // Specular shading
//     vec3 reflectDir = reflect(-lightDir, normal);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material_shininess);
//     // Combine results
//     vec3 ambient = light.ambient * vec3(texture(material_diffuse, TexCoords));
//     vec3 diffuse = light.diffuse * diff * vec3(texture(material_diffuse, TexCoords));
//     vec3 specular = light.specular * spec * vec3(texture(material_specular, TexCoords));
//     return (ambient + diffuse + specular);
// }

// Function prototypes
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Phase 1: Directional lighting
    //vec3 result = CalcDirLight(dirLight, norm, viewDir);
    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    // Phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    // Phase 3: Spot light
    for(int i = 0; i < NR_SPOT_LIGHTS; i++)
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);

    color = vec4(result /*+ ambient*/, 1.0);
    //color = vec4(vec3(texture(material_diffuse, TexCoords)), 1.0); // for development purposes only
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material_shininess);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Combine results
    vec3 ambient = light.ambient * vec3(texture(material_diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material_diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material_specular, TexCoords));

    return (diffuse + specular) * attenuation * light.color;
}

// Calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material_shininess);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outer_cutoff;
    float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0, 1.0);
    // Combine results
    vec3 ambient = light.ambient * vec3(texture(material_diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material_diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material_specular, TexCoords));

    return (diffuse + specular) * attenuation * intensity * light.color;
}
