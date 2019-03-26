#ifndef TRIANGLE_DRAWER_H
#define TRIANGLE_DRAWER_H

#include "create_triangle/CreateTriangle.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <vector>

using std::vector;
using Triangle::VAOId;
using Triangle::VBOId;
using Triangle::shaderProgram;
using Triangle::EBOId;

namespace TriangleDrawerConstants {
	enum GLSLversion { NEW_VERSION, OLD_VERSION };
}

class TriangleDrawer {
private:
	const char* glsl_version;
public:
	TriangleDrawer(enum TriangleDrawerConstants::GLSLversion ver) {
		if (ver == 0) {
			this->glsl_version = "#version 150";
		}
		else {
			this->glsl_version = "#version 130";
		}
	}
	void createGUI() {
		GLFWwindow* window = CreateWindow::createWindow();
		ImVec4 color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

		bool ImGui = true;
		bool colorfulTriangle = true;
		bool bonusTriangle = false;
		bool showLine = false;
		bool basicTriangle = true;

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		ImGui::StyleColorsClassic();

		Triangle::createShader();

		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			
			vector<unsigned int> ind;

			float vertices[] = {
				0.0f, 1.0f, 0.0f, color.x, color.y, color.z, // top
				1.0f, -1.0f, 0.0f,  color.x, color.y, color.z,// right
				-1.0f, -1.0f, 0.0f, color.x, color.y, color.z, // left
				1.0f, 1.0f, 0.0f, color.x, color.y, color.z, // top-right
				-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // line-left
				1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f // line-right
			};

			if (colorfulTriangle) {
				vertices[3] = 1.0f;
				vertices[4] = 0.0f;
				vertices[5] = 0.0f;

				vertices[9] = 0.0f;
				vertices[10] = 0.0f;
				vertices[11] = 1.0f;

				vertices[15] = 0.0f;
				vertices[16] = 1.0f;
				vertices[17] = 0.0f;

				vertices[21] = 1.0f;
				vertices[22] = 0.0f;
				vertices[23] = 0.0f;
			}

			if (bonusTriangle) {
				ind.push_back(0);
				ind.push_back(1);
				ind.push_back(3);
			}

			if (basicTriangle) {
				ind.push_back(0);
				ind.push_back(1);
				ind.push_back(2);
			}

			unsigned int* indices = ind.data();
			int lengthOfIndices = ind.size();

			// create VAO VBO EBO
			glGenVertexArrays(1, &VAOId);
			glGenBuffers(1, &VBOId);
			glGenBuffers(1, &EBOId);
			// Bind VAO
			glBindVertexArray(VAOId);
			// Bind VBO and send data
			glBindBuffer(GL_ARRAY_BUFFER, VBOId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			// Bind EBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, lengthOfIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
			// solve data
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			// use shader
			glUseProgram(shaderProgram);

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			if (showLine) {
				glDrawArrays(GL_LINE_STRIP, 4, 2);
			}
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGui::Begin("Edit color", &ImGui, ImGuiWindowFlags_MenuBar);
			ImGui::ColorEdit3("triangle color", (float*)&color);
			ImGui::Checkbox("colorful Triangle", &colorfulTriangle);
			ImGui::Checkbox("bonus Triangle", &bonusTriangle);
			ImGui::Checkbox("bonus Line", &showLine);
			ImGui::Checkbox("basic Triangle", &basicTriangle);
			ImGui::End();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
		return;
	}
};

#endif
