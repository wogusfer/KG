#define ESCAPE '\033'

#include <glut.h>
#include <iostream>
#include<math.h>

GLint WinWid = 800, WinHei = 800;
double rotate_y = 0;
double rotate_x = 0;

void Timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(60, Timer, 0);
}

void Reshape(GLint w, GLint h)
{
	WinWid = w;
	WinHei = h;
	glViewport(0, 0, w, h);
	glClearColor(0.5, 0.5, 1, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WinWid / 2, WinWid / 2, -WinHei / 2, WinHei / 2, -600.0, 600.0);
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(int key, int x, int y) {

	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	glutPostRedisplay();

}

float ambient[] = { 0.4, 0.4, 0.4, 1.0 };
float diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
float diffuse2[] = { 1.0, 0.0, 0.0, 1.0 };
float diffuse3[] = { 0.0, 0.0, 1.0, 1.0 };
float spec[] = { 1.0, 0.0, 0.0, 1.0 };
float spec2[] = { 0.0, 1.0, 0.0, 1.0 };
float spec3[] = { 1.0, 1.0, 0.0, 1.0 };
float specref[] = { 1.0, 1.0, 1.0, 1.0 };
float lpos1[] = { WinWid / 2 - 100, WinHei / 2 + 100, 10.0, 1.0 };
float lpos2[] = { -WinWid / 2 + 100, WinHei / 2 - 100, 10.0, 1.0 }; 
float lpos3[] = { 0, -WinHei / 2 + 100, 10.0, 1.0 };
float black[] = { 0.0, 0.0, 0.0, 1.0 };

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_COLOR_MATERIAL);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT1, GL_POSITION, lpos2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec2);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse3);
	glLightfv(GL_LIGHT2, GL_POSITION, lpos3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, spec3);

	glColor3f(0.5, 0.5, 0.5);

	// икосаэдр
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glRotatef(rotate_y, 0, 1, 0);
	glRotatef(rotate_x, 1, 0, 0);
	
	glTranslatef(-200, 0, 0);
	glScalef(100, 100, 100);
	glutSolidIcosahedron();
	glPopMatrix();

	// тор
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 70);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_x, 1, 0, 0);
	
	glutSolidTorus(30, 75, 100, 500);

	glPopMatrix();

	// додекаэдр
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, -10);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_x, 1, 0, 0);

	glTranslatef(200, 0, 0);
	glScalef(55,55,55);
	glutSolidDodecahedron();

	glPopMatrix();

	glutSwapBuffers();

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WinWid, WinHei);
	glutCreateWindow("фигуры");
	glutDisplayFunc(Draw);
	glutReshapeFunc(Reshape);
	glutTimerFunc(60, Timer, 0);
	glutSpecialFunc(Keyboard);
	glutMainLoop();
	return 0;
}
