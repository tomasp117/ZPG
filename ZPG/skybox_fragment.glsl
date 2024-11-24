#version 330 core

in vec3 texCoords; // P�edan� sou�adnice z vertex shaderu
out vec4 frag_colour;

uniform samplerCube textureUnitID; // Sampler pro cube map

void main() {
    frag_colour = texture(textureUnitID, texCoords);
}