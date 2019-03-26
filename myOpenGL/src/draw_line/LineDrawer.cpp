#include "LineDrawer.h"

void LineDrawer::triangleRasterization(vector<pair<int, int> >& vertices, pair<int, int> v1, pair<int, int> v2, pair<int, int> v3) {
	float k1 = (float)(v3.second - v2.second) / (float)(v3.first - v2.first);
	float k2 = (float)(v1.second - v3.second) / (float)(v1.first - v3.first);
	float k3 = (float)(v2.second - v1.second) / (float)(v2.first - v1.first);

	float b1 = (float)v2.second - k1 * v2.first;
	float b2 = (float)v3.second - k2 * v3.first;
	float b3 = (float)v1.second - k3 * v1.first;

	int xMin = min(min(v1.first, v2.first), v3.first),
		xMax = max(max(v1.first, v2.first), v3.first),
		yMin = min(min(v1.second, v2.second), v3.second),
		yMax = max(max(v1.second, v2.second), v3.second);
	for (int i = xMin; i <= xMax; ++i) {
		for (int j = yMin; j <= yMax; ++j) {
			float u = (k1 * i - j + b1) * (k1 * v1.first - v1.second + b1);
			float v = (k2 * i - j + b2) * (k2 * v2.first - v2.second + b2);
			float w = (k3 * i - j + b3) * (k3 * v3.first - v3.second + b3);
			
			if (!(u < 0.0f || v < 0.0f || w < 0.0f)) {
				vertices.push_back(make_pair(i, j));
			}
		}
	}
}

void LineDrawer::genCircleVertices(vector<pair<int, int> >& vertices, 
	pair<int, int> center, int radius) {
	int x = center.first, y = center.second;
	int tx = 0, ty = radius, d = 3 - 2 * radius;
	while (tx <= ty) {
		vertices.push_back(make_pair(x + tx, y + ty));
		vertices.push_back(make_pair(x + tx, y - ty));
		vertices.push_back(make_pair(x - tx, y + ty));
		vertices.push_back(make_pair(x - tx, y - ty));
		vertices.push_back(make_pair(x + ty, y + tx));
		vertices.push_back(make_pair(x + ty, y - tx));
		vertices.push_back(make_pair(x - ty, y + tx));
		vertices.push_back(make_pair(x - ty, y - tx));
		if (d < 0) {
			d += 4 * tx + 6;
		}
		else {
			d += 4 * (tx - ty) + 10;
			ty--;
		}
		tx++;
	}
}

void LineDrawer::genLineVertices(vector<pair<int, int> >& vertices, pair<int, int> begin, pair<int, int> end) {
	bool steep = abs(end.second - begin.second) > abs(end.first - begin.first);
	if (steep) {
		auto t1 = begin.first;
		begin.first = begin.second;
		begin.second = t1;

		auto t2 = end.first;
		end.first = end.second;
		end.second = t2;
	}
	if (begin.first > end.first) {
		auto temp = begin;
		begin = end;
		end = temp;
	}
	int dx = end.first - begin.first,
		dy = abs(end.second - begin.second),
		error = dx / 2,
		y = begin.second;
	int ystep = (begin.second < end.second) ? 1 : -1;
	for (int x = begin.first; x < end.first; ++x) {
		if (steep) {
			vertices.push_back(make_pair(y, x));
		}
		else {
			vertices.push_back(make_pair(x, y));
		}
		error -= dy;
		if (error < 0) {
			y = y + ystep;
			error += dx;
		}
	}

} 

void LineDrawer::drawLine() {
	GLFWwindow* window = CreateWindow::createWindow();

	bool fillTriangle = false;
	bool showCircleOrTriangle = true;
	bool ImGui = true;
	int radius = MAX_WIDTH / 2;

	int triangleCoord[] = {
		-MAX_WIDTH, 0, MAX_WIDTH, 0, 0, MAX_HEIGHT
	};

	ImVec4 color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	GLuint VAOId, VBOId, EBOId;
	vector<pair<int, int> > ver;
	float* vertices = new float[(int)(MAX_WIDTH * MAX_HEIGHT * 6 * 4)];
	// create shader
	createShader();
	// create VAO VBO
	glGenVertexArrays(1, &VAOId);
	glGenBuffers(1, &VBOId);
	// init IMGUI
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glslVersion);
	ImGui::StyleColorsClassic();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		// create vertices
		if (showCircleOrTriangle) {
			genLineVertices(ver, make_pair(triangleCoord[0], triangleCoord[1]), make_pair(triangleCoord[4], triangleCoord[5]));
			genLineVertices(ver, make_pair(triangleCoord[0], triangleCoord[1]), make_pair(triangleCoord[2], triangleCoord[3]));
			genLineVertices(ver, make_pair(triangleCoord[2], triangleCoord[3]), make_pair(triangleCoord[4], triangleCoord[5]));
			if (fillTriangle) {
				triangleRasterization(ver, make_pair(triangleCoord[0], triangleCoord[1]), make_pair(triangleCoord[4], triangleCoord[5]),
					make_pair(triangleCoord[2], triangleCoord[3]));
			}
		}
		else {
			genCircleVertices(ver, make_pair(0, 0), radius);
		}
		const int vsize = ver.size();
		for (auto i = 0; i < vsize; ++i) {
			vertices[i * 6] = (float)(ver[i].first) / MAX_WIDTH;
			vertices[i * 6 + 1] = (float)(ver[i].second) / MAX_HEIGHT;
			vertices[i * 6 + 2] = 0.0f;
			vertices[i * 6 + 3] = color.x;
			vertices[i * 6 + 4] = color.y;
			vertices[i * 6 + 5] = color.z;
		}
		// Bind VAO
		glBindVertexArray(VAOId);
		// Bind VBO and send data
		glBindBuffer(GL_ARRAY_BUFFER, VBOId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vsize * 6, vertices, GL_STATIC_DRAW);
		// solve data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// use shader
		glUseProgram(shaderProgram);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// bind and draw
		glBindVertexArray(VAOId);
		glDrawArrays(GL_POINTS, 0, vsize);
		
		// create imgui components
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Edit color", &ImGui, ImGuiWindowFlags_MenuBar);
		ImGui::ColorEdit3("Graphics color", (float*)&color);
		ImGui::Checkbox("show circle or triangle", &showCircleOrTriangle);
		if (showCircleOrTriangle) {
			ImGui::Checkbox("Triangle Rasterization", &fillTriangle);
			ImGui::SliderInt("v1 x", &triangleCoord[0], -MAX_WIDTH, MAX_WIDTH);
			ImGui::SliderInt("v1 y", &triangleCoord[1], -MAX_HEIGHT, MAX_HEIGHT);
			ImGui::SliderInt("v2 x", &triangleCoord[2], -MAX_WIDTH, MAX_WIDTH);
			ImGui::SliderInt("v2 y", &triangleCoord[3], -MAX_HEIGHT, MAX_HEIGHT);
			ImGui::SliderInt("v3 x", &triangleCoord[4], -MAX_WIDTH, MAX_WIDTH);
			ImGui::SliderInt("v3 y", &triangleCoord[5], -MAX_HEIGHT, MAX_HEIGHT);
		}
		else {
			ImGui::SliderInt("circle radius", &radius, 0, MAX_WIDTH);
		}
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ver.clear();
		memset(vertices, 0, sizeof(float) * (int)(MAX_WIDTH * MAX_HEIGHT * 6 * 4));
		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}

	glDeleteBuffers(1, &VBOId);
	glDeleteVertexArrays(1, &VAOId);
	glDeleteBuffers(1, &EBOId);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}