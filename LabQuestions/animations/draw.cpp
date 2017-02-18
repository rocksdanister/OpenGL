#include<GL/glut.h>
#include<stdio.h>
#include<myheader.h>
#include<math.h>
int opt2;

GLfloat angleR;
GLfloat rateT;
int rateFix;
float ht;
void update()
{
	if(rateFix==0)
	{
	rateT+=0.05;
	}
	angleR=angleR+rateT;

    if(angleR>360)
    {
      angleR=0;
      rateFix=1;
      rateT+=0.2;
    }

    if(rateFix==1)
    {	
    	if(ht<3.5)
    	ht+=0.01;
    }
}

GLfloat objcolor[]={0.5f,0.5f,0.5f,1.f}; 
GLfloat white[]={1.0f,1.0f,1.0f,1.f};


float diffuseLight[] =
{ 0.8f, 0.8f, 0.8f, 1.0f };
float specularLight[] =
{ 1.0f, 1.0f, 1.0f, 1.0f };
float LightPosition[] =
{ 0.0f, 20.0f, 2.0f, 1.0f };
float local_view[] =
{ 0.0 };
 

void OnInit()
{
 
  glEnable(GL_LIGHTING); // Enable lighting.
 glShadeModel(GL_SMOOTH); 
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glClearDepth(1.0f);
 
  // Set light information
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
  glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
 
  // Enable light
  glEnable(GL_LIGHT0);
 
  // Set up the material information for objects
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, objcolor);
  glMateriali(GL_FRONT, GL_SHININESS, 128);
}
 
void deleteInitial()
{
system("rm temp.obj temp2.obj");
}

void draw()
{
/*
 // --------------- LIGHTING 
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glShadeModel(GL_SMOOTH);  
GLfloat light0_position[] = {0,0,10.0, 0.0};
glLightfv(GL_LIGHT0, GL_POSITION, light0_position); 
glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objcolor);
//---------------LIGHTING

*/
	if(opt2!=1)
  {
    OnInit();
    opt2=1;
    glClearColor (0.0,0.0,0.0,1.0); 
   	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(  x, 1.0f, z,
				x+lx, 1.0f, z+lz,
				0.0f, 1.0f, 0.0f);

   	glPushMatrix();
    initialOBJ(0);
    initialOBJ(1);
    objDraw(0);
    objDraw(1);
    deleteInitial();
    optimisationList();
    optimisationList2();
   	glPopMatrix();
   	glutSwapBuffers();
 	}
  else
  {

    glClearColor (0.0,0.0,0.0,1.0); 
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

lx = sin(-0.4);
lz = -cos(-0.4);

    gluLookAt(  x+3.5, 1.0f, z+3.5,
        x+lx+3.5, 1.0f, z+lz+3.5,
        0.0f, 1.0f, 0.0f);
glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -25.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f( 100.0f, 0.0f, 100.0f);
	glVertex3f( 100.0f, 0.0f, -25.0f);
	glEnd();
	
	glPopMatrix();
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0,ht,1);
     glRotatef(-120,0,1,0);
    glCallList(dlist);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,ht,1);
    glRotatef(angleR,0,1,0);
    glTranslatef(0,1.5,0);
    glCallList(dlist2);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
  }

}

