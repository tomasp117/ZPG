#pragma once
#include <GL/glew.h>
#include <stdio.h>

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

struct Vertex
{
	float Position[3];
	float Normal[3];
	float Texture[2];
	float Tangent[3];
};

class Model
{
private:
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;

	int numIndices;

public:
	Model();
	~Model();
	void createBuffer(const float* points, size_t size, bool hasNormal, bool hasTexture);
	void bindVAO();
	void unbindVAO();
	void load(std::string fileName);
	int getNumIndices();
};

