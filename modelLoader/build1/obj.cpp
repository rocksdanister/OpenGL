#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<myheader.h>

extern struct data p[100000];
extern struct data_temp q[1000000];
int i,j;
char line[60];

void initialOBJ()
{

FILE *fp;
fp=fopen("temp.obj","r");

	while(!(feof(fp)))
	{
		i=0;
		fscanf(fp,"%s",line);

		if(line[0]=='v'&&line[1]!='n'&&line[1]!='t')
		{
			while(i<3)
			{
			fscanf(fp,"%f",&q[vindex].v[i]);	
			i++;
			}
			vindex++;
		}
		else if(line[0]=='v'&&line[1]=='n')
		{

			while(i<3)
			{
			fscanf(fp,"%f",&q[vnindex].vn[i]);	
			i++;
			}
			vnindex++;
		}
		else if(line[0]=='v'&&line[1]=='t')
		{
			while(i<3)
			{
			fscanf(fp,"%f",&q[vtindex].vn[i]);	
			i++;
			}
			vtindex++;

		}

	}
	 fclose(fp);
	

}

void objDraw()
{
dlist=glGenLists(1);
 FILE *fp2;
 fp2=fopen("temp.obj","r");
 int eq,eq2;
 vindex=0; 
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
			printf("%d\t",eq);
			p[vindex].v[0]=q[eq].v[0];
			p[vindex].v[1]=q[eq].v[1];
			p[vindex].v[2]=q[eq].v[2];
			i++;vindex++;
			//... NORMAL
			while(j<strlen(line))
			{
			ch[j]=line[j+2];
			j++;
			}
			eq2=atoi(ch);
			//printf("eq2:= %d\t",eq2);
			j=0;
			p[vnindex].vn[0]=q[eq2].vn[0];
			p[vnindex].vn[1]=q[eq2].vn[1];
			p[vnindex].vn[2]=q[eq2].vn[2];
			vnindex++;
		}
		//printf("eq[0]=%f eq[1]=%f",q[0].vn[0],q[1].vn[0]);
		printf("\n");

	} 	

 }
 fclose(fp2);
}


void optimisationList()
{

glNewList(dlist, GL_COMPILE);

glBegin(GL_TRIANGLES);
for(i=0;i<vindex;i++)
{
//glNormal3f(p[i].vn[0],p[i].vn[1],p[i].vn[2]);
glVertex3f(p[i].v[0],p[i].v[1],p[i].v[2]);
}
glEnd();

glEndList();
}
