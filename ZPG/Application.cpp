#include "Application.h"

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

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	this->sceneManager = new SceneManager(ratio);
	controller = new Controller(this->window, this->sceneManager);
	// Sets the key callback
	glfwSetWindowUserPointer(this->window, this); // Adding pointer to Application

	glfwSetKeyCallback(this->window, controller->key_callback);

	glfwSetCursorPosCallback(this->window, controller->cursor_callback);

	glfwSetMouseButtonCallback(this->window, controller->button_callback);

	glfwSetWindowFocusCallback(this->window, controller->window_focus_callback);

	glfwSetWindowIconifyCallback(this->window, controller->window_iconify_callback);

	glfwSetWindowSizeCallback(this->window, controller->window_size_callback);

	
	this->sceneManager->initScene1();
	this->sceneManager->initScene2();
	this->sceneManager->initScene3();
	this->sceneManager->initScene4();
	this->sceneManager->initScene5();	

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