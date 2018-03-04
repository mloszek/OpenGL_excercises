#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <iostream>

//TODO: implementacja algorytmu tworzacego dywan

void Display()
{

}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GL_RGB);

	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 1);

	glutCreateWindow("Carpet");

	glutDisplayFunc(Display);

	glutReshapeFunc(Reshape);

	glutMainLoop();
	return 0;
}