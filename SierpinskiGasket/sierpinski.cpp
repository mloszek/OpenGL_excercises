#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>

enum
{
	FULL_WINDOW,
	ASPECT_1_1,
	ABOUT,
	EXIT
};

int aspect = ASPECT_1_1;

double scale = 1;

void drawShape(float vertex1[], float vertex2[], float vertex3[], int currentDepth)
{
	if (currentDepth >= 12)
	{
		return;
	}

	glBegin(GL_LINES);
	glVertex3fv(vertex1);
	glVertex3fv(vertex2);
	glVertex3fv(vertex3);
	glEnd();

	float nextVertex1[3] = { (vertex1[0] + vertex2[0]) / 2, (vertex1[1] + vertex2[1]) / 2, (vertex1[2] + vertex2[2]) / 2 };
	float nextVertex2[3] = { (vertex1[0] + vertex3[0]) / 2, (vertex1[1] + vertex3[1]) / 2, (vertex1[2] + vertex3[2]) / 2 };
	float nextVertex3[3] = { (vertex2[0] + vertex3[0]) / 2, (vertex2[1] + vertex3[1]) / 2, (vertex2[2] + vertex3[2]) / 2 };

	drawShape(nextVertex1, vertex1, nextVertex2, currentDepth + 1);
	drawShape(nextVertex1, vertex2, nextVertex3, currentDepth + 1);
	drawShape(nextVertex3, vertex3, nextVertex2, currentDepth + 1);
}

void Display()
{
	float vertex1[3] = { 2.0f * scale, 0.0, 0.0 };
	float vertex2[3] = { 0.0, 0.0, 0.0 };
	float vertex3[3] = { 1.0f * scale, 1.7f * scale, 0.0 };

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	drawShape(vertex1, vertex2, vertex3, 0);

	glFlush();

	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	if (aspect == ASPECT_1_1)
	{
		if (width < height && width > 0)
		{
			glOrtho(-2.0, 2.0, -2.0 * height / width, 2.0 * height / width, -2.0, 2.0);
		}
		else
		{

			if (width >= height && height > 0)
			{
				glOrtho(-2.0 * width / height, 2.0 * width / height, -2.0, 2.0, -2.0, 2.0);
			}
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
		aspect = FULL_WINDOW;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

	case ASPECT_1_1:
		aspect = ASPECT_1_1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

	case ABOUT:
		About();
		break;

	case EXIT:
		exit(0);
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '+')
	{
		scale += 0.1;
	}
	else if (key == '-' && scale > 0.1)
	{
		scale -= 0.1;
	}

	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(1000, 1000);

	glutCreateWindow("Sierpinski Gasket");

	glutDisplayFunc(Display);

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(Keyboard);

	glutCreateMenu(Menu);

	glutAddMenuEntry("Obszar renderingu - cale okno", FULL_WINDOW);
	glutAddMenuEntry("Obszar renderingu - aspekt 1:1", ASPECT_1_1);
	glutAddMenuEntry("About", ABOUT);
	glutAddMenuEntry("Exit", EXIT);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}