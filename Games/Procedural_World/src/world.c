#include<myheader.h>
#include<GL/glut.h>
#include<unistd.h>
#include<time.h>
extern struct path p[10];
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
			glVertex2i(i,j+50);		p[k].a[0][0]=i;p[k].a[0][1]=j+50;
			glVertex2i(i+50,j+50);		p[k].a[1][0]=i+50;p[k].a[1][1]=j+50;
			glVertex2i(i+50,j);		p[k].a[2][0]=i+50;p[k].a[2][1]=j;
			glVertex2i(i,j);		p[k].a[3][0]=i;p[k++].a[3][1]=j;
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

void init()
{
double now = glutGet(GLUT_ELAPSED_TIME);
double timeElapsedMs =(now-prev0);
queuedMilliseconds += timeElapsedMs ; 
init2();  
	while(queuedMilliseconds >= 25) {
		update();
        queuedMilliseconds -= 25;
    }
prev0=now;
}


