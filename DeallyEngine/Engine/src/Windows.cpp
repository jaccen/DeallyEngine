#include <GL/glew.h>
#include <iostream>
#include "Windows.h"

Window::Window(const char *name, int width, int height)
{
	_name = name;
	_width = width;
	_height = height;

	if (!init())
	{
		glfwTerminate();
	}
}

Window::~Window()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

bool Window::init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW and its components" << std::endl;
		return false;
	}

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	_window = glfwCreateWindow(_width, _height, _name, nullptr, nullptr);

	if (!_window)
	{
		std::cout << "Failed to create GLFW Window Context" << std::endl;
		glfwDestroyWindow(_window);
		return false;
	}

	glfwMakeContextCurrent(_window);
	glfwSetWindowSizeCallback(_window, resizeHandler);
	glfwSetKeyCallback(_window, key_callback);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "Initialization of GLEW failed with " << glewGetErrorString(err) << std::endl;
	}

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(_window, &width, &height);
	glViewport(0, 0, width, height);
	//
   return true;
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		//m_isfbo = !m_isfbo;
	}
}
int x = 100;
void Window::update(float dt)
{
	bool show_another_window = true;
	glfwPollEvents();
	
	glfwSwapBuffers(_window);
}

void Window::render()
{
}

void Window::clear()
{
	glClearColor(0.0, 0.0, 0.6, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::resizeHandler(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool Window::closed()
{
	return glfwWindowShouldClose(_window) == GLFW_TRUE;
}

void Window::close()
{
	glfwSetWindowShouldClose(_window, true);

}

void Window::setfbo(bool isfbo)
{
	m_isfbo = !isfbo;
}

