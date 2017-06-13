#include <GL/freeglut.h>

using namespace std;

float lightval[2][3]={
					{0,0,0},
					{0,0,0}

};

int input[][2]={
				{400,10}, // side 1 (front)
				{425,10},
				{425,110},
				{400,110},
				{380,20}, //2
				{400,10},
				{400,110},
				{380,120},
				{380,20},   //3
				{405,20},
				{405,120},
				{380,120},
				{425,10},  //4
				{405,20},
				{405,120},
				{425,110},
};

void init()
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);  // Default is smooth, not required.
	glClearColor(1,1,1,1);

}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );

	glBegin(GL_QUADS);
	for(int i=0;i<16;i++)
	{
		if(i%4==0)    // for smooth shading effect
			glColor3f(0.3,0.3,0.3);  
		else
			glColor3f(0.5,0.5,0.5);
		glVertex3i(input[i][0],input[i][1]*2,-200);
	}
	glEnd();

	glPushMatrix();
	glColor3fv(lightval[0]);
	glTranslatef(390,200,1);
	glutSolidSphere(8,110,110);  //L1 (top)
	glTranslatef(0,-30,0);
	glColor3fv(lightval[1]);
	glutSolidSphere(8,110,110);  //L2
	glPopMatrix();

	glutSwapBuffers();
}

int timer,flag;
void update(int j)
{	
	timer++;
	if(timer>50)
	{
		timer=0;
		if(flag==0)  //L1
		{
		lightval[1][1]=0.0;
		lightval[0][0]=1.0;
		flag=1;
		}
		else
		{
		lightval[0][0]=0.0;	
		lightval[1][1]=1.0;
		flag=0;
		}
	}

	glutPostRedisplay();
    glutTimerFunc(16.65, update, 0);

}

void handleResize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();   
    glViewport(0,0,w,h);
    glOrtho(0.0,w,0.0,h,-1,400); 
    glMatrixMode(GL_MODELVIEW); 
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,400);
	glutCreateWindow("Street Light");
	init();
	glutDisplayFunc(draw);
	glutTimerFunc(16.65,update,0); // 60fps
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}
