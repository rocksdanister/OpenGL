#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
int i,size,r,j,k,n,q,t,sx,sy,easy;
double p1;
double queuedMilliseconds,prev;
struct path
{
int a[4][2];
}p[10];


void draw()
{
srand(time(NULL));
glColor3f(0,0,0);
j=250;k=0;
for(i=0;i<500;)
{

	r=rand()%3;
	if(r==0)
	{
	if(p[k-1].a[1][0]==i&&p[k-1].a[1][1]==j&&k!=0)
	i=i-50;
		if(j!=500)
		{		
		
		glBegin(GL_QUADS);
			glVertex2i(i,j+50);			p[k].a[0][0]=i;p[k].a[0][1]=j+50;
			glVertex2i(i+50,j+50);			p[k].a[1][0]=i+50;p[k].a[1][1]=j+50;
			glVertex2i(i+50,j);			p[k].a[2][0]=i+50;p[k].a[2][1]=j;
			glVertex2i(i,j);			p[k].a[3][0]=i;p[k++].a[3][1]=j;
		glEnd();
		j=j+50;
		}
	}
	else if(r==1)
	{	
	if(p[k-1].a[1][0]==i+50 &&p[k-1].a[1][1]==j && p[k-1].a[2][0]==i+50 && p[k-1].a[2][1]==j-50&&k!=0 )
	{
	i=i+50;
	}	
	
		glBegin(GL_QUADS);
			glVertex2i(i,j);			p[k].a[0][0]=i;p[k].a[0][1]=j;
			glVertex2i(i+50,j);			p[k].a[1][0]=i+50;p[k].a[1][1]=j;
			glVertex2i(i+50,j-50);			p[k].a[2][0]=i+50;p[k].a[2][1]=j-50;
			glVertex2i(i,j-50);			p[k].a[3][0]=i;p[k++].a[3][1]=j-50;
		glEnd();
	i=i+50;
	
	}
	else
	{
	if(p[k-1].a[2][0]==i&&p[k-1].a[2][1]==j-50&&k!=0)
	{
	i=i-50;
	}	
	if(j!=0)
	{	
	glBegin(GL_QUADS);
		glVertex2i(i,j-50);		p[k].a[0][0]=i;p[k].a[0][1]=j-50;
		glVertex2i(i+50,j-50);		p[k].a[1][0]=i+50;p[k].a[1][1]=j-50;
		glVertex2i(i+50,j-100);		p[k].a[2][0]=i+50;p[k].a[2][1]=j-100;
		glVertex2i(i,j-100);		p[k].a[3][0]=i;p[k++].a[3][1]=j-100;
	glEnd();
		j=j-50;
	}
	if(j==0)
	j+=50;
	}
}

}

void draw2()
{
glColor3f(0,0,0);
for(i=0;i<k;i++)
{
glBegin(GL_QUADS);
	glVertex2i(p[i].a[0][0],p[i].a[0][1]);
	glVertex2i(p[i].a[1][0],p[i].a[1][1]);
	glVertex2i(p[i].a[2][0],p[i].a[2][1]);
	glVertex2i(p[i].a[3][0],p[i].a[3][1]);
glEnd();
}

}

void init2()
{
glClearColor(1,1,1,0);
glClear(GL_COLOR_BUFFER_BIT);
if(t==0)
{
	draw();
	sx=(p[0].a[0][0]+p[0].a[1][0])/2;
	sy=p[0].a[3][1]+25;
}
else
	draw2();
t=1;
glColor3f(1,1,1);
glPointSize(5);
glBegin(GL_POINTS);
	glVertex2f(sx+p1,sy+q);
glEnd();
glFlush();
}


void keyboard(int key,int x,int y)
{
    if (key == GLUT_KEY_RIGHT)
        {
                p1+=5;
	
        }
    else if (key == GLUT_KEY_LEFT)
        {
               // p1-=5;
     	
	   }
    else if (key == GLUT_KEY_DOWN)
        {
                q-=5;
        }	
    else if (key == GLUT_KEY_UP)
        {
                q+=5;
      	}
	else if(key==GLUT_KEY_F1)
	{
		t=0;
		q=0;
		p1=0;
	}
	else if(key==GLUT_KEY_F2)
	{
	p1=0;
	q=0;	
	}

}

void update()
{
	
    if(p1<20)
		p1=p1+.2;
	else if(p1<40)
		p1=p1+.4;
	else if(p1<60)
		p1=p1+.6;
	else if(p1<80)
		p1=p1+.8;
	else if(p1<100)
		p1=p1+1;
	else if(p1<120)
		p1=p1+1.2;
	else if(p1<180)
		p1=p1+1.4;
	else 
		p1=p1+1.5;

}

void rshape(int w,int h)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0,0,w,h);
glOrtho(0, w,0,h, 0.0f, 1.0f);
glMatrixMode(GL_MODELVIEW);
}

void init()
{
double now = glutGet(GLUT_ELAPSED_TIME);
double timeElapsedMs =(now-prev);
queuedMilliseconds += timeElapsedMs ; 
init2();  
	while(queuedMilliseconds >= 25) {
		update();
        queuedMilliseconds -= 25;
    }
prev=now;
}


int main(int argc,char **argv)
{
queuedMilliseconds=0;
prev=0;
p1=0;q=0;
t=0;
size=500;
printf("\n\tTrapped - ALPHA BUILD v1\n");
printf("Did this just for fun, code is horrible & stupid, Physics not implemented , difficulty not optimised \n");
printf(" >>CONTROLS<< :\n Arrow keys to move forwards(faster),up,down.\n F1: New Game F2: Restart Level\n");
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE);
glutInitWindowSize(size,size);
glutInitWindowPosition(100,100);
glutCreateWindow("Procedural World");
glutDisplayFunc(init);
glutIdleFunc(init);
glutReshapeFunc(rshape);
glutSpecialFunc(keyboard);
glutMainLoop();
return 0;
}
