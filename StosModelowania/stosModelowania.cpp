#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdlib.h>

enum
{
	FULL_WINDOW,
	ASPECT_1_1,
	EXIT
};

int aspect = FULL_WINDOW;

const GLdouble left = -10.0;
const GLdouble right = 10.0;
const GLdouble bottom = -10.0;
const GLdouble top = 10.0;
const GLdouble myNear = 50.0;
const GLdouble myFar = 70.0;

GLfloat scale = 1.0;

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

GLfloat translatex = 0.0;
GLfloat translatey = 0.0;

int button_state = GLUT_UP;
int button_x, button_y;

void Cube3x3()
{
	glutWireCube(1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);
	glTranslatef(0.0, -1.0, 0.0);
	glutWireCube(1.0);
	glTranslatef(-1.0, 0.0, 0.0);
	glutWireCube(1.0);
	glTranslatef(-1.0, 0.0, 0.0);
	glutWireCube(1.0);
	glTranslatef(0.0, 1.0, 0.0);
	glutWireCube(1.0);
	glTranslatef(0.0, 1.0, 0.0);
	glutWireCube(1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);
}

void Cube2x2()
{
	glutWireCube(1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);
	glTranslatef(0.0, -1.0, 0.0);
	glutWireCube(1.0);
	glTranslatef(-1.0, 0.0, 0.0);
	glutWireCube(1.0);
}

void Pyramid()
{
	// podstawa 6x6
	glPushMatrix();
	glTranslatef(1.5, 1.5, 0.0);
	Cube3x3();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.5, -1.5, 0.0);
	Cube3x3();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.5, -1.5, 0.0);
	Cube3x3();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.5, 1.5, 0.0);
	Cube3x3();
	glPopMatrix();

	// drugi poziom 5x5
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(1.0, 1.0, 0.0);
	Cube3x3();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0, -1.0, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.0, 2.0, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0, -1.0, 0.0);
	Cube3x3();
	glPopMatrix();
	glPopMatrix();

	// trzeci poziom 4x4
	glPushMatrix();
	glTranslatef(0.0, 0.0, 2.0);
	glPushMatrix();
	glTranslatef(0.5, -0.5, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5, 1.5, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.5, 1.5, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.5, -0.5, 0.0);
	Cube2x2();
	glPopMatrix();
	glPopMatrix();

	// czwarty poziom 3x3
	glPushMatrix();
	glTranslatef(0.0, 0.0, 3.0);
	Cube3x3();
	glPopMatrix();

	// pi¹ty poziom 2x2
	glPushMatrix();
	glTranslatef(0.0, 0.0, 4.0);
	glTranslatef(-0.5, 0.5, 0.0);
	Cube2x2();
	glPopMatrix();

	// szósty poziom 1x1
	glPushMatrix();
	glTranslatef(0.0, 0.0, 5.0);
	glutWireCube(1.0);
	glPopMatrix();
}

void Display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -(myNear + myFar) / 2);
	glTranslatef(translatex, translatey, 0.0);
	glScalef(scale, scale, scale);
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	glColor3f(0.0, 0.0, 0.0);

	Pyramid();

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
			glFrustum(left, right, bottom * height / width, top * height / width, myNear, myFar);
		}
		else if (width >= height && height > 0)
		{
			glFrustum(left * width / height, right * width / height, bottom, top, myNear, myFar);
		}
	}
	else
		glFrustum(left, right, bottom, top, myNear, myFar);

	Display();
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '+')
		scale += 0.1;
	else
	{
		if (key == '-' && scale > 0.1)
			scale -= 0.1;
	}

	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		rotatey -= 1;
		break;
	case GLUT_KEY_UP:
		rotatex -= 1;
		break;
	case GLUT_KEY_RIGHT:
		rotatey += 1;
		break;
	case GLUT_KEY_DOWN:
		rotatex += 1;
		break;
	}

	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		button_state = state;

		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}

void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		// pobranie macierz modelowania
		GLdouble model[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, model);

		// pobranie macierzy rzutowania
		GLdouble proj[16];
		glGetDoublev(GL_PROJECTION_MATRIX, proj);

		// pobranie obszaru renderingu
		GLint view[4];
		glGetIntegerv(GL_VIEWPORT, view);

		// tablice ze odczytanymi wspó³rzêdnymi w przestrzeni widoku
		GLdouble prev[3], curr[3];

		// pobranie wspó³rzêdnych w przestrzeni widoku
		// dla poprzedniego po³o¿enia kursora myszki
		gluUnProject(button_x, button_y, 0.0, model, proj, view, prev + 0, prev + 1, prev + 2);

		// pobranie wspó³rzêdnych w przestrzeni widoku
		// dla bie¿¹cego po³o¿enia kursora myszki
		gluUnProject(x, y, 0.0, model, proj, view, curr + 0, curr + 1, curr + 2);

		// obliczenie wspó³rzêdnych wektora przesuniêcia obiektu
		translatex += curr[0] - prev[0];
		translatey += prev[1] - curr[1];

		// zapamiêtanie po³o¿enia kursora myszki
		button_x = x;
		button_y = y;

		// odrysowanie okna
		glutPostRedisplay();
	}
}

// obs³uga menu podrêcznego

void Menu(int value)
{
	switch (value)
	{
		// obszar renderingu - ca³e okno
	case FULL_WINDOW:
		aspect = FULL_WINDOW;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// obszar renderingu - aspekt 1:1
	case ASPECT_1_1:
		aspect = ASPECT_1_1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// wyjœcie
	case EXIT:
		exit(0);
	}
}

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(400, 400);

	glutCreateWindow("Stos modelowania");

	glutDisplayFunc(Display);

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(Keyboard);

	glutSpecialFunc(SpecialKeys);

	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);

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