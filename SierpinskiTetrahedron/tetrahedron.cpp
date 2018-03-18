#include <GL\glew.h>
#include <GL\freeglut.h>
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

int aspect = FULL_WINDOW;

GLfloat scale = 1.0;

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;
GLfloat rotatez = 0.0;

GLfloat translatex = 0.0;
GLfloat translatey = 0.0;

GLdouble eyesx = 0;
GLdouble eyesy = 0;
GLdouble eyesz = 3;

GLuint depth = 1;

void drawTetrahedron(float vertex1[], float vertex2[], float vertex3[], float vertex4[], int currentDepth)
{
	if (currentDepth >= depth)
	{
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(vertex1[0], vertex1[1], vertex1[2]);
		glVertex3f(vertex2[0], vertex2[1], vertex2[2]);
		glVertex3f(vertex3[0], vertex3[1], vertex3[2]);
		glEnd();

		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(vertex1[0], vertex1[1], vertex1[2]);
		glVertex3f(vertex3[0], vertex3[1], vertex3[2]);
		glVertex3f(vertex4[0], vertex4[1], vertex4[2]);
		glEnd();

		glColor3f(0.0, 1.0, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(vertex2[0], vertex2[1], vertex2[2]);
		glVertex3f(vertex3[0], vertex3[1], vertex3[2]);
		glVertex3f(vertex4[0], vertex4[1], vertex4[2]);
		glEnd();

		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(vertex2[0], vertex2[1], vertex2[2]);
		glVertex3f(vertex1[0], vertex1[1], vertex1[2]);
		glVertex3f(vertex4[0], vertex4[1], vertex4[2]);
		glEnd();
	}
	else
	{
		float newVertex1[3] = { vertex1[0], vertex1[1], vertex1[2] };
		float newVertex2[3] = { (vertex1[0] + vertex2[0]) / 2, (vertex1[1] + vertex2[1]) / 2 , (vertex1[2] + vertex2[2]) / 2 };
		float newVertex3[3] = { vertex2[0], vertex2[1], vertex2[2] };
		float newVertex4[3] = { (vertex2[0] + vertex3[0]) / 2, (vertex2[1] + vertex3[1]) / 2 , (vertex2[2] + vertex3[2]) / 2 };
		float newVertex5[3] = { vertex3[0], vertex3[1], vertex3[2] };
		float newVertex6[3] = { (vertex3[0] + vertex1[0]) / 2, (vertex3[1] + vertex1[1]) / 2 , (vertex3[2] + vertex1[2]) / 2 };
		float newVertex7[3] = { (vertex1[0] + vertex4[0]) / 2, (vertex1[1] + vertex4[1]) / 2 , (vertex1[2] + vertex4[2]) / 2 };
		float newVertex8[3] = { (vertex2[0] + vertex4[0]) / 2, (vertex2[1] + vertex4[1]) / 2 , (vertex2[2] + vertex4[2]) / 2 };
		float newVertex9[3] = { (vertex3[0] + vertex4[0]) / 2, (vertex3[1] + vertex4[1]) / 2 , (vertex3[2] + vertex4[2]) / 2 };
		float newVertex10[3] = { vertex4[0], vertex4[1], vertex4[2] };

		drawTetrahedron(newVertex1, newVertex2, newVertex6, newVertex7, currentDepth + 1);
		drawTetrahedron(newVertex2, newVertex3, newVertex4, newVertex8, currentDepth + 1);
		drawTetrahedron(newVertex6, newVertex4, newVertex5, newVertex9, currentDepth + 1);
		drawTetrahedron(newVertex7, newVertex8, newVertex9, newVertex10, currentDepth + 1);
	}
}

void Display()
{
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glDepthFunc(GL_LEQUAL);


	glClearColor(0.8, 0.9, 1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eyesx, eyesy, eyesz, 0.0, 0.0, -3, 0, 1, 0);

	glTranslatef(0.0, 0.0, -3);	
	glScalef(scale, scale, scale);
	

	float vertex1[3] = { 0.0, -0.433, 0.433 };
	float vertex2[3] = { 0.5, -0.433, -0.433 };
	float vertex3[3] = { -0.5, -0.433, -0.433 };
	float vertex4[3] = { 0.0, 0.433, 0 };

	drawTetrahedron(vertex1, vertex2, vertex3, vertex4, 1);

	for (unsigned int i = 1; i < 20; i++)
	{
		glPushMatrix();
		glTranslatef((0.5 * i), 0, (-0.866 * i));
		drawTetrahedron(vertex1, vertex2, vertex3, vertex4, 1);	
		glPopMatrix();
		glPushMatrix();
		glTranslatef((-0.5 * i), 0, (-0.866 * i));
		drawTetrahedron(vertex1, vertex2, vertex3, vertex4, 1);
		glPopMatrix();
	}

	/*float vertices[] =
	{
		0.0, 0.0, 0.0,
		0.5, 0.0, 0.866,
		-0.5, 0.0, 0.866,

		0.0, 0.0, 0.0,
		0.5, 0.0, 0.866,
		0.0, 0.866, 0.433,
	};*/


	/*GLuint myBuffer;
	glGenBuffers(1, &myBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, myBuffer);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), vertices, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);*/

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
			glFrustum(-2.0, 2.0, -2.0 * height / width, 2.0 * height / width, 1, 100);
		}
		else if (width >= height && height > 0)
		{
			glFrustum(-2.0 * width / height, 2.0 * width / height, -2.0, 2.0, 1, 100);
		}
	}
	else
	{
		glFrustum(-2.0, 2.0, -2.0, 2.0, 1, 100);
	}

	Display();
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
	else if (key == 'm')
	{
		depth += 1;
	}
	else if (key == 'n')
	{
		depth -= 1;
	}

	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		eyesx -= 0.1;
		break;
	case GLUT_KEY_UP:
		eyesy -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		eyesx += 0.1; 
		break;
	case GLUT_KEY_DOWN:
		eyesy += 0.1;
		break;
	}

	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
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

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);

	glutInitWindowSize(600, 600);
	
	glutCreateWindow("Tetrahedron 666");

	glutDisplayFunc(Display);

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);

	int MenuAspect = glutCreateMenu(Menu);
	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);

	glutCreateMenu(Menu);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAddMenuEntry("Exit", EXIT);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}