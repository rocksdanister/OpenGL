extern double queuedMilliseconds,prev0,fps,responseTime;
extern int resX,resY,movementX;
extern double movementY;

void draw();
void mixedStepLoop();
void update(double);
void updateSynchronised();
void processSpecialKeys(int , int , int );
void movePhysics();