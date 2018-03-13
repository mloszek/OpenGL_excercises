#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <iostream>
#include <queue>

using namespace std;

enum
{
	FULL_WINDOW,
	ASPECT_1_1,
	ABOUT,
	EXIT
};

int Aspect = ASPECT_1_1;

float centerx1 = -0.66;
float centerx2 = 1.34;
float centery1 = -0.66;
float centery2 = 1.34;
float scale = 1.0;

void drawInnerSquare(float vertex1[], float vertex2[], float vertex3[], float vertex4[], int depth)
{
	if (depth >= 6)
	{
		return;
	}	
	
	float x1 = ((vertex1[0] + vertex2[0]) / 2) - ((vertex2[0] - vertex1[0]) * 0.1667);
	float x2 = ((vertex1[0] + vertex2[0]) / 2) + ((vertex2[0] - vertex1[0]) * 0.1667);
	float y1 = ((vertex1[1] + vertex4[1]) / 2) - ((vertex4[1] - vertex1[1]) * 0.1667);
	float y2 = ((vertex1[1] + vertex4[1]) / 2) + ((vertex4[1] - vertex1[1]) * 0.1667);

	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_POLYGON);
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x1, y2, 0.0);
	glEnd();

	float newVertex1[3] =  {vertex1[0], vertex1[1], 0.0};
	float newVertex2[3] =  {x1, vertex1[1], 0.0};
	float newVertex3[3] =  {x2, vertex1[1], 0.0};
	float newVertex4[3] =  {vertex2[0], vertex1[1], 0.0};
	float newVertex5[3] =  {vertex1[0], y1, 0.0};
	float newVertex6[3] =  {x1, y1, 0.0};
	float newVertex7[3] =  {x2, y1, 0.0};
	float newVertex8[3] =  {vertex2[0], y1, 0.0};
	float newVertex9[3] =  {vertex1[0], y2, 0.0};
	float newVertex10[3] = {x1, y2, 0.0 };
	float newVertex11[3] = {x2, y2, 0.0 };
	float newVertex12[3] = {vertex2[0], y2, 0.0};
	float newVertex13[3] = {vertex1[0], vertex4[1], 0.0};
	float newVertex14[3] = {x1, vertex4[1], 0.0};
	float newVertex15[3] = {x2, vertex4[1], 0.0};
	float newVertex16[3] = {vertex2[0], vertex4[1], 0.0};

	drawInnerSquare (newVertex1, newVertex2, newVertex6, newVertex5, depth + 1);
	drawInnerSquare (newVertex2, newVertex3, newVertex7, newVertex6, depth + 1);
	drawInnerSquare (newVertex3, newVertex4, newVertex8, newVertex7, depth + 1);
	drawInnerSquare (newVertex5, newVertex6, newVertex10, newVertex9, depth + 1);
	drawInnerSquare (newVertex7, newVertex8, newVertex12, newVertex11, depth + 1);
	drawInnerSquare (newVertex9, newVertex10, newVertex14, newVertex13, depth + 1);
	drawInnerSquare (newVertex10, newVertex11, newVertex15, newVertex14, depth + 1);
	drawInnerSquare (newVertex11, newVertex12, newVertex16, newVertex15, depth + 1);

}

void Display()
{
	float vertex1[3] = {centerx1 * scale, centery1 * scale, 0.0};
	float vertex2[3] = {centerx2 * scale, centery1 * scale, 0.0};
	float vertex3[3] = {centerx2 * scale, centery2 * scale, 0.0};
	float vertex4[3] = {centerx1 * scale, centery2 * scale, 0.0};

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);	

	glBegin(GL_POLYGON);
	glVertex3fv(vertex1);
	glVertex3fv(vertex2);
	glVertex3fv(vertex3);
	glVertex3fv(vertex4);
	glEnd();
	
	drawInnerSquare(vertex1, vertex2, vertex3, vertex4, 0);

	glFlush();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	if (Aspect == ASPECT_1_1)
	{
		if (width < height && width > 0)
		{
			glOrtho(-2.0, 2.0, -2.0 * height / width, 2.0 * height / width, -2.0, 2.0);
		}
		else if (width >= height && height > 0)
		{
			glOrtho(-2.0 * width / height, 2.0 * width / height, -2.0, 2.0, -2.0, 2.0);
		}
	}
	else
	{
		glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	}

	Display();
}

void About()
{
	MessageBox(nullptr, TEXT("I am about to take a shit"), TEXT("About"), MB_OK);
}

void Menu(int value)
{
	switch (value)
	{
	case FULL_WINDOW:
		Aspect = FULL_WINDOW;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case ASPECT_1_1:
		Aspect = ASPECT_1_1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case ABOUT:
		About();
		break;
	case EXIT:
		exit(0);
	default:
		exit(1);
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '+')
	{
		scale += 0.1;
	}
	else if (key == '-')
	{
		scale -= 0.1;		
	}

	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		centerx1 -= 0.1;
		centerx2 -= 0.1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case GLUT_KEY_LEFT:
		centerx1 += 0.1;
		centerx2 += 0.1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;	
	case GLUT_KEY_DOWN:
		centery1 += 0.1;
		centery2 += 0.1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case GLUT_KEY_UP:
		centery1 -= 0.1;
		centery2 -= 0.1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	}
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(600, 600);

	glutCreateWindow("Carpet");

	glutDisplayFunc(Display);

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(Keyboard);

	glutSpecialFunc(SpecialKeys);

	glutCreateMenu(Menu);

	glutAddMenuEntry("Obszar renderingu - cale okno", FULL_WINDOW);
	glutAddMenuEntry("Obszar renderingu - aspekt 1:1", ASPECT_1_1);
	glutAddMenuEntry("About", ABOUT);
	glutAddMenuEntry("Exit", EXIT);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}