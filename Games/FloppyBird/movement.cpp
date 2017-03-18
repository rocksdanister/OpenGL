#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <floppy.h>
using namespace std;

vector<char> inputKey; 
double g,v;
int cnt;
void movePhysics()
{
int ii;
g=9.8;
for(ii=0;ii<inputKey.size();ii++)	
	{
		if(inputKey[ii]=='U')
			{
				if((movementY+(resY/2)+50)<resY)
				movementY+=4;
				cnt++;
			}	
		if(cnt==10)
			{	
				cnt=0;	
				inputKey.erase(inputKey.begin()+ii);
			}	
		
	}
//...GRAVITY
if(inputKey.size()==0)
{
v=0.5;
movementY-= v*v/2*g;
}

}

void processSpecialKeys(int key, int xx, int yy)
{
	int speed=40;
	switch (key) 
	{
		case GLUT_KEY_UP :
				inputKey.push_back('U');
			break;
	}
}