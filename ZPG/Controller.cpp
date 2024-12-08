#include "Controller.h"

Controller::Controller(GLFWwindow* window, SceneManager* sceneManager)
{
	this->window = window;
	this->sceneManager = sceneManager;
}

void Controller::handleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	activeScene = sceneManager->getActiveScene();
	vector<DrawableObject*> objects = activeScene->getObjects(); // Get all objects in the scene

	// Time management
	static float lastFrameTime = 0.0f; // Time of the last frame
	float currentFrameTime = (float)glfwGetTime(); // Time of the current frame
	float deltaTime = currentFrameTime - lastFrameTime; // Time between the last frame and the current frame

	const float maxDeltaTime = 0.01f; // Maximum time between frames
	if (deltaTime > maxDeltaTime)
		deltaTime = maxDeltaTime; // Limit the time between frames

	lastFrameTime = currentFrameTime; // Update the time of the last frame

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		sceneManager->switchScene(); // Switch the scene
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_W)
			activeScene->getCamera()->moveForward(deltaTime);
		if (key == GLFW_KEY_S)
			activeScene->getCamera()->moveBackward(deltaTime);
		if (key == GLFW_KEY_A)
			activeScene->getCamera()->moveLeft(deltaTime);
		if (key == GLFW_KEY_D)
			activeScene->getCamera()->moveRight(deltaTime);
	}

	if (action == GLFW_PRESS && key == GLFW_KEY_INSERT) {

		// Insert a new object
		Model* model = new Model();
		model->load("tree.obj");

		ShaderProgram* shader = new ShaderProgram(GL_TRIANGLES, 0, model->getNumIndices(), 1);
		shader->createShaderProgram("vertex_shader.glsl", "lambert_fragment.glsl");

		activeScene->getCamera()->addObserver(shader); // Add the shader as an observer of the camera
		
		for (Light* light : activeScene->getLights()) {
			light->addObserver(shader); // Add the shader as an observer of the light
		}

		Texture* texture = new Texture("tree.png");
		DrawableObject* object = new DrawableObject(model, shader, new Material(1.0f, 1.0f, 1.0f, 32.0f), texture); 
		object->addComponent(new Scale(glm::vec3(0.05f))); 
		
		activeScene->InsertObject(object); // Insert the object into the scene
	}

	if (action == GLFW_PRESS && key == GLFW_KEY_DELETE) {
		// Delete the selected object
		activeScene->deleteSelectedObject();
		
	}

	if (action == GLFW_PRESS && key == GLFW_KEY_P && activeScene->getSkyBox()) {
		
		if (!activeScene->getSkyBox()->getFollowCamera()) {
			activeScene->getCamera()->addObserver(activeScene->getSkyBox()); // Add the skybox as an observer of the camera	
			activeScene->getSkyBox()->getTransformation()->setPosition(activeScene->getCamera()->getPosition()); // Set the position of the skybox to the camera position
		}
		else {
			activeScene->getCamera()->removeObserver(activeScene->getSkyBox()); // Remove the skybox as an observer of the camera
		}
		activeScene->getSkyBox()->setFollowCamera(!activeScene->getSkyBox()->getFollowCamera());
	}
}

void Controller::handleCursorInput(GLFWwindow* window, double x, double y)
{
	activeScene = sceneManager->getActiveScene();
	static double lastX, lastY;
	static bool firstMouse = true; // Flag for the first mouse movement
	int rightButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT); // Check if the right mouse button is pressed
	if (rightButton == GLFW_PRESS) {
		
		// If it is the first mouse movement, set the last cursor position to the current cursor position
		if (firstMouse) { 
			lastX = x;
			lastY = y;
			firstMouse = false;
		}

		// Calculate the offset between the last cursor position and the current cursor position
		double offsetX = x - lastX; 
		double offsetY = lastY - y; 

		// Set the last cursor position to the current cursor position
		lastX = x; 
		lastY = y;

		// Sensitivity of the camera rotation
		float sensitivity = 0.1f;

		offsetX *= sensitivity;
		offsetY *= sensitivity;

		activeScene->getCamera()->rotate((float)offsetX, (float)offsetY); // Rotate the camera
	}
	else {
		firstMouse = true; // Set the first mouse movement flag to true
	}
}

// Handles resize of the window and updates the projection matrix of the camera to match the new aspect ratio and keep objects from stretching
void Controller::handleWindowResize(GLFWwindow* window, int width, int height)
{
	activeScene = sceneManager->getActiveScene();

	activeScene->getCamera()->updateProjectionMatrix(width / (float)height); // Update the projection matrix of the camera

	activeScene->getCamera()->setWidth(width); 
	activeScene->getCamera()->setHeight(height);

	glViewport(0, 0, width, height); // Set the viewport
}

void Controller::handleButtonInput(GLFWwindow* window, int button, int action, int mode)
{
	activeScene = sceneManager->getActiveScene();


	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) { 

		GLbyte color[4]; // Color of the pixel
		GLfloat depth; // Depth of the pixel
		GLuint index; // Stencil index of the pixel

		// Get the cursor position
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		GLint x = (GLint)xpos;
		GLint y = (GLint)ypos;

		int newy = activeScene->getCamera()->getHeight() - y; // Invert the y coordinate

		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color); // Read the color of the pixel
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth); // Read the depth of the pixel
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index); // Read the stencil index of the pixel

		glm::vec3 screenX = glm::vec3(x, newy, depth); // Screen coordinates
		glm::mat4 view = activeScene->getCamera()->getViewMatrix();	 
		glm::mat4 projection = activeScene->getCamera()->getProjectionMatrix();
		glm::vec4 viewPort = glm::vec4(0, 0, activeScene->getCamera()->getWidth(), activeScene->getCamera()->getHeight());

		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort); // Unproject the screen coordinates to world coordinates

		activeScene->setInsertPosition(pos); // Set the position where the object will be inserted

		activeScene->setSelectedObject(index); // Set the selected object

		printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

		printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
	}
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
	Controller* controller = (Controller*)glfwGetWindowUserPointer(window);
	controller->handleButtonInput(window, button, action, mode);
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}