#ifndef PROJECTION_CUBE_H
#define PROJECTION_CUBE_H

#include "../create_window/CreateWindow.hpp"
#include "../Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Projection {
	float vertices[36 * 6] = {
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f,  2.0f, -2.0f,  0.0f, 1.0f, 0.0f,
		2.0f,  2.0f, -2.0f,  0.0f, 1.0f, 0.0f,
		-2.0f,  2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,

		-2.0f, -2.0f, 2.0f,  0.5f, 0.0f, 0.0f,
		2.0f, -2.0f, 2.0f,  0.0f, 0.0f, 0.5f,
		2.0f,  2.0f, 2.0f,  0.0f, 0.5f, 0.0f,
		2.0f,  2.0f, 2.0f,  0.0f, 0.5f, 0.0f,
		-2.0f,  2.0f, 2.0f,  0.5f, 0.5f, 0.0f,
		-2.0f, -2.0f, 2.0f,  0.5f, 0.0f, 0.0f,

		-2.0f, 2.0f, 2.0f,  0.5f, 0.5f, 0.0f,
		-2.0f, 2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, 2.0f,  0.5f, 0.0f, 0.0f,
		-2.0f, 2.0f, 2.0f,  0.5f, 0.5f, 0.0f,

		2.0f, 2.0f, 2.0f,  0.0f, 0.5f, 0.0f,
		2.0f, 2.0f, -2.0f,  0.0f, 1.0f, 0.0f,
		2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, -2.0f, 2.0f,  0.0f, 0.0f, 0.5f,
		2.0f, 2.0f, 2.0f,  0.0f, 0.5f, 0.0f,

		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, -2.0f, 2.0f,  0.0f, 0.0f, 0.5f,
		2.0f, -2.0f, 2.0f,  0.0f, 0.0f, 0.5f,
		-2.0f, -2.0f, 2.0f,  0.5f, 0.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,

		-2.0f, 2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		2.0f, 2.0f, -2.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 2.0f, 2.0f,  0.0f, 0.5f, 0.0f,
		2.0f,  2.0f, 2.0f,  0.0f, 0.5f, 0.0f,
		-2.0f, 2.0f, 2.0f,  0.5f, 0.5f, 0.0f,
		-2.0f, 2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
	};
public:
	void drawCube();
};

#endif
