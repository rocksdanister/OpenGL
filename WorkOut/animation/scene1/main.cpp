#include<GL/glut.h>
#include<anime.h>

float lx=0.0f,lz=1.0f,x=0.0f,z=5.0f,angle=0.0f;
double p,q,r;
void handleResize(int w, int h)
{

if (h == 0)
h = 1;
float ratio = w * 1.0 / h;

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0, 0, w, h);
gluPerspective(45.0f, ratio, 1.0f, 100.0f);
glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(700,700);
glutCreateWindow("Scene1");
glutDisplayFunc(draw);
glutReshapeFunc(handleResize);
glutIdleFunc(draw);
glutKeyboardFunc(processNormalKeys);
glutSpecialFunc(processSpecialKeys);
glEnable(GL_DEPTH_TEST);
glutMainLoop();

return 1;
}
