
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;

GLdouble radius=1;
float jj,angle = 0.0;
GLfloat light0_position[] = {0.0,0.0,5, 1.0};
GLfloat white[]={1.0f,1.0f,1.0f,1.f};
GLfloat red[]={0.9,0.1,0,1};
GLfloat objcolor[]={1.0f,0.0f,0.0f,1.0f}; 
GLfloat suncolor[]={ 0.98f, 0.834f, 0.25f ,1.0f};
GLfloat planetColor[8][3]={{0.7,0.7,0.7},
						   {1,1,0},
						   {0,0,0.8},
						   {1,0,0},
						   {0.5,0.5,0.5},
						   {0.7,0.7,0},
						   {0,0,1},
						   {0,0,0.7}
						  };
int ii;
GLfloat planetRadius[8]={0.2,0.3,0.35,0.25,0.78,0.69,0.65,0.6};
GLfloat planetAngle[8];

void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  
    glShadeModel(GL_SMOOTH); 
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position); 
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,white);
    glMateriali(GL_FRONT, GL_SHININESS, 100);
    glClearColor(0,0,0,1);
}
double rX=0;
int size;
// Rotate Y
double rY=0;
void drawCircle(float r)
{
float cx=0;
float cy=0;
int i;
int segments=100;

 glRotatef( rX, 1.0, 0.0, 0.0 );
 glRotatef( rY, 0.0, 1.0, 0.0 );
float x,y,theta;
glBegin(GL_LINE_LOOP);
for(i=0;i<segments;i++)
{
theta=2.0f*3.14f*(float)i/(float)segments;
x=r*cosf(theta);
y=r*sinf(theta);
glVertex3f(x+cx,y+cy,0);
}
glEnd();

}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    gluLookAt(0,-20,5,0.5,0.5,-0.1,0,1,0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    //glTranslatef(0.0, 0.0, -7.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,white);
    for(jj=0.5,ii=0;ii<8;ii++)
    {
    	jj+=.60;
    	drawCircle(jj);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,red);

    //.... SUN
    glScalef(.4,.4,.4);
    glutSolidSphere(radius,50,50);
    //...PLANETS
    for(jj=3,ii=0;ii<8;ii++)
    {
    	glPushMatrix();
    	glRotatef(planetAngle[ii], 0.0, 0.0, 1.0);
    	glTranslatef(jj,1,0);
    	jj+=1.5;
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,planetColor[ii]);
    	glutSolidSphere(planetRadius[ii],50,50);
    	glPopMatrix();
    }

    glPopMatrix();
    glutSwapBuffers();
}

GLfloat planetAdd[8]={0.24,0.62,1,1.00,1.32,1.55,1.88,2};
void update(int value)
{
    //angle += 1.0f;
    //if (angle > 360)
      //  angle -= 360;

	for(ii=0;ii<8;ii++)
	planetAngle[ii]+=planetAdd[ii];
    glutPostRedisplay();
    glutTimerFunc(16.67, update, 0);
}


void keyboard (unsigned char key, int x, int y)
{
 switch (key) {
      case 27:
         exit(0);
         break;
     }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("Solar System");
    init();
    glutDisplayFunc(draw);
    glutTimerFunc(16.67, update, 0);
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(keyboard); 
    glutMainLoop();
    return 0;
}
