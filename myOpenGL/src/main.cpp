 #include "create_triangle/createtriangle.hpp"
 #include "draw_triangle/triangledrawer.h"
// using namespace triangledrawerconstants;

#include "draw_line\LineDrawer.h"

int main() {
	LineDrawer drawer = LineDrawer();
	drawer.drawLine();
	/*TriangleDrawer solution(OLD_VERSION);
	solution.createGUI();*/
	return 0;
}