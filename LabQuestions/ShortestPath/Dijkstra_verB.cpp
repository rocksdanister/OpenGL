#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <GL/glut.h>
#include<unistd.h>
#include <limits>

using namespace std;
struct lis{
	int data;
    int weight;
    int status;
	lis *ptr;
};
class vert
{
	public:
	int x,y;
	int data;
    int dist;
	float color;
};
int mx,my;
vert *V;
int *previo;
vert tmp;
lis *node;
lis *temp;
lis *Q[20];
int N;
int *dist;
int flag=0;

string str;
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;

void drawstr(GLuint x, GLuint y, const char* format, int length)
{

  glRasterPos2i(x, y);  
  for(int i=0; i<length; ++i)
    glutBitmapCharacter(font_style, *(format+i) );
}

void drawCircle(double a,int x,int y)
{
    glLoadIdentity();
    glColor3f(a,a,a);
    glTranslatef(x,y,-1);
    glutSolidSphere(30,100,100);
    glTranslatef(-x,-y,0);
    glColor3f(1,0,0);
    drawstr(x-5,y-5, str.c_str(), str.length());

}

void connectGraph()
{
    glLineWidth(2);
    lis *temp;
    for(int i=0;i<N;i++)
    {
        temp=Q[i]->ptr;
        while(temp!=NULL)
        {

                if(temp->status==0)    
                glColor3f(0,0,0);
                else if((previo[temp->data-1]==i)||(previo[i]==(temp->data-1)))
                 glColor3f(0,1,0);
                else
                 glColor3f(1,0,0);
                
                glBegin(GL_LINES);
                glVertex3f(V[i].x,V[i].y,-80);
                glVertex3f(V[temp->data-1].x,V[temp->data-1].y,-80);
                glEnd();
                glColor3f(0,0,0);
                str=std::to_string(temp->weight);
                mx=(V[i].x+V[temp->data-1].x)/2;my=((V[i].y+V[temp->data-1].y)/2)+10;
                drawstr(mx,my, str.c_str(), str.length());
             temp=temp->ptr;   
            }
        }
    }
    
 

int length(int a,int b)
{
    lis *temp;
    temp=Q[a]->ptr;
    while(temp!=NULL)
    {
        if(temp->data-1==b)
            return temp->weight;
        temp=temp->ptr;
    }
}
void draw();

void Dijkstra(int source)
{
    sleep(2);
    int dis;
    lis *temp;
    dist[source]=0;
    for(int i=0;i<N;i++)
    {
        
        temp=Q[i]->ptr;
        while(temp!=NULL)
        {
            dis=dist[i]+length(i,temp->data-1);
            if(dis<dist[temp->data-1])
            {
                dist[temp->data-1]=dis;
                previo[temp->data-1]=i;
            }
            temp->status=1;
            temp=temp->ptr;
            draw();
            sleep(2);
        }
    }
}
void draw()
{
   
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i=0;i<N;i++)
    {
        
    	str=std::to_string(V[i].data);
    	drawCircle(V[i].color,V[i].x,V[i].y);
    }
    
    connectGraph();

    glutSwapBuffers();
    if(flag==0)
	{
        
        flag++;
		Dijkstra(0);
    }
}

void handleResize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);  // Transformations being applied to Projection Matrix
	glLoadIdentity();  // Always call after changing matrix
	glViewport(0,0,w,h);
	glOrtho(0,w,0,h,1,200); // Here clipping range is zNear=1,zFar=-200
	glMatrixMode(GL_MODELVIEW); // Transformations on ModelView Matrix(default)
}

int main(int argc, char **argv)
{
    
	
	cout<<"Enter the no:of vertices:";
	cin>>N;
	V=new vert[N];
    dist=new int[N];
    previo=new int[N];
    for(int i=0;i<N;i++)
    {
        dist[i]=std::numeric_limits<int>::max();
        previo[i]=-1;
    }
	for(int i=0;i<N;i++)
	{
        int vt,wt;
		V[i].data=i+1;
		V[i].color=1;
		cout<<"Enter vertex co:ordinates of vertex "<<i+1<<":";
		cin>>V[i].x>>V[i].y;
		Q[i]=new lis;
		Q[i]->data=0;
       	Q[i]->ptr=NULL;
		cout<<"Enter the vertices to which vertex "<<i+1<<" is linked and weight:";
		cin>>vt>>wt;
        if(vt!=0)
		{
			temp=Q[i];
			while(vt!=0)
			{
			node=new lis;
			node->data=vt;
            node->weight=wt;
            node->status=0;
			node->ptr=NULL;
			cin>>vt;
            cin>>wt;
			temp->ptr=node;
			temp=temp->ptr;
			}
		}
	}
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Dijkstra");
    glutDisplayFunc(draw);
    glutReshapeFunc(handleResize);
    glutMainLoop();
}
