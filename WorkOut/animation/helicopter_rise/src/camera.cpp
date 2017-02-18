#include<GL/glut.h>
#include <math.h>
#include<myheader.h>


float lx=0.0f,lz=-1.0f;

float x=0.0f,z=5.0f;

float angle = 0.0f;

void processSpecialKeys(int key, int xx, int yy)
{

float fraction = 0.1f;

switch (key) {
case GLUT_KEY_LEFT :
angle -= 0.01f;
lx = sin(angle);
lz = -cos(angle);
break;
case GLUT_KEY_RIGHT :
angle += 0.01f;
lx = sin(angle);
lz = -cos(angle);
break;
case GLUT_KEY_UP :
x += lx * fraction;
z += lz * fraction;
break;
case GLUT_KEY_DOWN :
x -= lx * fraction;
z -= lz * fraction;
break;
}
}
