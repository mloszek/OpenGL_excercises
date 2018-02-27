#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// sta³e do obs³ugi menu podrêcznego
enum
{
	FULL_WINDOW,
	ASPECT_1_1,
	ABOUT,
	EXIT // wyjœcie
};

//definicja pola Aspect potrzebnego do przeliczania rozdzielczoœci
int Aspect = FULL_WINDOW;

void Display()
{
	// kolor t³a - zawartoœæ bufora koloru
	glClearColor(0, 0, 0, 0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// obrót szeœcianu
	/*glRotated(15, 0, 1, 0);
	glRotated(15, 1, 0, 0);*/

	// kolor krawêdzi szeœcianu
	glColor3f(1.0, 0.0, 0.0);

	// pocz¹tek definicji krawêdzi szeœcianu
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

	// skierowanie poleceñ do wykonania
	glFlush();

	// zamiana buforów koloru
	glutSwapBuffers();
}

// zmiana wielkoœci okna
void Reshape(int width, int height)
{
	// obszar renderingu - ca³e okno
	glViewport(0, 0, width, height);

	// wybór macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	// parametry bry³y obcinania
	if (Aspect == ASPECT_1_1)
	{
		// wysokoœæ okna wiêksza od szerokoœci okna
		if (width < height && width > 0)
		{
			glOrtho(-2.0, 2.0, -2.0 * height / width, 2.0 * height / width, -2.0, 2.0);
		}
		// szerokoœæ okna wiêksza lub równa wysokoœci okna
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

//metoda wyœwietlaj¹ca okno About
void AboutInfo()
{
	MessageBox(nullptr, TEXT("I am about to take a shit"), TEXT("About"), MB_OK);
	Beep(500, 300);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '+')
	{
		//TODO
	}

		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obs³uga menu podrêcznego
void Menu(int value)
{
	switch (value)
	{
		// obszar renderingu - ca³e okno
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

		// wyjœcie
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

	// rozmiary g³ównego okna programu
	glutInitWindowSize(400, 400);

	// utworzenie g³ównego okna programu
	glutCreateWindow("Szescian 1");

	// do³¹czenie funkcji generuj¹cej scenê 3D
	glutDisplayFunc(Display);

	// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// utworzenie menu podrêcznego
	glutCreateMenu(Menu);

	// dodatnie pozycji do menu podrêcznego
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

	// okreœlenie przycisku myszki obs³uguj¹cej menu podrêczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();
	return 0;
}