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
	Camera* camera1 = new Camera(glm::vec3(0.0f, 1.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, this->ratio);
	camera1->setHeight(this->height);
	camera1->setWidth(this->width);

	vector<Light*> lights1;
	lights1.push_back(new Light(0, glm::vec3(6.0f, 5.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.5f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f));

	Scene* scene = new Scene(camera1, lights1);
	scenes.push_back(scene);

	// Triangle vertices
	float triangle[] = {
		// Position         // Normal           // Texture Coordinates
		1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,  // Vertex 1
		2.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Vertex 2
		1.5f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.5f, 1.0f   // Vertex 3
	};

	// Lines init
	float x_axis[] = {
		-5.0f, 0.0f, 0.0f,
		5.0f, 0.0f, 0.0f
	};
	float y_axis[] = {
		0.0f, -5.0f, 0.0f,
		0.0f, 5.0f, 0.0f
	};
	float z_axis[] = {
		0.0f, 0.0f, -5.0f,
		0.0f, 0.0f, 5.0f
	};

	// Shader init
	ShaderProgram* shader_triangle = createShader("vertex_shader.glsl", "constant_fragment.glsl", GL_TRIANGLES, 0, sizeof(triangle) / sizeof(float) / 3, lights1, camera1);
	ShaderProgram* shader_skybox = createShader("vertex_shader.glsl", "skybox_fragment.glsl", GL_TRIANGLES, 0, sizeof(skycube) / sizeof(float) / 3, lights1, camera1);
	ShaderProgram* shader_line_x = createShader("vertex_shader.glsl", "constant_fragment.glsl", GL_LINES, 0, sizeof(x_axis) / sizeof(float) / 3, lights1, camera1);
	ShaderProgram* shader_line_y = createShader("vertex_shader.glsl", "constant_fragment.glsl", GL_LINES, 0, sizeof(y_axis) / sizeof(float) / 3, lights1, camera1);
	ShaderProgram* shader_line_z = createShader("vertex_shader.glsl", "constant_fragment.glsl", GL_LINES, 0, sizeof(z_axis) / sizeof(float) / 3, lights1, camera1);

	// Model init
	Model* model_triangle = ModelFactory::createModelWithNormalsAndTextures(triangle, sizeof(triangle));
	Model* model_skybox = ModelFactory::createModel(skycube, sizeof(skycube));
	Model* model_line_x = ModelFactory::createModel(x_axis, sizeof(x_axis));
	Model* model_line_y = ModelFactory::createModel(y_axis, sizeof(y_axis));
	Model* model_line_z = ModelFactory::createModel(z_axis, sizeof(z_axis));

	// Object init
	Model* model_login = ModelFactory::createModelFromObj("login.obj");
	ShaderProgram* shader_login = createShader("vertex_shader.glsl", "lambert_fragment.glsl", GL_TRIANGLES, 0, model_login->getNumIndices(), lights1, camera1);

	// Material init
	Material* material = new Material(1.0f, 1.0f, 1.0f, 32.0f);

	// Texture init
	Texture* texture_grass = new Texture("grass.png");
	Texture* texture_wooden_fence = new Texture("wooden_fence.png");
	Texture* texture_house = new Texture("grass.png");
	Texture* texture_skybox = new Texture("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg");

	// Skybox init
	SkyBox* skybox = new SkyBox(model_skybox, shader_skybox ,texture_skybox);
	camera1->addObserver(skybox);
	scenes[0]->setSkyBox(skybox);


	// Triangle object init
	DrawableObject* triangle_object = new DrawableObject(model_triangle, shader_triangle, material, texture_grass);
	triangle_object->addComponent(new Scale(glm::vec3(2.0f)));
	triangle_object->addComponent(new Rotate(45.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
	triangle_object->addComponent(new DynamicTranslate(glm::vec3(-1.0f, 0.0f, 0.0f)));
	triangle_object->setColor(glm::vec3(0.0f, 1.0f, 0.0f)); // Green
	scenes[0]->addObject(triangle_object);

	DrawableObject* triangle_object2 = new DrawableObject(model_triangle, shader_triangle, material, texture_wooden_fence);
	triangle_object2->addComponent(new Scale(glm::vec3(2.0f)));
	triangle_object2->addComponent(new Rotate(45.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
	triangle_object2->addComponent(new Translate(glm::vec3(1.0f, 0.0f, 0.0f)));
	triangle_object2->setColor(glm::vec3(0.0f, 1.0f, 0.0f)); // Green
	scenes[0]->addObject(triangle_object2);

	DrawableObject* triangle_object3 = new DrawableObject(model_triangle, shader_triangle, material, texture_grass);
	triangle_object3->addComponent(new Scale(glm::vec3(2.0f)));
	triangle_object3->addComponent(new Rotate(45.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
	triangle_object3->addComponent(new Translate(glm::vec3(2.0f, 0.0f, 0.0f)));
	triangle_object3->setColor(glm::vec3(0.0f, 1.0f, 0.0f)); // Green
	scenes[0]->addObject(triangle_object3);
	
	// Line objects init
	DrawableObject* x_axis_object = new DrawableObject(model_line_x, shader_line_x);
	x_axis_object->setColor(glm::vec3(0.0f, 0.0f, 1.0f)); // Modrá
	x_axis_object->addComponent(new Translate(glm::vec3(2.0f, 0.0f, 0.0f)));
	scenes[0]->addObject(x_axis_object);

	DrawableObject* y_axis_object = new DrawableObject(model_line_y, shader_line_y);
	y_axis_object->setColor(glm::vec3(1.0f, 1.0f, 0.0f)); // Žlutá
	y_axis_object->addComponent(new Translate(glm::vec3(0.0f, 2.0f, 0.0f)));
	scenes[0]->addObject(y_axis_object);

	DrawableObject* z_axis_object = new DrawableObject(model_line_z, shader_line_z);
	z_axis_object->setColor(glm::vec3(0.0f, 1.0f, 0.0f)); // Zelená
	z_axis_object->addComponent(new Translate(glm::vec3(0.0f, 0.0f, 2.0f)));
	scenes[0]->addObject(z_axis_object);

	// Login object init
	DrawableObject* login_object = new DrawableObject(model_login, shader_login, material, texture_house);
	login_object->addComponent(new Scale(glm::vec3(0.05f)));
	scenes[0]->addObject(login_object);

	camera1->notifyObservers();
	for (Light* light : lights1) {
		light->notifyObservers();
	}

	scenes[0]->getCamera()->rotate(-90.0f, 0.0f);
}

void SceneManager::initScene2() {
	// Camera setup
	Camera* camera2 = new Camera(glm::vec3(0.0f, 10.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, this->ratio);
	camera2->setHeight(this->height);
	camera2->setWidth(this->width);

	// Light setup
	vector<Light*> lights2;

	Light* flashlight = new Light(0, glm::vec3(0.0f, 7.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.5f, glm::vec3(0.0f, 0.0f, 0.0f), 2, 25.5f, 6.5f);
	lights2.push_back(flashlight);

	// Light as observer
	camera2->addObserver(flashlight);
	
	// Scene setup
	Scene* scene = new Scene(camera2, lights2);
	scenes.push_back(scene);

	//Shader init
	ShaderProgram* shader_tree = createShader("vertex_shader.glsl", "lambert_fragment.glsl", GL_TRIANGLES, 0, 92814, lights2, camera2);
	ShaderProgram* shader_bush = createShader("vertex_shader.glsl", "lambert_fragment.glsl", GL_TRIANGLES, 0, 8730, lights2, camera2);
	ShaderProgram* shader_plain = createShader("vertex_shader.glsl", "lambert_fragment.glsl", GL_TRIANGLES, 0, 6, lights2, camera2);
	
	// Model init
	Model* model_tree = ModelFactory::createModelWithNormals(tree, sizeof(tree));
	Model* model_bush = ModelFactory::createModelWithNormals(bushes, sizeof(bushes));
	Model* model_plain = ModelFactory::createModelWithNormalsAndTextures(plain2, sizeof(plain2));

	// Object model and shader init
	Model* model_house = ModelFactory::createModelFromObj("login.obj");
	ShaderProgram* shader_house = createShader("vertex_shader.glsl", "lambert_fragment.glsl", GL_TRIANGLES, 0, model_house->getNumIndices(), lights2, camera2);

	// Texture init
	Texture* texture_grass = new Texture("grass.png");
	Texture* texture_house = new Texture("house.png");

	DrawableObject* plain_object = new DrawableObject(model_plain, shader_plain, texture_grass);
	plain_object->addComponent(new Scale(glm::vec3(10.0f)));
	plain_object->setColor(glm::vec3(1.0f, 0.0f, 0.0f)); // Green
	scenes[1]->addObject(plain_object);

	// Generate random trees and bushes
	for (int i = 0; i < 80; i++) {

		float scale_size_tree = getRandFloat(0.1f, 0.5f);
		float posX_tree = getRandFloat(-10.0f, 10.0f);
		float posZ_tree = getRandFloat(-10.0f, 10.0f);
		glm::vec3 randomPos_tree(posX_tree, 0.0f, posZ_tree);

		DrawableObject* tree_object = new DrawableObject(model_tree, shader_tree);
		tree_object->addComponent(new Translate(randomPos_tree));
		tree_object->addComponent(new Scale(glm::vec3(scale_size_tree)));
		tree_object->addComponent(new DynamicRotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		scenes[1]->addObject(tree_object);

		for (int j = 0; j < 60; j++) {
			float scale_size_bush = getRandFloat(0.5f, 1.0f);
			float posX_bush = getRandFloat(-10.0f , 10.0f );
			float posZ_bush = getRandFloat(-10.0f , 10.0f );
			glm::vec3 randomPos_bush(posX_bush, 0.0f, posZ_bush);

			DrawableObject* bush_object = new DrawableObject(model_bush, shader_bush);
			bush_object->addComponent(new Translate(randomPos_bush));
			bush_object->addComponent(new Scale(glm::vec3(scale_size_bush)));
			
			scenes[1]->addObject(bush_object);
		}
	}

	DrawableObject* house_object = new DrawableObject(model_house, shader_house, new Material(1.0f, 1.0f, 1.0f, 32.0f), texture_house);
	house_object->addComponent(new Scale(glm::vec3(2.0f)));
	house_object->addComponent(new Translate(glm::vec3(0.0f, 2.0f, -5.0f)));
	scenes[1]->addObject(house_object);

	camera2->notifyObservers();
	for (Light* light : lights2) {
		light->notifyObservers();
	}

	scenes[1]->getCamera()->rotate(-90.0f, 0.0f);
}

void SceneManager::initScene3() {
	Camera* camera3 = new Camera(glm::vec3(0.0f, 2.0f, -4.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, ratio);
	camera3->setHeight(this->height);
	camera3->setWidth(this->width);

	vector<Light*> lights3;
	lights3.push_back(new Light(0, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.1f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f));

	Scene* scene = new Scene(camera3, lights3);
	scenes.push_back(scene);

	// Shader init
	ShaderProgram* shader_sphere = createShader("vertex_shader.glsl", "phong_fragment.glsl", GL_TRIANGLES, 0, 92814, lights3, camera3);

	// Model init
	Model* model_sphere = ModelFactory::createModelWithNormals(sphere, sizeof(sphere));

	// Material init
	Material* material = new Material(0.3f, 1.0f, 1.0f, 32.0f);
	Material* material2 = new Material(1.0f, 0.2f, 1.0f, 32.0f);
	Material* material3 = new Material(1.5f, 1.0f, 2.2f, 32.0f);
	Material* material4 = new Material(1.0f, 1.0f, 1.0f, 2.0f);

	// Sphere objects init
	DrawableObject* sphere_object1 = new DrawableObject(model_sphere, shader_sphere, material);
	sphere_object1->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object1->addComponent(new Translate(glm::vec3(-4.0f, 0.0f, 0.0f)));
	sphere_object1->addComponent(new Rotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	scenes[2]->addObject(sphere_object1);

	DrawableObject* sphere_object2 = new DrawableObject(model_sphere, shader_sphere, material2);
	sphere_object2->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object2->addComponent(new Translate(glm::vec3(4.0f, 0.0f, 0.0f)));
	scenes[2]->addObject(sphere_object2);

	DrawableObject* sphere_object3 = new DrawableObject(model_sphere, shader_sphere, material3);
	sphere_object3->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object3->addComponent(new Translate(glm::vec3(0.0f, 4.0f, 0.0f)));
	scenes[2]->addObject(sphere_object3);

	DrawableObject* sphere_object4 = new DrawableObject(model_sphere, shader_sphere, material4);
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
	Camera* camera4 = new Camera(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, ratio);
	camera4->setHeight(this->height);
	camera4->setWidth(this->width);

	vector<Light*> lights4;
	lights4.push_back(new Light(0, glm::vec3(0.0f, 5.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.1f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f));
	lights4.push_back(new Light(1, glm::vec3(0.0f, -20.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.1f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f));

	for (auto light : lights4) {
		camera4->addObserver(light);
	}

	Scene* scene = new Scene(camera4, lights4);
	scenes.push_back(scene);

	// Shader init
	ShaderProgram* shader_sphere1 = createShader("vertex_shader.glsl", "constant_fragment.glsl", GL_TRIANGLES, 0, 2880, lights4, camera4);
	ShaderProgram* shader_sphere2 = createShader("vertex_shader.glsl", "lambert_fragment.glsl", GL_TRIANGLES, 0, 2880, lights4, camera4);
	ShaderProgram* shader_tree = createShader("vertex_shader.glsl", "phong_fragment.glsl", GL_TRIANGLES, 0, 92814, lights4, camera4);
	ShaderProgram* shader_tree2 = createShader("vertex_shader.glsl", "blinn_fragment.glsl", GL_TRIANGLES, 0, 92814, lights4, camera4);

	// Model init
	Model* model_sphere = ModelFactory::createModelWithNormals(sphere, sizeof(sphere));
	Model* model_tree = ModelFactory::createModelWithNormals(tree, sizeof(tree));

	// Object init
	DrawableObject* sphere_object1 = new DrawableObject(model_sphere, shader_sphere1);
	sphere_object1->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object1->addComponent(new Translate(glm::vec3(-4.0f, 0.0f, 0.0f)));
	scenes[3]->addObject(sphere_object1);

	DrawableObject* sphere_object2 = new DrawableObject(model_sphere, shader_sphere2);
	sphere_object2->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object2->addComponent(new Translate(glm::vec3(4.0f, 0.0f, 0.0f)));
	scenes[3]->addObject(sphere_object2);

	DrawableObject* tree_object1 = new DrawableObject(model_tree, shader_tree);
	tree_object1->addComponent(new Scale(glm::vec3(1.0f)));
	tree_object1->addComponent(new Translate(glm::vec3(0.0f, 0.0f, 4.0f)));
	scenes[3]->addObject(tree_object1);

	DrawableObject* tree_object2 = new DrawableObject(model_tree, shader_tree2);
	tree_object2->addComponent(new Scale(glm::vec3(1.0f)));
	tree_object2->addComponent(new Translate(glm::vec3(0.0f, 0.0f, -4.0f)));
	scenes[3]->addObject(tree_object2);


	camera4->notifyObservers();
	for (Light* light : lights4) {
		light->notifyObservers();
	}
	scenes[3]->getCamera()->rotate(-90.0f, 0.0f);
}

void SceneManager::initScene5() {
	// Camera setup
	Camera* camera2 = new Camera(glm::vec3(0.0f, 10.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, this->ratio);
	camera2->setHeight(this->height);
	camera2->setWidth(this->width);

	// Light setup
	vector<Light*> lights2 = {
		new Light(0, glm::vec3(-7.0f, 0.5f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.01f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f),
		new Light(1, glm::vec3(7.0f, 0.5f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.01f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f),
		new Light(2, glm::vec3(1.0f, 0.5f, 7.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.01f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f),
		new Light(3, glm::vec3(0.0f, 11.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.07f, glm::vec3(0.0f, 0.0f, 0.0f), 1, 0.0f, 0.0f)
	};

	// Light as observer
	for (auto light : lights2) {
		camera2->addObserver(light);
	}

	// Scene setup
	Scene* scene = new Scene(camera2, lights2);
	scenes.push_back(scene);

	// Shader init
	ShaderProgram* shader_tree = createShader("vertex_shader.glsl", "lambert_fragment.glsl", GL_TRIANGLES, 0, 92814, lights2, camera2);
	ShaderProgram* shader_bush = createShader("vertex_shader.glsl", "lambert_fragment.glsl", GL_TRIANGLES, 0, 8730, lights2, camera2);
	ShaderProgram* shader_plain = createShader("vertex_shader.glsl", "lambert_fragment.glsl", GL_TRIANGLES, 0, 6, lights2, camera2);
	ShaderProgram* shader_skybox = createShader("vertex_shader.glsl", "skybox_fragment.glsl", GL_TRIANGLES, 0, 36, lights2, camera2);

	// Model init
	Model* model_tree = ModelFactory::createModelWithNormals(tree, sizeof(tree));
	Model* model_bush = ModelFactory::createModelWithNormals(bushes, sizeof(bushes));
	Model* model_plain = ModelFactory::createModelWithNormalsAndTextures(plain2, sizeof(plain2));
	Model* model_skybox = ModelFactory::createModel(skycube, sizeof(skycube));

	// Texture setup
	Texture* texture_grass = new Texture("grass.png");
	Texture* texture_house = new Texture("house.png");
	Texture* texture_skybox = new Texture("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg");
	
	SkyBox* skybox = new SkyBox(model_skybox, shader_skybox, texture_skybox);
	camera2->addObserver(skybox);
	scene->setSkyBox(skybox);

	// Plain object
	DrawableObject* plain_object = new DrawableObject(model_plain, shader_plain, texture_grass);
	plain_object->addComponent(new Scale(glm::vec3(10.0f)));
	plain_object->setColor(glm::vec3(1.0f, 0.0f, 0.0f)); // Green
	scene->addObject(plain_object);

	// Generate random trees and bushes
	for (int i = 0; i < 80; i++) {
		float scale_size_tree = getRandFloat(0.1f, 0.5f);
		float posX_tree = getRandFloat(-10.0f, 10.0f);
		float posZ_tree = getRandFloat(-10.0f, 10.0f);
		glm::vec3 randomPos_tree(posX_tree, 0.0f, posZ_tree);

		DrawableObject* tree_object = new DrawableObject(model_tree, shader_tree);
		tree_object->addComponent(new Translate(randomPos_tree));
		tree_object->addComponent(new Scale(glm::vec3(scale_size_tree)));
		tree_object->addComponent(new DynamicRotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		scene->addObject(tree_object);

		for (int j = 0; j < 60; j++) {
			float scale_size_bush = getRandFloat(0.5f, 1.0f);
			float posX_bush = getRandFloat(-10.0f, 10.0f);
			float posZ_bush = getRandFloat(-10.0f, 10.0f);
			glm::vec3 randomPos_bush(posX_bush, 0.0f, posZ_bush);

			DrawableObject* bush_object = new DrawableObject(model_bush, shader_bush);
			bush_object->addComponent(new Translate(randomPos_bush));
			bush_object->addComponent(new Scale(glm::vec3(scale_size_bush)));
			scene->addObject(bush_object);
		}
	}

	// House model
	Model* model_house = ModelFactory::createModelFromObj("house.obj");
	ShaderProgram* shader_house = createShader("vertex_shader.glsl", "lambert_fragment.glsl", GL_TRIANGLES, 0, model_house->getNumIndices(), lights2, camera2);
	DrawableObject* house_object = new DrawableObject(model_house, shader_house, new Material(1.0f, 1.0f, 1.0f, 32.0f), texture_house);
	house_object->addComponent(new Translate(glm::vec3(0.0f, 0.0f, -8.0f)));
	house_object->addComponent(new Scale(glm::vec3(0.2f)));
	scene->addObject(house_object);

	// Notify observers
	camera2->notifyObservers();
	for (Light* light : lights2) {
		light->notifyObservers();
	}
}



Scene* SceneManager::getActiveScene()
{
	return this->scenes[this->active_scene];
}

void SceneManager::switchScene()
{
	this->active_scene = (this->active_scene + 1) % scenes.size();
}

ShaderProgram* SceneManager::createShader(const char* vertexShader, const char* fragmentShader, GLenum mode, int start, int count, vector<Light*> lights, Camera* camera)
{
	
	ShaderProgram* shader = new ShaderProgram(mode, start, count, lights.size());
	shader->createShaderProgram(vertexShader, fragmentShader);

	camera->addObserver(shader);
	for (Light* light : lights) {
		light->addObserver(shader);
	}

	return shader;
}

vector<Scene*> SceneManager::getScenes()
{
	return this->scenes;
}
