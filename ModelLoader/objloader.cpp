#include<GL/glut.h>
#include<stdio.h>

GLfloat angle;

void drawOBJ(char *fname)
{
 FILE *fp;
 int length;
 GLfloat x, y, z;
 fp=fopen(fname,"r");
 char ch;
 glPointSize(2.0);
 glPushMatrix();
 glBegin(GL_POINTS);
 	while(!(feof(fp)))
 	{
 		length=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
 		if(length==4&&ch=='v')
 		{
 			glVertex3f(x,y,z);
 		}
 	}
 glEnd();
 glPopMatrix();
 fclose(fp);
}

void draw()
{
    glClearColor (0.0,0.0,0.0,1.0); 
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
     glTranslatef(0,-50,-150);
     glScalef(0.1,0.1,0.1);
     glRotatef(angle,0,1,0);
     drawOBJ("object.obj");
     angle=angle+0.5;
     if(angle>360)
    	angle=0;
     glPopMatrix();
    glutSwapBuffers();
 
}

void handleResize(int w,int h)
{
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    glViewport(0,0,w,h);
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1, 500);
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();

}

int main(int argc, char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
glutInitWindowSize(800,800);
glutInitWindowPosition(100,100);
glutCreateWindow("OBJ Loader");
glutReshapeFunc(handleResize);
glutDisplayFunc(draw);
glutIdleFunc(draw);
glutMainLoop();
}
