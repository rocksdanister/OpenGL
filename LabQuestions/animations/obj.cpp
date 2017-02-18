#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<myheader.h>

extern struct data p[2][100000];
extern struct data_temp q[2][1000000];
int i,j;
char line[60];

void initialOBJ(int select)
{
dlist=glGenLists(1);
dlist2=glGenLists(1);

vindex[select]=0; 
FILE *fp;
if(select==0)
fp=fopen("temp.obj","r");
else if(select==1)
fp=fopen("temp2.obj","r");	

	while(!(feof(fp)))
	{
		i=0;
		fscanf(fp,"%s",line);

		if(line[0]=='v'&&line[1]!='n'&&line[1]!='t')
		{
			while(i<3)
			{
			fscanf(fp,"%f",&q[select][vindex[select]].v[i]);
			//printf("%f\t",q[select][vindex[select]].v[i]);	
			i++;
			}
			//printf("\n");
			vindex[select]++;
		}
		else if(line[0]=='v'&&line[1]=='n')
		{
		
			while(i<3)
			{
			fscanf(fp,"%f",&q[select][vnindex[select]].vn[i]);	
			i++;
			}
			vnindex[select]++;
			
		}
		else if(line[0]=='v'&&line[1]=='t')
		{
			while(i<3)
			{
			fscanf(fp,"%f",&q[select][vtindex[select]].vn[i]);	
			i++;
			}
			vtindex[select]++;

		}
		

	}
	 fclose(fp);

}

void objDraw(int select)
{
 FILE *fp2;
 if(select==0)
 fp2=fopen("temp.obj","r");
 else if(select==1)
 fp2=fopen("temp2.obj","r");	
 int eq,eq2;
 vindex[select]=0; 
 char ch[10];
 while(!(feof(fp2)))
 {	
 	i=0;
 	fscanf(fp2,"%s",line);
	if(line[0]=='f')
	{	

		while(i<3)	
		{
			//... VERTEX
			fscanf(fp2,"%d%s",&eq,line);
			//printf("%d\t",eq);
			p[select][vindex[select]].v[0]=q[select][eq].v[0];
			p[select][vindex[select]].v[1]=q[select][eq].v[1];
			p[select][vindex[select]].v[2]=q[select][eq].v[2];
			i++;vindex[select]++;
			//... NORMAL
			while(j<strlen(line))
			{
			ch[j]=line[j+2];
			j++;
			}
			eq2=atoi(ch);
			//printf("eq2:= %d\t",eq2);
			j=0;
			p[select][vnindex[select]].vn[0]=q[select][eq2].vn[0];
			p[select][vnindex[select]].vn[1]=q[select][eq2].vn[1];
			p[select][vnindex[select]].vn[2]=q[select][eq2].vn[2];
			vnindex[select]++;
		}
		//printf("eq[0]=%f eq[1]=%f",q[0].vn[0],q[1].vn[0]);
		//printf("\n");

	} 	

 }
 fclose(fp2);
}


void optimisationList()
{

glNewList(dlist, GL_COMPILE);

glBegin(GL_TRIANGLES);
for(i=0;i<vindex[0];i++)
{
//glNormal3f(p[i].vn[0],p[i].vn[1],p[i].vn[2]);
glVertex3f(p[0][i].v[0],p[0][i].v[1],p[0][i].v[2]);
}
glEnd();

glEndList();
}

void optimisationList2()
{

glNewList(dlist2, GL_COMPILE);

glBegin(GL_TRIANGLES);
for(i=0;i<vindex[1];i++)
{
//glNormal3f(p[i].vn[0],p[i].vn[1],p[i].vn[2]);
glVertex3f(p[1][i].v[0],p[1][i].v[1],p[1][i].v[2]);
}
glEnd();

glEndList();
}