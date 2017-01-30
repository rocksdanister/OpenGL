#include<myheader.h>
#include<GL/glut.h>

void keyboard(int key,int x,int y)
{
    if (key == GLUT_KEY_RIGHT)
        {
                p1+=5;
	
        }
    else if (key == GLUT_KEY_LEFT)
        {
               // p1-=5;
     	
	   }
    else if (key == GLUT_KEY_DOWN)
        {
                q-=5;
        }	
    else if (key == GLUT_KEY_UP)
        {
                q+=5;
      	}
	else if(key==GLUT_KEY_F1)
	{
		t=0;
		q=0;
		p1=0;
	}
	else if(key==GLUT_KEY_F2)
	{
	p1=0;
	q=0;	
	}

}

