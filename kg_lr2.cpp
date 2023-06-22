#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#include <glut.h>


void display();
void specialKeys(int key, int x, int y);

double rotate_y = 0;
double rotate_x = 0;

void display() {

    //  очистка буфера и экрана
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // сброс преобразований
    glLoadIdentity();

    // поворот, когда пользователь изменяет rotate_x и rotate_y
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    // разноцветная сторона - фронтальная
    glBegin(GL_POLYGON);

    glColor3f(1.0, 0.0, 0.0);     glVertex3f(0.5, -0.5, -0.5);      // P1 красный
    glColor3f(0.0, 1.0, 0.0);     glVertex3f(0.5, 0.5, -0.5);      // P2 зеленый
    glColor3f(0.0, 0.0, 1.0);     glVertex3f(-0.5, 0.5, -0.5);      // P3 голубой
    glColor3f(1.0, 0.0, 1.0);     glVertex3f(-0.5, -0.5, -0.5);      // P4 фиолетовый

    glEnd();

    // белая сторона - задняя
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    // фиолетовая сторона - правая
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    // зеленая сторона - левая
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    // голубая сторона - верхняя
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // красная сторона - нижняя
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {

    // стрелка вправо - увеличение поворота на 5 градусов
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;

    // стрелка влево - уменьшить поворот на 5 градусов
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;

    else if (key == GLUT_KEY_UP)
        rotate_x += 5;

    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;

    // запрос обновления дисплея
    glutPostRedisplay();

}

int main(int argc, char* argv[]) {

    // инициализация GLUT и обработка пользовательских параметров
    glutInit(&argc, argv);

    // запрос двойного буферизованного окна истинного цвета с Z-буфером
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // создать окно
    glutCreateWindow("Awesome Cube");

    // включить тест глубины Z-буфера
    glEnable(GL_DEPTH_TEST);

    // функция обратного вызова
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    // передайте управление в GLUT для событий
    glutMainLoop();

    // возвращение в ОС
    return 0;
}
