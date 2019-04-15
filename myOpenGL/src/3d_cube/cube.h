#ifndef CUBE_H
#define CUBE_H

#include "../create_window/CreateWindow.hpp"
#include "../Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

class Cube {
#define TRANS_STEP 0.3f
#define ROTATE_STEP 10.0f
#define SCALE_STEP 0.1f
private:
	const char* glslVersion = "#version 130";
	double updateTime = 0.0f;
	float scale = 1.0f;
	float scaleDir = 1.0f;
	float movementx = 0.0f;
	float moveDir = 1.0f;
	float rotation = 0.0f;
	glm::vec3 cubePositions = glm::vec3(0.0f, 0.0f, 0.0f);
	void updateParams();
	float vertices[36 * 6] = {
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f,  2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		2.0f,  2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f,  2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,

		-2.0f, -2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		2.0f,  2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		2.0f,  2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f,  2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, -2.0f, 2.0f,  1.0f, 0.0f, 0.0f,

		-2.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, 2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, -2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,

		2.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, 2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		2.0f, -2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		2.0f, -2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		2.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,

		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		2.0f, -2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, -2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,

		-2.0f, 2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, 2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, 2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		2.0f,  2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, 2.0f, 2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, 2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
	};
public:
	void drawCube();
};


#endif