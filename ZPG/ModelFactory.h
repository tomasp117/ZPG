#pragma once

// PRO0366 Tomáš Prorok 

#include "Model.h"

class ModelFactory
{
public:
    static Model* createModel(const float* vertices, size_t size);

    static Model* createModelWithNormals(const float* vertices, size_t size);

    static Model* createModelWithNormalsAndTextures(const float* vertices, size_t size);

    static Model* createModelFromObj(const std::string& fileName);

};

