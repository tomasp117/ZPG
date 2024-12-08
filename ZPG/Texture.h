#pragma once

// PRO0366 Tomáš Prorok 


#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <SOIL.h>

class Texture
{
private:
    GLuint textureID;


public:
	Texture(const char* filePath); // Load texture from file
    
	// create constructor for cubemap
	Texture(const char* x_pos, const char* x_neg, const char* y_pos, const char* y_neg, const char* z_pos, const char* z_neg);
    ~Texture();

    GLuint getTextureID();

    void bind(GLuint unit = 0) const;  // Bind texture to a texture unit
    void unbind() const;
    void bindCube(GLuint unit) const;
	void unbindCube() const;
};

