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
	float color;
};

vert *V;
vert tmp;
vert QU[20];
int i,j,N,wx,hy;
lis *node;
lis *temp;
lis *Q[20];
int flag=0;
int bot=-1;
int top=-1;

void drawCircle(double a,int x,int y)
{
        glLoadIdentity();
        glColor3f(a,a,a);
        glTranslatef(x,y,-1);
        glutSolidSphere(30,100,100);

}

void connectGraph(int a,int b)
{
glLoadIdentity();
glColor3f(0,0,0);
glBegin(GL_LINES);
glVertex3f(V[a].x,V[a].y,-80);
glVertex3f(V[b].x,V[b].y,-80);
glEnd();

}


void draw()
{
    
    glEnable(GL_DEPTH_TEST);
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
    if(flag==0)
	{
		lis *temp1;
		flag++;
		sleep(2);
        for(int l=0;l<N;l++)
        {
        if(V[l].color==1)
        {
        V[l].color=0.5;
		draw();
		sleep(2);
		top=0;
		bot=0;
		QU[top++]=V[l];
		while(top!=bot)
		{
			tmp=QU[bot++];
			temp1=Q[tmp.data-1]->ptr;
			while(temp1!=NULL)
			{
				if(V[(temp1->data)-1].color==1)
				{
					V[(temp1->data)-1].color=0.5;
					draw();
					sleep(2);
					QU[top++]=V[(temp1->data)-1];

				}
				temp1=temp1->ptr;
			}
			V[tmp.data-1].color=0;
			draw();
			sleep(2);
		}
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
    glutCreateWindow("BFS");
    glutDisplayFunc(draw);
    glutReshapeFunc(handleResize);
    glutMainLoop();
}
