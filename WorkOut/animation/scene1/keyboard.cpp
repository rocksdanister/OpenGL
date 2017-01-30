#include<GL/glut.h>
#include<anime.h>
#include<math.h>

void processNormalKeys(unsigned char key, int x, int y)
{

if (key == 27)
exit(0);
}

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
