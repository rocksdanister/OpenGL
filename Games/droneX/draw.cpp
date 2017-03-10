#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <drone.h>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

GLuint dlist[2];
int width, height,tx,ty;
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/terrains/sidescroll.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	glBindTexture(GL_TEXTURE_2D, texName[1]);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/drones/black-drone.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/obstacles/cloud.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	glEnable(GL_TEXTURE_2D);
}

int worldX;
int angleRotate;
int ii;

void update()
{

	worldX-=5;
	if(worldX<-1920)
		worldX=0;

	angleRotate+=30;
	if(angleRotate>360)
		angleRotate=0;
}

void drawObstacle(int posx,int posy, int type,int objX)
{
	//printf("Obstacle: %d\n",posy);
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

		if(((abs((movementX+40)-(obstacleList[ii].x+100+obstacleList[ii].objdisp)))<=100) && (abs((movementY+500)-(obstacleList[ii].y+50))<=90))
		{
		//printf("\t\tHIT:%d %d %d %d \n",abs((movementX+40)-(obstacleList[ii].x+100+obstacleList[ii].objdisp)),abs((movementY+500)-(obstacleList[ii].y+50)),(movementY+500),(obstacleList[ii].y+50));
		printf("\t\tYOUR SCORE: %f \n",score);
		exit(0);
		}
	}


}

void initialiseList()
{
dlist[0]=glGenLists(1);
dlist[1]=glGenLists(1);
}

void staticBackground()
{

glNewList(dlist[0], GL_COMPILE);

glBindTexture(GL_TEXTURE_2D, SPACETEXTURE); // world texture active
	//glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(0,0,-1.1);
			glTexCoord2f(1.0, 0.0); glVertex3f(3840,0,-1.1);
			glTexCoord2f(1.0, -1.0); glVertex3f(3840,1080,-1.1);                        
			glTexCoord2f(0.0, -1.0); glVertex3f(0,1080,-1.1);
		glEnd();
	//glPopMatrix();

glEndList();
}

void staticDrone()
{

glNewList(dlist[1], GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D, DRONETEXTURE); // drone texture active
	//glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(-40,-40,-1);
			glTexCoord2f(1.0, 0.0); glVertex3f(40,-40,-1);
			glTexCoord2f(1.0, -1.0); glVertex3f(40,40,-1);                        
			glTexCoord2f(0.0, -1.0); glVertex3f(-40,40,-1);
		glEnd();
	//glPopMatrix();

glEndList();
}

GLvoid *font_style = GLUT_STROKE_ROMAN;

void renderStrokeFont(int x,int y,int z,const char* temp)
{
  glPushMatrix();
  glTranslatef(x,y,z);
  glLineWidth(10);
  glScalef(0.8,0.8,0.8);
  const char *c;
  
  for (c=temp; *c != '\0'; c++) {
    glutStrokeCharacter(font_style, *c);
  }

  glPopMatrix();
}


int opt1;
void draw()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(opt1==0)
	{
	initialiseList();
	staticBackground();
	staticDrone();
	opt1=1;
	}
	else
	{
	//...WORLD	
	glPushMatrix();
	glTranslatef(worldX,0,0);
	glCallList(dlist[0]);
	glPopMatrix();

	//TOP-SCORE BAR
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glVertex3f(0,1000,3);
	glVertex3f(1920,1000,3);
	glVertex3f(1920,1080,3);
	glVertex3f(0,1080,3);
	glEnd();
	glPopMatrix();

	//...SCORE
	glColor3f(0,0,0);
	int tempscore;
	tempscore=score;
	string str="SCORE: "+to_string(tempscore);
	const char * c = str.c_str();
	renderStrokeFont(100,1000,3,c);

	// OBSTACLES
	glColor3f(1,1,1);
	for(ii=0;ii<obstacleList.size();ii++)
	{
		obstacleList[ii].objdisp-=5;
		if (obstacleList[ii].objdisp==-2750)
		{
			obstacleList.erase(obstacleList.begin()+ii);
		}
		else
		{
		//..OBSTACLES	
		drawObstacle(obstacleList[ii].x, obstacleList[ii].y, obstacleList[ii].type,obstacleList[ii].objdisp);
		}
	}

	if(temp==50)
	{
		temp=0;
		tx= 2000+(rand()%600);
		ty= rand()%900;
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
	
	//..DRONE
	glPushMatrix();
	glTranslatef(40,500,0);
	glTranslatef(movementX,movementY,0);
    glRotatef(-angleRotate,0,0,1);
	glCallList(dlist[1]);
	glPopMatrix();
	hitDetection();
	}	
	glutSwapBuffers();
}
