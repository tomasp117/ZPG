#include "SceneManager.h"

#include "sphere.h"
#include "tree.h"
#include "bushes.h"
#include "plain.h"

#include "Scale.h"
#include "Rotate.h"
#include "Translate.h"

#include <random>
#include <time.h>

SceneManager::SceneManager(float ratio)
{
	this->ratio = ratio;
	this->active_scene = 0;
}

float getRandFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void SceneManager::initScene1() {
	Camera* camera1 = new Camera(glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, this->ratio);
	//Light* light1 = new Light(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f ));

	vector<Light*> lights1;
	lights1.push_back(new Light(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.1f));
	lights1.push_back(new Light(glm::vec3(0.0f, -20.0f, 0.0f), glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), 0.1f));



	scenes.push_back(new Scene(camera1));

	float triangle[] = { 1.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f };
	size_t size_triangle = sizeof(triangle);
	DrawableObject* triangle_object = new DrawableObject(triangle, size_triangle, false, GL_TRIANGLES, 0, "vertex_shader.txt", "fragment_shader.txt", camera1, lights1);
	triangle_object->addComponent(new Scale(glm::vec3(2.0f)));
	triangle_object->addComponent(new Rotate(45.0f, glm::vec3(1.0f, 0.0f, 0.0f), true));
	triangle_object->addComponent(new Scale(glm::vec3(0.5f)));
	triangle_object->setColor(glm::vec3(0.0f, 1.0f, 0.0f)); // Green
	scenes[0]->addObject(triangle_object);

	float x_axis[] = {
	-5.0f, 0.0f, 0.0f, // Zaèátek (vlevo)
	5.0f, 0.0f, 0.0f   // Konec (vpravo)
	};
	DrawableObject* x_axis_object = new DrawableObject(x_axis, sizeof(x_axis), false, GL_LINES, 0, "vertex_shader.txt", "fragment_shader.txt", camera1, lights1);
	x_axis_object->setColor(glm::vec3(0.0f, 0.0f, 1.0f)); // Modrá
	x_axis_object->addComponent(new Translate(glm::vec3(2.0f, 0.0f, 0.0f)));
	scenes[0]->addObject(x_axis_object);

	// Osa Y (žlutá)
	float y_axis[] = {
		0.0f, -5.0f, 0.0f, // Zaèátek (dolù)
		0.0f, 5.0f, 0.0f   // Konec (nahoru)
	};
	DrawableObject* y_axis_object = new DrawableObject(y_axis, sizeof(y_axis), false, GL_LINES, 0, "vertex_shader.txt", "fragment_shader.txt", camera1, lights1);
	y_axis_object->setColor(glm::vec3(1.0f, 1.0f, 0.0f)); // Žlutá
	y_axis_object->addComponent(new Translate(glm::vec3(0.0f, 2.0f, 0.0f)));
	scenes[0]->addObject(y_axis_object);

	// Osa Z (zelená)
	float z_axis[] = {
		0.0f, 0.0f, -5.0f, // Zaèátek (pøed kamerou)
		0.0f, 0.0f, 5.0f   // Konec (za kamerou)
	};
	DrawableObject* z_axis_object = new DrawableObject(z_axis, sizeof(z_axis), false, GL_LINES, 0, "vertex_shader.txt", "fragment_shader.txt", camera1, lights1);
	z_axis_object->setColor(glm::vec3(0.0f, 1.0f, 0.0f)); // Zelená
	z_axis_object->addComponent(new Translate(glm::vec3(0.0f, 0.0f, 2.0f)));
	scenes[0]->addObject(z_axis_object);
	scenes[0]->getCamera()->rotate(-90.0f, 0.0f);
}

void SceneManager::initScene2()
{
	Camera* camera2 = new Camera(glm::vec3(0.0f, 10.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, this->ratio);

	/*Light* light2 = new Light(
		glm::vec3(0.0f, 5.0f, 0.0f),
		glm::vec4(0.1, 0.1, 0.1, 1.0)
		
	);*/

	vector<Light*> lights2;
	lights2.push_back(new Light(glm::vec3(0.0f, 7.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 1.0f));
	lights2.push_back(new Light(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.01f));
	lights2.push_back(new Light(glm::vec3(-7.0f, 1.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.0001f));
	lights2.push_back(new Light(glm::vec3(7.0f, 1.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.0001f));
	//lights2.push_back(new Light(glm::vec3(0.0f, 1.0f, 7.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.0001f));
	scenes.push_back(new Scene(camera2));

	// Created global shaders and models
	ShaderProgram* shader = new ShaderProgram(GL_TRIANGLES, 0, 92814, camera2, lights2);
	shader->createShaderProgram("vertex_shader.txt", "lambert_fragment.txt");
	Model* model = new Model();
	model->createBuffer(tree, sizeof(tree), true);

	ShaderProgram* shader_b = new ShaderProgram(GL_TRIANGLES, 0, 8730, camera2, lights2);
	shader_b->createShaderProgram("vertex_shader.txt", "lambert_fragment.txt");
	Model* model_b = new Model();
	model_b->createBuffer(bushes, sizeof(bushes), true);

	

	size_t size_plain2 = sizeof(plain);
	DrawableObject* plain_object2 = new DrawableObject(plain, size_plain2, true, GL_TRIANGLES, 0, "vertex_shader.txt", "lambert_fragment.txt", camera2, lights2);
	/*Transformation* trans_plain2 = new Transformation();
	trans_plain2->scale(glm::vec3(10.0f));
	plain_object2->setTransformation(trans_plain2);*/
	plain_object2->addComponent(new Scale(glm::vec3(10.0f)));
	scenes[1]->addObject(plain_object2);
	for (int i = 0; i < 80; i++) {
		// Random tree transformations
		float scale_size_tree = getRandFloat(0.1f, 0.5f);
		float posX_tree = getRandFloat(-10.0f / scale_size_tree, 10.0f / scale_size_tree);
		float posZ_tree = getRandFloat(-10.0f / scale_size_tree, 10.0f / scale_size_tree);
		glm::vec3 randomPos_tree(posX_tree, 0.0f, posZ_tree);
		float random_rotation_tree = (rand() % 360);

		// Random tree
		//DrawableObject* tree_object = new DrawableObject(tree, size_tree, true, GL_TRIANGLES, 0, 92814, vertex_shader, fragment_shader, camera2);
		DrawableObject* tree_object = new DrawableObject(model, shader);


		tree_object->addComponent(new Scale(glm::vec3(scale_size_tree)));
		tree_object->addComponent(new Translate(randomPos_tree));
		tree_object->addComponent(new Rotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), true));
		scenes[1]->addObject(tree_object);

		for (int j = 0; j < 60; j++) {
			// Random bush transformations
			float scale_size_bush = getRandFloat(0.5f, 1.0f);
			float posX_bush = getRandFloat(-10.0f / scale_size_bush, 10.0f / scale_size_bush);
			float posZ_bush = getRandFloat(-10.0f / scale_size_bush, 10.0f / scale_size_bush);
			glm::vec3 randomPos_bush(posX_bush, 0.0f, posZ_bush);

			// Random bush
			//DrawableObject* bush_object = new DrawableObject(bushes, size_bush, true, GL_TRIANGLES, 0, 8730, vertex_shader, fragment_shader, camera2);;
			DrawableObject* bush_object = new DrawableObject(model_b, shader_b);


			bush_object->addComponent(new Scale(glm::vec3(scale_size_bush)));
			bush_object->addComponent(new Translate(randomPos_bush));
			scenes[1]->addObject(bush_object);

		}

	}
	scenes[1]->getCamera()->rotate(-90.0f, 0.0f);// Update camera after creating objects  

}

void SceneManager::initScene3()
{
	Camera* camera3 = new Camera(glm::vec3(0.0f, 2.0f, -4.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, ratio);

	/*Light* light3 = new Light(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
		
	);*/

	vector<Light*> lights3;
	lights3.push_back(new Light(glm::vec3(0.0f, 0.0f, 0.0f),glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.1f));
	//lights3.push_back(new Light(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.1f));

 
	scenes.push_back(new Scene(camera3));

	size_t size_sphere = sizeof(sphere);

	DrawableObject* sphere_object = new DrawableObject(sphere, size_sphere, true, GL_TRIANGLES, 0, "vertex_shader.txt", "phong_fragment.txt", camera3, lights3);
	sphere_object->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object->addComponent(new Translate(glm::vec3(-4.0f, 0.0f, 0.0f)));
	scenes[2]->addObject(sphere_object);

	DrawableObject* sphere_object2 = new DrawableObject(sphere, size_sphere, true, GL_TRIANGLES, 0, "vertex_shader.txt", "phong_fragment.txt", camera3, lights3);
	sphere_object2->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object2->addComponent(new Translate(glm::vec3(4.0f, 0.0f, 0.0f)));
	scenes[2]->addObject(sphere_object2);

	DrawableObject* sphere_object3 = new DrawableObject(sphere, size_sphere, true, GL_TRIANGLES, 0, "vertex_shader.txt", "phong_fragment.txt", camera3, lights3);
	sphere_object3->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object3->addComponent(new Translate(glm::vec3(0.0f, 4.0f, 0.0f)));
	scenes[2]->addObject(sphere_object3);

	DrawableObject* sphere_object4 = new DrawableObject(sphere, size_sphere, true, GL_TRIANGLES, 0, "vertex_shader.txt", "phong_fragment.txt", camera3, lights3);
	sphere_object4->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object4->addComponent(new Translate(glm::vec3(0.0f, -4.0f, 0.0f)));
	scenes[2]->addObject(sphere_object4);

	scenes[2]->getCamera()->rotate(90.0f, 0.0f);// Update camera after creating objects 
}

void SceneManager::initScene4()
{
	Camera* camera4 = new Camera(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, ratio);

	/*Light* light4 = new Light(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
		
	);*/
	vector<Light*> lights4;
	lights4.push_back(new Light(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.1f));
	lights4.push_back(new Light(glm::vec3(0.0f, -20.0f, 0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.1f));

	scenes.push_back(new Scene(camera4));

	size_t size_sphere2 = sizeof(sphere);
	size_t size_tree2 = sizeof(tree);

	DrawableObject* sphere_object5 = new DrawableObject(sphere, size_sphere2, true, GL_TRIANGLES, 0, "vertex_shader.txt", "fragment_shader.txt", camera4, lights4);
	sphere_object5->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object5->addComponent(new Translate(glm::vec3(-4.0f, 0.0f, 0.0f)));
	scenes[3]->addObject(sphere_object5);

	DrawableObject* sphere_object6 = new DrawableObject(sphere, size_sphere2, true, GL_TRIANGLES, 0, "vertex_shader.txt", "lambert_fragment.txt", camera4, lights4);
	sphere_object6->addComponent(new Scale(glm::vec3(1.0f)));
	sphere_object6->addComponent(new Translate(glm::vec3(4.0f, 0.0f, 0.0f)));
	scenes[3]->addObject(sphere_object6);

	DrawableObject* tree_object1 = new DrawableObject(tree, size_tree2, true, GL_TRIANGLES, 0, "vertex_shader.txt", "phong_fragment.txt", camera4, lights4);
	tree_object1->addComponent(new Scale(glm::vec3(1.0f)));
	tree_object1->addComponent(new Translate(glm::vec3(0.0f, 0.0f, 4.0f)));
	scenes[3]->addObject(tree_object1);

	DrawableObject* tree_object2 = new DrawableObject(tree, size_tree2, true, GL_TRIANGLES, 0, "vertex_shader.txt", "blinn_fragment.txt", camera4, lights4);
	tree_object2->addComponent(new Scale(glm::vec3(1.0f)));
	tree_object2->addComponent(new Translate(glm::vec3(0.0f, 0.0f, -4.0f)));
	scenes[3]->addObject(tree_object2);

	scenes[3]->getCamera()->rotate(-90.0f, 0.0f);// Update camera after creating objects 
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
