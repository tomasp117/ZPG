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

in vec3 fragNormal; // normal in world space
in vec3 fragPos; // position in world space
in vec2 uvt; // texture coordinates

out vec4 frag_colour; // output color

uniform sampler2D textureUnitID; // texture unit ID
uniform bool useTexture; // use texture or not (color or texture)

uniform Light lights[MAX_LIGHTS];
uniform int numLights;
uniform vec3 objectColor;
uniform vec3 viewPosition; // camera position

uniform Material material; 

uniform float constant = 1.0; 
uniform float linear = 0.09;
uniform float quadratic = 0.012;

void main() {
    vec3 norm = normalize(fragNormal); // normal in world space
    vec3 viewDir = normalize(viewPosition - fragPos); // view direction
    vec3 result = vec3(0.0); // final color

    for (int i = 0; i < numLights; i++) {

        if (lights[i].lightType == NO_LIGHT) { // no light
            continue;
        }

        vec3 lightDir;
        float attenuation = 1.0;
        
        if (lights[i].lightType == POINT_LIGHT) { // point light
            lightDir = normalize(lights[i].lightPosition - fragPos);
            float distance = length(lights[i].lightPosition - fragPos); // distance between light and fragment 
            attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance)); 

        } else if (lights[i].lightType == DIRECTIONAL_LIGHT) { // directional light
            lightDir = normalize(-lights[i].lightDirection); 
            attenuation = 1.0;

        } else if (lights[i].lightType == SPOT_LIGHT) { // spot light
            lightDir = normalize(lights[i].lightPosition - fragPos);
            float distance = length(lights[i].lightPosition - fragPos); // distance between light and fragment
            attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

            float theta = dot(lightDir, normalize(-lights[i].lightDirection)); // angle between light direction and light cone direction
            float epsilon = lights[i].cutOff - lights[i].outerCutOff; // angle between inner and outer cone
            float intensity = clamp((theta - lights[i].outerCutOff) / epsilon, 0.0, 1.0); // intensity of the light 
            attenuation *= intensity; // apply intensity to the attenuation
        }

        vec3 ambient = lights[i].ambientStrength * lights[i].lightColor * material.ra; 

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].lightColor * material.rd; // diffuse reflection

        vec3 halfDir = normalize(lightDir + viewDir); // half vector
        float spec = pow(max(dot(norm, halfDir), 0.0), material.shininess);
        vec3 specular = spec * lights[i].lightColor * material.rs; // specular reflection

        vec3 lightEffect = (ambient + diffuse + specular) * attenuation; 
        result += lightEffect; // sum up all light effects
    }

    result = result * (useTexture ? vec3(texture(textureUnitID, uvt)) : objectColor); // apply texture or object color
    frag_colour = vec4(result, 1.0); // output color
}