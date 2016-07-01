#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Actor.h"
#include "MatrixUtil.h"

class Triangle: public Actor {
private:
	GLuint vaoID;
	GLuint vboID;
	GLuint shader;
	GLfloat* vertices;
	//GLfloat** transform;

public:
	Triangle() {}

	Triangle(/*GLfloat** transform,*/ GLuint shader, const GLfloat arr[]) {
		//this->transform = transform;
		this->shader = shader;

		//printf("%d\n", sizeof(arr));

		vertices = new GLfloat[9];
		for (int i = 0; i < 9; i++) {
			vertices[i] = arr[i];
		}


		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);

		glGenBuffers(1, &vboID);
	}

	void render() {
		const GLfloat vertTemp[] = /*matrix3fMult(vertices, *transform);*/
		{
			vertices[0], vertices[1], vertices[2],
			vertices[3], vertices[4], vertices[5],
			vertices[6], vertices[7], vertices[8]
		};
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertTemp), vertTemp, GL_STATIC_DRAW);


		glBindVertexArray(vaoID);

		glEnableVertexAttribArray(0);


		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, NULL, NULL);

		glUseProgram(shader);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glDisableVertexAttribArray(0);
	}
};