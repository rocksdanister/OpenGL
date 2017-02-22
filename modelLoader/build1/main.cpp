
#include<GL/glut.h>
#include<stdio.h>
#include<myheader.h>

struct data p[100000];
struct data_temp q[1000000];
int vindex,vnindex,vtindex;
double queuedMilliseconds,prev0,fps,responseTime;
GLuint dlist;

void initialSetup()
{

	system("cp porschefix.obj temp.obj");
}


void handleResize(int w,int h)
{
    glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();  
	glViewport(0,0,w,h);
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1, 1000.0);
	glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();

}


int main(int argc, char** argv)
{
	//..gameLoop setup
	queuedMilliseconds=0;
	prev0=0;
	fps=60;
	responseTime=(1/fps)*1000;

initialSetup();
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
glutInitWindowSize(800,800);
glutInitWindowPosition(100,100);
glutCreateWindow("OBJ Loader");
glutReshapeFunc(handleResize);
glutDisplayFunc(draw);
glutIdleFunc(mixedStepLoop);
glutSpecialFunc(processSpecialKeys);
glEnable(GL_DEPTH_TEST);
glutMainLoop();
}

