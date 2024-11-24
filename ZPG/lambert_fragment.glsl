#version 330 core

#define MAX_LIGHTS 4
#define NO_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2
#define DIRECTIONAL_LIGHT 3

struct Light {
    vec3 lightPosition;   // Pozice svìtla
    vec3 lightColor;      // Barva svìtla
    float ambientStrength; // Síla ambientního svìtla
    vec3 lightDirection;       // Smìr svìtla (pro spotlight a directional)
    float cutOff;         // Úhel kužele pro spotlight (cosine hodnoty)
    float outerCutOff;    // Vnìjší úhel kužele pro rozptýlený okraj (pro spotlight)
    int lightType;             // Typ svìtla: POINT_LIGHT, SPOT_LIGHT, DIRECTIONAL_LIGHT
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
    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; i++) {
        if (lights[i].lightType == NO_LIGHT) {
            continue;
        }
        vec3 lightDir;
        float attenuation = 1.0;

        // Rozlišení typu svìtla
        if (lights[i].lightType == POINT_LIGHT) {
            // Point Light: svìtlo vyzaøuje ze svého støedu
            lightDir = normalize(lights[i].lightPosition - fragPos);
            float distance = length(lights[i].lightPosition - fragPos);
            attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

        } else if (lights[i].lightType == DIRECTIONAL_LIGHT) {
            // Directional Light: svìtlo má pouze smìr
            lightDir = normalize(-lights[i].lightDirection);
            attenuation = 1.0;  // Directional light nemá útlum

        } else if (lights[i].lightType == SPOT_LIGHT) {
            // Spotlight: svìtlo smìøuje v kuželu od svìtelného bodu
            lightDir = normalize(lights[i].lightPosition - fragPos);
            float distance = length(lights[i].lightPosition - fragPos);
            attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

            // Výpoèet intenzity kuželu
            float theta = dot(lightDir, normalize(-lights[i].lightDirection));
            float epsilon = lights[i].cutOff - lights[i].outerCutOff;
            float intensity = clamp((theta - lights[i].outerCutOff) / epsilon, 0.0, 1.0);

            // Úprava difúzní a spekulární složky pro spotlight efekt
            attenuation *= intensity;
        }

        // Ambientní složka
        vec3 ambient = lights[i].ambientStrength * lights[i].lightColor * material.ra;

        // Difúzní složka
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].lightColor * material.rd;

    

        // Výpoèet celkového efektu svìtla (ambient + diffuse) s útlumem
        vec3 lightEffect = (ambient + diffuse) * attenuation;
        result += lightEffect;
    }

    // Aplikace barvy objektu a výstup finální barvy fragmentu
    result = result * (useTexture ? vec3(texture(textureUnitID, uvt)) : objectColor);
    frag_colour = vec4(result, 1.0);
}