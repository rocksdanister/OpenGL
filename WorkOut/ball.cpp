
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <GL/glut.h>

using namespace std;

GLdouble radius=1;
float angle = 0.0;
GLfloat light0_position[] = {0.0,0.0,1.0, 0.0};
GLfloat white[]={1.0f,1.0f,1.0f,1.f};
GLfloat objcolor[]={1.0f,0.0f,0.0f,1.f}; 

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
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objcolor);
    //glMateriali(GL_FRONT, GL_SHININESS, 100);
    glClearColor(1,1,1,1);
}


void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glRotatef(angle, 1.0, 1.0, 1.0);
    glRotatef(angle, 1.0, 0.0, 1.0 );
    glRotatef(angle, 0.0, 1.0, 1.0 );
    glTranslatef(-0.5, -1.0, 0.0);
    glScalef(.8,.8,.8);
    glutSolidSphere(radius,50,50);
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value)
{
    angle += 1.0f;
    if (angle > 360)
        angle -= 360;

    glutPostRedisplay();
    glutTimerFunc(16.66, update, 0);
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
    glutCreateWindow("Cube Animation");
    init();
    glutDisplayFunc(draw);
    glutTimerFunc(16.66, update, 0);
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(keyboard); 
    glutMainLoop();
    return 0;
}

