#ifndef PROJECTION_CUBE_H
#define PROJECTION_CUBE_H

#include "../create_window/CreateWindow.hpp"
#include "../Shader.h"
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <iostream>

#include "../camera/Camera.h"

using namespace std;

//void mouseCallback(GLFWwindow*, double xpos, double ypos);

class Projection {
	const float cameraRadius = 10.0f;
	const char* glslVersion = "#version 130";
	float vertices[36 * 6] = {
		-2.0001f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0001f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0001f,  2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0001f,  2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0001f,  2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0001f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,

		-2.0002f, -2.0f, 2.0f,  0.0f, 1.0f, 0.0f,
		2.0002f, -2.0f, 2.0f,  0.0f, 1.0f, 0.0f,
		2.0002f,  2.0f, 2.0f,  0.0f, 1.0f, 0.0f,
		2.0002f,  2.0f, 2.0f,  0.0f, 1.0f, 0.0f,
		-2.0002f,  2.0f, 2.0f,  0.0f, 1.0f, 0.0f,
		-2.0002f, -2.0f, 2.0f,  0.0f, 1.0f, 0.0f,

		-2.0003f, 2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		-2.0003f, 2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		-2.0003f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		-2.0003f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		-2.0003f, -2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		-2.0003f, 2.0f, 2.0f,  0.0f, 0.0f, 1.0f,

		2.0004f, 2.0f, 2.0f,  0.0f, 1.0f, 1.0f,
		2.0004f, 2.0f, -2.0f,  0.0f, 1.0f, 1.0f,
		2.0004f, -2.0f, -2.0f,  0.0f, 1.0f, 1.0f,
		2.0004f, -2.0f, -2.0f,  0.0f, 1.0f, 1.0f,
		2.0004f, -2.0f, 2.0f,  0.0f, 1.0f, 1.0f,
		2.0004f, 2.0f, 2.0f,  0.0f, 1.0f, 1.0f,

		-2.0005f, -2.0f, -2.0f,  1.0f, 0.0f, 1.0f,
		2.0005f, -2.0f, -2.0f,  1.0f, 0.0f, 1.0f,
		2.0005f, -2.0f, 2.0f,  1.0f, 0.0f, 1.0f,
		2.0005f, -2.0f, 2.0f,  1.0f, 0.0f, 1.0f,
		-2.0005f, -2.0f, 2.0f,  1.0f, 0.0f, 1.0f,
		-2.0005f, -2.0f, -2.0f,  1.0f, 0.0f, 1.0f,

		-2.0006f, 2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		2.0006f, 2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		2.0006f, 2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		2.0006f,  2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		-2.0006f, 2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		-2.0006f, 2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
	};
	// params of ortho projection
	float widthStart = -20.0f;
	float widthEnd = 20.0f;
	float heightStart = -20.0f;
	float heightEnd = 20.0f;
	float nearOrtho = -20.0f;
	float farOrtho = 20.0f;
	// params of perspective projection
	float fov = 90.0f;
	float viewWidth = 800.0f;
	float viewHeight = 800.0f;
	float nearPer = 1.0f;
	float farPer = 30.0f;
	// auto camera params
	double currentTime = 0.0;
	float autoCamX = 0.0f;
	float autoCamZ = 0.0f;
	void updateCamera();
public:
	void drawCube();
	// my camera
	static Camera myCamera;
	static float xPos;
	static float yPos;
};

#endif
