#include<stdio.h>
#include<GL/glut.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<myheader.h>

int i,size,r,j,k,n,q,t,sx,sy,easy;
double p1;
double queuedMilliseconds,prev0;
struct path p[10];
void rshape(int w,int h)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0,0,w,h);
glOrtho(0, w,0,h, 0.0f, 1.0f);
glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char **argv)
{
queuedMilliseconds=0;
prev0=0;
p1=0;q=0;
t=0;
size=500;
printf("\n\tTrapped - ALPHA BUILD v1\n");
printf("Did this just for fun, code is horrible & stupid, Physics not implemented , difficulty not optimised \n");
printf(" >>CONTROLS<< :\n Arrow keys to move forwards(faster),up,down.\n F1: New Game F2: Restart Level\n");
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE);
glutInitWindowSize(size,size);
glutInitWindowPosition(100,100);
glutCreateWindow("Procedural World");
glutDisplayFunc(init);
glutIdleFunc(init);
glutReshapeFunc(rshape);
glutSpecialFunc(keyboard);
glutMainLoop();
return 0;
}

