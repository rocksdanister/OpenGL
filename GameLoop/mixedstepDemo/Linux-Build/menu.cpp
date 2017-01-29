#include<myheader.h>
#include<GL/glut.h>

void processMenuEvents(int options){
    switch(options)
    {
        case 1:
        {
            fps=60;
            break;
        }
        case 2:
        {
            fps=30;
            break;
        }
        case 3:
        {
            fps=24;
            break;
        }
        case 4:
        { 
            fps=-1;
            break;
        }
    }
    if(fps!=-1)
        responseTime=(1/fps)*1000;
}


void createGLUTMenus()
{
    int menu;
    menu=glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("60fps",1);
    glutAddMenuEntry("30fps",2);
    glutAddMenuEntry("24fps",3);
    glutAddMenuEntry("Nocap(physics locked)",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

