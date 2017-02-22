#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <drone.h>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

int width, height;
static GLuint texName[3];
int movementY,movementX;
unsigned char* image;

struct obstacle
{
	int x,y;
	int type;
	int objdisp;
};

vector<obstacle> obstacleList;
obstacle obj;

#define SPACE 0
#define DRONE 1
#define CLOUD 2
#define SPACETEXTURE texName[0]
#define DRONETEXTURE texName[1]
#define CLOUDTEXTURE texName[2]

void init()
{
	glShadeModel(GL_FLAT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenTextures(3,texName); // 3 textures generated, identified by numbers stored in texName

	glBindTexture(GL_TEXTURE_2D, texName[0]);  //texture 1 active 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	image = SOIL_load_image( "res/terrains/sidescroll_lowres3.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	glBindTexture(GL_TEXTURE_2D, texName[1]);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	image = SOIL_load_image( "res/drones/black-drone.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	image = SOIL_load_image( "res/obstacles/cloud.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	glEnable(GL_TEXTURE_2D);
}

//int objX;
int worldX;
int angleRotate;
int ii;

void update()
{
	//objX-=5; 
	worldX-=5;
/*
	if(objX==-2700) // no need
		objX=0; // no need
*/
	if(worldX<-1920)
		worldX=0;

	angleRotate+=30;
	if(angleRotate>360)
		angleRotate=0;
}


void drawDrone()
{	
	printf("POSITION: %d %d \n",movementX+40,movementY+40+500);
	glBindTexture(GL_TEXTURE_2D, DRONETEXTURE); // drone texture active
	glPushMatrix();
		glTranslatef(40,500,0);
		glTranslatef(movementX,movementY,0);
		glRotatef(-angleRotate,0,0,1);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(-40,-40,-1);
			glTexCoord2f(1.0, 0.0); glVertex3f(40,-40,-1);
			glTexCoord2f(1.0, -1.0); glVertex3f(40,40,-1);                        
			glTexCoord2f(0.0, -1.0); glVertex3f(-40,40,-1);
		glEnd();
	glPopMatrix();
}

void drawObstacle(int posx,int posy, int type,int objX)
{
	glBindTexture(GL_TEXTURE_2D, CLOUDTEXTURE);
	glPushMatrix();
		glTranslatef(posx,posy,0);
		glTranslatef(objX,0,0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(0,0,-1);
			glTexCoord2f(1.0, 0.0); glVertex3f(200,0,-1);
			glTexCoord2f(1.0, -1.0); glVertex3f(200,100,-1);                                
			glTexCoord2f(0.0, -1.0); glVertex3f(0,100,-1);
		glEnd();
	glPopMatrix();
}
int temp=0;

void hitDetection()
{


	for(ii=0;ii<obstacleList.size();ii++)
	{

			//printf("HIT:%d %d \n",abs((movementX+40)-(obstacleList[ii].x+100+obstacleList[ii].objdisp)),abs((movementY+40+500)-(obstacleList[ii].y+50)));
		if(	((abs((movementX+40)-(obstacleList[ii].x+100+obstacleList[ii].objdisp)))<=100) && (abs((movementY+40+500)-(obstacleList[ii].y+50))<=90))
		{
			printf("HIT:%d %d \n",abs((movementX+40)-(obstacleList[ii].x+100+obstacleList[ii].objdisp)),abs((movementY+40+500)-(obstacleList[ii].y+50)));
			exit(0);
		}
	}


}

void draw()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	//top score bar, will check it later
	glBegin(GL_QUADS);
		// glColor3f(0.5,0.5,0.5);
		glVertex3f(0,1080,-1);
		glVertex3f(1920,1080,-1);
		glVertex3f(1920,1040,-1);
		glVertex3f(0,1040,-1);
	glEnd();
	*/
	glBindTexture(GL_TEXTURE_2D, SPACETEXTURE); // world texture active
	glPushMatrix();
		glTranslatef(worldX,0,0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(0,0,-1.1);
			glTexCoord2f(1.0, 0.0); glVertex3f(3840,0,-1.1);
			glTexCoord2f(1.0, -1.0); glVertex3f(3840,1080,-1.1);                        
			glTexCoord2f(0.0, -1.0); glVertex3f(0,1080,-1.1);
		glEnd();
	glPopMatrix();
	
	drawDrone();

	/*  
	for(obstacle &obj : obstacleList)
	{
		obj.objdisp-=5;
		if(obj.objdisp==-2700)
			obstacleList.pop_back();
		else
		{
		drawObstacle(obj.x, obj.y, obj.type,obj.objdisp);
		//obstacleList.pop_back();
		obstacleList.push_back(obj);
		}

	}
	*/

	for(ii=0;ii<obstacleList.size();ii++)
	{
		obstacleList[ii].objdisp-=5;
		if (obstacleList[ii].objdisp==-2750)
		{
			obstacleList.erase(obstacleList.begin()+ii);
		}
		else
		{
		drawObstacle(obstacleList[ii].x, obstacleList[ii].y, obstacleList[ii].type,obstacleList[ii].objdisp);
		}
	}

	if(temp==100)
	{
		temp=0;
		int tx= 2000+(rand()%600);
		int ty= rand()%950;
		obj.x=tx;
		obj.y=ty;
		obj.type= CLOUD;
		obj.objdisp=0;
		obstacleList.push_back(obj);
	}
	else
	{
		temp++;
	}
	hitDetection();
	glutSwapBuffers();
}
