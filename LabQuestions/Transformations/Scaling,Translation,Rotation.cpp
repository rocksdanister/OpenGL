#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
int i,n,size;
float x[5],y[5],tx,ty,sx,sy,theta;
int ch;
void draw()
{
glColor3f(1,1,1);
glBegin(GL_LINE_LOOP);
for(i=0;i<n;i++)
glVertex2f(x[i]/size,y[i]/size);
glEnd();
}


void init()
{
glClearColor(0,0,0,1);
glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_LINES);
glColor3f(1,0,0);
glVertex2f(-1,0);
glVertex2f(1,0);
glVertex2f(0,-1);
glVertex2f(0,1);
glEnd();
//glLoadIdentity();
draw();
glFlush();
glutSwapBuffers();
printf("Enter required Transformation\n 1.Translate 2.Scale 3.Rotate 4.Reflection 0.Exit\n");
scanf("%d",&ch);
    if(ch==1)
    {
    printf("Enter x & y Translate values\n");
    scanf("%f %f",&tx,&ty);
        for(i=0;i<n;i++)
        {
        x[i]+=tx;
        y[i]+=ty;
        }
    glutPostRedisplay();
    }

    if(ch==2)
    {
    printf("Enter x & y scale factors\n");
    scanf("%f %f",&sx,&sy);    
        for(i=0;i<n;i++)
        {
        x[i]*=sx;
        y[i]*=sy;        
        }   
    glutPostRedisplay();    
    }

    if(ch==3)
    {
    printf("Enter rotate Angle\n");
    scanf("%f",&theta);
    theta=(theta*3.14)/180;
 	printf("Enter wrt point?\n");
	scanf("%f %f",&tx,&ty);
	for(i=0;i<n;i++)
      	{
        x[i]-=tx;
        y[i]-=ty;
        }		
		for(i=0;i<n;i++)
        {
        x[i]=x[i]*cosf(theta)-y[i]*sinf(theta);
        y[i]=x[i]*sinf(theta)+y[i]*cosf(theta);           
        }
		for(i=0;i<n;i++)
		{
		x[i]+=tx;
		y[i]+ty;
		}
		
//    draw();
    glutPostRedisplay();
    }
	if(ch==4)
	{
	printf("Enter Choice 1. x-axis 2. y-axis 3.origin\n");
	scanf("%d",&ch);
	if(ch==1)
	{
	for(i=0;i<n;i++)
	y[i]=-1*y[i];
	
	}
	else if(ch==2)
	{
	for(i=0;i<n;i++)
	x[i]=-1*x[i];

	}
	else
	{
	for(i=0;i<n;i++)
	{
	x[i]=-1*x[i];
	y[i]=-1*y[i];
	}
	}	

	glutPostRedisplay();
	}
    if(ch==0)
    exit(0);
}


int main(int argc,char **argv)
{
size=800;
printf("Enter No: of Vertices\n");
scanf("%d",&n);
for(i=0;i<n;i++)
{
printf("Enter %d vertex points (x,y) ( %dx%d Window Size ) \n",i+1,size,size);
scanf("%f %f",&x[i],&y[i]);
}
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
glutInitWindowSize(size,size);
glutInitWindowPosition(100,100);
glutCreateWindow("Viewer");
glutDisplayFunc(init);
glutMainLoop();
return 0;
}
