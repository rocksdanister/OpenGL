extern double queuedMilliseconds,prev0,fps,responseTime;
extern float lx,lz,x,z,angle;
extern int vindex,vnindex,vtindex;
extern GLuint dlist;

void mixedStepLoop();
void processSpecialKeys(int , int , int );
void draw();
void initialOBJ();
void objDraw();
void optimisationList();


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