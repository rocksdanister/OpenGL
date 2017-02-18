extern double queuedMilliseconds,prev0,fps,responseTime;
extern float lx,lz,x,z,angle;
extern int vindex[3],vnindex[3],vtindex[3];
extern GLuint dlist;
extern GLuint dlist2;
extern GLfloat rateT;

void mixedStepLoop();
void processSpecialKeys(int , int , int );
void draw();
void initialOBJ(int);
void objDraw(int);
void optimisationList();
void optimisationList2();
void update();

struct data
{
GLfloat v[3];
GLfloat vn[3];
GLfloat tex[3];
};

struct data_temp
{
GLfloat v[3];
GLfloat vn[3];
GLfloat tex[3];
};
