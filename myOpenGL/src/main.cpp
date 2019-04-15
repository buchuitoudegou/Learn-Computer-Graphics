 //#include "create_triangle/createtriangle.hpp"
 //#include "draw_triangle/triangledrawer.h"
// using namespace triangledrawerconstants;

//#include "draw_line\linedrawer.h"

#include "3d_cube/cube.h"

#include "solar_sys/Solar.h"

int main() {
	/*LineDrawer drawer = LineDrawer();
	drawer.drawLine();*/
	/*TriangleDrawer solution(OLD_VERSION);
	solution.createGUI();*/
	Cube cube;
	cube.drawCube();
	Solar solar;
	solar.drawSolarSys();
	return 0;
}