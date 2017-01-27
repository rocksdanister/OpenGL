// Compile with new compiler: g++ -std=c++14  or g++ -std=c++11

#include<bits/stdc++.h>
#include <GL/glut.h>
#include<unistd.h>

using namespace std;

struct lis
{
  int data,distance,par;
  lis *next;
};

class vertex
{
	public:
	int data,distance,x,y,color,parent;
	vertex()
	{}
	vertex(int val,int d,int posx,int posy,int col,int p)
	{
		data=val;
		distance=d;
		x=posx;
		y=posy;
		color=col;
		parent=p;
	}	
};

class myComparator
{
  public:
  int operator()(const vertex& v1,const vertex& v2) //To compare two vertices with distance as key value. The operator() is overloaded. 
     {
 	 return v1.distance>v2.distance;
     }	
}; 

vertex V[20];
lis *adj[20];

lis *node,*temp;

vertex s[20];
int s_size=0,wx,hy,N,min_ver,flag=0;

priority_queue<vertex,vector<vertex>,myComparator > pq; //Priority Queue pq for maintaining Min Heap.

string str;
GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;

void display();

void drawstr(GLuint x, GLuint y, const char* format, int length)
{
  if(*format=='i')
  {
    glTranslatef(-22,0,0);
  }	
  glRasterPos2i(x, y);  
  for(int i=0; i<length; ++i)
  {
    glutBitmapCharacter(font_style, *(format+i) );
  }
}

void drawCircle(double a,int x,int y)
{
    glLoadIdentity();
    glColor3f(a,a,a);
    glTranslatef(x,y,-1);
    glutSolidSphere(30,100,100);
    glTranslatef(-x-5,-y-5,0);
    glColor3f(0.8,0.4,0.3);
    drawstr(x,y, str.c_str(), str.length());
}

void connectGraph(int a,int b,lis *temp3)
{
  glLoadIdentity();
  if(temp3->par==V[b].parent)
    glColor3f(0,1,0);
  else
    glColor3f(1,0,0);
  glBegin(GL_LINES);
  glVertex3f(V[a].x,V[a].y,-80);
  glVertex3f(V[b].x,V[b].y,-80);
  glEnd();
}
void relax(int n,lis *v,int w)  // Relax(u,v,w)
{
   int vval=v->data-1;
   if(V[vval].distance>(V[n].distance+w))  // If d[v]>d[u]+w(u,v) then d[v]= d[u]+w(u,v) and Parent[v]=u
     {
      V[vval].distance=(V[n].distance+w);
      V[vval].parent=n+1;
      display();
      sleep(2);
     }
}

void Dijkstra()
{
    while(pq.empty()==false)    //Until Priority Queue is empty
      {
 	 vertex v=pq.top();    //Vertex with the minimum distance from source 
         min_ver=v.data;
         V[min_ver-1].color=0;
         display();
         sleep(2);
         node=adj[min_ver-1];
         lis *temp2;
         temp2=node;
         s[s_size++]=v;     //Set of vertices whose final shortest path have been determined. Just for algorithm sake.
         while(temp2!=NULL)
          {
            relax(min_ver-1,temp2,temp2->distance);   // Relax(u,v,w) Testing whether we can improve the shortest path to v through u. w is the weight of edge (u,v) 
    	    temp2=temp2->next;
          }
        pq.pop();           //Top-most element(the one with minimum value) is popped.
      }
}
void display()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.4f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i=0;i<N;i++)
    {
    	if(V[i].distance==1000)  
    	str="infinity";
    	else
    	str=std::to_string(V[i].distance);
    	drawCircle(V[i].color,V[i].x,V[i].y);
    }

    for(int i=0;i<N;i++)
    {
        temp=adj[i]->next;
        while(temp!=NULL)
        {
            connectGraph(i,temp->data-1,temp);
            temp=temp->next;
        }
    }
    
    glutSwapBuffers();
    
    if(flag==0)     // Needs to be called only once.
	{
	    flag=1;
	    Dijkstra();
        }
}

void handleResize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);   // Transformations being applied to Projection Matrix
    glLoadIdentity();   // Always call after switching matrix
    glViewport(0,0,w,h);
    glOrtho(0,w,0,h,1,200); // Here clipping range is zNear=1,zFar=-200
    glMatrixMode(GL_MODELVIEW); // Transformations on ModelView Matrix(default)
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
        dis=0;     // Source is initialised with distance 0
      else
        dis=1000;  // Vertices other than source as initialised with 1000. Here 1000 represents infinity,

      pq.push(V[i]=vertex(i+1,dis,posx,posy,1,0));   //Each vertex is added to the Priority Queue pq

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
	    node->par=i+1;
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

   cout<<"Adjacency List: \n";
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

}

			
			
