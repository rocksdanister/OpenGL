#include<iostream>
#include<bits/stdc++.h>
#include <GL/glut.h>
#include<unistd.h>
using namespace std;

struct lis{
	int data,distance;
	lis *next;
};

class vertex
{
	public:
	int data,distance,x,y,color;
	vertex()
	{}
	vertex(int val,int d,int posx,int posy,int col)
	{
		data=val;
		distance=d;
		x=posx;
		y=posy;
		color=col;
	}	
};

class myComparator
{
  public:
  int operator()(const vertex& v1,const vertex& v2)
	 {
	 	 return v1.distance>v2.distance;
	 }	
}; 

vertex V[20];
lis *adj[20];

lis *node,*temp;

vertex s[20];
int s_size=0,wx,hy,N,min_ver,flag=0;

priority_queue<vertex,vector<vertex>,myComparator > pq; //Queue for maintaining Min Heap

string str;
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;

void display();

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
  glColor3f(0.7,0.4,0.2);
  drawstr(x,y, str.c_str(), str.length());
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

void relax(int n,lis *v,int w)
{
	int vval=v->data-1;
	if(V[vval].distance>(V[n].distance+w))
		{
			V[vval].distance=(V[n].distance+w);
			display();
			sleep(3);
		}

}

void display()
{
	glEnable(GL_DEPTH_TEST);
  glClearColor(0.4f, 0.3f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for(int i=0;i<N;i++)
    {
    	str=std::to_string(V[i].distance);
    	drawCircle(V[i].color,V[i].x,V[i].y);
    }

   for(int i=0;i<N;i++)
    {
        temp=adj[i]->next;
        while(temp!=NULL)
        {
            connectGraph(i,temp->data-1);
            temp=temp->next;
        }
    }
    glutSwapBuffers();
    if(flag==0)
	{
		flag=1;
	   while(pq.empty()==false)
       {
 	     vertex v=pq.top();
         min_ver=v.data;
         V[min_ver-1].color=0;
         display();
         sleep(2);
         node=adj[min_ver-1];
         lis *temp2;
         temp2=node->next;
         s[s_size++]=v;
         while(temp2!=NULL)
          {
        	relax(min_ver-1,temp2,temp2->distance);
    	    temp2=temp2->next;
          }
         pq.pop();
       }
     }

}

void handleResize(int w, int h)
{
  glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();  
	glViewport(0,0,w,h);
	glOrtho((w/wx),w,(h/hy),h,1,200); 
	glMatrixMode(GL_MODELVIEW); 
}

int main(int argc,char *argv[])
{
  int dis,j,posx,posy;
  wx=700,hy=700;

	cout<<"Enter the no of vertices: ";
	cin>>N;

	for(int i=0;i<N;i++)
	{
		cout<<"\nEnter the co-ordinates of vertes "<<i+1<<" : ";
		cin>>posx>>posy;
		if(i==0)
		 dis=0;
	  else
		 dis=100;
		pq.push(V[i]=vertex(i+1,dis,posx,posy,1));
		adj[i]=new lis;
		adj[i]->data=0;
		adj[i]->next=NULL;
		cout<<"\nEnter the vertex to which vertex "<<i+1<<" is linked: ";
		cin>>j;
		if(j!=0)
		{
			temp=adj[i];
			while(j!=0)
			{
			node=new lis;
			node->data=j;
			if(j!=0)
				{
					cout<<"\nEnter the distance of edge ("<<i+1<<','<<j<<") :";
					cin>>dis;
					node->distance=dis;
				}
			node->next=NULL;
			cout<<"\nEnter the vertex to which vertex "<<i+1<<" is linked: ";
			cin>>j;
			temp->next=node;
			temp=temp->next;
			}
		}
	}
 cout<<"LIST\n";
	for(int i=0;i<N;i++)
	{
		cout<<"\n";
		temp=adj[i]->next;
		while(temp!=NULL)
		{
			cout<<temp->data<<" ";
			temp=temp->next;
		}
		cout<<"\n";
	}
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(700, 700);
 glutInitWindowPosition(100, 100);
 glutCreateWindow("Dijkstra's Algorithm");
 glutDisplayFunc(display);
 glutReshapeFunc(handleResize);
 glutMainLoop();

 for(int i=0;i<s_size;i++)
  cout<<'\n'<<V[i].data<<'\t'<<V[i].distance;
}

			
			
