#include "ModelFactory.h"

Model* ModelFactory::createModel(const float* vertices, size_t size)
{
	Model* model = new Model();
	model->createBuffer(vertices, size, false, false);
	return model;
}

Model* ModelFactory::createModelWithNormals(const float* vertices, size_t size)
{
	Model* model = new Model();
	model->createBuffer(vertices, size, true, false);
	return model;
}

Model* ModelFactory::createModelWithNormalsAndTextures(const float* vertices, size_t size)
{
	Model* model = new Model();
	model->createBuffer(vertices, size, true, true);
	return model;
}

Model* ModelFactory::createModelFromObj(const std::string& fileName)
{
	Model* model = new Model();
	model->load(fileName);
	return model;
}