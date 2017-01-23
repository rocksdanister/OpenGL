#include<stdio.h>

#include<GL/glut.h>
#include<GL/gl.h>
#include<math.h>
//float d2r=3.14/180;
double rX=0;
int size;
// Rotate Y
double rY=0;
void drawCircle()
{
float cx=0;
float cy=0;
float r=.5;
int i;
int segments=100;

glClearColor(1,1,1,0);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glLoadIdentity();
 glRotatef( rX, 1.0, 0.0, 0.0 );
    glRotatef( rY, 0.0, 1.0, 0.0 );
//glOrtho(1.0, 1.0, 1.0, 1.0, -1.0, 1.0);
float x,y,theta;
glColor3f(1,0,0);
glBegin(GL_LINE_LOOP);
//float x,y,theta;
for(i=0;i<segments;i++)
{
theta=2.0f*3.14f*(float)i/(float)segments;
x=r*cosf(theta);
y=r*sinf(theta);
glVertex2f(x+cx,y+cy);
}
glEnd();
glFlush();
glutSwapBuffers();
}
void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
//    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
}

 

int main(int argc,char **argv)
{
size=500;
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE);
glutInitWindowSize(size,size);
glutInitWindowPosition(100,100);
glutCreateWindow("Circle");
glutDisplayFunc(drawCircle);
glutMainLoop();
return 0;
}
