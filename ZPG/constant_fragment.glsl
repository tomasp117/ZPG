#version 330

out vec4 frag_colour;

uniform vec3 objectColor;
uniform sampler2D textureUnitID;
uniform bool useTexture;

in vec2 uvt;

void main () {
    //frag_colour = vec4(objectColor, 1.0);

    if (useTexture)
        frag_colour = texture(textureUnitID, uvt);
    else
        frag_colour = vec4(objectColor, 1.0);
}