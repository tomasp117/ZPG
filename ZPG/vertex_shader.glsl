#version 330

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;
layout(location=2) in vec2 vt;

out vec2 uvt;
out vec3 fragNormal;
out vec3 fragPos;
out vec3 texCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

//uniform mat3 normalMatrix ;


void main () {   
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
    fragPos = vec3(modelMatrix * vec4(vp, 1.0));
    fragNormal = normalize(mat3(transpose(inverse(modelMatrix))) * vn);
    texCoords = vp;
    //fragNormal = transpose(inverse(mat3(modelMatrix))) * vn;
    uvt = vt;
};