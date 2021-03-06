
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
GLfloat planetColor[8][3]={		    
					       {0.7,0.7,0.7},
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
int planetPeriod[8];

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
    //glMateriali(GL_FRONT, GL_SHININESS, 100);
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

GLvoid *font_style = GLUT_STROKE_ROMAN;
void renderStrokeFont(int x,int y,int z,const char* temp,float s)
{
  glPushMatrix();
  glTranslatef(x,y,z);
  //glLineWidth(2);
  glScalef(s,s,s);
  const char *c;
  
  for (c=temp; *c != '\0'; c++) {
    glutStrokeCharacter(font_style, *c);
  }
  glPopMatrix();
}

void drawString()
{

	gluLookAt(0,-20,15,0,0,0,0,1,0);
	string str="Solar System Simulation";
	const char * c1=str.c_str();
	renderStrokeFont(-9,7,0,c1,0.01);
	string str2="Orbital Periods: "+to_string(planetPeriod[0])+"  "+to_string(planetPeriod[1])+"  "+to_string(planetPeriod[2])+"  "+to_string(planetPeriod[3])+"  "+to_string(planetPeriod[4])+"  "+to_string(planetPeriod[5])+"  "+to_string(planetPeriod[6])+"  "+to_string(planetPeriod[7]);
	const char * c2 = str2.c_str();
	renderStrokeFont(-6,-7,0,c2,0.003);
	glLoadIdentity();
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
     //...TEXT 
    drawString();
	//...RENDER
    gluLookAt(0,-16,5,0.5,0.5,-0.1,0,1,0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,white);

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

GLfloat planetAdd[8]={82,27.33,16.4,8.631,1.378,1.798,0.195,0.1};
/* .. PLANET ORBITAL PERIOD
Mercury: 87.97 days (0.2 years)
Venus : 224.70 days (0.6 years)
Earth: 365.26 days(1 year)
Mars: 686.98 days(1.9 years)
Jupiter: 4,332.82 days (11.9 years)
Saturn: 10,755.70 days (29.5 years)
Uranus: 30,687.15 days (84 years)
Neptune: 60,190.03 days (164.8 years)

For Earth, Divide 360/60*60, i.e 360 degree= 1 revolution in 60no of 60frames,it gives 16.4, then divide it
by the number of years for each planet, e.g Neptune =16.4/164=>0.1
*/

void update(int value)
{

	for(ii=0;ii<8;ii++)
    {
	planetAngle[ii]+=planetAdd[ii];
		if(planetAngle[ii]>360)
		{
		planetAngle[ii]=0;
		planetPeriod[ii]++;
		}
    }
    glutPostRedisplay();
    glutTimerFunc(66.66, update, 0);
}


void keyboard (unsigned char key, int x, int y)
{
 switch (key) {
      case 27: //ESC for EXIT
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
    glutTimerFunc(66.66, update, 0);  // 15fps
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

