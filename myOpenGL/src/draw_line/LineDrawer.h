#ifndef LineDrawer_H
#define LineDrawer_H

#include <iostream>
#include <vector>
#include <utility>
#include "../create_window/CreateWindow.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <algorithm>

using std::min;
using std::max;
using std::pair;
using std::vector;
using std::cout;
using std::endl;
using std::make_pair;

#define MAX_WIDTH 200.0f
#define MAX_HEIGHT 200.0f

class LineDrawer {
private:
	// properties
	GLuint shaderProgram;
	const char* glslVersion;
	/*vector<pair<int, int> > vertices;*/

	// shader
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
	
	void genLineVertices(vector<pair<int, int> >& vertices, pair<int, int> begin, pair<int, int> end);

	void genCircleVertices(vector<pair<int, int> >& vertices, pair<int, int>, int);

	void triangleRasterization(vector<pair<int, int> >& vertices, pair<int, int> v1, pair<int, int> v2, pair<int, int> v3);
public:
	LineDrawer() {
		glslVersion = "#version 130";
	}
	void drawLine();
};

#endif // !LineDrawer
