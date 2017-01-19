#include <iostream>
#include <stdlib.h>
#include<time.h>
#include<stdio.h>
#include <GL/glut.h>
#include<string.h>

using namespace std;
double queuedMilliseconds,prev,fps,responseTime;
double xmo=0;
double s;
int flag=0;
/*
//ARAVIND
int m, top=-1, arr[10][10], ar[10], sta[10], i, j, k=0, l;
void push(int m){
	sta[++top]=m;
}
int pop(){
	int item = sta[top--];
	printf("%d ", item);
	return item;
}

//ARAVIND
*/

/*

//FONT
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_10;

void setfont(char* name, int size)
{
	font_style = GLUT_BITMAP_HELVETICA_10;
	if (strcmp(name, "helvetica") == 0) {
		if (size == 12) 
			font_style = GLUT_BITMAP_HELVETICA_12;
		else if (size == 18)
			font_style = GLUT_BITMAP_HELVETICA_18;
	} else if (strcmp(name, "times roman") == 0) {
		font_style = GLUT_BITMAP_TIMES_ROMAN_10;
		if (size == 24)
			font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	} else if (strcmp(name, "8x13") == 0) {
		font_style = GLUT_BITMAP_8_BY_13;
	} else if (strcmp(name, "9x15") == 0) {
		font_style = GLUT_BITMAP_9_BY_15;
	}
}


void drawstr(GLuint x, GLuint y, const char* format, int length)
{
	glRasterPos2i(x, y);	
	for(int i=0; i<length; ++i)
		glutBitmapCharacter(font_style, *(format+i) );
}

*/

void drawCircle(int x,int y)
{
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1,1,1);
        glTranslatef(x,y,-1);
        glutSolidSphere(50,100,100);
   	    
}

void draw()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawCircle(100,100);
    glFlush();
    glutSwapBuffers();
}



void initRendering()
{
        //glEnable(GL_DEPTH_TEST);
        glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
       // glEnable(GL_AUTO_NORMAL) ;
        //glEnable(GL_LIGHTING);
        //glEnable(GL_LIGHT0);
      //  glEnable(GL_NORMALIZE);
}



void handleResize(int w, int h)
{
       glViewport(0, 0, w, h);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
      // gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
       // glFrustum(-100,700,-100,700,1,100);
       glOrtho(0,700,0,700,1,100);
}


int main(int argc, char **argv)
{
	/*
//ARAVIND
	
printf("Enter the no. of vertices\n");
scanf("%d",&m);
printf("\nEnter adjacency matrix\n");
	for(i=0;i<m;i++)
		for(j=0;j<m;j++)
			scanf("%d",&arr[i][j]);
	printf("\nAdjacency Matrix is :\n");
	for(i=0;i<m;i++){
		printf("\n");
		for(j=0;j<m;j++)
			printf("%d ",arr[i][j]);
	}
	printf("\n\nDFS : ");
	push(0);
	int flag = 0;
	while(top!=-1){
		i = pop();
		ar[k++] = i;
		for(j=0;j<m;j++){
			for(l=0;l<m;l++){
				if(j==ar[l]){
					flag=1;
					break;
				}
			}
			if(flag == 0){
				if(arr[i][j] == 1)
					push(j);
			}
			flag = 0;
		}
	}
	printf("\n");

//ARAVIND
*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DFS");
    initRendering();
    glutDisplayFunc(draw);
	//glutIdleFunc(mixedStepLoop);
    glutReshapeFunc(handleResize);
    glutMainLoop();
    return 0;
}
