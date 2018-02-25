#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// sta�e do obs�ugi menu podr�cznego
enum
{
	ABOUT,
	EXIT // wyj�cie
};

// pionowy k�t pola widzenia
GLdouble fovy = 90;

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

	// obliczenie aspektu obrazu z uwzgl�dnieniem
	// przypadku, gdy wysoko�� obrazu wynosi 0
	GLdouble aspect = 1;
	if (height > 0)
		aspect = width / (GLdouble)height;

	// rzutowanie perspektywiczne
	gluPerspective(fovy, aspect, 1.0, 5.0);

	// generowanie sceny 3D
	Display();
}

//metoda wy�wietlaj�ca okno About
void AboutInfo()
{
	MessageBox(nullptr, TEXT("I am about to take a shit"), TEXT("About"), MB_OK);
	Beep(500, 300);
}

// obs�uga klawiatury
void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+' && fovy < 180)
	{
		cout << fovy << endl;
		fovy++;
	}
	// klawisz -
	else if (key == '-' && fovy > 0)
	{
		cout << fovy << endl;
		fovy--;
	}

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obs�uga menu podr�cznego
void Menu(int value)
{
	switch (value)
	{
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
	glutCreateWindow("Szescian 3");

	// do��czenie funkcji generuj�cej scen� 3D
	glutDisplayFunc(Display);

	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// do��czenie funkcji obs�ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// utworzenie menu podr�cznego
	glutCreateMenu(Menu);

	// dodatnie pozycji do menu podr�cznego
#ifdef WIN32

	glutAddMenuEntry("About", ABOUT);
	glutAddMenuEntry("Exit", EXIT);
#else

	glutAddMenuEntry("About", ABOUT);
	glutAddMenuEntry("Exit", EXIT);
#endif

	// okre�lenie przycisku myszki obs�uguj�cej menu podr�czne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// wprowadzenie programu do obs�ugi p�tli komunikat�w
	glutMainLoop();
	return 0;
}