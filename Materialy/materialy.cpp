#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "materials.h"

enum
{
	// obiekty
	SPHERE, // kula
	CYLINDER, // cylinder
	DISK, // dysk
	PARTIAL_DISK, // cz�ciowy dysk

				  // materia�y
				  BRASS, // mosi�dz
				  BRONZE, // br�z
				  POLISHED_BRONZE, // polerowany br�z
				  CHROME, // chrom
				  COPPER, // mied�
				  POLISHED_COPPER, // polerowana mied�
				  GOLD, // z�oto
				  POLISHED_GOLD, // polerowane z�oto
				  PEWTER, // grafit (cyna z o�owiem)
				  SILVER, // srebro
				  POLISHED_SILVER, // polerowane srebro
				  EMERALD, // szmaragd
				  JADE, // jadeit
				  OBSIDIAN, // obsydian
				  PEARL, // per�a
				  RUBY, // rubin
				  TURQUOISE, // turkus
				  BLACK_PLASTIC, // czarny plastik
				  BLACK_RUBBER, // czarna guma

								// wektory normalne
								NORMALS_SMOOTH, // GLU_SMOOTH
								NORMALS_FLAT, // GLU_FLAT
								NORMALS_NONE, // GLU_NONE

											  // orientacja
											  ORIENTATION_OUTSIDE, // GLU_OUTSIDE
											  ORIENTATION_INSIDE, // GLU_INSIDE

																  // styl
																  STYLE_POINT, // GLU_POINT
																  STYLE_LINE, // GLU_LINE
																  STYLE_FILL, // GLU_FILL
																  STYLE_SILHOUETTE, // GLU_SILHOUETTE

																					// obszar renderingu
																					FULL_WINDOW, // aspekt obrazu - ca�e okno
																					ASPECT_1_1, // aspekt obrazu 1:1
																					EXIT // wyj�cie
};

// aspekt obrazu

int aspect = FULL_WINDOW;

// rozmiary bry�y obcinania

const GLdouble left = -1.0;
const GLdouble right = 1.0;
const GLdouble bottom = -1.0;
const GLdouble top = 1.0;
const GLdouble m_near = 3.0;
const GLdouble m_far = 7.0;

// k�ty obrotu obiektu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

// wska�nik naci�ni�cia lewego przycisku myszki

int button_state = GLUT_UP;

// po�o�enie kursora myszki

int button_x, button_y;

// wsp�czynnik skalowania

GLfloat scale = 1.05;

// w�a�ciwo�ci materia�u - domy�lnie mosi�dz

const GLfloat * ambient = BrassAmbient;
const GLfloat * diffuse = BrassDiffuse;
const GLfloat * specular = BrassSpecular;
GLfloat shininess = BrassShininess;

// wy�wietlany obiekt 3D

int object = SPHERE;

// wektory normalne

int normals = NORMALS_SMOOTH;

// orientacja

int orientation = GLU_OUTSIDE;

// styl

int style = GLU_FILL;

// ilo�� segmant�w obiektu

int segments = 10;

// licznik ramek (FPS)

int frames = 0;

// licznik czasu

long start_time = 0;

// tablica znak�w ze warto�ci� FPS

char time_string[100] = "FPS:";

// funkcja rysuj�ca napis w wybranym miejscu

void DrawString(GLfloat x, GLfloat y, char * string)
{
	// po�o�enie napisu
	glRasterPos2f(x, y);

	// wy�wietlenie napisu
	int len = strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);

}

// funkcja generuj�ca scen� 3D

void Display()
{
	// licznik czasu
	if (!frames++)
		start_time = clock();

	// kolor t�a - zawarto�� bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru i bufora g��boko�ci
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// wyb�r macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// w��czenie testu bufora g��boko�ci
	glEnable(GL_DEPTH_TEST);

	// w��czenie o�wietlenia
	glEnable(GL_LIGHTING);

	// w��czenie �wiat�a GL_LIGHT0 z parametrami domy�lnymi
	glEnable(GL_LIGHT0);

	// w��czenie automatycznej normalizacji wektor�w normalnych
	glEnable(GL_NORMALIZE);

	// przesuni�cie uk�adu wsp�rz�dnych obiektu do �rodka bry�y odcinania
	glTranslatef(0, 0, -(m_near + m_far) / 2);

	// obroty obiektu
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);

	// w�a�ciwo�ci materia�u
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	// utworzenie kwadryki
	GLUquadricObj * quadobj = gluNewQuadric();

	// spos�b generacji wektor�w normalnych
	gluQuadricNormals(quadobj, normals);

	// styl ((wygl�d) generowanej kwadryki
	gluQuadricDrawStyle(quadobj, style);

	// okre�lenie orientacji wektor�w normalnych kwadryki
	gluQuadricOrientation(quadobj, orientation);

	// wyb�r rysowanego obiektu 3D
	switch (object)
	{
	case SPHERE:
		gluSphere(quadobj, 1, segments, segments);
		break;
	case CYLINDER:
		gluCylinder(quadobj, 0.5, 0.5, 1, segments, segments);
		break;
	case DISK:
		gluDisk(quadobj, 0.5, 1.0, segments, segments);
		break;
	case PARTIAL_DISK:
		gluPartialDisk(quadobj, 0.5, 1.0, segments, segments, 90, 180);
		break;
	}

	// usuni�cie kwadryki
	gluDeleteQuadric(quadobj);

	// wy��czenie o�wietlenia
	glDisable(GL_LIGHTING);

	// wy��czenie testu bufora g��boko�ci
	glDisable(GL_DEPTH_TEST);

	// trzeba odpowiednio przekszta�ci� uk�ad wsp�rz�dnych
	// aby napis znajdowa� si� na samej "g�rze" bry�y obcinania
	glLoadIdentity();
	glTranslatef(0, 0, -m_near);

	// komunikat o ilo�ci ramek rysowanych na sekund� (FPS)
	/*glColor3fv(Black);
	if (frames == 1000)
	{
		frames = 0;
		sprintf(time_string, "FPS: %i", (int)(1000 * CLOCKS_PER_SEC / (float)(clock() - start_time)));
	}*/

	// narysowanie napisu
	DrawString(left, bottom, time_string);

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
	if (aspect == ASPECT_1_1)
	{
		// wysoko�� okna wi�ksza od wysoko�ci okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom * height / width, top * height / width, m_near, m_far);
		else

			// szeroko�� okna wi�ksza lub r�wna wysoko�ci okna
			if (width >= height && height > 0)
				glFrustum(left * width / height, right * width / height, bottom, top, m_near, m_far);

	}
	else
		glFrustum(left, right, bottom, top, m_near, m_far);

	// generowanie sceny 3D
	Display();
}

// obs�uga klawiatury

void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
		scale += 0.05;
	else

		// klawisz -
		if (key == '-' && scale > 0.05)
			scale -= 0.05;

	// narysowanie sceny
	Display();
}

// obs�uga przycisk�w myszki

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapami�tanie stanu lewego przycisku myszki
		button_state = state;

		// zapami�tanie po�o�enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}

// obs�uga ruchu kursora myszki

void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		rotatey += 30 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) *(x - button_x);
		button_x = x;
		rotatex -= 30 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) *(button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}

// obs�uga klawiszy funkcyjnych i klawiszy kursora

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// PageUp
	case GLUT_KEY_PAGE_UP:
		segments += 10;
		break;

		// PageDown
	case GLUT_KEY_PAGE_DOWN:
		if (segments > 10)
			segments -= 10;

		break;
	}

	// odrysowanie okna
	Display();
}

// obs�uga menu podr�cznego

void Menu(int value)
{
	switch (value)
	{
		// rysowany obiekt - kula
	case SPHERE:
		object = SPHERE;
		Display();
		break;

		// rysowany obiekt - cylinder
	case CYLINDER:
		object = CYLINDER;
		Display();
		break;

		// rysowany obiekt - dysk
	case DISK:
		object = DISK;
		Display();
		break;

		// rysowany obiekt - cz�ciowy dysk
	case PARTIAL_DISK:
		object = PARTIAL_DISK;
		Display();
		break;

		// materia� - mosi�dz
	case BRASS:
		ambient = BrassAmbient;
		diffuse = BrassDiffuse;
		specular = BrassSpecular;
		shininess = BrassShininess;
		Display();
		break;

		// materia� - br�z
	case BRONZE:
		ambient = BronzeAmbient;
		diffuse = BronzeDiffuse;
		specular = BronzeSpecular;
		shininess = BronzeShininess;
		Display();
		break;

		// materia� - polerowany br�z
	case POLISHED_BRONZE:
		ambient = PolishedBronzeAmbient;
		diffuse = PolishedBronzeDiffuse;
		specular = PolishedBronzeSpecular;
		shininess = PolishedBronzeShininess;
		Display();
		break;

		// materia� - chrom
	case CHROME:
		ambient = ChromeAmbient;
		diffuse = ChromeDiffuse;
		specular = ChromeSpecular;
		shininess = ChromeShininess;
		Display();
		break;

		// materia� - mied�
	case COPPER:
		ambient = CopperAmbient;
		diffuse = CopperDiffuse;
		specular = CopperSpecular;
		shininess = CopperShininess;
		Display();
		break;

		// materia� - polerowana mied�
	case POLISHED_COPPER:
		ambient = PolishedCopperAmbient;
		diffuse = PolishedCopperDiffuse;
		specular = PolishedCopperSpecular;
		shininess = PolishedCopperShininess;
		Display();
		break;

		// materia� - z�oto
	case GOLD:
		ambient = GoldAmbient;
		diffuse = GoldDiffuse;
		specular = GoldSpecular;
		shininess = GoldShininess;
		Display();
		break;

		// materia� - polerowane z�oto
	case POLISHED_GOLD:
		ambient = PolishedGoldAmbient;
		diffuse = PolishedGoldDiffuse;
		specular = PolishedGoldSpecular;
		shininess = PolishedGoldShininess;
		Display();
		break;

		// materia� - grafit (cyna z o�owiem)
	case PEWTER:
		ambient = PewterAmbient;
		diffuse = PewterDiffuse;
		specular = PewterSpecular;
		shininess = PewterShininess;
		Display();
		break;

		// materia� - srebro
	case SILVER:
		ambient = SilverAmbient;
		diffuse = SilverDiffuse;
		specular = SilverSpecular;
		shininess = SilverShininess;
		Display();
		break;

		// materia� - polerowane srebro
	case POLISHED_SILVER:
		ambient = PolishedSilverAmbient;
		diffuse = PolishedSilverDiffuse;
		specular = PolishedSilverSpecular;
		shininess = PolishedSilverShininess;
		Display();
		break;

		// materia� - szmaragd
	case EMERALD:
		ambient = EmeraldAmbient;
		diffuse = EmeraldDiffuse;
		specular = EmeraldSpecular;
		shininess = EmeraldShininess;
		Display();
		break;

		// materia� - jadeit
	case JADE:
		ambient = JadeAmbient;
		diffuse = JadeDiffuse;
		specular = JadeSpecular;
		shininess = JadeShininess;
		Display();
		break;

		// materia� - obsydian
	case OBSIDIAN:
		ambient = ObsidianAmbient;
		diffuse = ObsidianDiffuse;
		specular = ObsidianSpecular;
		shininess = ObsidianShininess;
		Display();
		break;

		// materia� - per�a
	case PEARL:
		ambient = PearlAmbient;
		diffuse = PearlDiffuse;
		specular = PearlSpecular;
		shininess = PearlShininess;
		Display();
		break;

		// metaria� - rubin
	case RUBY:
		ambient = RubyAmbient;
		diffuse = RubyDiffuse;
		specular = RubySpecular;
		shininess = RubyShininess;
		Display();
		break;

		// materia� - turkus
	case TURQUOISE:
		ambient = TurquoiseAmbient;
		diffuse = TurquoiseDiffuse;
		specular = TurquoiseSpecular;
		shininess = TurquoiseShininess;
		Display();
		break;

		// materia� - czarny plastik
	case BLACK_PLASTIC:
		ambient = BlackPlasticAmbient;
		diffuse = BlackPlasticDiffuse;
		specular = BlackPlasticSpecular;
		shininess = BlackPlasticShininess;
		Display();
		break;

		// materia� - czarna guma
	case BLACK_RUBBER:
		ambient = BlackRubberAmbient;
		diffuse = BlackRubberDiffuse;
		specular = BlackRubberSpecular;
		shininess = BlackRubberShininess;
		Display();
		break;

		// wektory normalne - GLU_SMOOTH
	case NORMALS_SMOOTH:
		normals = GLU_SMOOTH;
		Display();
		break;

		// wektory normalne - GLU_FLAT
	case NORMALS_FLAT:
		normals = GLU_FLAT;
		Display();
		break;

		// wektory normalne - GLU_NONE
	case NORMALS_NONE:
		normals = GLU_NONE;
		Display();
		break;

		// orientacja - GLU_OUTSIDE
	case ORIENTATION_OUTSIDE:
		orientation = GLU_OUTSIDE;
		Display();
		break;

		// orientacja - GLU_INSIDE
	case ORIENTATION_INSIDE:
		orientation = GLU_INSIDE;
		Display();
		break;

		// styl - GLU_POINT
	case STYLE_POINT:
		style = GLU_POINT;
		Display();
		break;

		// styl - GLU_LINE
	case STYLE_LINE:
		style = GLU_LINE;
		Display();
		break;

		// styl - GLU_FILL
	case STYLE_FILL:
		style = GLU_FILL;
		Display();
		break;

		// styl - GLU_SILHOUETTE
	case STYLE_SILHOUETTE:
		style = GLU_SILHOUETTE;
		Display();
		break;

		// obszar renderingu - ca�e okno
	case FULL_WINDOW:
		aspect = FULL_WINDOW;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// obszar renderingu - aspekt 1:1
	case ASPECT_1_1:
		aspect = ASPECT_1_1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// wyj�cie
	case EXIT:
		exit(0);
	}
}

int main(int argc, char * argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);

	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// rozmiary g��wnego okna programu
	glutInitWindowSize(500, 500);

	// utworzenie g��wnego okna programu
#ifdef WIN32

	glutCreateWindow("Materia�y");
#else

	glutCreateWindow("Materialy");
#endif

	// do��czenie funkcji generuj�cej scen� 3D
	glutDisplayFunc(Display);

	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// do��czenie funkcji obs�ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// do��czenie funkcji obs�ugi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);

	// obs�uga przycisk�w myszki
	glutMouseFunc(MouseButton);

	// obs�uga ruchu kursora myszki
	glutMotionFunc(MouseMotion);

	// utworzenie menu podr�cznego
	glutCreateMenu(Menu);

	// utworzenie podmenu - obiekt
	int MenuObject = glutCreateMenu(Menu);
	glutAddMenuEntry("Kula", SPHERE);
	glutAddMenuEntry("Cylinder", CYLINDER);
	glutAddMenuEntry("Dysk", DISK);
#ifdef WIN32

	glutAddMenuEntry("Cz�ciowy dysk", PARTIAL_DISK);
#else

	glutAddMenuEntry("Czesciowy dysk", PARTIAL_DISK);
#endif

	// utworzenie podmenu - Materia�
	int MenuMaterial = glutCreateMenu(Menu);
#ifdef WIN32

	glutAddMenuEntry("Mosi�dz", BRASS);
	glutAddMenuEntry("Br�z", BRONZE);
	glutAddMenuEntry("Polerowany br�z", POLISHED_BRONZE);
	glutAddMenuEntry("Chrom", CHROME);
	glutAddMenuEntry("Mied�", COPPER);
	glutAddMenuEntry("Polerowana mied�", POLISHED_COPPER);
	glutAddMenuEntry("Z�oto", GOLD);
	glutAddMenuEntry("Polerowane z�oto", POLISHED_GOLD);
	glutAddMenuEntry("Grafit (cyna z o�owiem)", PEWTER);
	glutAddMenuEntry("Srebro", SILVER);
	glutAddMenuEntry("Polerowane srebro", POLISHED_SILVER);
	glutAddMenuEntry("Szmaragd", EMERALD);
	glutAddMenuEntry("Jadeit", JADE);
	glutAddMenuEntry("Obsydian", OBSIDIAN);
	glutAddMenuEntry("Per�a", PEARL);
	glutAddMenuEntry("Rubin", RUBY);
	glutAddMenuEntry("Turkus", TURQUOISE);
	glutAddMenuEntry("Czarny plastik", BLACK_PLASTIC);
	glutAddMenuEntry("Czarna guma", BLACK_RUBBER);
#else

	glutAddMenuEntry("Mosiadz", BRASS);
	glutAddMenuEntry("Braz", BRONZE);
	glutAddMenuEntry("Polerowany braz", POLISHED_BRONZE);
	glutAddMenuEntry("Chrom", CHROME);
	glutAddMenuEntry("Miedz", COPPER);
	glutAddMenuEntry("Polerowana miedz", POLISHED_COPPER);
	glutAddMenuEntry("Zloto", GOLD);
	glutAddMenuEntry("Polerowane zloto", POLISHED_GOLD);
	glutAddMenuEntry("Grafit (cyna z o�owiem)", PEWTER);
	glutAddMenuEntry("Srebro", SILVER);
	glutAddMenuEntry("Polerowane srebro", POLISHED_SILVER);
	glutAddMenuEntry("Szmaragd", EMERALD);
	glutAddMenuEntry("Jadeit", JADE);
	glutAddMenuEntry("Obsydian", OBSIDIAN);
	glutAddMenuEntry("Perla", PEARL);
	glutAddMenuEntry("Rubin", RUBY);
	glutAddMenuEntry("Turkus", TURQUOISE);
	glutAddMenuEntry("Czarny plastik", BLACK_PLASTIC);
	glutAddMenuEntry("Czarna guma", BLACK_RUBBER);
#endif

	// utworzenie podmenu - Wektory normalne
	int MenuNormals = glutCreateMenu(Menu);
	glutAddMenuEntry("GLU_SMOOTH", NORMALS_SMOOTH);
	glutAddMenuEntry("GLU_FLAT", NORMALS_FLAT);
	glutAddMenuEntry("GLU_NONE", NORMALS_NONE);

	// utworzenie podmenu - Orientacja
	int MenuOrientation = glutCreateMenu(Menu);
	glutAddMenuEntry("GLU_OUTSIDE", ORIENTATION_OUTSIDE);
	glutAddMenuEntry("GLU_INSIDE", ORIENTATION_INSIDE);

	// utworzenie podmenu - Styl
	int MenuStyle = glutCreateMenu(Menu);
	glutAddMenuEntry("GLU_POINT", STYLE_POINT);
	glutAddMenuEntry("GLU_LINE", STYLE_LINE);
	glutAddMenuEntry("GLU_FILL", STYLE_FILL);
	glutAddMenuEntry("GLU_SILHOUETTE", STYLE_SILHOUETTE);

	// utworzenie podmenu - Aspekt obrazu
	int MenuAspect = glutCreateMenu(Menu);
#ifdef WIN32

	glutAddMenuEntry("Aspekt obrazu - ca�e okno", FULL_WINDOW);
#else

	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
#endif

	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);

	// menu g��wne
	glutCreateMenu(Menu);
	glutAddSubMenu("Obiekt", MenuObject);

#ifdef WIN32

	glutAddSubMenu("Materia�", MenuMaterial);
#else

	glutAddSubMenu("Material", MenuMaterial);
#endif

	glutAddSubMenu("Wektory normalne", MenuNormals);
	glutAddSubMenu("Orientacja", MenuOrientation);
	glutAddSubMenu("Styl", MenuStyle);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
#ifdef WIN32

	glutAddMenuEntry("Wyj�cie", EXIT);
#else

	glutAddMenuEntry("Wyjscie", EXIT);
#endif

	// okre�lenie przycisku myszki obs�uguj�cej menu podr�czne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// funkcja bezczynno�ci
	glutIdleFunc(Display);

	// wprowadzenie programu do obs�ugi p�tli komunikat�w
	glutMainLoop();
	return 0;
}