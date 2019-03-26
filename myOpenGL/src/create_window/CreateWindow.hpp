#ifndef CREATE_WINDOW_HPP
#define CREATE_WINDOW_HPP

#include "../headers.h";

namespace CreateWindow {
	void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	void processInput(GLFWwindow* window);

	GLFWwindow* createWindow();
}

#endif
