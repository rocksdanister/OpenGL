#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <GL/glut.h>
#include<unistd.h>  

using namespace std;
struct lis{
	int data;
	lis *ptr;
};

class vert
{
	public:
	int x,y;
	int data;
	double color;
};

vert *V;
int i,j,N,wx,hy;
lis *node;
lis *temp;
lis *Q[20];
int flag=0;

void drawCircle(double a,int x,int y)
{
	glLoadIdentity();  // refresh modelView matrix 
        glColor3f(a,a,a);
        glTranslatef(x,y,-1);
        glutSolidSphere(30,100,100);
   	    
}

void connectGraph(int a,int b)
{
glLoadIdentity();
glColor3f(0,0,0);
glBegin(GL_LINES);
glVertex3f(V[a].x,V[a].y,-80);  // Line is drawn behind sphere in 3D
glVertex3f(V[b].x,V[b].y,-80);
glEnd();

}

void draw();

void DFS_VISIT(int a,vert V[],lis *Q[])
{
	lis *temp1;
	V[a].color=0.5;
	cout<<"Node "<<V[a].data<<" is gray\n";
	//getchar();
	draw();
	sleep(3);  // wait for animation.
	temp1=Q[a]->ptr;
	while(temp1!=NULL)
	{
		if(V[(temp1->data)-1].color==1)
		{
			
			DFS_VISIT((temp1->data)-1,V,Q);
		}
		temp1=temp1->ptr;
	}
	V[a].color=0;
	cout<<"Node "<<V[a].data<<"  is black\n";
	draw();
	sleep(3);
}



void draw()
{
	glEnable(GL_DEPTH_TEST);  // Enable hidden surface elimination in 3D
    glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(i=0;i<N;i++)
    {
    	drawCircle(V[i].color,V[i].x,V[i].y);
    }
    
    for(i=0;i<N;i++)
    {
        temp=Q[i]->ptr;
        while(temp!=NULL)
        {
            connectGraph(i,temp->data-1);
            temp=temp->ptr;
        }
    }
    glutSwapBuffers();
    
    if(flag==0)  // Code execution & Animation part.
	{
		flag=1;
		sleep(2);
	    	for(int l=0;l<N;l++)
		{
			if(V[l].color==1.0)
			{
				DFS_VISIT(l,V,Q);
			}
		}
	}
}


void handleResize(int w, int h)
{
	glMatrixMode(GL_PROJECTION);  // Transformations being applied to Projection Matrix
	glLoadIdentity();  // Always call after changing matrix
	glViewport(0,0,w,h);
	glOrtho((w/wx),w,(h/hy),h,1,200); // Here object is being moved along with window, wx & hy window size. Here clipping range is zNear=1,zFar=-200
	glMatrixMode(GL_MODELVIEW); // Transformations on ModelView Matrix(default)
}


int main(int argc, char **argv)
{
	wx=700;hy=700;
	cout<<"Enter the no:of vertices:";
	cin>>N;
	V=new vert[N];
	
	for(i=0;i<N;i++)
	{
		V[i].data=i+1;
		V[i].color=1;
		cout<<"Enter vertex co:ordinates of vertex "<<i+1<<":";
		cin>>V[i].x>>V[i].y;
		Q[i]=new lis;
		Q[i]->data=0;
		Q[i]->ptr=NULL;
		cout<<"Enter the vertices to which vertex "<<i+1<<" is linked:";
		cin>>j;
		if(j!=0)
		{
			temp=Q[i];
			while(j!=0)
			{
			node=new lis;
			node->data=j;
			node->ptr=NULL;
			cin>>j;
			temp->ptr=node;
			temp=temp->ptr;
			}
		}
	}

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);  
    glutCreateWindow("DFS");
    glutDisplayFunc(draw);
    glutReshapeFunc(handleResize);  // Invoked when window is resized
    glutMainLoop();
}
			
