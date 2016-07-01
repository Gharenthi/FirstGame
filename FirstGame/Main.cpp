#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdlib.h>

#include "ShaderUtil.h"
#include "Scene.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Polygon.h"

#define TITLE "A window"
#define BACKGROUND_COLOR (0, 0, 0, 0)
#define WIDTH 400
#define HEIGHT 400
#define XPOS 100
#define YPOS 100

#define RED basicShader(1, 0, 0, 0.8)
#define GREEN basicShader(0, 1, 0, 0.8)
#define BLUE basicShader(0.15, 0.025, 0.35, 0.8)

/*	ERROR CODES
0 - no error
1 - glfw failed to initialize
2 - window was not created
3 - glew failed to initialize
*/



GLFWwindow* window;
bool running;

Scene scene;

void init();
void initScene();
void update();
void render();

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

int main() {
	init();
	initScene();
	while (running) {
		if (glfwWindowShouldClose(window)) {
			running = false;
			break;
		}
		update();
		render();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void init() {
	if (! glfwInit()) exit(1);

	window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

	if (! window) {
		glfwTerminate();
		exit(2);
	}

	glfwSetWindowPos(window, XPOS, YPOS);

	/*
	glfwWindowHint(GLFW_SAMPLES, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	*/

	
	glfwMakeContextCurrent(window);
	glClearColor BACKGROUND_COLOR;
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(3);
	}


	glfwSetKeyCallback(window, key_callback);

	running = true;
}

void initScene() {
	scene = *new Scene();
	/*
	scene.addActor(new Polygon(6, 0, 0, -0.65, 0.4, 0, basicShader(1, 0.6, 0, 0.9)));
	*/
	scene.addActor(new Triangle(BLUE, new const GLfloat[9]{
		-1.0, -1.0, 0.0,
		1.0, -1.0, 0.0,
		0.0, 1.0, -1.0
	}));

	scene.addActor(new Triangle(GREEN, new const GLfloat[9]{
		-1.0, 1.0, 0.0,
		1.0, 1.0, 0.0,
		0.0, -1.0, -1.0
	}));
	
	scene.addActor(new Rectangle(RED, new const GLfloat[12]{
		-0.38f, -0.6f, -0.6f,
		0.38f, -0.6f, -0.6f,
		0.38f, 0.6f, -0.6f,
		-0.38f, 0.6f, -0.6f
	}));
	//*/
}

void update() {
	glfwPollEvents();
}


void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene.render();
	
	glfwSwapBuffers(window);
}


static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action = GLFW_PRESS) switch (key) {
	case GLFW_KEY_ESCAPE:
		running = false;
		break;
	};
}