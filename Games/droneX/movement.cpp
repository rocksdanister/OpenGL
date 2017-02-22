#include <GL/glut.h>
#include <drone.h>

void processSpecialKeys(int key, int xx, int yy)
{

	int speed=40;
	switch (key) 
	{
		case GLUT_KEY_DOWN :
				movementY-=speed;
			break;
		case GLUT_KEY_UP :
				movementY+=speed;
			break;
		case GLUT_KEY_RIGHT :
				movementX+=speed;
			break;
		case GLUT_KEY_LEFT :
				movementX-=speed;
			break;
	}
}