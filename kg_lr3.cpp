#include <glut.h>
#include <iostream>
#include<math.h>

int Angle = 0.0;
float Scale = 1.0;

void Timer(int)
{
	++Angle;
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 0);
}

void Reshape(GLint w, GLint h)
{
	GLint WinWid, WinHei;
	WinWid = w;
	WinHei = h;
	glViewport(0, 0, w, h);
	glClearColor(0.0, 0.0, 0.0, 1.0); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WinWid / 2, WinWid / 2, -WinHei / 2, WinHei / 2, -600.0, 600.0);
	glMatrixMode(GL_MODELVIEW);
}

float ambient[] = { 0.4, 0.4, 0.4, 1.0 };
float light[] = { 1.0, 1.0, 1.0, 1.0 };
float lpos[] = { 400, 0, 0.0, 1.0 };
float black[] = { 0.0, 0.0, 0.0, 1.0 };

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0); 
	glEnable(GL_COLOR_MATERIAL); 

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient); 
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 20); 
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE); 
	 
	glPushMatrix(); 
	glRotatef(Angle, 0.0, 1.0, 0.0); 
	glRotatef(50, 0.0, 0.0, 1.0); 
	
	// основной параллелепипед
	glBegin(GL_QUADS); // нижняя
	glColor3f(1, 0.5, 0.0); 
	glNormal3f(0.0, 0.0, -1.0); 
	glVertex3f(-300, -200, -100); 
	glVertex3f(-300, 0, -100);
	glVertex3f(300, 0, -100);
	glVertex3f(300, -200, -100);
	glEnd();

	glBegin(GL_QUADS); // верхняя
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-300, -200, 100);
	glVertex3f(-300, 0, 100);
	glVertex3f(300, 0, 100);
	glVertex3f(300, -200, 100);
	glEnd();

	glBegin(GL_QUADS); // левая боковая
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-300, -200, -100);
	glVertex3f(-300, 0, -100);
	glVertex3f(-300, 0, 100);
	glVertex3f(-300, -200, 100);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0); // правая боковая
	glVertex3f(300, -200, -100);
	glVertex3f(300, 0, -100);
	glVertex3f(300, 0, 100);
	glVertex3f(300, -200, 100);
	glEnd();

	glBegin(GL_QUADS); // лицевая
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-300, 0, -100);
	glVertex3f(-300, 0, 100);
	glVertex3f(300, 0, 100);
	glVertex3f(300, 0, -100);
	glEnd();

	glBegin(GL_QUADS); // задняя
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-300, -200, -100);
	glVertex3f(-300, -200, 100);
	glVertex3f(300, -200, 100);
	glVertex3f(300, -200, -100);
	glEnd();

	glPopMatrix(); 

	glPushMatrix(); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);

	glRotatef(Angle, 0.0, 1.0, 0.0); 
	glRotatef(50, 0.0, 0.0, 1.0); 

	//нижний куб
	glBegin(GL_QUADS); // нижняя
	glColor3f(1, 0.5, 1); 
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-100, 0, -300); 
	glVertex3f(100, 0, -300);
	glVertex3f(100, -200, -300);
	glVertex3f(-100, -200, -300);
	glEnd();

	glBegin(GL_QUADS); // верхняя
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-100, 0, -100);
	glVertex3f(100, 0, -100);
	glVertex3f(100, -200, -100);
	glVertex3f(-100, -200, -100);
	glEnd();

	glBegin(GL_QUADS); // левая боковая
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-100, 0, -300);
	glVertex3f(-100, -200, -300);
	glVertex3f(-100, -200, -100);
	glVertex3f(-100, 0, -100);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0); // правая боковая
	glVertex3f(100, 0, -100);
	glVertex3f(100, 0, -300);
	glVertex3f(100, -200, -300);
	glVertex3f(100, -200, -100);
	glEnd();

	glBegin(GL_QUADS); // лицевая
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-100, 0, -300);
	glVertex3f(100, 0, -300);
	glVertex3f(100, 0, -100);
	glVertex3f(-100, 0, -100);
	glEnd();

	glBegin(GL_QUADS); // задняя
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-100, -200, -300);
	glVertex3f(-100, -200, -100);
	glVertex3f(100, -200, -100);
	glVertex3f(100, -200, -300);
	glEnd();

	glPopMatrix();

	glPushMatrix(); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);

	glRotatef(Angle, 0.0, 1.0, 0.0); 
	glRotatef(50, 0.0, 0.0, 1.0); 

	//верхний куб
	glBegin(GL_QUADS); // нижняя
	glColor3f(1, 0.5, 0.5); 
	glNormal3f(0.0, 0.0, -1.0); 
	glVertex3f(-100, 0, 100); 
	glVertex3f(100, 0, 100);
	glVertex3f(100, -200, 100);
	glVertex3f(-100, -200, 100);
	glEnd();

	glBegin(GL_QUADS); // верхняя
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-100, 0, 300);
	glVertex3f(100, 0, 300);
	glVertex3f(100, -200, 300);
	glVertex3f(-100, -200, 300);
	glEnd();

	glBegin(GL_QUADS); // левая боковая
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-100, 0, 300);
	glVertex3f(-100, -200, 300);
	glVertex3f(-100, -200, 100);
	glVertex3f(-100, 0, 100);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0); // правая боковая
	glVertex3f(100, 0, 100);
	glVertex3f(100, 0, 300);
	glVertex3f(100, -200, 300);
	glVertex3f(100, -200, 100);
	glEnd();

	glBegin(GL_QUADS); // лицевая
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-100, 0, 300);
	glVertex3f(100, 0, 300);
	glVertex3f(100, 0, 100);
	glVertex3f(-100, 0, 100);
	glEnd();

	glBegin(GL_QUADS); // задняя
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-100, -200, 300);
	glVertex3f(-100, -200, 100);
	glVertex3f(100, -200, 100);
	glVertex3f(100, -200, 300);
	glEnd();

	glPopMatrix();

	glutSwapBuffers(); 
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Плюсик");
	glutDisplayFunc(Draw);
	glutReshapeFunc(Reshape);
	glutTimerFunc(20, Timer, 0);
	glutMainLoop();
	return 0;
}
