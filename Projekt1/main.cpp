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
	EYES_CENTERED,
	EYES_FREE,
	ABOUT,
	EXIT // wyjœcie
};

//definicja pola Aspect potrzebnego do przeliczania rozdzielczoœci
GLint Aspect = FULL_WINDOW;

//definicja pola EyesCentered potrzebnego do ustawiania oczu kamery
GLboolean EyesCentered = true;

//definicja zmiennej zmieniaj¹cej kolor
GLfloat MyColorVariable1 = 0.0;
GLfloat MyColorVariable2 = 90.0;

// wpó³rzêdne po³o¿enia obserwatora
GLdouble eyex = 0;
GLdouble eyey = 0;
GLdouble eyez = 3;

// wspó³rzêdne punktu w którego kierunku jest zwrócony obserwator,
GLdouble centerx = 0;
GLdouble centery = 0;
GLdouble centerz = -100;

void Display()
{
	// kolor t³a - zawartoœæ bufora koloru
	glClearColor(0, 0, 0, 1.0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// ustawienie obserwatora
	if (EyesCentered)
	{
		gluLookAt(eyex, eyey, eyez, 0, 0, -100, 0, 1, 0);
	}
	else
	{
		gluLookAt(eyex, eyey, eyez, eyex, eyey, -100, 0, 1, 0);
	}

	// kolor krawêdzi
	glColor3f(0.33 * cos(MyColorVariable1 += 0.02) + 0.5, 0.33 * cos(MyColorVariable2 += 0.02) + 0.5, 0.33 * sin(MyColorVariable2 += 0.02) + 0.5);

	glBegin(GL_LINES);

	int a = 0;
	int b = 0;
	int c = -100;

	while (c < 1)
	{
		while (a < 101)
		{
			while (b < 101)
			{
				glVertex3f(0.0 + b, 1.0 + a, 1.0 + c);
				glVertex3f(0.0 + b, -1.0 + a, 1.0 + c);

				glVertex3f(0.0 + b, -1.0 + a, 1.0 + c);
				glVertex3f(2.0 + b, -1.0 + a, 1.0 + c);

				glVertex3f(0.0 + b, -1.0 + a, 1.0 + c);
				glVertex3f(0.0 + b, -1.0 + a, -1.0 + c);

				b += 2;
			}
			b = 0;
			a += 2;
		}
		a = 0;
		c += 2;
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
			glFrustum(-2.0, 2.0, -2.0 * height / width, 2.0 * height / width, 1.0, 100.0);
		}
		// szerokoœæ okna wiêksza lub równa wysokoœci okna
		else if (width >= height && height > 0)
		{
			glFrustum(-2.0 * width / height, 2.0 * width / height, -2.0, 2.0, 1.0, 100.0);
		}
	}
	else
	{
		glFrustum(-2.0, 2.0, -2.0, 2.0, 1.0, 100.0);
	}

	// generowanie sceny 3D
	Display();
}

//metoda wyœwietlaj¹ca okno About
void AboutInfo()
{
	cout << glGetString(GL_VERSION) << endl;
	MessageBox(nullptr, TEXT("I am about to take a shit"), TEXT("About"), MB_OK);
	Beep(500, 300);
}

// obs³uga klawiatury
void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
	{
		eyez -= 0.1;
	}
	// klawisz -
	else if (key == '-')
	{
		eyez += 0.1;
	}

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:

		eyex += 0.1;
		if (!EyesCentered)
		{
			centerx += 0.1;
		}
		break;

		// kursor w górê
	case GLUT_KEY_UP:
		eyey -= 0.1;
		if (!EyesCentered)
		{
			centery -= 0.1;
		}
		break;

		// kursor w prawo
	case GLUT_KEY_RIGHT:

		eyex -= 0.1;
		if (!EyesCentered)
		{
			centerx -= 0.1;
		}
		break;

		// kursor w dó³
	case GLUT_KEY_DOWN:
		eyey += 0.1;
		if (!EyesCentered)
		{
			centery += 0.1;
		}
		break;
	}

	// odrysowanie okna
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

		// oczy zablokowane na punkcie (0, 0, -100)
	case EYES_CENTERED:
		EyesCentered = true;
		Beep(500, 300);
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// oczy skierowane przed siebie
	case EYES_FREE:
		EyesCentered = false;
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
	glutCreateWindow("Lazerhawk 666");

	// do³¹czenie funkcji generuj¹cej scenê 3D
	glutDisplayFunc(Display);

	// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// do³¹czenie funkcji obs³ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// do³¹czenie funkcji obs³ugi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);

	// utworzenie menu podrêcznego
	glutCreateMenu(Menu);

	

	// dodatnie pozycji do menu podrêcznego
#ifdef WIN32

	glutAddMenuEntry("Obszar renderingu - cale okno", FULL_WINDOW);
	glutAddMenuEntry("Obszar renderingu - aspekt 1:1", ASPECT_1_1);
	glutAddMenuEntry("Oczy zablokowane na punkcie w dali", EYES_CENTERED);
	glutAddMenuEntry("Oczy skierowane przed siebie", EYES_FREE);
	glutAddMenuEntry("About", ABOUT);
	glutAddMenuEntry("Exit", EXIT);
#else

	glutAddMenuEntry("Obszar renderingu - cale okno", FULL_WINDOW);
	glutAddMenuEntry("Obszar renderingu - aspekt 1:1", ASPECT_1_1);
	glutAddMenuEntry("Oczy zablokowane na punkcie w dali", EYES_CENTERED);
	glutAddMenuEntry("Oczy skierowane przed siebie", EYES_FREE);
	glutAddMenuEntry("About", ABOUT);
	glutAddMenuEntry("Exit", EXIT);
#endif

	// okreœlenie przycisku myszki obs³uguj¹cej menu podrêczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();
	return 0;
}