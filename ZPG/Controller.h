#pragma once

#include "ShaderProgram.h"
#include "Model.h"
#include "sphere.h"
#include "tree.h"
#include "bushes.h"
#include "plain.h"
#include "Scene.h"
#include "DrawableObject.h"
#include "Transformation.h"
#include "TransformationComponent.h"
#include "Scale.h"
#include "Rotate.h"
#include "Translate.h"
#include "SceneManager.h"
#include "Application.h"

#include <random>
#include <time.h>

using namespace std;


class Controller
{

private:
	GLFWwindow* window;
	SceneManager* sceneManager;
	Scene* activeScene;


public:
	Controller(GLFWwindow* window, SceneManager* sceneManager);
	void handleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	void handleCursorInput(GLFWwindow* window, double x, double y);
	void handleWindowResize(GLFWwindow* window, int width, int height);

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
};

