#pragma once

#include "Actor.h"

class Rectangle : public Actor {
private:
	GLuint vaoID;
	GLuint vboID;
	GLuint shader;

public:
	Rectangle() {}

	Rectangle(GLuint inShader, const GLfloat arr[]) {
		shader = inShader;

		//printf("%d\n", sizeof(arr));

		const GLfloat vertices[]{
			arr[0], arr[1], arr[2],
			arr[3], arr[4], arr[5],
			arr[6], arr[7], arr[8],
			arr[9], arr[10], arr[11]
		};

		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

	void render() {
		glBindVertexArray(vaoID);

		glEnableVertexAttribArray(0);


		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, NULL, NULL);

		glUseProgram(shader);
		glDrawArrays(GL_QUADS, 0, 4);


		glDisableVertexAttribArray(0);
	}
};