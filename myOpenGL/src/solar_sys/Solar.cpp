#include "Solar.h"
#include <iostream>

using namespace std;

void Solar::rotateByAxis(Coord& coord, Coord axis) {
	float x = coord.x, y = coord.y, z = coord.z;
	float u = axis.x, v = axis.y, w = axis.z;
	double sinTheta = sin(PI * SOLAR_STEP / 180), cosTheta = cos(PI * SOLAR_STEP / 180);
	coord.x = (u * u + (1 - u * u) * cosTheta) * x +
		(u * v * (1 - cosTheta) - w * sinTheta) * y +
		(u * w * (1 - cosTheta) + v * sinTheta) * z;
	coord.y = (u * v * (1 - cosTheta) + w * sinTheta) * x +
		(v * v + (1 - v * v) * cosTheta) * y +
		(v * w * (1 - cosTheta) - u * sinTheta) * z;
	coord.z = (u * w * (1 - cosTheta) - v * sinTheta) * x +
		(v * w * (1 - cosTheta) + u * sinTheta) * y +
		(w * w + (1 - w * w) * cosTheta) *  z;
}


void Solar::updateParams() {
	double newTime = glfwGetTime();
	if (newTime - updateTime > 0.01) {
		float x = earthX;
		float z = earthZ;
		earthX = x * cos(PI * SOLAR_STEP / 180.0f) - z * sin(PI * SOLAR_STEP / 180.0f);
		earthZ = z * cos(PI * SOLAR_STEP / 180.0f) + x * sin(PI * SOLAR_STEP / 180.0f);
		for (int i = 0; i < planets.size(); ++i) {
			rotateByAxis(planets[i], axises[i]);
		}
		updateTime = newTime;
	}
}


void Solar::drawSolarSys() {
	GLFWwindow* window = CreateWindow::createWindow();
	glEnable(GL_DEPTH_TEST);
	Shader shader("./src/3d_cube/cube.vs", "./src/3d_cube/cube.fs");
	GLuint VBO, VAO;
	GLuint planetVBO, planetVAO;
	planets.push_back(Coord(10, 10, 0));
	axises.push_back(Coord(-0.7071067, 0.7071067, 0));
	planets.push_back(Coord(-10, 10, 0));
	axises.push_back(Coord(0.7071067, 0.7071067, 0));
	planets.push_back(Coord(0, 10, 10));
	axises.push_back(Coord(0, 0.7071067, -0.7071067));
	// create earth and sun
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &planetVAO);
	glGenBuffers(1, &planetVBO);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glBindVertexArray(planetVAO);
		glBindBuffer(GL_ARRAY_BUFFER, planetVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pvertices), pvertices, GL_STATIC_DRAW);
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		using namespace CreateWindow;
		projection = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -30.0f));
		view = glm::rotate(view, glm::radians(22.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, glm::radians(-45.0f), glm::vec3(0, 1, 0));

		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		glBindVertexArray(planetVAO);

		// earth model
		glm::mat4 earthModel = glm::mat4(1.0f);
		earthModel = glm::translate(earthModel, glm::vec3(earthX, 0, earthZ));
		earthModel = glm::scale(earthModel, glm::vec3(0.5, 0.5, 0.5));
		shader.setMat4("model", earthModel);
		// draw earth
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// planet model
		for (int i = 0; i < planets.size(); ++i) {
			glm::mat4 pmodel = glm::mat4(1.0f);
			pmodel = glm::translate(pmodel, glm::vec3(planets[i].x, planets[i].y, planets[i].z));
			pmodel = glm::scale(pmodel, glm::vec3(0.5, 0.5, 0.5));
			shader.setMat4("model", pmodel);
			// draw planets
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(VAO);
		// sun model
		glm::mat4 sunModel = glm::mat4(1.0f);
		sunModel = glm::translate(sunModel, glm::vec3(0, 0, 0));
		shader.setMat4("model", sunModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		updateParams();
		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &planetVAO);
	glDeleteBuffers(1, &planetVBO);
	glfwTerminate();
}