#include "projection_cube.h"

Camera Projection::myCamera = Camera(glm::vec3(0.0, 10.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
float Projection::xPos = 0.0f;
float Projection::yPos = 0.0f;
bool firstMouse = true;
bool keys[1024];

void Projection::updateCamera() {
	double newTime = glfwGetTime();
	if (newTime - currentTime > 0.01) {
		autoCamX = sin(newTime) * cameraRadius;
		autoCamZ = cos(newTime) * cameraRadius;
		currentTime = newTime;
	}
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}


void mouseCallback(GLFWwindow*, double xpos, double ypos) {
	if (firstMouse) {
		Projection::xPos = xpos;
		Projection::yPos = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - Projection::xPos;
	float yoffset = Projection::yPos - ypos;
	Projection::myCamera.mouseMoveHandler(-xoffset, -yoffset);
	Projection::xPos = xpos;
	Projection::yPos = ypos;
}

void scrollCallback(GLFWwindow*, double xoffset, double yoffset) {
	Projection::myCamera.mouseScrollHandler(yoffset);
}

void move(GLfloat dtime) {
	if (keys[GLFW_KEY_W]) {
		Projection::myCamera.keyboardHandler(FORWARD, dtime);
	}
	if (keys[GLFW_KEY_S]) {
		Projection::myCamera.keyboardHandler(BACKWARD, dtime);
	}
	if (keys[GLFW_KEY_A]) {
		Projection::myCamera.keyboardHandler(LEFT, dtime);
	}
	if (keys[GLFW_KEY_D]) {
		Projection::myCamera.keyboardHandler(RIGHT, dtime);
	}
}


void Projection::drawCube() {
	autoCamX = sin(0) * cameraRadius;
	autoCamZ = cos(0) * cameraRadius;
	GLFWwindow* window = CreateWindow::createWindow();
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetKeyCallback(window, keyCallback);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	Shader shader("./src/projection_cube/pcube.vs", "./src/projection_cube/pcube.fs");
	GLuint VAO, VBO;
	GLfloat curFrame = 0.0f, lastFrame = 0.0f;
	bool menu = true;
	bool perspectiveOrOrtho = true;
	bool placeToNewPlace = false;
	bool myCam = true;
	// create VAO VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// ImgUI
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glslVersion);
	ImGui::StyleColorsClassic();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		curFrame = glfwGetTime();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// position attr
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attr
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.use();
		
		// projection and view
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		using namespace CreateWindow;
		if (!perspectiveOrOrtho) {
			projection = glm::ortho(widthStart, widthEnd, heightStart, heightEnd, nearOrtho, farOrtho);
		} else {
			projection = glm::perspective(glm::radians(fov), viewWidth / viewHeight, nearPer, farPer);
		}
		if (!myCam) {
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f));
			view = glm::rotate(view, glm::radians(22.5f), glm::vec3(3.0f, -1.0f, 0.0f));
			view = glm::lookAt(glm::vec3(autoCamX, 10.0, autoCamZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0f, 0.0));
		} else {
			view = myCamera.getViewMat();
		}
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		glBindVertexArray(VAO);
		glm::mat4 model = glm::mat4(1.0f);
		if (placeToNewPlace) {
			model = glm::translate(model, glm::vec3(-1.5, 0.5, -1.5));
		} else {
			model = glm::translate(model, glm::vec3(0, 0, 0));
		}
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// Imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Menu", &menu, ImGuiWindowFlags_MenuBar);
		ImGui::Checkbox("perspective or ortho", &perspectiveOrOrtho);
		ImGui::Checkbox("use my camera", &myCam);
		ImGui::Checkbox("place to (-1.5, 0.5, -1.5)?", &placeToNewPlace);
		if (!perspectiveOrOrtho) {
			ImGui::SliderFloat("ortho: width start", &widthStart, -20.0f, 0.0f);
			ImGui::SliderFloat("ortho: width end", &widthEnd, 0.0f, 20.0f);
			ImGui::SliderFloat("ortho: height start", &heightStart, -20.0f, 0.0f);
			ImGui::SliderFloat("ortho: height end", &heightEnd, 0.0f, 20.0f);
			ImGui::SliderFloat("ortho: near", &nearOrtho, -20.0f, 20.0f);
			ImGui::SliderFloat("ortho: far", &farOrtho, -20.0f, 20.0f);
		} else {
			ImGui::SliderFloat("perspective: fov", &fov, 45.0f, 135.0f);
			ImGui::SliderFloat("perspective: height", &viewHeight, 0.0f, 800.0f);
			ImGui::SliderFloat("perspective: width", &viewWidth, 0.0f, 800.0f);
			ImGui::SliderFloat("perspective: near", &nearPer, -5.0f, 5.0f);
			ImGui::SliderFloat("perspective: far", &farPer, 0.0f, 60.0f);
		}
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		updateCamera();
		move(curFrame - lastFrame);
		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
		lastFrame = curFrame;
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}