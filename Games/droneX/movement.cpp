#include <GL/glut.h>
#include <drone.h>

void processSpecialKeys(int key, int xx, int yy)
{

	int speed=40;
	switch (key) 
	{
		case GLUT_KEY_DOWN :
				if(movementY!=-440)
				movementY-=speed;
			break;
		case GLUT_KEY_UP :
				if(movementY!=440)
				movementY+=speed;
			break;
		case GLUT_KEY_RIGHT :
				if(movementX!=1840)
				movementX+=speed;
			break;
		case GLUT_KEY_LEFT :
				if(movementX!=0)
				movementX-=speed;
			break;
	}
}