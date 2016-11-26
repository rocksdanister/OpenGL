#include <iostream>
#include <stdlib.h>
#include<time.h>
#include<stdio.h>
#include <GL/glut.h>


using namespace std;
double queuedMilliseconds,prev,fps,responseTime;
double x = 0.6;
double y = 0.6;
double z = 0.6;
GLdouble radius=1;
float angle = 0.0;

void drawCube()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0, 0.0, -5.0);  
        glRotatef(angle, 1.0, 1.0, 1.0);
    	glRotatef(angle, 1.0, 0.0, 1.0 );
  	    glRotatef(angle, 0.0, 1.0, 1.0 );
        glTranslatef(-0.5, -1.0, 0.0);
        glScalef(.8,.8,.8);
        //draw sphere
     	glColor3f(.8, 0.0, 0.0); 
     	glutSolidSphere(radius,20,20);
    glutSwapBuffers();
}

void update()
{
        angle += 1.0f;
        if (angle > 360)
        {
                        angle -= 360;
        }

}


void init()
{
        glEnable(GL_DEPTH_TEST);
		glClearColor(1,1,1,1);
}



void handleResize(int w, int h)
{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void mixedStepLoop()
{
double now = glutGet(GLUT_ELAPSED_TIME);
double timeElapsedMs =(now-prev);
queuedMilliseconds += timeElapsedMs ;
if(fps<0)
{
drawCube();
}
while(queuedMilliseconds >= responseTime) {
		update();
        queuedMilliseconds -= responseTime;
	if(fps>0)
	glutPostRedisplay();
	}
prev=now;
}


void processMenuEvents(int options){
switch(options){
case 1:fps=60;
	responseTime=(1/fps)*1000;
	break;
case 2:fps=30;
	responseTime=(1/fps)*1000;
	break;
case 3:fps=24;
	responseTime=(1/fps)*1000;
	break;
case 4: fps=-1;
	break;
}
}


void createGLUTMenus()
{
int menu;
menu=glutCreateMenu(processMenuEvents);
glutAddMenuEntry("60fps",1);
glutAddMenuEntry("30fps",2);
glutAddMenuEntry("24fps",3);
glutAddMenuEntry("Nocap(physics locked)",4);
glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
	printf("Right Click to select target Framerate\n");
	queuedMilliseconds=0;
	prev=0;
	fps=30;
	responseTime=(1/fps)*1000;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("StepGameLoop Demo -Sphere");
    init();
    glutDisplayFunc(drawCube);
	glutIdleFunc(mixedStepLoop);
    glutReshapeFunc(handleResize);
	createGLUTMenus();
    glutMainLoop();
    return 0;
}
