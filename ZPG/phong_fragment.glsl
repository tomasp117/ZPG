#version 330 core

#define MAX_LIGHTS 4
#define NO_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2
#define DIRECTIONAL_LIGHT 3

struct Light {
    vec3 lightPosition;
    vec3 lightColor;
    float ambientStrength;
    vec3 lightDirection;
    float cutOff;
    float outerCutOff;
    int lightType;
};

struct Material {
    float ra;
    float rd;
    float rs;
    float shininess;
};



in vec3 fragNormal;
in vec3 fragPos;
in vec2 uvt;

out vec4 frag_colour;

uniform sampler2D textureUnitID;
uniform bool useTexture;


uniform Light lights[MAX_LIGHTS];
uniform int numLights;
uniform vec3 objectColor;
uniform vec3 viewPosition;

uniform Material material;  

uniform float constant = 1.0;
uniform float linear = 0.09;
uniform float quadratic = 0.012;

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(viewPosition - fragPos);
    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; i++) {
        if (lights[i].lightType == NO_LIGHT) {
            continue;
        }
        vec3 lightDir;
        float attenuation = 1.0;

        if (lights[i].lightType == POINT_LIGHT) {
            lightDir = normalize(lights[i].lightPosition - fragPos);
            float distance = length(lights[i].lightPosition - fragPos);
            attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

        } else if (lights[i].lightType == DIRECTIONAL_LIGHT) {
            lightDir = normalize(-lights[i].lightDirection);
            attenuation = 1.0;

        } else if (lights[i].lightType == SPOT_LIGHT) {
            lightDir = normalize(lights[i].lightPosition - fragPos);
            float distance = length(lights[i].lightPosition - fragPos);
            attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

            float theta = dot(lightDir, normalize(-lights[i].lightDirection));
            float epsilon = lights[i].cutOff - lights[i].outerCutOff;
            float intensity = clamp((theta - lights[i].outerCutOff) / epsilon, 0.0, 1.0);
            attenuation *= intensity;
        }

        vec3 ambient = lights[i].ambientStrength * lights[i].lightColor * material.ra; // ra

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].lightColor * material.rd; // rd

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // shininess
        vec3 specular = spec * lights[i].lightColor * material.rs; // rs 

        vec3 lightEffect = (ambient + diffuse + specular) * attenuation;
        result += lightEffect;
    }

    result = result * (useTexture ? vec3(texture(textureUnitID, uvt)) : objectColor);
    frag_colour = vec4(result, 1.0);
}