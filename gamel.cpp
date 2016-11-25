#include "GL/freeglut.h"
#include<GL/gl.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
int size,x;clock_t t1;
int px,qx;
double queuedMilliseconds,prev;


void fixedTimestep()
{
glClearColor(1,1,1,0);
glClear(GL_COLOR_BUFFER_BIT);
//glPointSize(100);
glColor3f(0,0,0);
glBegin(GL_TRIANGLES);
glVertex3f(1+x,10,0);
glVertex3f(100+x,100,0);
glVertex3f(100+x,10,0);
glEnd();
glBegin(GL_TRIANGLES);
glVertex3f(200+px,200+qx,0);
glVertex3f(300+px,200+qx,0);
glVertex3f(250+px,250+qx,0);
glEnd();
glFlush();
glutSwapBuffers();
}

void updatestate()
{
x++;
}

void init()
{
 // (calculate timeDifference here)
	double now = glutGet(GLUT_ELAPSED_TIME);
	double timeElapsedMs =(now-prev);
    queuedMilliseconds += timeElapsedMs ;
	//clock_t t0 = clock();
	/* Work. */
	//printf("%Lf", (long double)(t1 - t0)*1000/CLOCKS_PER_SEC);
	printf("TIME: %f %f %f  \n",now,prev,queuedMilliseconds);
	fixedTimestep();    
	while(queuedMilliseconds >= 100) {
		updatestate();
        queuedMilliseconds -= 100;
    }
//printf("NEW: %f\n",queuedMilliseconds);
prev=now;
//t1 = clock();
}


void rshape(int w,int h)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0,0,w,h);
glOrtho(w/size, w, h/size,h, -1, 1);
glMatrixMode(GL_MODELVIEW);
}

void keyboard(int key,int x,int y)
{
 if (key == GLUT_KEY_RIGHT)
px+=5;
 else if (key == GLUT_KEY_LEFT)
px-=5;
 else if (key == GLUT_KEY_UP)
qx+=5;
 else if (key == GLUT_KEY_DOWN)
qx-=5;
}


int main(int argc,char **argv)
{
px=0;qx=0;
x=0;
size=800;
queuedMilliseconds=0;
prev=0;
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE);
glutInitWindowSize(size,size);
glutInitWindowPosition(100,100);
glutCreateWindow("Window 2");
/*
glutDisplayFunc(fixedTimestep);
glutIdleFunc(fixedTimestep);
*/
glutDisplayFunc(init);
glutIdleFunc(init);
glutReshapeFunc(rshape);
glutSpecialFunc(keyboard);
glutMainLoop();
return 0;
}
