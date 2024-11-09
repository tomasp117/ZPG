#include "Application.h"



void Application::error_callback(int error, const char* description) { fputs(description, stderr); }

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	
	Application* app = (Application*)glfwGetWindowUserPointer(window);
	Scene* scene = app->sceneManager->getActiveScene();
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
		app->sceneManager->switchScene();
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
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

	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Application::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Application::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	/*Application* app = (Application*)glfwGetWindowUserPointer(window);
	for (auto scene : app->scenes) {
		scene->getCamera()->UpdateProjectionMatrix();
	}*/
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) { 
	Application* app = (Application*)glfwGetWindowUserPointer(window);
	Scene* scene = app->sceneManager->getActiveScene();//app->scenes[app->active_scene];

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
	//printf("cursor_callback \n"); 
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

	this->sceneManager = new SceneManager(ratio);
	this->sceneManager->initScene1();
	this->sceneManager->initScene2();
	this->sceneManager->initScene3();
	this->sceneManager->initScene4();

}

void Application::run()
{
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(this->window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sceneManager->getActiveScene()->render();
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