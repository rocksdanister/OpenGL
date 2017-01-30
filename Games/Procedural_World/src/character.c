#include<myheader.h>
#include<GL/glut.h>

extern struct path p[10];
void draw2()
{
glColor3f(0,0,0);
for(i=0;i<k;i++)
{
glBegin(GL_QUADS);
	glVertex2i(p[i].a[0][0],p[i].a[0][1]);
	glVertex2i(p[i].a[1][0],p[i].a[1][1]);
	glVertex2i(p[i].a[2][0],p[i].a[2][1]);
	glVertex2i(p[i].a[3][0],p[i].a[3][1]);
glEnd();
}
}
