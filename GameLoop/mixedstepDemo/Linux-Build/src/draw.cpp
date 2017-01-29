#include <GL/glut.h>
#include<myheader.h>

double queuedMilliseconds=0;
GLdouble radius=1;
float angle = 0.0;


void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(angle, 1.0, 1.0, 1.0);
    glRotatef(angle, 1.0, 0.0, 1.0 );
    glRotatef(angle, 0.0, 1.0, 1.0 );
    glTranslatef(-0.5, -1.0, 0.0);
    glScalef(.8,.8,.8);
    //draw sphere
    glColor3f(.8, 0.0, 0.0);
    glutSolidSphere(radius,20,20);
    glutSwapBuffers();
}

void update()
{
    angle += 1.0f;
    if (angle > 360)
        angle -= 360;
}

void mixedStepLoop()
{
    double now = glutGet(GLUT_ELAPSED_TIME);
    double timeElapsedMs =(now-prev);
    queuedMilliseconds += timeElapsedMs ;
    if(fps<0)
    {
	//update();  WARNING, will cause seizures and or nausea depending on the person since fast animation/color changes.  
        draw();
    }
    while(queuedMilliseconds >= responseTime) 
    {
        update();
        queuedMilliseconds -= responseTime;
        if(fps>0)
            glutPostRedisplay();
    }
    prev=now;
}



