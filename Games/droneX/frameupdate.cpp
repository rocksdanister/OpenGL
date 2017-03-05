#include <GL/glut.h>
#include <drone.h>

void mixedStepLoop()
{
    double now = glutGet(GLUT_ELAPSED_TIME);
    double timeElapsedMs =(now-prev0);
    queuedMilliseconds += timeElapsedMs ;
    while(queuedMilliseconds >= responseTime) 
    {
        update();
        queuedMilliseconds -= responseTime;
        glutPostRedisplay();
    }
    score+=(timeElapsedMs/1000);
    prev0=now;
}

