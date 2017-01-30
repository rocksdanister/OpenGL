#include<GL/glut.h>
#include<time.h>
#include<anime.h>

GLUquadric* qobj;
 int rloc,t1;
void init() // only call once on startup
{
  qobj = gluNewQuadric();
  gluQuadricNormals(qobj, GLU_SMOOTH);
}
 
void cleanup() // exit pgm
{
  gluDeleteQuadric(qobj);
}

void tree(double x,double z)
{

glPushMatrix();
 glColor3ub(34,139,34);
 glTranslatef(x,0.5,z);
 glRotatef(-90,1,0,0);
 glutSolidCone(0.5,0.6,100,100);
glPopMatrix();


glPushMatrix();
glColor3ub(178,34,34);
glTranslatef(x,0,z);
glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
gluCylinder(qobj,0.1f,0.1f,0.5f,32,32);
glPopMatrix();

}

void scene1()
{

// --------------- LIGHTING	
glEnable(GL_LIGHTING);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_LIGHT0);
glShadeModel(GL_SMOOTH);  
GLfloat light0_position[] = {-0.7,0.9,0.0, 1.0};
glLightfv(GL_LIGHT0, GL_POSITION, light0_position); 

//glNormal3d(0, 0, 1);

//---------------LIGHTING

//.....MOON
glColor3f(1.0f, 1.0f, 1.0f);
glPushMatrix();
glTranslatef(10,20,-80);
glColor3ub(224,224,224);
glutSolidSphere(6,100,100);
glPopMatrix();
//....MOON


srand(time(NULL));

//....STARS
rloc=rand()%300;

//...STARS

p=0.6;
q=0.6;
r=0.6;
 glColor3f(0.5, 0.3, 0.2);
  	//-----------CUBE
  		// FRONT
    glBegin(GL_POLYGON);
    glVertex3f(p, -q, r);
    glVertex3f(p, q, r);
    glVertex3f(-p, q, r);
    glVertex3f(-p, -q, r);
    glEnd();

        // BACK
    glBegin(GL_POLYGON);
    glVertex3f(-p, q, -r);
    glVertex3f(-p, -q, -r);
    glVertex3f(p, -q, -r);
    glVertex3f(p, q, -r);
    glEnd();

        // LEFT
    glBegin(GL_POLYGON);
    glVertex3f(-p, -q, -r);
    glVertex3f(-p, -q, r);
    glVertex3f(-p, q, r);
    glVertex3f(-p, q, -r);
    glEnd();

        // RIGHT
    glBegin(GL_POLYGON);
    glVertex3f(p, -q, -r);
    glVertex3f(p, -q, r);
    glVertex3f(p, q, r);
    glVertex3f(p, q, -r);
    glEnd();

        // TOP
    glBegin(GL_POLYGON);
    glColor3f(1,0,1);
    glVertex3f(p, q, r);
    glVertex3f(-p, q, r);
    glVertex3f(-p, q, -r);
    glVertex3f(p, q, -r);
    glEnd();

        // BOTTOM
    glBegin(GL_POLYGON);
    glVertex3f(-p, -q, -r);
    glVertex3f(-p, -q, r);
    glVertex3f(p, -q, r);
    glVertex3f(p, -q, -r);
    glEnd();

    //DOOR
    glColor3ub(51,25,0);
    glBegin(GL_POLYGON);
    glVertex3f(-p+0.4,0,r+0.01);
    glVertex3f(-p+0.4,0.3,r+0.01);
    glVertex3f(-p+0.8,0.3,r+0.01);
    glVertex3f(-p+0.8,0,r+0.01);
    glEnd();

  //-------------CUBE

   //..............ROOF
glColor3f(0.5,0,0);
// FRONT
	glBegin(GL_TRIANGLES);
	glColor3f(1,0,0);
    glVertex3f(-p, q, r);
    glVertex3f(p, q, r);
    glVertex3f(-p+0.6,q+0.5,r-0.6);
    glEnd();
//LEFT
    glBegin(GL_TRIANGLES);
    glVertex3f(-p, q, r);
    glVertex3f(-p, q, -r);
    glVertex3f(-p+0.6,q+0.5,r-0.6);
   	glEnd();
//RIGHT
    glBegin(GL_TRIANGLES);
    glVertex3f(p, q, -r);
    glVertex3f(p, q, r);
    glVertex3f(p-0.6,q+0.5,r-0.6);
   	glEnd();
//BACK
   	glBegin(GL_TRIANGLES);
   	glVertex3f(-p, q, -r);
    glVertex3f(p, q, -r);
    glVertex3f(-p+0.6,q+0.5,-r+0.6);
   	glEnd();
   	//.........ROOF
init();
double t;
//LEFT
for(t=-20;t<-0.9;t=t+1.2)
tree(t,0);	

for(t=-20;t<-0.9;t=t+1.2)
tree(t,-3);	

for(t=-20;t<-0.9;t=t+1.2)
tree(t,-8);	


//RIGHT
for(t=1.6;t<20;t=t+1.2)
tree(t,0);

for(t=1.6;t<20;t=t+1.2)
tree(t,-2);

for(t=1.6;t<20;t=t+1.2)
tree(t,-4);


//BEHIND
for(t=-0.6;t<0.6;t=t+0.9)
tree(t,-1.2);

for(t=-0.6;t<0.6;t=t+0.6)
tree(t,-2.4);

}


void draw()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
glEnable(GL_NORMALIZE);
gluLookAt(	x, 1.0f, z,
x+lx, 1.0f, z+lz,
0.0f, 1.0f, 0.0f);

glColor3ub(189, 183, 107);
glBegin(GL_QUADS);
glVertex3f(-100.0f, 0.0f, -25.0f);
glVertex3f(-100.0f, 0.0f, 100.0f);
glVertex3f( 100.0f, 0.0f, 100.0f);
glVertex3f( 100.0f, 0.0f, -25.0f);
glEnd();

glColor3ub(135,206,250);
glBegin(GL_QUADS);
glVertex3f(-100,0,-100);
glVertex3f(-100,0,-25);
glVertex3f(100,0,-25);
glVertex3f(100,0,-100);
glEnd();

scene1();

glutSwapBuffers();
}

