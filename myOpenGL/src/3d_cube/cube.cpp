#include "cube.h"

using namespace std;

void Cube::updateParams() {
	double newTime = glfwGetTime();
	if (newTime - updateTime > 0.1) {
		// translation
		if (fabs(movementx) >= 3.0f) {
			moveDir = -moveDir;
		}
		movementx += moveDir * TRANS_STEP;
		// rotation
		rotation += ROTATE_STEP;
		if (rotation > 360.0f) {
			rotation -= 360.0f;
		}
		// scaling
		if (scale >= 1.0f || scale <= 0.5f) {
			scaleDir = -scaleDir;
		}
		scale += scaleDir * SCALE_STEP;
		updateTime = newTime;
	}
}


void Cube::drawCube() {
	GLFWwindow* window = CreateWindow::createWindow();
	glEnable(GL_DEPTH_TEST);
	bool ImGui = true;
	bool showRotate = true;
	bool showTrans = true;
	bool showScale = true;
	Shader shader("./src/3d_cube/cube.vs", "./src/3d_cube/cube.fs");
	GLuint VAOId, VBOId;
	// create VAO VBO
	glGenVertexArrays(1, &VAOId);
	glGenBuffers(1, &VBOId);

	// ImgUI
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glslVersion);
	ImGui::StyleColorsClassic();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glBindVertexArray(VAOId);
		glBindBuffer(GL_ARRAY_BUFFER, VBOId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.use();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		using namespace CreateWindow;
		projection = glm::perspective(glm::radians(90.0f), (float) SCR_WIDTH/ (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f));
		view = glm::rotate(view, glm::radians(22.5f), glm::vec3(1.0f, 0.0f, 0.0f));

		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		glBindVertexArray(VAOId);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions);
		model = glm::translate(model, glm::vec3(movementx, 0, 0));
		model = glm::scale(model, glm::vec3(scale, scale, scale));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		shader.setMat4("model", model);

		// ImgUI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Menu", &ImGui, ImGuiWindowFlags_MenuBar);
		ImGui::Checkbox("rotate", &showRotate);
		ImGui::Checkbox("translate", &showTrans);
		ImGui::Checkbox("scale", &showScale);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glDrawArrays(GL_TRIANGLES, 0, 36);
		updateParams();
		if (!showRotate) {
			rotation = 0.0f;
		}
		if (!showTrans) {
			movementx = 0.0f;
		}
		if (!showScale) {
			scale = 1.0f;
		}
		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAOId);
	glDeleteBuffers(1, &VBOId);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}