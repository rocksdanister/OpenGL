
#include "GL/freeglut.h"
#include "GL/gl.h"

void drawTriangle()
{
    glClearColor(1,1,1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(0, 800, 0, 480, -1, 1);
   glColor3f(.886,.051,.051);
        glBegin(GL_TRIANGLES);
                glVertex3f(10,10,0);
                glVertex3f(200,10,0);
                glVertex3f(100,200,0);
        glEnd();
 glutSwapBuffers();
}

int main(int argc, char **argv)
{
	int mainWindow,subWindow1;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800, 480);
    glutInitWindowPosition(100, 100);
   	mainWindow=glutCreateWindow("Main");
    glutDisplayFunc(drawTriangle);
	subWindow1 = glutCreateSubWindow(mainWindow, border,border,w-2*border, 		h/2 - border*3/2);
	glutDisplayFunc(renderScenesw1);
    glutMainLoop();
    return 0;
}
