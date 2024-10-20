#include "Application.h"



void Application::error_callback(int error, const char* description) { fputs(description, stderr); }

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	
	Application* app = (Application*)glfwGetWindowUserPointer(window);
	Scene& scene = app->scenes[app->active_scene];
	vector<DrawableObject>& objects = scene.getObjects();

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		printf("Switching scene\n");
		app->switchScene();
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		/*for (auto& object : objects) {
			Transformation currentTransformation = object.getTransformation(); 


			if (key == GLFW_KEY_W) {
				currentTransformation.translate(glm::vec3(0.0f, 0.1f, 0.0f));
				object.setTransformation(currentTransformation); 
			}
			else if (key == GLFW_KEY_S) {
				currentTransformation.translate(glm::vec3(0.0f, -0.1f, 0.0f));
				object.setTransformation(currentTransformation);
			}

			if (key == GLFW_KEY_A) {
				currentTransformation.rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
				object.setTransformation(currentTransformation);
			}
			else if (key == GLFW_KEY_D) {
				currentTransformation.rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
				object.setTransformation(currentTransformation);
			}

			if (key == GLFW_KEY_R) {
				currentTransformation.scale(glm::vec3(1.01f, 1.01f, 1.01f));
				object.setTransformation(currentTransformation);
			}
			else if (key == GLFW_KEY_F) {
				currentTransformation.scale(glm::vec3(0.99f, 0.99f, 0.99f));
				object.setTransformation(currentTransformation);
			}
		}*/

		float cameraSpeed = 2.5f;  // Default speed
		if (mods == GLFW_MOD_SHIFT) {
			cameraSpeed = 5.0f;  // Faster when Shift is pressed
		}

		// Ovládání pohybu kamery pomocí kláves
		if (key == GLFW_KEY_W) {
			printf("fasgbjfhafkjasfjkhafukhjaf");
			scene.getCamera()->moveForward(cameraSpeed);
			
		}
		if (key == GLFW_KEY_S) {
			scene.getCamera()->moveBackward(cameraSpeed);
		}
		if (key == GLFW_KEY_A) {
			scene.getCamera()->moveLeft(cameraSpeed);
		}
		if (key == GLFW_KEY_D) {
			scene.getCamera()->moveRight(cameraSpeed);
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

void Application::cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
	
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

	// Sets the key callback
	glfwSetWindowUserPointer(this->window, this); // Adding pointer to Application

	glfwSetKeyCallback(this->window, key_callback);

	glfwSetCursorPosCallback(this->window, cursor_callback);

	glfwSetMouseButtonCallback(this->window, button_callback);

	glfwSetWindowFocusCallback(this->window, window_focus_callback);

	glfwSetWindowIconifyCallback(this->window, window_iconify_callback);

	glfwSetWindowSizeCallback(this->window, window_size_callback);

	Camera2* camera = new Camera2(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, ratio);
	Camera2* camera2 = new Camera2(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, ratio);

	this->active_scene = 0;
	scenes.push_back(Scene(camera));
	scenes.push_back(Scene(camera2));

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
		//"     fragPos = vp;\n"
		"}\n";

	const char* vertex_shader_2D =
		"#version 330\n"
		"layout(location=0) in vec3 vp;\n"
		"layout(location=1) in vec3 vn;\n"
		"out vec3 fragNormal;\n"
		//"out vec3 fragPos;\n"
		"uniform mat4 modelMatrix;\n"
		"void main () {\n"
		"     gl_Position = modelMatrix * vec4(vp, 1.0);\n"
		"     fragNormal = vn;\n"
		//"     fragPos = vp;\n"
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
	//Scene 1 
	// 
	// Trees

	ShaderProgram s_tree_2D(GL_TRIANGLES, 0, 92814);  // Pøedpokládám, že GL_TRIANGLES a další parametry jsou správnì
	s_tree_2D.createShaderProgram(vertex_shader_2D, fragment_shader);  // Používá se nový vertex shader a fragment shader pro 2D
	this->shaders.push_back(s_tree_2D);


	/*ShaderProgram s_tree(GL_TRIANGLES, 0, 92814);
	s_tree.createShaderProgram(vertex_shader, fragment_shader);
	this->shaders.push_back(s_tree);*/

	size_t size_tree_2D = sizeof(tree);
	Models tree_model_2D;
	tree_model_2D.createBuffer(tree, size_tree_2D, false);
	this->models.push_back(tree_model_2D);

	DrawableObject tree_object_2D(tree_model_2D, s_tree_2D);

	Transformation trans;
	trans.scale(glm::vec3(0.1f));

	tree_object_2D.setTransformation(trans);
	scenes[0].addObject(tree_object_2D);

	// Bushes
	ShaderProgram s_bush_2D(GL_TRIANGLES, 0, 8730);
	s_bush_2D.createShaderProgram(vertex_shader_2D, fragment_shader2);
	
	size_t size_bush = sizeof(bushes);
	Models bush_model;
	bush_model.createBuffer(bushes, size_bush, false);
	this->models.push_back(bush_model);

	DrawableObject bush_object(bush_model, s_bush_2D);

	Transformation trans2;
	trans2.scale(glm::vec3(0.5));
	trans2.translate(glm::vec3(0.5f, 0.2f, 0.0f));
	bush_object.setTransformation(trans2);
	scenes[0].addObject(bush_object);
	
	//Scene 2 
	// 

	ShaderProgram s_tree(GL_TRIANGLES, 0, 92814);
	s_tree.createShaderProgram(vertex_shader, fragment_shader);
	this->shaders.push_back(s_tree);

	size_t size_tree_3D = sizeof(tree);
	Models tree_model_3D;
	tree_model_3D.createBuffer(tree, size_tree_3D, true);
	this->models.push_back(tree_model_3D);


	// Bushes
	ShaderProgram s_bush_scene2(GL_TRIANGLES, 0, 8730);
	s_bush_scene2.createShaderProgram(vertex_shader, fragment_shader);
	this->shaders.push_back(s_bush_scene2);

	size_t size_bush_3D = sizeof(bushes);
	Models bush_model_3D;
	bush_model_3D.createBuffer(bushes, size_bush_3D, true);
	this->models.push_back(bush_model_3D);



	for (int i = 0; i < 10; ++i) {


		// Random tree transformations
		float scale_size_tree = 0.05f + (rand() % 6) / 100.0f;
		float posX_tree = -12.5f + rand() % 21; 
		float posY_tree = 0.5f + (rand() % 5) / 10.0f;
		glm::vec3 randomPos_tree(posX_tree, posY_tree, 0.5f + (rand() % 5) / 10.0f);
		float random_rotation_tree = (rand() % 31) - 15;

		// Random tree
		DrawableObject tree_object_3D(tree_model_3D, s_tree);
		Transformation tree_trans;

		tree_trans.scale(glm::vec3(scale_size_tree));
		tree_trans.translate(glm::vec3(randomPos_tree));
		tree_trans.rotate(random_rotation_tree, glm::vec3(0.0f, 1.0f, 0.0f));

		tree_object_3D.setTransformation(tree_trans);
		scenes[1].addObject(tree_object_3D);

		// Random bush transformations
		float scale_size_bush = 0.05f + (rand() % 6) / 100.0f;
		float posX_bush = -12.5f + rand() % 21;
		float posY_bush = -0.5f - (rand() % 3) / 10.0f;
		glm::vec3 randomPos_bush(posX_bush, posY_bush, 0.5f + (rand() % 5) / 10.0f);

		// Random bush
		DrawableObject bush_object(bush_model_3D, s_bush_scene2);
		Transformation bush_trans;

		bush_trans.scale(glm::vec3(scale_size_bush));
		bush_trans.translate(glm::vec3(randomPos_bush));
		 
		bush_object.setTransformation(bush_trans);
		scenes[1].addObject(bush_object);
	}

}

void Application::switchScene() {
	this->active_scene = (this->active_scene + 1) % scenes.size();
}


void Application::run()
{
	glm::mat4 C = glm::mat4(1.0f);

	vector<glm::mat4> v;

	
	C = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
	C = glm::translate(C, glm::vec3(-5.0f, 0.0f, 0.0f));
	


	v.push_back(C);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(this->window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//for (size_t i = 0; i < this->shaders.size(); i++) {
		//	//glUseProgram(this->shaders[i].getShaderProgram());
		//	for (int j = 0; j < this->treeTransforms.size(); j++) {
		//		this->shaders[i].useProgram(this->treeTransforms[j]);
		//		this->models[i].bindVAO();
		//		this->shaders[i].drawShaderArrays();
		//	}
		//	
		//}
		scenes[this->active_scene].render();
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
/*
void Application::createShaders()
{

	const char* sphere_vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;\n" 
		"layout(location=1) in vec3 vn;\n" 
		"out vec3 fragNormal;\n" 
		"out vec3 fragPos;\n"
		"void main () {\n"
		"     gl_Position =vec4(vp, 1.0);\n"
		"     fragNormal = vn;\n"  
		"	  fragPos = vp;\n"
		"}";

	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;\n"
		"layout(location=1) in vec3 vn;\n"
		"out vec3 fragNormal;\n"
		"out vec3 fragPos;\n"
		"uniform mat4 modelMatrix;\n"
		"void main () {\n"
		"     gl_Position = modelMatrix * vec4(vp, 1.0);\n"
		"     fragNormal = vn;\n"
		"	  fragPos = vp;\n"
		"}";

	const char* fragment_shader =
		"#version 330\n"
		"in vec3 fragNormal;\n"
		"in vec3 fragPos;\n"
		"out vec4 frag_colour;\n"
		"void main () {\n"
		"     vec3 normalizedNormal = normalize(fragNormal);\n" 
		"     frag_colour = vec4(fragPos, 1.0);\n"  
		"}";
	const char* fragment_shader2 =
		"#version 330\n"
		"in vec3 fragNormal;\n"
		"in vec3 fragPos;\n"
		"out vec4 frag_colour;\n"
		"void main () {\n"
		"     frag_colour = vec4(1.0, 1.0, 1.0, 1.0);  // Nastavení èistì bílé barvy\n"
		"}\n";


	ShaderProgram s_tree(GL_TRIANGLES, 0, 92814);
	GLuint shaderProgram_tree = s_tree.createShaderProgram(vertex_shader, fragment_shader);
	s_tree.setShaderProgram(shaderProgram_tree);
	this->shaders.push_back(s_tree);

	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		glm::mat4 M = glm::mat4(1.0f);
		float scale_size = 0.05f + (rand() % 6) / 100.0f;
		M = glm::scale(M, glm::vec3(scale_size));
		float posX = -5.0f + rand() % 11;
		float posY = -8.0f + rand() % 12;
		glm::vec3 randomPos(posX, posY, 0.0f);
		M = glm::translate(M, randomPos);
		this->treeTransforms.push_back(M);
	}


}

void Application::createModels()
{
	size_t size_tree = sizeof(tree);
	Models tree_model;
	tree_model.createBuffer(tree, size_tree);
	this->models.push_back(tree_model);
}
*/
