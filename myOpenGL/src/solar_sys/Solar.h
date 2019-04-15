#ifndef SOLAR_H
#define SOLAR_H

#include "../create_window/CreateWindow.hpp"
#include "../Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../create_window/CreateWindow.hpp"
#include <math.h>
#include <vector>

#define PI 3.141592658
#define SOLAR_STEP 2.0f

using std::vector;

struct Coord {
	double x;
	double y;
	double z;
	Coord(double x, double y, double z):x(x),y(y),z(z) {}
};


class Solar {
private:
	float updateTime = 0.0f;
	float vertices[36 * 6] = {
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f,  2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f,  2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f,  2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,

		-2.0f, -2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		2.0f,  2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		2.0f,  2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f,  2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, 2.0f,  1.0f, 0.0f, 0.0f,

		-2.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, 2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,

		2.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, 2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,

		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, -2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,

		-2.0f, 2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, 2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		2.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		2.0f,  2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, 2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
	};
	float pvertices[36 * 6] = {
		-2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f,  2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f,  2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f,  2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,

		-2.0f, -2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, -2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		2.0f,  2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		2.0f,  2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f,  2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, -2.0f, 2.0f,  0.0f, 0.0f, 1.0f,

		-2.0f, 2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, 2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, -2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, 2.0f, 2.0f,  0.0f, 0.0f, 1.0f,

		2.0f, 2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, -2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 2.0f,  0.0f, 0.0f, 1.0f,

		-2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, -2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, -2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, -2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,

		-2.0f, 2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		2.0f,  2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, 2.0f, 2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, 2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
	};
	float earthX = 0.0f;
	float earthZ = 10.0f;
	vector<Coord> planets;
	vector<Coord> axises;
	// method
	void rotateByAxis(Coord&, Coord);
	void updateParams();
public:
	void drawSolarSys();
};

#endif