#include "Controller.h"

Controller::Controller(GLFWwindow* window, SceneManager* sceneManager)
{
	this->window = window;
	this->sceneManager = sceneManager;
}

void Controller::handleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	activeScene = sceneManager->getActiveScene();
	vector<DrawableObject*> objects = activeScene->getObjects();

	static float lastFrameTime = 0.0f;
	float currentFrameTime = glfwGetTime();
	float deltaTime = currentFrameTime - lastFrameTime;

	const float maxDeltaTime = 0.01f;
	if (deltaTime > maxDeltaTime) deltaTime = maxDeltaTime;
	lastFrameTime = currentFrameTime;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		printf("Switching scene\n");
		sceneManager->switchScene();
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		float cameraSpeed = (mods == GLFW_MOD_SHIFT) ? 5.0f : 2.5f; // Faster when Shift is pressed

		if (key == GLFW_KEY_W) activeScene->getCamera()->moveForward(deltaTime);
		if (key == GLFW_KEY_S) activeScene->getCamera()->moveBackward(deltaTime);
		if (key == GLFW_KEY_A) activeScene->getCamera()->moveLeft(deltaTime);
		if (key == GLFW_KEY_D) activeScene->getCamera()->moveRight(deltaTime);
	}
}

void Controller::handleCursorInput(GLFWwindow* window, double x, double y)
{
	activeScene = sceneManager->getActiveScene();
	static double lastX = 400, lastY = 300;
	static bool firstMouse = true;
	int rightButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
	if (rightButton == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (firstMouse) {
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

		activeScene->getCamera()->rotate(offsetX, offsetY);
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstMouse = true;
	}
}

void Controller::handleWindowResize(GLFWwindow* window, int width, int height)
{
	activeScene = sceneManager->getActiveScene();
	activeScene->getCamera()->updateProjectionMatrix(width / (float)height);
	glViewport(0, 0, width, height);
}

void Controller::error_callback(int error, const char* description) { fputs(description, stderr); }

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Controller* controller = (Controller*)glfwGetWindowUserPointer(window);
	controller->handleKeyInput(window, key, scancode, action, mods);
}

void Controller::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Controller::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Controller::window_size_callback(GLFWwindow* window, int width, int height) {
	Controller* controller = (Controller*)glfwGetWindowUserPointer(window);
	controller->handleWindowResize(window, width, height);
}

void Controller::cursor_callback(GLFWwindow* window, double x, double y) {
	Controller* controller = (Controller*)glfwGetWindowUserPointer(window);
	controller->handleCursorInput(window, x, y);
}

void Controller::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);

}