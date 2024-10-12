#include "Application.h"
#include "Models.h"
#include "Shaders.h"

void Application::error_callback(int error, const char* description) { fputs(description, stderr); }

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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
	glfwSetKeyCallback(this->window, key_callback);

	glfwSetCursorPosCallback(this->window, cursor_callback);

	glfwSetMouseButtonCallback(this->window, button_callback);

	glfwSetWindowFocusCallback(this->window, window_focus_callback);

	glfwSetWindowIconifyCallback(this->window, window_iconify_callback);

	glfwSetWindowSizeCallback(this->window, window_size_callback);
}

void Application::run()
{
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(this->window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (size_t i = 0; i < this->shaders.size(); i++) {
			//glUseProgram(this->shaders[i].getShaderProgram());
			this->shaders[i].useProgram();
			glBindVertexArray(models[i]);
			this->shaders[i].drawShaderArrays();
		}
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

void Application::createShaders()
{
	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"void main () {"
		"     gl_Position = vec4 (vp, 1.0);"
		"}";



	const char* fragment_shader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";
	/*
	Shaders s(GL_TRIANGLES, 0, 3);
	GLuint shaderProgram = s.createShaderProgram(vertex_shader, fragment_shader);
	s.checkLinking(shaderProgram);
	s.setShaderProgram(shaderProgram);

	this->shaders.push_back(s);

	const char* fragment_shader_square =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (0.0, 0.5, 0.0, 1.0);"
		"}";



	Shaders s_square(GL_TRIANGLES, 0, 6);
	GLuint shaderProgram_square = s_square.createShaderProgram(vertex_shader, fragment_shader);
	s_square.checkLinking(shaderProgram_square);
	s_square.setShaderProgram(shaderProgram_square);
	this->shaders.push_back(s_square); */

	const char* sphere_vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;\n" 
		"layout(location=1) in vec3 vn;\n" 
		"out vec3 fragNormal;\n" 
		"out vec3 fragPos;\n"
		"void main () {\n"
		"     gl_Position = vec4(vp, 1.0);\n"
		"     fragNormal = vn;\n"  
		"	  fragPos = vp;\n"
		"}";

	const char* fragment_shader_sphere =
		"#version 330\n"
		"in vec3 fragNormal;\n"
		"in vec3 fragPos;\n"
		"out vec4 frag_colour;\n"
		"void main () {\n"
		"     vec3 normalizedNormal = normalize(fragNormal);\n" 
		"     frag_colour = vec4(fragPos, 1.0);\n"  
		"}";




	Shaders s_sphere(GL_TRIANGLES, 0, 2880);
	GLuint shaderProgram_sphere = s_sphere.createShaderProgram(sphere_vertex_shader, fragment_shader_sphere);
	s_sphere.checkLinking(shaderProgram_sphere);
	s_sphere.setShaderProgram(shaderProgram_sphere);
	this->shaders.push_back(s_sphere);




}

void Application::createModels()
{
	/*
	float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
	};



	size_t size = sizeof(points);

	Models m;
	GLuint VAO = m.createBuffer(points, size);

	this->models.push_back(VAO);

	float squarePoints[] = {
		0.25f,  0.5f, 0.0f,
		0.30f,  0.5f, 0.0f,
		0.30f,  0.45f, 0.0f,

		0.25f,  0.5f, 0.0f,
		0.30f,  0.45f, 0.0f,
		0.25f,  0.45f, 0.0f
	};

	size_t squareSize = sizeof(squarePoints);

	Models squareModel;
	GLuint squareVAO = squareModel.createBuffer(squarePoints, squareSize);

	this->models.push_back(squareVAO);
	*/
	/*
	float a[] = {
	 -.5f, -.5f, .5f,  0, 0, 1,
	 -.5f, .5f, .5f,  0, 0, 1,
	   .5f, .5f, .5f,  0, 0, 1,
	   .5f, -.5f, .5f,  0, 0, 1 };

*/


	size_t size_sphere = sizeof(sphere);

	Models spehere_model;
	GLuint sphereVAO = spehere_model.createBuffer(sphere, size_sphere);

	this->models.push_back(sphereVAO);


}

