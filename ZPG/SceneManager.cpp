#include "SceneManager.h"

#include "sphere.h"
#include "tree.h"
#include "bushes.h"
#include "plain.h"
#include "skycube.h"

#include "Scale.h"
#include "Rotate.h"
#include "Translate.h"
#include "DynamicRotate.h"
#include "DynamicTranslate.h"

#include <random>
#include <time.h>

SceneManager::SceneManager(float ratio, int width, int height)
{
	this->ratio = ratio;
	this->active_scene = 0;
	this->width = width;
	this->height = height;

}

float getRandFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}



void SceneManager::initScene1() {
	Camera* camera2 = new Camera(glm::vec3(0.0f, 1.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, this->ratio);
	camera2->setHeight(this->height);
	camera2->setWidth(this->width);

	vector<Light*> lights2;
	lights2.push_back(new Light(0, glm::vec3(6.0f, 5.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.5f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f));
	/*
	camera2->addObserver(lights2[1]);
	camera2->addObserver(lights2[0]);*/
	scenes.push_back(new Scene(camera2, lights2));

	float triangle[] = {
		// Position         // Normal           // Texture Coordinates
		1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,  // Vertex 1
		2.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Vertex 2
		1.5f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.5f, 1.0f   // Vertex 3
	};
	size_t size_triangle = sizeof(triangle);
	ShaderProgram* shader_triangle = new ShaderProgram(GL_TRIANGLES, 0, size_triangle / sizeof(float) / 3, lights2.size());
	shader_triangle->createShaderProgram("vertex_shader.glsl", "constant_fragment.glsl");

	camera2->addObserver(shader_triangle);
	
	for (Light* light : lights2) {
		light->addObserver(shader_triangle);
	}

	Model* model_triangle = new Model();
	model_triangle->createBuffer(triangle, sizeof(triangle), true, true);

	Material* material = new Material(1.0f, 1.0f, 1.0f, 32.0f);

	Texture* texture = new Texture("grass.png");
	
	Texture* texture2 = new Texture("wooden_fence.png");



	ShaderProgram* shader_skybox = new ShaderProgram(GL_TRIANGLES, 0, sizeof(skycube) / sizeof(float) / 3, lights2.size());
	shader_skybox->createShaderProgram("vertex_shader.glsl", "skybox_fragment.glsl");

	Model* model_skybox = new Model();
	model_skybox->createBuffer(skycube, sizeof(skycube), false, false);

	camera2->addObserver(shader_skybox);

	for (Light* light : lights2) {
		light->addObserver(shader_skybox);
	}

	Texture* texture_skybox = new Texture("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg");

	SkyBox* skybox = new SkyBox(model_skybox, shader_skybox ,texture_skybox);
	camera2->addObserver(skybox);

	scenes[0]->setSkyBox(skybox);

	DrawableObject* triangle_object = new DrawableObject(model_triangle, shader_triangle, material, texture);
	triangle_object->addComponent(new Scale(glm::vec3(2.0f)));
	triangle_object->addComponent(new Rotate(45.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
	triangle_object->addComponent(new DynamicTranslate(glm::vec3(-1.0f, 0.0f, 0.0f)));
	triangle_object->setColor(glm::vec3(0.0f, 1.0f, 0.0f)); // Green
	scenes[0]->addObject(triangle_object);

	DrawableObject* triangle_object2 = new DrawableObject(model_triangle, shader_triangle, material, texture2);
	triangle_object2->addComponent(new Scale(glm::vec3(2.0f)));
	triangle_object2->addComponent(new Rotate(45.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
	triangle_object2->addComponent(new Translate(glm::vec3(1.0f, 0.0f, 0.0f)));
	triangle_object2->setColor(glm::vec3(0.0f, 1.0f, 0.0f)); // Green
	scenes[0]->addObject(triangle_object2);

	DrawableObject* triangle_object3 = new DrawableObject(model_triangle, shader_triangle, material, texture);
	triangle_object3->addComponent(new Scale(glm::vec3(2.0f)));
	triangle_object3->addComponent(new Rotate(45.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
	triangle_object3->addComponent(new Translate(glm::vec3(2.0f, 0.0f, 0.0f)));
	triangle_object3->setColor(glm::vec3(0.0f, 1.0f, 0.0f)); // Green
	scenes[0]->addObject(triangle_object3);


	float x_axis[] = {
		-5.0f, 0.0f, 0.0f,
		5.0f, 0.0f, 0.0f   
	};

	ShaderProgram* shader_lineX = new ShaderProgram(GL_LINES, 0, sizeof(x_axis) / sizeof(float) / 3, lights2.size());
	shader_lineX->createShaderProgram("vertex_shader.glsl", "constant_fragment.glsl");

	camera2->addObserver(shader_lineX);
	
	for (Light* light : lights2) {
		light->addObserver(shader_lineX);
	}

	
	Model* model_linesX = new Model();
	model_linesX->createBuffer(x_axis, sizeof(x_axis), false, false);

	
	DrawableObject* x_axis_object = new DrawableObject(model_linesX, shader_lineX);
	x_axis_object->setColor(glm::vec3(0.0f, 0.0f, 1.0f)); // Modrá
	x_axis_object->addComponent(new Translate(glm::vec3(2.0f, 0.0f, 0.0f)));
	scenes[0]->addObject(x_axis_object);

	// Osa Y (žlutá)
	float y_axis[] = {
		0.0f, -5.0f, 0.0f, 
		0.0f, 5.0f, 0.0f   
	};

	ShaderProgram* shader_lineY = new ShaderProgram(GL_LINES, 0, sizeof(y_axis) / sizeof(float) / 3, lights2.size());
	shader_lineY->createShaderProgram("vertex_shader.glsl", "constant_fragment.glsl");

	camera2->addObserver(shader_lineY);
	
	for (Light* light : lights2) {
		light->addObserver(shader_lineY);
	}

	Model* model_linesY = new Model();
	model_linesY->createBuffer(y_axis, sizeof(y_axis), false, false);

	DrawableObject* y_axis_object = new DrawableObject(model_linesY, shader_lineY);
	y_axis_object->setColor(glm::vec3(1.0f, 1.0f, 0.0f)); // Žlutá
	y_axis_object->addComponent(new Translate(glm::vec3(0.0f, 2.0f, 0.0f)));
	scenes[0]->addObject(y_axis_object);

	// Osa Z (zelená)
	float z_axis[] = {
		0.0f, 0.0f, -5.0f, 
		0.0f, 0.0f, 5.0f   
	};

	ShaderProgram* shader_lineZ = new ShaderProgram(GL_LINES, 0, sizeof(z_axis) / sizeof(float) / 3, lights2.size());
	shader_lineZ->createShaderProgram("vertex_shader.glsl", "constant_fragment.glsl");

	camera2->addObserver(shader_lineZ);
	
	for (Light* light : lights2) {
		light->addObserver(shader_lineZ);
	}

	Model* model_linesZ = new Model();
	model_linesZ->createBuffer(z_axis, sizeof(z_axis), false, false);

	DrawableObject* z_axis_object = new DrawableObject(model_linesZ, shader_lineZ);
	z_axis_object->setColor(glm::vec3(0.0f, 1.0f, 0.0f)); // Zelená
	z_axis_object->addComponent(new Translate(glm::vec3(0.0f, 0.0f, 2.0f)));
	scenes[0]->addObject(z_axis_object);

	Model* model_house = new Model();
	model_house->load("login.obj");

	ShaderProgram* shader_house = new ShaderProgram(GL_TRIANGLES, 0, model_house->getNumIndices(), lights2.size());
	shader_house->createShaderProgram("vertex_shader.glsl", "lambert_fragment.glsl");

	camera2->addObserver(shader_house);
	for (Light* light : lights2) {
		light->addObserver(shader_house);
	}

	Texture* texture_house = new Texture("grass.png");

	DrawableObject* house_object = new DrawableObject(model_house, shader_house, material, texture_house);
	house_object->addComponent(new Scale(glm::vec3(0.05f)));
	scenes[0]->addObject(house_object);


	camera2->notifyObservers();
	for (Light* light : lights2) {
		light->notifyObservers();
	}

	scenes[0]->getCamera()->rotate(-90.0f, 0.0f);

}

void SceneManager::initScene2() {
	// Nastavení kamery
	Camera* camera2 = new Camera(glm::vec3(0.0f, 10.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, this->ratio);
	camera2->setHeight(this->height);
	camera2->setWidth(this->width);

	// Nastavení svìtel
	vector<Light*> lights2;
	lights2.push_back(new Light(0, glm::vec3(0.0f, 7.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.5f, glm::vec3(0.0f, 0.0f, 0.0f), 2, 25.5f, 6.5f));
	//lights2.push_back(new Light(1, glm::vec3(0.0f, 3.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0, 0));
	// Pøidání svìtel jako observerù kamery
	camera2->addObserver(lights2[0]);
	
	// Vytvoøení scény s kamerou a svìtly
	scenes.push_back(new Scene(camera2, lights2));

	// Vytvoøení shaderù a modelù pro objekty
	ShaderProgram* shader = new ShaderProgram(GL_TRIANGLES, 0, 92814, lights2.size());
	shader->createShaderProgram("vertex_shader.glsl", "blinn_fragment.glsl");

	ShaderProgram* shader_b = new ShaderProgram(GL_TRIANGLES, 0, 8730, lights2.size());
	shader_b->createShaderProgram("vertex_shader.glsl", "blinn_fragment.glsl");

	Model* model = new Model();
	model->createBuffer(tree, sizeof(tree), true, false);

	Model* model_b = new Model();
	model_b->createBuffer(bushes, sizeof(bushes), true, false);

	// Pøidání shaderù jako observerù kamery a svìtel
	camera2->addObserver(shader);
	camera2->addObserver(shader_b);

	for (auto light : lights2) {
		light->addObserver(shader);
		light->addObserver(shader_b);
	}

	// Pøidání plain objektu na scénu
	Model* model_plain = new Model();
	model_plain->createBuffer(plain2, sizeof(plain2), true, true);



	//generate model and shader program for plain	
	ShaderProgram* shader2 = new ShaderProgram(GL_TRIANGLES, 0, 6, lights2.size());
	shader2->createShaderProgram("vertex_shader.glsl", "lambert_fragment.glsl");

	camera2->addObserver(shader2);
	for (auto light : lights2) {
		light->addObserver(shader2);
	}

	Texture* texture = new Texture("grass.png");

	DrawableObject* plain_object = new DrawableObject(model_plain, shader2, texture);
	plain_object->addComponent(new Scale(glm::vec3(10.0f)));
	plain_object->setColor(glm::vec3(1.0f, 0.0f, 0.0f)); // Green
	scenes[1]->addObject(plain_object);

	// Generování stromù a keøù s náhodnými transformacemi
	for (int i = 0; i < 80; i++) {
		// Vytvoøení náhodného stromu
		float scale_size_tree = getRandFloat(0.1f, 0.5f);
		float posX_tree = getRandFloat(-10.0f / scale_size_tree, 10.0f / scale_size_tree);
		float posZ_tree = getRandFloat(-10.0f / scale_size_tree, 10.0f / scale_size_tree);
		glm::vec3 randomPos_tree(posX_tree, 0.0f, posZ_tree);

		DrawableObject* tree_object = new DrawableObject(model, shader);
		tree_object->addComponent(new Scale(glm::vec3(scale_size_tree)));
		tree_object->addComponent(new Translate(randomPos_tree));
		tree_object->addComponent(new DynamicRotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		scenes[1]->addObject(tree_object);

		// Vytvoøení náhodných keøù kolem stromu
		for (int j = 0; j < 60; j++) {
			float scale_size_bush = getRandFloat(0.5f, 1.0f);
			float posX_bush = getRandFloat(-10.0f / scale_size_bush, 10.0f / scale_size_bush);
			float posZ_bush = getRandFloat(-10.0f / scale_size_bush, 10.0f / scale_size_bush);
			glm::vec3 randomPos_bush(posX_bush, 0.0f, posZ_bush);

			DrawableObject* bush_object = new DrawableObject(model_b, shader_b);
			bush_object->addComponent(new Scale(glm::vec3(scale_size_bush)));
			bush_object->addComponent(new Translate(randomPos_bush));
			scenes[1]->addObject(bush_object);
		}
	}
	
	Model* model_house = new Model();
	model_house->load("login.obj");

	ShaderProgram* shader_house = new ShaderProgram(GL_TRIANGLES, 0, model_house->getNumIndices(), lights2.size());
	shader_house->createShaderProgram("vertex_shader.glsl", "lambert_fragment.glsl");

	camera2->addObserver(shader_house);
	for (Light* light : lights2) {
		light->addObserver(shader_house);
	}

	Texture* texture_house = new Texture("house.png");

	DrawableObject* house_object = new DrawableObject(model_house, shader_house, new Material(1.0f, 1.0f, 1.0f, 32.0f), texture_house);
	house_object->addComponent(new Scale(glm::vec3(2.0f)));
	house_object->addComponent(new Translate(glm::vec3(0.0f, 2.0f, -5.0f)));
	scenes[1]->addObject(house_object);

	// Oznámení observerùm a natoèení kamery
	camera2->notifyObservers();
	for (Light* light : lights2) {
		light->notifyObservers();
	}


	scenes[1]->getCamera()->rotate(-90.0f, 0.0f);
}

void SceneManager::initScene3() {
	// Nastavení kamery
	Camera* camera3 = new Camera(glm::vec3(0.0f, 2.0f, -4.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, ratio);
	camera3->setHeight(this->height);
	camera3->setWidth(this->width);
	// Nastavení svìtel
	vector<Light*> lights3;
	lights3.push_back(new Light(0, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.1f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f));

	

	// Vytvoøení scény s kamerou a svìtly
	scenes.push_back(new Scene(camera3, lights3));

	Material* material = new Material(0.3f, 1.0f, 1.0f, 32.0f);
	Material* material2 = new Material(1.0f, 0.2f, 1.0f, 32.0f);
	Material* material3 = new Material(1.5f, 1.0f, 2.2f, 32.0f);
	Material* material4 = new Material(1.0f, 1.0f, 1.0f, 2.0f);

	// Vytvoøení shaderu a modelu pro objekty
	ShaderProgram* shader = new ShaderProgram(GL_TRIANGLES, 0, 92814, lights3.size());
	shader->createShaderProgram("vertex_shader.glsl", "phong_fragment.glsl");

	// Pøidání shaderu jako observeru kamery a svìtel
	camera3->addObserver(shader);
	for (auto light : lights3) {
		light->addObserver(shader);
	}

	Model* model = new Model();
	model->createBuffer(sphere, sizeof(sphere), true, false);

	// Pøidání objektù na scénu
	DrawableObject* sphere_object1 = new DrawableObject(model, shader, material);
	sphere_object1->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object1->addComponent(new Translate(glm::vec3(-4.0f, 0.0f, 0.0f)));
	sphere_object1->addComponent(new Rotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	scenes[2]->addObject(sphere_object1);

	DrawableObject* sphere_object2 = new DrawableObject(model, shader, material2);
	sphere_object2->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object2->addComponent(new Translate(glm::vec3(4.0f, 0.0f, 0.0f)));
	scenes[2]->addObject(sphere_object2);

	DrawableObject* sphere_object3 = new DrawableObject(model, shader, material3);
	sphere_object3->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object3->addComponent(new Translate(glm::vec3(0.0f, 4.0f, 0.0f)));
	scenes[2]->addObject(sphere_object3);

	DrawableObject* sphere_object4 = new DrawableObject(model, shader, material4);
	sphere_object4->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object4->addComponent(new Translate(glm::vec3(0.0f, -4.0f, 0.0f)));
	scenes[2]->addObject(sphere_object4);

	// Oznámení observerùm a natoèení kamery
	camera3->notifyObservers();
	for (Light* light : lights3) {
		light->notifyObservers();
	}
	scenes[2]->getCamera()->rotate(90.0f, 0.0f);
}
void SceneManager::initScene4() {
	// Nastavení kamery
	Camera* camera4 = new Camera(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, ratio);
	camera4->setHeight(this->height);
	camera4->setWidth(this->width);
	// Nastavení svìtel
	vector<Light*> lights4;
	lights4.push_back(new Light(0, glm::vec3(0.0f, 5.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.1f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f));
	lights4.push_back(new Light(1, glm::vec3(0.0f, -20.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.1f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f));

	// Pøidání svìtel jako observerù kamery
	for (auto light : lights4) {
		camera4->addObserver(light);
	}

	// Vytvoøení scény s kamerou a svìtly
	scenes.push_back(new Scene(camera4, lights4));

	// Vytvoøení shaderù a modelù pro objekty
	ShaderProgram* shader1 = new ShaderProgram(GL_TRIANGLES, 0, 92814, lights4.size());
	shader1->createShaderProgram("vertex_shader.glsl", "constant_fragment.glsl");

	ShaderProgram* shader2 = new ShaderProgram(GL_TRIANGLES, 0, 92814, lights4.size());
	shader2->createShaderProgram("vertex_shader.glsl", "lambert_fragment.glsl");

	ShaderProgram* shader3 = new ShaderProgram(GL_TRIANGLES, 0, 92814, lights4.size());
	shader3->createShaderProgram("vertex_shader.glsl", "phong_fragment.glsl");

	ShaderProgram* shader4 = new ShaderProgram(GL_TRIANGLES, 0, 92814, lights4.size());
	shader4->createShaderProgram("vertex_shader.glsl", "blinn_fragment.glsl");

	// Pøidání shaderù jako observerù kamery a svìtel
	camera4->addObserver(shader1);
	camera4->addObserver(shader2);
	camera4->addObserver(shader3);
	camera4->addObserver(shader4);

	for (auto light : lights4) {
		light->addObserver(shader1);
		light->addObserver(shader2);
		light->addObserver(shader3);
		light->addObserver(shader4);
	}

	Model* sphereModel = new Model();
	sphereModel->createBuffer(sphere, sizeof(sphere), true, false);

	Model* treeModel = new Model();
	treeModel->createBuffer(tree, sizeof(tree), true, false);

	// Pøidání objektù na scénu
	DrawableObject* sphere_object1 = new DrawableObject(sphereModel, shader1);
	sphere_object1->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object1->addComponent(new Translate(glm::vec3(-4.0f, 0.0f, 0.0f)));
	scenes[3]->addObject(sphere_object1);

	DrawableObject* sphere_object2 = new DrawableObject(sphereModel, shader2);
	sphere_object2->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object2->addComponent(new Translate(glm::vec3(4.0f, 0.0f, 0.0f)));
	scenes[3]->addObject(sphere_object2);

	DrawableObject* tree_object1 = new DrawableObject(treeModel, shader3);
	tree_object1->addComponent(new Scale(glm::vec3(1.0f)));
	tree_object1->addComponent(new Translate(glm::vec3(0.0f, 0.0f, 4.0f)));
	scenes[3]->addObject(tree_object1);

	DrawableObject* tree_object2 = new DrawableObject(treeModel, shader4);
	tree_object2->addComponent(new Scale(glm::vec3(1.0f)));
	tree_object2->addComponent(new Translate(glm::vec3(0.0f, 0.0f, -4.0f)));
	scenes[3]->addObject(tree_object2);

	// Oznámení observerùm a natoèení kamery
	camera4->notifyObservers();
	for (Light* light : lights4) {
		light->notifyObservers();
	}
	scenes[3]->getCamera()->rotate(-90.0f, 0.0f);
}

void SceneManager::initScene5() {
	// Nastavení kamery
	Camera* camera2 = new Camera(glm::vec3(0.0f, 10.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, this->ratio);
	camera2->setHeight(this->height);
	camera2->setWidth(this->width);
	// Nastavení svìtel
	vector<Light*> lights2;
	lights2.push_back(new Light(0, glm::vec3(-7.0f, 0.5f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.01f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f));
	lights2.push_back(new Light(1, glm::vec3(7.0f, 0.5f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.01f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f));
	lights2.push_back(new Light(2, glm::vec3(1.0f, 0.5f, 7.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.01f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f));
	lights2.push_back(new Light(3, glm::vec3(0.0f, 11.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.07f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f));



	// Vytvoøení scény s kamerou a svìtly
	scenes.push_back(new Scene(camera2, lights2));

	ShaderProgram* shader_skybox = new ShaderProgram(GL_TRIANGLES, 0, sizeof(skycube) / sizeof(float) / 3, lights2.size());
	shader_skybox->createShaderProgram("vertex_shader.glsl", "skybox_fragment.glsl");

	Model* model_skybox = new Model();
	model_skybox->createBuffer(skycube, sizeof(skycube), false, false);

	camera2->addObserver(shader_skybox);

	for (Light* light : lights2) {
		light->addObserver(shader_skybox);
	}

	Texture* texture_skybox = new Texture("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg");

	SkyBox* skybox = new SkyBox(model_skybox, shader_skybox, texture_skybox);
	camera2->addObserver(skybox);

	scenes[4]->setSkyBox(skybox);

	// Vytvoøení shaderù a modelù pro objekty
	ShaderProgram* shader = new ShaderProgram(GL_TRIANGLES, 0, 92814, lights2.size());
	shader->createShaderProgram("vertex_shader.glsl", "lambert_fragment.glsl");

	ShaderProgram* shader_b = new ShaderProgram(GL_TRIANGLES, 0, 8730, lights2.size());
	shader_b->createShaderProgram("vertex_shader.glsl", "lambert_fragment.glsl");

	Model* model = new Model();
	model->createBuffer(tree, sizeof(tree), true, false);

	Model* model_b = new Model();
	model_b->createBuffer(bushes, sizeof(bushes), true, false);

	// Pøidání shaderù jako observerù kamery a svìtel
	camera2->addObserver(shader);
	camera2->addObserver(shader_b);

	for (auto light : lights2) {
		light->addObserver(shader);
		light->addObserver(shader_b);
	}

	// Pøidání plain objektu na scénu
	Model* model_plain = new Model();
	model_plain->createBuffer(plain2, sizeof(plain2), true, true);

	Texture* texture = new Texture("grass.png");
	Material* material = new Material(0.3f, 1.0f, 1.0f, 32.0f);
	//generate model and shader program for plain	
	ShaderProgram* shader2 = new ShaderProgram(GL_TRIANGLES, 0, 6, lights2.size());
	shader2->createShaderProgram("vertex_shader.glsl", "lambert_fragment.glsl");

	camera2->addObserver(shader2);
	for (auto light : lights2) {
		light->addObserver(shader2);
	}


	DrawableObject* plain_object = new DrawableObject(model_plain, shader2, material, texture);
	plain_object->addComponent(new Scale(glm::vec3(10.0f)));
	scenes[4]->addObject(plain_object);

	// Generování stromù a keøù s náhodnými transformacemi
	for (int i = 0; i < 80; i++) {
		// Vytvoøení náhodného stromu
		float scale_size_tree = getRandFloat(0.1f, 0.5f);
		float posX_tree = getRandFloat(-10.0f / scale_size_tree, 10.0f / scale_size_tree);
		float posZ_tree = getRandFloat(-10.0f / scale_size_tree, 10.0f / scale_size_tree);
		glm::vec3 randomPos_tree(posX_tree, 0.0f, posZ_tree);

		DrawableObject* tree_object = new DrawableObject(model, shader);
		tree_object->addComponent(new Scale(glm::vec3(scale_size_tree)));
		tree_object->addComponent(new Translate(randomPos_tree));
		tree_object->addComponent(new DynamicRotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		scenes[4]->addObject(tree_object);

		// Vytvoøení náhodných keøù kolem stromu
		for (int j = 0; j < 60; j++) {
			float scale_size_bush = getRandFloat(0.5f, 1.0f);
			float posX_bush = getRandFloat(-10.0f / scale_size_bush, 10.0f / scale_size_bush);
			float posZ_bush = getRandFloat(-10.0f / scale_size_bush, 10.0f / scale_size_bush);
			glm::vec3 randomPos_bush(posX_bush, 0.0f, posZ_bush);

			DrawableObject* bush_object = new DrawableObject(model_b, shader_b);
			bush_object->addComponent(new Scale(glm::vec3(scale_size_bush)));
			bush_object->addComponent(new Translate(randomPos_bush));
			scenes[4]->addObject(bush_object);
		}
	}

	Model* model_house = new Model();
	model_house->load("house.obj");

	ShaderProgram* shader_house = new ShaderProgram(GL_TRIANGLES, 0, model_house->getNumIndices(), lights2.size());
	shader_house->createShaderProgram("vertex_shader.glsl", "lambert_fragment.glsl");

	camera2->addObserver(shader_house);
	for (Light* light : lights2) {
		light->addObserver(shader_house);
	}

	Texture* texture_house = new Texture("house.png");

	DrawableObject* house_object = new DrawableObject(model_house, shader_house, new Material(1.0f, 1.0f, 1.0f, 32.0f), texture_house);	
	house_object->addComponent(new Translate(glm::vec3(0.0f, 0.0f, -8.0f)));
	house_object->addComponent(new Scale(glm::vec3(0.2f)));
	scenes[4]->addObject(house_object);

	// Login model
	Model* model_login = new Model();
	model_login->load("login.obj");

	ShaderProgram* shader_login = new ShaderProgram(GL_TRIANGLES, 0, model_login->getNumIndices(), lights2.size());
	shader_login->createShaderProgram("vertex_shader.glsl", "lambert_fragment.glsl");

	camera2->addObserver(shader_login);
	for (Light* light : lights2) {
		light->addObserver(shader_login);
	}

	Texture* texture_login = new Texture("grass.png");

	DrawableObject* login_object = new DrawableObject(model_login, shader_login, new Material(1.0f, 1.0f, 1.0f, 32.0f), texture_login);
	login_object->addComponent(new Translate(glm::vec3(0.0f, 4.0f, -8.0f)));
	login_object->addComponent(new Scale(glm::vec3(2.0f)));

	scenes[4]->addObject(login_object);




	// Oznámení observerùm a natoèení kamery
	camera2->notifyObservers();
	for (Light* light : lights2) {
		light->notifyObservers();
	}
	scenes[4]->getCamera()->rotate(-90.0f, 0.0f);
}


Scene* SceneManager::getActiveScene()
{
	return this->scenes[this->active_scene];
}

void SceneManager::switchScene()
{
	this->active_scene = (this->active_scene + 1) % scenes.size();
}

vector<Scene*> SceneManager::getScenes()
{
	return this->scenes;
}
