#include <iostream>
#include <stdlib.h>
#include<time.h>
#include<stdio.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;
int a,b,c,d,e,f,g,h,i;
//a=-2;b=-2;c=4;d=0;e=0;f=0;g=0;h=1;i=0;
double queuedMilliseconds,prev,fps,responseTime;
double xmo=0;
double s;
int flag=0;

void crackDamage()
{
	glLoadIdentity();
	glPointSize(20);
	glColor3f(0,0,0);
	glBegin(GL_POINTS);
	glVertex3f(598,275,-1.5);
	glEnd();

/*
glBegin(GL_LINES);
glVertex3f(598);
glVertex3f(598);
glEnd();

*/
}


void drawCube()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

       // glTranslatef(.4, 0.0, 0);
     // gluLookAt(a,b,c,d,e,f,g,h,i);
        // Add an ambient light
        /*
        GLfloat ambientColor[] = {0.2, 0.2, 0.2, 1.0};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
*/
        // Add a positioned light
        /*
        GLfloat lightColor0[] = {0.5, 0.5, 0.5, 1.0};
        GLfloat lightPos0[] = {4.0, 0.0, 8.0, 1.0};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
        */

      //  glTranslatef(0.5, 1.0, 0.0);
      //  glRotatef(angle, 1.0, 1.0, 1.0);

    //	glRotatef( angle, 1.0, 0.0, 1.0 );
  	  //  glRotatef( angle, 0.0, 1.0, 1.0 );
      //  glTranslatef(-0.5, -1.0, 0.0);

        // Create the 3D cube

   		 // BACK
 	   glBegin(GL_POLYGON);
	   glColor3f(1, 0, 0);
	   glVertex3f(650/s, 200/s, -1);
	   glVertex3f(650/s, 600/s, -1);
	   glVertex3f(650/s, 600/s,-2);
 	   glVertex3f(650/s, 200/s,-2);
 	   glEnd();

        // FRONT
        glBegin(GL_POLYGON);
        glColor3f(0, 0, 1);
        glVertex3f(600/s, 200/s, -1);
        glVertex3f(600/s, 600/s, -1);
        glVertex3f(600/s, 600/s, -2);
        glVertex3f(600/s, 200/s, -2 );
        glEnd();

        // LEFT
        glBegin(GL_POLYGON);
        glColor3f(0, 0, 1);
        glVertex3f(600/s, 200/s, -2);
        glVertex3f(650/s, 200/s, -2);
        glVertex3f(650/s, 600/s, -2);
        glVertex3f(600/s, 200/s, -2);
        glEnd();


        // RIGHT
        glBegin(GL_POLYGON);
        glColor3f(0, 1, 0);
        glVertex3f(600/s, 200/s, -1);
        glVertex3f(650/s, 200/s, -1);
        glVertex3f(650/s, 600/s, -1);
        glVertex3f(600/s, 600/s, -1);
        glEnd();

        // TOP
        glBegin(GL_POLYGON);
        glColor3f(0, 0, 0);
        glVertex3f(600/s, 600/s, -1);
        glVertex3f(650/s, 600/s, -1);
        glVertex3f(650/s, 600/s, -2);
        glVertex3f(600/s, 600/s, -2);
        glEnd();


        // BOTTOM
        glBegin(GL_POLYGON);
        glColor3f(1, 0, 0);
        glVertex3f(600/s,200/s, -2);
        glVertex3f(650/s, 200/s, -2);
        glVertex3f(650/s, 200/s, -1);
        glVertex3f(600/s, 200/s, -1);
        glEnd();


glLoadIdentity();
glColor3f(.5,.5,.5);
glTranslatef(0+xmo,0,-1.5);

glBegin(GL_TRIANGLES);
glVertex3f(20,250,0);
glVertex3f(20,300,0);
glVertex3f(40,275,0);
glEnd();
glBegin(GL_POLYGON);
glVertex3f(20,250,0);
glVertex3f(20,300,0);
glVertex3f(5,300,0);
glVertex3f(5,250,0);

glEnd();
if(flag==1)
		crackDamage();
/*
glBegin(GL_TRIANGLES);
glColor3f(.5,.5,.5);
glVertex3f(10,250,0);
glVertex3f(10,260,-2);
glVertex3f(20,260,0);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(.5,.5,.5);
glVertex3f(10,270,0);
glVertex3f(10,260,-2);
glVertex3f(20,260,0);
glEnd();
*/
//glEnable(GL_AUTO_NORMAL) ;
   
   // glTranslatef(0, 0.0, -100.0);
        
        //glLoadIdentity();
      // gluLookAt(a,b,c,d,e,f,g,h,i);
/*
		 glTranslatef(0, 0,-2);
      //glScalef(0.06,.06,.06);
    //draw sphere
  	  glColor3f(1.0, 0.0, 0.0);
   	  glutSolidSphere(20,10,10);
    */

      glFlush();
    glutSwapBuffers();
}


void update()
{
	if(xmo<=595)
    xmo+=10; 
	else
		flag=1;
	
        
}


void initRendering()
{
        glEnable(GL_DEPTH_TEST);
       // glEnable(GL_COLOR_MATERIAL);
        glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
        glEnable(GL_AUTO_NORMAL) ;
        //glEnable(GL_LIGHTING);
        //glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
}



void handleResize(int w, int h)
{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
      // gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
        glFrustum(-100,700,-100,700,1,100);
        //glOrtho(0,700,0,700,1,100);
}

void mixedStepLoop()
{
double now = glutGet(GLUT_ELAPSED_TIME);
double timeElapsedMs =(now-prev);
queuedMilliseconds += timeElapsedMs ;

while(queuedMilliseconds >= responseTime) {
	update();
        queuedMilliseconds -= responseTime;
	if(fps>0)
	glutPostRedisplay();
	}
prev=now;
}


void processMenuEvents(int options){
switch(options){
case 1:fps=60;
	responseTime=(1/fps)*1000;
	break;
case 2:fps=30;
	responseTime=(1/fps)*1000;
	break;
case 3:fps=12;
	responseTime=(1/fps)*1000;
	break;
case 4: fps=-1;
	break;
}
}


void createGLUTMenus()
{
int menu;
menu=glutCreateMenu(processMenuEvents);
glutAddMenuEntry("60fps",1);
glutAddMenuEntry("30fps",2);
glutAddMenuEntry("24fps",3);
glutAddMenuEntry("Nocap",4);
glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void keyboard(unsigned char key,int x,int y)
{

      if (key ==113 )
      a++;
      else if(key==97)
      a--;
      else  if (key ==119)
      b++;
      else if(key==115)
      b--;
      else  if (key == 101)
      c++;
      else if(key==100)
      c--;
      else  if (key == 114)
      d++;
      else if(key==102)
      d--;
      else  if (key == 116)
      e++;
      else if(key==103)
      e--;
      else  if (key == 121)
      f++;
      else if(key==104)
      f--;
      else  if (key ==117)
      g++;
      else if(key==106)
      g--;
      else  if(key == 105)
      h++;
      else if(key==107)
      h--;
      else  if(key == 111)
      i++;
      else if(key==108)
      i--;
      system("clear");
      //system("");
      printf("BACK: red FRONT: green LEFT: blue RIGHT:white TOP:black BOTTOM:yellow \n");
      printf("\neyeX\teyeY\teyeZ\tcenterX\tcenterY\tcenterZ\tupX\tupY\tupZ\t\n");
      printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",a,b,c,d,e,f,g,h,i);
}

int main(int argc, char **argv)
{
 a=0;b=0;c=0;d=0;e=0;f=0;h=0;i=0;
//	a=-2;b=-2;c=4;d=0;e=0;f=0;g=0;h=1;i=0;
	queuedMilliseconds=0;
	s=1;
	prev=0;
	fps=30;
	responseTime=(1/fps)*1000;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Test v1");
    initRendering();
    glutDisplayFunc(drawCube);
	  glutIdleFunc(mixedStepLoop);
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(keyboard);
    //createGLUTMenus();
    glutMainLoop();
    return 0;
}
