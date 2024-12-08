//#version 330
//
//layout(location = 0) in vec3 vp;
//
//out vec3 texCoords;
//
//uniform mat4 modelMatrix;
//
//
//uniform mat4 projectionMatrix;
//uniform mat4 viewMatrix;
//
//void main() {
//    mat4 view = mat4(mat3(viewMatrix)); // Remove translation from the view matrix
//    texCoords = vp;
//    gl_Position = projectionMatrix * view * vec4(vp, 1.0);
//}
//