#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//TODO: dodac strzalki do przesuwania

// sta�e do obs�ugi menu podr�cznego
enum
{
	FULL_WINDOW,
	ASPECT_1_1,
	RESET_VIEW,
	ABOUT,
	EXIT // wyj�cie
};

// definicja pola Aspect potrzebnego do przeliczania rozdzielczo�ci
GLint Aspect = FULL_WINDOW;

// definicja zmiennej potrzebnej do skalowania
GLfloat myScale = 1;

// definicja zmiennych do obrotu sze�cianu
GLfloat rotAngleX = 0;
GLfloat rotAngleY = 0;

void Display()
{
	// kolor t�a - zawarto�� bufora koloru
	glClearColor(0, 0, 0, 0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT);

	// wyb�r macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// obracanie
	glRotatef(rotAngleX, 1, 0, 0);
	glRotatef(rotAngleY, 0, 1, 0);

	// skalowanie
	glScalef(myScale, myScale, myScale);

	// kolor kraw�dzi sze�cianu
	glColor3f(1.0, 0.0, 0.0);

	// pocz�tek definicji kraw�dzi sze�cianu
	glBegin(GL_LINES);

	GLfloat a = 0;

	while (a < 1)
	{
		glVertex3f(1.0 - a, 1.0 - a, 1.0 - a);
		glVertex3f(1.0 - a, -1.0 + a, 1.0 - a);

		glVertex3f(1.0 - a, -1.0 + a, 1.0 - a);
		glVertex3f(1.0 - a, -1.0 + a, -1.0 + a);

		glVertex3f(1.0 - a, -1.0 + a, -1.0 + a);
		glVertex3f(1.0 - a, 1.0 - a, -1.0 + a);

		glVertex3f(1.0 - a, 1.0 - a, -1.0 + a);
		glVertex3f(1.0 - a, 1.0 - a, 1.0 - a);

		glVertex3f(-1.0 + a, 1.0 - a, 1.0 - a);
		glVertex3f(-1.0 + a, -1.0 + a, 1.0 - a);

		glVertex3f(-1.0 + a, -1.0 + a, 1.0 - a);
		glVertex3f(-1.0 + a, -1.0 + a, -1.0 + a);

		glVertex3f(-1.0 + a, -1.0 + a, -1.0 + a);
		glVertex3f(-1.0 + a, 1.0 - a, -1.0 + a);

		glVertex3f(-1.0 + a, 1.0 - a, -1.0 + a);
		glVertex3f(-1.0 + a, 1.0 - a, 1.0 - a);

		glVertex3f(1.0 - a, 1.0 - a, 1.0 - a);
		glVertex3f(-1.0 + a, 1.0 - a, 1.0 - a);

		glVertex3f(1.0 - a, -1.0 + a, 1.0 - a);
		glVertex3f(-1.0 + a, -1.0 + a, 1.0 - a);

		glVertex3f(1.0 - a, -1.0 + a, -1.0 + a);
		glVertex3f(-1.0 + a, -1.0 + a, -1.0 + a);

		glVertex3f(1.0 - a, 1.0 - a, -1.0 + a);
		glVertex3f(-1.0 + a, 1.0 - a, -1.0 + a);

		a += 0.01;
	}

	// koniec definicji prymitywu
	glEnd();

	// skierowanie polece� do wykonania
	glFlush();

	// zamiana bufor�w koloru
	glutSwapBuffers();
}

// zmiana wielko�ci okna
void Reshape(int width, int height)
{
	// obszar renderingu - ca�e okno
	glViewport(0, 0, width, height);

	// wyb�r macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	// parametry bry�y obcinania
	if (Aspect == ASPECT_1_1)
	{
		// wysoko�� okna wi�ksza od szeroko�ci okna
		if (width < height && width > 0)
		{
			glOrtho(-2.0, 2.0, -2.0 * height / width, 2.0 * height / width, -2.0, 2.0);
		}
		// szeroko�� okna wi�ksza lub r�wna wysoko�ci okna
		else if (width >= height && height > 0)
		{
			glOrtho(-2.0 * width / height, 2.0 * width / height, -2.0, 2.0, -2.0, 2.0);
		}
	}
	else
	{
		glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	}

	// generowanie sceny 3D
	Display();
}

//metoda wy�wietlaj�ca okno About
void AboutInfo()
{
	MessageBox(nullptr, TEXT("I am about to take a shit"), TEXT("About"), MB_OK);
	Beep(500, 300);
}

// metoda resetuj�ca pozycj�
void ResetView()
{
	rotAngleX = 0;
	rotAngleY = 0;
	myScale = 1;
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '+')
	{
		myScale *= 1.05;
	}
	else if (key == '-')
	{
		myScale /= 1.05;
	}

	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		rotAngleX += 1;
		break;

	case GLUT_KEY_DOWN:
		rotAngleX -= 1;
		break;

	case GLUT_KEY_LEFT:
		rotAngleY += 1;
		break;

	case GLUT_KEY_RIGHT:
		rotAngleY -= 1;
		break;
	}

	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obs�uga menu podr�cznego
void Menu(int value)
{
	switch (value)
	{
		// obszar renderingu - ca�e okno
	case FULL_WINDOW:
		Aspect = FULL_WINDOW;
		Beep(500, 300);
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// obszar renderingu - aspekt 1:1
	case ASPECT_1_1:
		Aspect = ASPECT_1_1;
		Beep(500, 300);
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// reset rotacji
	case RESET_VIEW:
		Beep(500, 300);
		ResetView();
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// About
	case ABOUT:
		Beep(500, 300);
		AboutInfo();
		break;

		// wyj�cie
	case EXIT:
		Beep(500, 300);
		exit(0);
	}
}

int main(int argc, char * argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);

	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// rozmiary g��wnego okna programu
	glutInitWindowSize(400, 400);

	// utworzenie g��wnego okna programu
	glutCreateWindow("Szescian 1");

	// do��czenie funkcji generuj�cej scen� 3D
	glutDisplayFunc(Display);

	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// do��czenie funkcji obs�ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// do��czenie sterowania strza�kami
	glutSpecialFunc(SpecialKeys);

	// utworzenie menu podr�cznego
	glutCreateMenu(Menu);

	// dodatnie pozycji do menu podr�cznego
	glutAddMenuEntry("Obszar renderingu - cale okno", FULL_WINDOW);
	glutAddMenuEntry("Obszar renderingu - aspekt 1:1", ASPECT_1_1);
	glutAddMenuEntry("Reset widoku", RESET_VIEW);
	glutAddMenuEntry("About", ABOUT);
	glutAddMenuEntry("Exit", EXIT);

	// okre�lenie przycisku myszki obs�uguj�cej menu podr�czne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// wprowadzenie programu do obs�ugi p�tli komunikat�w
	glutMainLoop();
	return 0;
}