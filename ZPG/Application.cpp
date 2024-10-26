#include "Application.h"



void Application::error_callback(int error, const char* description) { fputs(description, stderr); }

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	
	Application* app = (Application*)glfwGetWindowUserPointer(window);
	Scene* scene = app->scenes[app->active_scene];
	vector<DrawableObject*> objects = scene->getObjects();

	static float lastFrameTime = 0.0f;
	float currentFrameTime = glfwGetTime();
	float deltaTime = currentFrameTime - lastFrameTime;

	const float maxDeltaTime = 0.01f;

	if (deltaTime > maxDeltaTime) {
		deltaTime = maxDeltaTime;
	}
	lastFrameTime = currentFrameTime;

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		printf("Switching scene\n");
		app->switchScene();
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		/*for (auto object : objects) {
			Transformation* currentTransformation = object->getTransformation(); 


			if (key == GLFW_KEY_W) {
				currentTransformation->translate(glm::vec3(0.0f, 0.1f, 0.0f));
				object->setTransformation(currentTransformation); 
			}
			else if (key == GLFW_KEY_S) {
				currentTransformation->translate(glm::vec3(0.0f, -0.1f, 0.0f));
				object->setTransformation(currentTransformation);
			}

			if (key == GLFW_KEY_A) {
				currentTransformation->rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
				object->setTransformation(currentTransformation);
			}
			else if (key == GLFW_KEY_D) {
				currentTransformation->rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
				object->setTransformation(currentTransformation);
			}

			if (key == GLFW_KEY_R) {
				currentTransformation->scale(glm::vec3(1.01f, 1.01f, 1.01f));
				object->setTransformation(currentTransformation);
			}
			else if (key == GLFW_KEY_F) {
				currentTransformation->scale(glm::vec3(0.99f, 0.99f, 0.99f));
				object->setTransformation(currentTransformation);
			}
		}*/

		float cameraSpeed = 2.5f;  // Default speed
		if (mods == GLFW_MOD_SHIFT) {
			cameraSpeed = 5.0f;  // Faster when Shift is pressed
		}

		// Ovládání pohybu kamery pomocí kláves
		if (key == GLFW_KEY_W) {
			
			scene->getCamera()->moveForward(deltaTime);
		}
		if (key == GLFW_KEY_S) {
			scene->getCamera()->moveBackward(deltaTime);
		}
		if (key == GLFW_KEY_A) {
			scene->getCamera()->moveLeft(deltaTime);
		}
		if (key == GLFW_KEY_D) {
			scene->getCamera()->moveRight(deltaTime);
		}
	}

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Application::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Application::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) { 
	Application* app = (Application*)glfwGetWindowUserPointer(window);
	Scene* scene = app->scenes[app->active_scene];
	vector<DrawableObject*> objects = scene->getObjects();
	static double lastX = 400, lastY = 300;
	static bool firstMouse = true;

	if (firstMouse)
	{
		lastX = x;
		lastY = y;

		firstMouse = false;
	}
	double offsetX = x - lastX;
	double offsetY = lastY - y;

	lastX = x;
	lastY = y;

	float sensitivity = 0.1f;
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	scene->getCamera()->rotate(offsetX, offsetY);
	printf("cursor_callback \n"); 
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
	
}

float getRandomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void Application::initialization()
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Sets the key callback
	glfwSetWindowUserPointer(this->window, this); // Adding pointer to Application

	glfwSetKeyCallback(this->window, key_callback);

	glfwSetCursorPosCallback(this->window, cursor_callback);

	glfwSetMouseButtonCallback(this->window, button_callback);

	glfwSetWindowFocusCallback(this->window, window_focus_callback);

	glfwSetWindowIconifyCallback(this->window, window_iconify_callback);

	glfwSetWindowSizeCallback(this->window, window_size_callback);

	Camera* camera = new Camera(glm::vec3(0.0f, 0.1f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, ratio);
	Camera* camera2 = new Camera(glm::vec3(0.0f, 5.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, ratio);
	
	this->active_scene = 0;
	scenes.push_back(new Scene(camera));
	scenes.push_back(new Scene(camera2));

	// Vertex shader
	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;\n"
		"layout(location=1) in vec3 vn;\n"
		"out vec3 fragNormal;\n"
		//"out vec3 fragPos;\n"
		"uniform mat4 modelMatrix;\n"
		"uniform mat4 viewMatrix;\n"
		"uniform mat4 projectionMatrix;\n"
		"void main () {\n"
		"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);\n"
		"     fragNormal = vn;\n"
		"}\n";

	const char* vertex_shader2 =
		"#version 330\n"
		"layout(location=0) in vec3 vp;\n"
		"layout(location=1) in vec3 vn;\n"
		"out vec3 fragNormal;\n"
		//"out vec3 fragPos;\n"
		"uniform mat4 modelMatrix;\n"

		"void main () {\n"
		"     gl_Position = modelMatrix * vec4(vp, 1.0);\n"
		"     fragNormal = vn;\n"
		"}\n";

	// Fragment shader Normal
	const char* fragment_shader =
		"#version 330\n"
		"in vec3 fragNormal;\n"
		//"in vec3 fragPos;\n"
		"out vec4 frag_colour;\n"
		"void main () {\n"
		"     frag_colour = vec4(fragNormal, 1.0);\n"  // Barevné nastavení podle pozice
		"}\n";

	// Fragment shader2
	const char* fragment_shader2 =
		"#version 330\n"
		"out vec4 frag_colour;\n"
		"void main () {\n"
		"     frag_colour = vec4(1.0, 1.0, 1.0, 1.0);  // Nastavení èistì bílé barvy\n"
		"}\n";


	srand(time(NULL));
	// Created global shaders and models
	ShaderProgram* shader = new ShaderProgram(GL_TRIANGLES, 0, 92814, camera2);
	shader->createShaderProgram(vertex_shader, fragment_shader);
	Model* model = new Model();
	model->createBuffer(tree, sizeof(tree), true);

	ShaderProgram* shader_b = new ShaderProgram(GL_TRIANGLES, 0, 8730, camera2);
	shader_b->createShaderProgram(vertex_shader, fragment_shader);
	Model* model_b = new Model();
	model_b->createBuffer(bushes, sizeof(bushes), true);


	// Scene 1
	size_t size_plain = sizeof(plain);
	DrawableObject* plain_object = new DrawableObject(plain, size_plain, true, GL_TRIANGLES, 0, 6, vertex_shader, fragment_shader, camera);
	
	Transformation* trans_plain = new Transformation();
	trans_plain->scale(glm::vec3(10.0f));
	plain_object->setTransformation(trans_plain);
	scenes[0]->addObject(plain_object);

	size_t size_tree = sizeof(tree);
	size_t size_bush = sizeof(bushes);
	DrawableObject* tree_object = new DrawableObject(tree, size_tree, true, GL_TRIANGLES, 0, 92814, vertex_shader, fragment_shader, camera);
	Transformation* trans_tree = new Transformation();
	trans_tree->scale(glm::vec3(0.1f));

	tree_object->setTransformation(trans_tree);
	scenes[0]->addObject(tree_object);

	DrawableObject* bush_object = new DrawableObject(bushes, size_bush, true, GL_TRIANGLES, 0, 8730, vertex_shader, fragment_shader, camera);
	Transformation* trans_bush = new Transformation();
	trans_bush->scale(glm::vec3(0.5));
	trans_bush->translate(glm::vec3(0.5f, 0.2f, 0.0f));
	bush_object->setTransformation(trans_bush);
	scenes[0]->addObject(bush_object);
	scenes[0]->getCamera()->rotate(-90.0f, 0.0f); // Update camera after creating objects


	// Scene 2
	DrawableObject* plain_object2 = new DrawableObject(plain, size_plain, true, GL_TRIANGLES, 0, 6, vertex_shader, fragment_shader, camera2);
	Transformation* trans_plain2 = new Transformation();
	trans_plain2->scale(glm::vec3(10.0f));
	plain_object2->setTransformation(trans_plain2);
	scenes[1]->addObject(plain_object2);
	for (int i = 0; i < 80; ++i) {
		// Random tree transformations
		float scale_size_tree = getRandomFloat(0.1f, 0.5f);
		float posX_tree = getRandomFloat(-10.0f / scale_size_tree, 10.0f / scale_size_tree);
		float posZ_tree = getRandomFloat(-10.0f / scale_size_tree, 10.0f / scale_size_tree);
		glm::vec3 randomPos_tree(posX_tree, 0.0f, posZ_tree);
		float random_rotation_tree = (rand() % 360);

		// Random tree
		//DrawableObject* tree_object = new DrawableObject(tree, size_tree, true, GL_TRIANGLES, 0, 92814, vertex_shader, fragment_shader, camera2);
		DrawableObject* tree_object = new DrawableObject(model, shader);
		Transformation* tree_trans = new Transformation();

		tree_trans->scale(glm::vec3(scale_size_tree));
		tree_trans->translate(randomPos_tree);
		
		//tree_trans->rotate(random_rotation_tree, glm::vec3(1.0f, 0.0f, 0.0f));
		
		

		tree_object->setTransformation(tree_trans);
		scenes[1]->addObject(tree_object);

		for (int j = 0; j < 60; ++j) {
			// Random bush transformations
			float scale_size_bush = getRandomFloat(0.5f, 1.0f);
			float posX_bush = getRandomFloat(-10.0f / scale_size_bush, 10.0f / scale_size_bush);
			float posZ_bush = getRandomFloat(-10.0f / scale_size_bush, 10.0f / scale_size_bush);
			glm::vec3 randomPos_bush(posX_bush, 0.0f, posZ_bush);

			// Random bush
			//DrawableObject* bush_object = new DrawableObject(bushes, size_bush, true, GL_TRIANGLES, 0, 8730, vertex_shader, fragment_shader, camera2);;
			DrawableObject* bush_object = new DrawableObject(model_b, shader_b);
			Transformation* bush_trans = new Transformation();

			bush_trans->scale(glm::vec3(scale_size_bush));
			bush_trans->translate(randomPos_bush);



			bush_object->setTransformation(bush_trans);
			scenes[1]->addObject(bush_object);
			
		}
		
	}
	scenes[1]->getCamera()->rotate(-90.0f, 0.0f);// Update camera after creating objects  

	

}

void Application::switchScene() {
	this->active_scene = (this->active_scene + 1) % scenes.size();
}


void Application::run()
{
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(this->window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scenes[this->active_scene]->render();
		//glDrawArrays(GL_TRIANGLES, 0, 6); // two triangles
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->window);
	}
	
	glfwDestroyWindow(this->window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}