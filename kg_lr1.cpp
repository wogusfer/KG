#include <glut.h>

void init(void)
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void display(void)
{
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 0.25, 0.0);
	glVertex3f(0.75, 0.25, 0.0);
	glVertex3f(0.75, 0.75, 0.0);
	glVertex3f(0.25, 0.75, 0.0);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // производит начальную инициализацию самой биб-лиотеки GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // инициализирует буфер кадра и настраивает полноцветный режим RGB
	glutInitWindowSize(500, 500); // используется для задания начальных раз-меров окна
	glutInitWindowPosition(100, 100);
	glutCreateWindow("first"); // задает заголовок окна и визуализирует само окно на экране

	init();
	glutDisplayFunc(display);

	glutMainLoop(); // происходит контроль всех событий и вызов нужных функ-ций

	return 0;
}
