#pragma once

#include <cmath>

#include "Actor.h"
#include "Triangle.h"

class Polygon: public Actor {
private:
	const float pi = 2 * asin(1);

	Triangle* triangles;
	int n;
	
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat r;

	GLuint shader;

	float theta;
	float intAngle;

public:
	Polygon() {}

	Polygon(int nIN, GLfloat xIN, GLfloat yIN, GLfloat zIN, GLfloat rIN, float thetaIN, /*GLfloat** transform,*/ GLuint shaderIN) {
		x = xIN;
		y = yIN;
		z = zIN;
		r = abs(rIN);
		n = nIN;
		theta = thetaIN + (pi / 2);
		shader = shaderIN;

		triangles = new Triangle[n];

		intAngle = (2 * pi / n);

		for (int i = 0; i < n; i++) {
			triangles[i] = *new Triangle(/*transform, */shader, new const GLfloat[9]{
				x, y, z,
				x + xTrans(i), y + yTrans(i), z,
				x + xTrans(i + 1), y + yTrans(i + 1), z
			});
		}
	}


	GLfloat xTrans(int i) {
		return(r * cos((i * intAngle) + theta));
	}

	GLfloat yTrans(int i) {
		return(r * sin((i * intAngle) + theta));
	}

	void render() {
		for (int i = 0; i < n; i++) {
			triangles[i].render();
		}
	}
};