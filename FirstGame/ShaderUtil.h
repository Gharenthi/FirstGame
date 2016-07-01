#pragma once

#include<GL\glew.h>
#include<GLFW\glfw3.h>

#include<string>
#include<fstream>

std::string loadFileToString(const char* path) {
	std::string fileData = "";
	std::ifstream stream(path, std::ios::in);

	if (stream.is_open()) {
		std::string line = "";

		while (getline(stream, line)) {
			fileData += "\n" + line;
		}

		stream.close();
	}
	return fileData;
}

GLuint loadShaders(const char* vertPath, const char* fragPath) {
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertData = loadFileToString(vertPath);
	std::string fragData = loadFileToString(fragPath);

	const char* rawVertData = vertData.c_str();
	const char* rawFragData = fragData.c_str();
	glShaderSource(vertShader, 1, &rawVertData, NULL);
	glShaderSource(fragShader, 1, &rawFragData, NULL);

	glCompileShader(vertShader);
	glCompileShader(fragShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	return program;
}

GLuint basicShader(float r, float g, float b, float a) {
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertData = loadFileToString("basicVert.vs");
	
	
	std::string fragData = "#version 330 core\nout vec4 color;\n\nvoid main(){\n    gl_FragColor = vec4(";
	fragData.append(std::to_string(r));
	fragData.append(", ");
	fragData.append(std::to_string(g));
	fragData.append(", ");
	fragData.append(std::to_string(b));
	fragData.append(", ");
	fragData.append(std::to_string(a));
	fragData.append(");\n}");


	const char* rawVertData = vertData.c_str();
	const char* rawFragData = fragData.c_str();
	glShaderSource(vertShader, 1, &rawVertData, NULL);
	glShaderSource(fragShader, 1, &rawFragData, NULL);

	glCompileShader(vertShader);
	glCompileShader(fragShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	return program;
}

GLuint basicShader(float r, float g, float b) {
	return basicShader(r, g, b, 1);
}