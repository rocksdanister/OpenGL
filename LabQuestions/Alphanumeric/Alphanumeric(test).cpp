#include <GL/glut.h>
#include <iostream>
#include <string.h>
using namespace std;

GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_10;

void setfont(char* name, int size)
{
	font_style = GLUT_BITMAP_HELVETICA_10;
	if (strcmp(name, "helvetica") == 0) {
		if (size == 12) 
			font_style = GLUT_BITMAP_HELVETICA_12;
		else if (size == 18)
			font_style = GLUT_BITMAP_HELVETICA_18;
	} else if (strcmp(name, "times roman") == 0) {
		font_style = GLUT_BITMAP_TIMES_ROMAN_10;
		if (size == 24)
			font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	} else if (strcmp(name, "8x13") == 0) {
		font_style = GLUT_BITMAP_8_BY_13;
	} else if (strcmp(name, "9x15") == 0) {
		font_style = GLUT_BITMAP_9_BY_15;
	}
}

void drawstr(GLuint x, GLuint y, const char* format, int length)
{
	glRasterPos2i(x, y);	
	for(int i=0; i<length; ++i)
		glutBitmapCharacter(font_style, *(format+i) );
}

void displayf()
{
	glClearColor(0.8, 0.8, 0.8, 0.0);	
	glClear(GL_COLOR_BUFFER_BIT );
	glOrtho(0,800,0,480,-1,1);
	glColor3ub(255, 0, 0);
	setfont("helvetica", 18);
	string str = "The Sun doesn't need to go to college, it already has 28 million degrees.";
	drawstr(100,200, str.c_str(), str.length());
	glutSwapBuffers();
}



int main(int argc, char **argv)
{

  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 480);
	glutInitWindowPosition(50, 50);	
	glutCreateWindow("BitmapFont");
	glutDisplayFunc(displayf);
	glutMainLoop();
	return 0;
}




