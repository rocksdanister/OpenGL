#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<unistd.h> 
int i,n,size,j,t,s[400][2],l1,t2,flag,f1,k,pos;
float x[5],y[5],a[3];
struct data
{
int x;
int y;
float mn;
float mp;
}d[7];

void draw()
{
glColor3f(0,0,0);
glBegin(GL_LINE_LOOP);
for(i=0;i<n;i++)
glVertex2i(d[i].x,d[i].y);
glEnd();
}

void search(int p,int q)
{
pos=-1;
for(k=0;k<n;k++)
{
	if((d[k].x==p)&&(d[k].y==q))
	{
	pos=k;			
	}
}
}

void scanline()
{
t=0;
a[0]=1;
a[1]=1;
a[2]=1;
f1=0;
    for(i=0;i<=size;i++)
        for(j=0;j<=size;j++)
        {
        glReadPixels(j,i,1,1,GL_RGB,GL_FLOAT,a);
        printf("%d %d\t:Color : %f %f %f \n",j,i,a[0],a[1],a[2]);            
            if((a[0]==0)&&(a[1]==0)&&(a[2]==0))
            {
			glReadPixels(j+1,i,1,1,GL_RGB,GL_FLOAT,a);	
			if(((a[0]==1)&&(a[1]==1)&&(a[2]==1))||f1==0)	
			{    f1=1;        
				s[t][0]=j;
            	s[t++][1]=i;       
			}			
            }
        
        }

    }
void pts()
{
for(i=0;i<t;i++)
{
for(j=0;j<2;j++)
{    
printf("%d\t",s[i][j]);
}
printf("\n");
}
}

float edgedetect(int o,int t)
{
float temp;
	if(d[o].y==d[t].y)
	return 0;
	
	if(d[o].x==d[t].x)
	{
	return 500;
	}		
	else 
	{
	temp=(d[o].y-d[t].y)/(d[o].x-d[t].x);	
	return temp;
	}
}



void paint()
{
glColor3f(1,0,0);
for(i=0;i<t;)
{	
	for(j=s[i][0];j<s[i+1][0];j++)
	{	
	glBegin(GL_POINTS);
	glVertex2i(s[i][0]++,s[i][1]); 	
	usleep(500);
	glEnd();
	glFlush();
	}

search(s[i][0],s[i][1]);
if(pos>=0)
{
if(d[pos].mn>0&&d[pos].mp<0)
i=i+1;
else
i=i+2;
}
else
i=i+2;	
}

}

void slope()
{

d[0].mn=edgedetect(0,1);
d[0].mp=edgedetect(0,n-1);
d[n-1].mn=edgedetect(n-1,0);
d[n-1].mp=edgedetect(n-1,n-2);
for(i=1;i<n-1;i++)
{
d[i].mn=edgedetect(i,i+1);
d[i].mp=edgedetect(i,i-1);
}
}
                
void init()
{
glClearColor(1,1,1,0);
glClear(GL_COLOR_BUFFER_BIT);
glOrtho(0.0f, size, 0.0f,size, 0.0f, 1.0f);
//glScaled(2,2,2);
draw();
glFlush();
slope();
scanline();
//pts();
paint();
glFlush();
//glutSwapBuffers();
}

int main(int argc,char **argv)
{
size=400;
printf("Enter No: of Vertices\n");
scanf("%d",&n);
for(i=0;i<n;i++)
{
printf("Enter %d vertex points (x,y) ( %dx%d Window Size ) \n",i+1,size,size);
scanf("%d %d",&d[i].x,&d[i].y);
}
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
glutInitWindowSize(size,size);
glutInitWindowPosition(100,100);
glutCreateWindow("Scanline");
glutDisplayFunc(init);
glutMainLoop();
return 0;
}

