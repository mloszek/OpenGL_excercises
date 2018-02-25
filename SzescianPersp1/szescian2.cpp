#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// sta�e do obs�ugi menu podr�cznego
enum
{
	FULL_WINDOW,
	ASPECT_1_1,
	ABOUT,
	EXIT // wyj�cie
};

//definicja pola Aspect potrzebnego do przeliczania rozdzielczo�ci
int Aspect = FULL_WINDOW;

void Display()
{
	// kolor t�a - zawarto�� bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT);

	// wyb�r macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// przesuni�cie obiektu o wektor [0,0,-3]
	glTranslatef(0, 0, -3.0);

	// kolor kraw�dzi sze�cianu
	glColor3f(0.0, 0.0, 1.0);

	// pocz�tek definicji kraw�dzi sze�cianu
	glBegin(GL_LINES);

	// wsp�rz�dne kolejnych kraw�dzi sze�cianu
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);

	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);

	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);

	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);

	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);

	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);

	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);

	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);

	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);

	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);

	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);

	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);

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
		// wysoko�� okna wi�ksza od wysoko�ci okna
		if (width < height && width > 0)
		{
			glFrustum(-2.0, 2.0, -2.0 * height / width, 2.0 * height / width, 1.0, 5.0);
		}
		// szeroko�� okna wi�ksza lub r�wna wysoko�ci okna
		else if (width >= height && height > 0)
		{
			glFrustum(-2.0 * width / height, 2.0 * width / height, -2.0, 2.0, 1.0, 5.0);
		}
	}
	else
	{
		glFrustum(-2.0, 2.0, -2.0, 2.0, 1.0, 5.0);
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

		//About
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
	glutCreateWindow("Szescian 2");

	// do��czenie funkcji generuj�cej scen� 3D
	glutDisplayFunc(Display);

	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// utworzenie menu podr�cznego
	glutCreateMenu(Menu);

	// dodatnie pozycji do menu podr�cznego
#ifdef WIN32

	glutAddMenuEntry("Obszar renderingu - cale okno", FULL_WINDOW);
	glutAddMenuEntry("Obszar renderingu - aspekt 1:1", ASPECT_1_1);
	glutAddMenuEntry("About", ABOUT);
	glutAddMenuEntry("Exit", EXIT);
#else

	glutAddMenuEntry("Obszar renderingu - cale okno", FULL_WINDOW);
	glutAddMenuEntry("Obszar renderingu - aspekt 1:1", ASPECT_1_1);
	glutAddMenuEntry("About", ABOUT);
	glutAddMenuEntry("Exit", EXIT);
#endif

	// okre�lenie przycisku myszki obs�uguj�cej menu podr�czne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// wprowadzenie programu do obs�ugi p�tli komunikat�w
	glutMainLoop();
	return 0;
}