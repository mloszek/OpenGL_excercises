#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdlib.h>
#include <iostream>

// sta³e do obs³ugi menu podrêcznego
enum
{
	FULL_WINDOW, // aspekt obrazu - ca³e okno
	ASPECT_1_1, // aspekt obrazu 1:1
	WIRE_SPHERE, // kula
	WIRE_CONE, // sto¿ek
	WIRE_CUBE, // szeœcian
	WIRE_TORUS, // torus
	WIRE_DODECAHEDRON, // dwunastoœcian
	WIRE_TEAPOT, // czajnik
	WIRE_OCTAHEDRON, // oœmioœcian
	WIRE_TETRAHEDRON, // czworoœcian
	WIRE_ICOSAHEDRON, // dwudziestoœcian
	ABOUT,
	EXIT // wyjœcie
};

// aspekt obrazu
int aspect = FULL_WINDOW;

// rodzaj obiektu
int object = WIRE_SPHERE;

// rozmiary bry³y obcinania
const GLdouble left = -10.0;
const GLdouble right = 10.0;
const GLdouble bottom = -10.0;
const GLdouble top = 10.0;
const GLdouble myNear = 50.0;
const GLdouble myFar = 70.0;

// wspó³czynnik skalowania
GLfloat scale = 1.0;

// k¹ty obrotu
GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

// przesuniêcie
GLfloat translatex = 0.0;
GLfloat translatey = 0.0;

// wskaŸnik naciœniêcia lewego przycisku myszki
int button_state = GLUT_UP;

// po³o¿enie kursora myszki
int button_x, button_y;

// funkcja generuj¹ca scenê 3D
void Display()
{
	// kolor t³a - zawartoœæ bufora koloru
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// przesuniêcie uk³adu wspó³rzêdnych obiektu do œrodka bry³y odcinania
	glTranslatef(0, 0, -(myNear + myFar) / 2);

	// przesuniêcie obiektu - ruch myszk¹
	glTranslatef(translatex, translatey, 0.0);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);

	// obroty obiektu - klawisze kursora
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	// kolor krawêdzi obiektu
	glColor3f(1.0, 1.0, 0.0);

	// rysowanie obiektu
	switch (object)
	{
		// kula
	case WIRE_SPHERE:
		glutWireSphere(1.0, 20, 10);
		break;

		// sto¿ek
	case WIRE_CONE:
		glutWireCone(1.0, 2.0, 20, 10);
		break;

		// szeœcian
	case WIRE_CUBE:
		glutWireCube(1.0);
		break;

		// torus
	case WIRE_TORUS:
		glutWireTorus(0.2, 1, 10, 20);
		break;

		// dwunastoœcian
	case WIRE_DODECAHEDRON:
		glutWireDodecahedron();
		break;

		// czajnik
	case WIRE_TEAPOT:
		glutWireTeapot(1.0);
		break;

		// oœmioœcian
	case WIRE_OCTAHEDRON:
		glutWireOctahedron();
		break;

		// czworoœcian
	case WIRE_TETRAHEDRON:
		glutWireTetrahedron();
		break;

		// dwudziestoœcian
	case WIRE_ICOSAHEDRON:
		glutWireIcosahedron();
		break;
	}

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
	if (aspect == ASPECT_1_1)
	{
		// wysokoœæ okna wiêksza od wysokoœci okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom * height / width, top * height / width, myNear, myFar);
		else

			// szerokoœæ okna wiêksza lub równa wysokoœci okna
			if (width >= height && height > 0)
				glFrustum(left * width / height, right * width / height, bottom, top, myNear, myFar);

	}
	else
	{
		glFrustum(left, right, bottom, top, myNear, myFar);
	}

	// generowanie sceny 3D
	Display();
}

//metoda wyœwietlaj¹ca okno About
void AboutInfo()
{
	std::cout << glGetString(GL_VERSION) << std::endl;
	MessageBox(nullptr, TEXT("I am about to take a shit"), TEXT("About"), MB_OK);
	Beep(500, 300);
}

// obs³uga klawiatury
void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
	{
		scale += 0.1;
	}
	// klawisz -	
	else if (key == '-' && scale > 0.1)
	{
		scale -= 0.1;
	}

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obs³uga klawiszy funkcyjnych i klawiszy kursora
void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:
		rotatey -= 1;
		break;

		// kursor w górê
	case GLUT_KEY_UP:
		rotatex -= 1;
		break;

		// kursor w prawo
	case GLUT_KEY_RIGHT:
		rotatey += 1;
		break;

		// kursor w dó³
	case GLUT_KEY_DOWN:
		rotatex += 1;
		break;
	}

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obs³uga przycisków myszki
void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapamiêtanie stanu lewego przycisku myszki
		button_state = state;

		// zapamiêtanie po³o¿enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}

// obs³uga ruchu kursora myszki
void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		translatex += 1.1 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		translatey += 1.1 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
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
		Beep(500, 300);
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// obszar renderingu - aspekt 1:1
	case ASPECT_1_1:
		aspect = ASPECT_1_1;
		Beep(500, 300);
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// kula
	case WIRE_SPHERE:
		object = WIRE_SPHERE;
		Beep(500, 300);
		Display();
		break;

		// cylinder
	case WIRE_CONE:
		object = WIRE_CONE;
		Beep(500, 300);
		Display();
		break;

		// szeœcian
	case WIRE_CUBE:
		object = WIRE_CUBE;
		Beep(500, 300);
		Display();
		break;

		// torus
	case WIRE_TORUS:
		object = WIRE_TORUS;
		Beep(500, 300);
		Display();
		break;

		// dwunastoœcian
	case WIRE_DODECAHEDRON:
		object = WIRE_DODECAHEDRON;
		Beep(500, 300);
		Display();
		break;

		// czajnik
	case WIRE_TEAPOT:
		object = WIRE_TEAPOT;
		Beep(500, 300);
		Display();
		break;

		// oœmioœcian
	case WIRE_OCTAHEDRON:
		object = WIRE_OCTAHEDRON;
		Beep(500, 300);
		Display();
		break;

		// czworoœcian
	case WIRE_TETRAHEDRON:
		object = WIRE_TETRAHEDRON;
		Beep(500, 300);
		Display();
		break;

		// dwudziestoœcian
	case WIRE_ICOSAHEDRON:
		object = WIRE_ICOSAHEDRON;
		Beep(500, 300);
		Display();
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
	glutCreateWindow("Przeksztalcenia");

	// do³¹czenie funkcji generuj¹cej scenê 3D
	glutDisplayFunc(Display);

	// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// do³¹czenie funkcji obs³ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// do³¹czenie funkcji obs³ugi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);

	// obs³uga przycisków myszki
	glutMouseFunc(MouseButton);

	// obs³uga ruchu kursora myszki
	glutMotionFunc(MouseMotion);

	// utworzenie podmenu - aspekt obrazu
	int MenuAspect = glutCreateMenu(Menu);

	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);

	// utworzenie podmenu - obiekt
	int MenuObject = glutCreateMenu(Menu);
	glutAddMenuEntry("Kula", WIRE_SPHERE);
	glutAddMenuEntry("Stozek", WIRE_CONE);
	glutAddMenuEntry("Szescian", WIRE_CUBE);
	glutAddMenuEntry("Torus", WIRE_TORUS);
	glutAddMenuEntry("Dwunastoscian", WIRE_DODECAHEDRON);
	glutAddMenuEntry("Czajnik", WIRE_TEAPOT);
	glutAddMenuEntry("Osmioscian", WIRE_OCTAHEDRON);
	glutAddMenuEntry("Czworoscian", WIRE_TETRAHEDRON);
	glutAddMenuEntry("Dwudziestoscian", WIRE_ICOSAHEDRON);

	// menu g³ówne
	glutCreateMenu(Menu);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAddSubMenu("Obiekt", MenuObject);
	glutAddMenuEntry("About", ABOUT);
	glutAddMenuEntry("Wyjscie", EXIT);

	// okreœlenie przycisku myszki obs³uguj¹cego menu podrêczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();
	return 0;
}