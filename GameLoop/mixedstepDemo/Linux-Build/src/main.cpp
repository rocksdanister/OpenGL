
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <GL/glut.h>
#include<myheader.h>

using namespace std;

void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1,1,1,1);
}


double responseTime,prev,fps;

int main(int argc, char **argv)
{
	printf("Right Click to select target Framerate\n");
	prev=0;
	fps=30;
	responseTime=(1/fps)*1000;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("StepGameLoop Demo -Sphere");
    init();
    glutDisplayFunc(draw);
    glutIdleFunc(mixedStepLoop);
    glutReshapeFunc(handleResize);
    createGLUTMenus();
    glutMainLoop();
    return 0;
}

