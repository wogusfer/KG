#include <iostream>
#include <glut.h>
#include <glaux.h>
using namespace std;

GLfloat light_white[] = { 0.8f, 0.8f, 0.8f };
GLuint filter;
GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR };
GLuint fogfilter = 0;
GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
bool f1_is_active = false;
int object_number = 2;
float alfa = 0.0f;
unsigned int textures[1]; 
GLfloat ctrlpoints[4][4][3] 
{
{{-3.5, 0.0, -4.5}, {-0.5, 0.0,-4.5 }, {0.5, 0.0, -4.5 }, {3.5, -1.0,-4.5}},
{{-3.5, 0.0, -0.5}, {-0.5, -3.0,-0.5 }, {0.5, -3.0, -0.5 }, {3.5, 0.0,-0.5}},
{{-3.5, 0.0, 0.5}, {-0.5, 4.0, 0.5 }, {0.5, -5.0, 0.5 }, {3.5, 0.0, 0.5}},
{{-3.5, 0.0, 4.5}, {-0.5, 0.0, 4.5 }, {0.5, 1.0, 4.5 }, {3.5, 0.0, 4.5}}
};

//Загрузить текстуру
void LoadTexture()
{
	AUX_RGBImageRec* texture1 = auxDIBImageLoadA("C:\\space.bmp");
	glGenTextures(1, &textures[0]);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
}

//Создать список
GLvoid BuildList()
{
	glNewList(1, GL_COMPILE);
	{
		glBindTexture(GL_TEXTURE_BINDING_2D, textures[0]); 
		glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[4]{ 1.0, 1.0, 1.0, 1.0 }); 
		glMaterialfv(GL_FRONT, GL_AMBIENT, light_white); 

		glBegin(GL_TRIANGLES);
		glNormal3f(1.0, 0.0, 0.0); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, 0.0, 0.0); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, 0.0, 0.0); 
		glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0, 0.28, 0.7); 
		glEnd(); 

		glBegin(GL_TRIANGLES); 
		glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5, 0.0, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 0.85, 0.0);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0, 0.28, 0.7);
		glEnd(); 
		
		glBegin(GL_TRIANGLES);
		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.85, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, 0.0, 0.0);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0, 0.28, 0.7);
		glEnd();

		glBegin(GL_TRIANGLES);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.85, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, 0.0, 0.0);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(-0.5, 0.0, 0.0);
		glEnd();
	}
	glEndList();
}

//Изменить проекцию камеры в зависисмоти от изменения размера окна
void ChangeWindowSize(int h, int w)
{
	if (h == 0)
	{
		h = 1;
	}
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glViewport(0, 0, w, h); 
	gluPerspective(50.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW); 
}

//Создать сцену
void CreateScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 
	glEnable(GL_LIGHTING); 
	glLightModeli(GL_FRONT, GL_TRUE); 
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, fogMode[fogfilter]); 
	glFogfv(GL_FOG_COLOR, fogColor); 
	glFogf(GL_FOG_DENSITY, 0.15f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 1.0f);
	glFogf(GL_FOG_END, 100.0f);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_white); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_white); 
	glShadeModel(GL_SMOOTH);
	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	glRotatef(alfa, 0.0f, 1.0f, 0.0f); 
	for (GLuint yloop = 0; yloop <= object_number; yloop++)
	{
		for (GLuint xloop = 0; xloop < yloop; xloop++) 
		{
			glLoadIdentity(); 
			glTranslatef(1.4f + (float(xloop) * 2.8f) - (float(yloop) * 1.4f),
				((6.0f - float(yloop)) * 2.4f) - 7.0f, -20.0f);
			glRotatef(45.0f - (2.0f * yloop) + alfa, 1.0f, 0.0f, 0.0f); 
			glRotatef(45.0f + alfa, 0.0f, 1.0f, 0.0f); 
			glScalef(yloop, yloop, yloop); 
			glCallList(1); 
		}
	}
	alfa += 0.01f;

	//Нарисовать плоскость
	for (int j = 0; j <= 50; j++)
	{
		glBegin(GL_LINES);
		for (int i = 0; i <= 100; i++)
		{
			glEvalCoord2f((GLfloat)i / 100.0, (GLfloat)j / 40.0);
		}
		glEnd();
		glBegin(GL_LINES);
		for (int i = 0; i <= 100; i++)
		{
			glEvalCoord2f((GLfloat)j / 50.0, (GLfloat)i / 100.0);
		}
		glEnd();
	}
	glFlush(); 
	glutSwapBuffers(); 
}

//Получения ввода с клавиатуры. При нажатии на кнопку F1 меняется тип тумана
void Keyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_F1 && !f1_is_active)
	{
		f1_is_active = true;
		fogfilter += 1;
		if (fogfilter > 2)
		{
			fogfilter = 0;
		}
		glFogi(GL_FOG_MODE, fogMode[fogfilter]);
	}

	if (key == GLUT_KEY_F1)
	{
		f1_is_active = false;
	}
}

//Основная функция программы
void Init(void)
{
	LoadTexture(); 
	BuildList(); 
	glEnable(GL_TEXTURE_2D); 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glClearColor(1.0, 1.0, 1.0, 0.0); 
	glEnable(GL_MAP2_VERTEX_3); 
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0); 
	glEnable(GL_DEPTH_TEST); 
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); 
	glutInitWindowSize(1000, 1000); 
	glutCreateWindow("6lrkg"); 
	Init(); 
	glutDisplayFunc(CreateScene); 
	glutReshapeFunc(ChangeWindowSize); 
	glutIdleFunc(CreateScene); 
	glutSpecialFunc(Keyboard);
	glutMainLoop(); 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return 1;
}
