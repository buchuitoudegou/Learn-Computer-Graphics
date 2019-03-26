#ifndef CREATE_TRIANGLE_HPP
#define CREATE_TRIANGLE_HPP
#include "headers.h"

#include "create_window/CreateWindow.hpp"
#include <vector>

namespace Triangle {
	using std::cout;
	using std::endl;
	using std::vector;

	GLuint shaderProgram;
	GLuint VAOId, VBOId, EBOId;

	GLfloat vertices[] = {
		0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f
	};

	void createTriangleVAO() {
		//GLuint VAOId, VBOId;
		// create and bind VAO object
		glGenVertexArrays(1, &VAOId);
		glBindVertexArray(VAOId);

		// create and bind VBO object
		glGenBuffers(1, &VBOId);
		glBindBuffer(GL_ARRAY_BUFFER, VBOId);

		// send data to GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// solve data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);

		// unbind VBO and VAO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	GLuint createVertexShader() {
		const GLchar* vertexShaderSource = 
			"#version 330\n"
      "layout(location = 0) in vec3 position;\n"
			"layout(location = 1) in vec3 color;"
			"out vec3 vertColor;"
      "void main() {\n"
			"gl_Position = vec4(position, 1.0);\n"
			"vertColor = color;\n"
			"}";
		// create shader and attach source code
		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
		// compile shader
		glCompileShader(vertexShaderId);
		GLint status = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);
			vector<GLchar> errLog(maxLength);
			glGetShaderInfoLog(vertexShaderId, maxLength, &maxLength, &errLog[0]);
			cout << "Error::shader vertex shader compile failed," << &errLog[0] << endl;
		}
		return vertexShaderId;
	}

	GLuint createFragmentShader() {
		const GLchar* fragmentShaderSource =
			"#version 330 core\n"
			"in vec3 vertColor;"
			"out vec4 color;\n"
			"void main() {\n"
			"color = vec4(vertColor, 1.0);\n;"
			"}";
		// create shader and attach source code
		GLuint fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		// compile shader
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		GLint status = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
			vector<GLchar> errLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errLog[0]);
			cout << "Error::shader fragment shader compile failed," << &errLog[0] << endl;
		}
		return fragmentShader;
	}

	void createShader() {
		GLuint vertexShader, fragmentShader;

		vertexShader = createVertexShader();
		fragmentShader = createFragmentShader();

		// create shader program
		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		int success = 0;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		}
		// delete shader
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}

	int createTriangle() {
		
		GLFWwindow* window = CreateWindow::createWindow();

		if (!window) {
			return -1;
		}

		//create and bind VAO object
		glGenVertexArrays(1, &VAOId);
		glBindVertexArray(VAOId);

		// create and bind VBO object
		glGenBuffers(1, &VBOId);
		glBindBuffer(GL_ARRAY_BUFFER, VBOId);

		// send data to GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// solve data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);

		// unbind VBO and VAO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		createShader();

		while (!glfwWindowShouldClose(window)) {
			CreateWindow::processInput(window);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(shaderProgram);
			glBindVertexArray(VAOId);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glfwPollEvents();
			glfwSwapBuffers(window);
		}
		glDeleteVertexArrays(1, &VAOId);
		glDeleteBuffers(1, &VBOId);
		
		glfwTerminate();

		return 0;
	}
}

#endif // !CREATE_TRIANGLE_HPP
