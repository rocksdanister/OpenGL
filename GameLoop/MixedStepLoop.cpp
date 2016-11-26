

void mixedStepLoop()
{
double now = glutGet(GLUT_ELAPSED_TIME);  // get the time at which draw function is called
double timeElapsedMs =(now-prev);  // time difference calculate b/w current and previous loop
queuedMilliseconds += timeElapsedMs ; // stores the time as chunks
if(fps==0) // no fps cap, gamestate update is determined by the  physics function though, WARNING will get over 6000fps depending on the hardware
{
// draw function goes here
}
while(queuedMilliseconds >= responseTime) {  // update it in intervals given by responseTime by substracting -responseTime , ie a new frame every 16.65ms (60fps) or..
	   // physics calculation function goes here
        queuedMilliseconds -= responseTime;
	if(fps!=0)
	glutPostRedisplay(); // update the display by calling draw function, extra calls will stack
	}
prev=now; // stores the mixedstepLoop enter time for next loop
}

int main(int argc, char **argv)
{
  queuedMilliseconds=0;
  fps=30;
  responseTime=(1/fps)*1000;  // 33.33..ms is the responsetime for 30fps, 16.65.. for 60fps etc..
  // glut window properties & stuff
  glutDisplayFunc(mixedStepLoop); // or call the draw function if you like it that way
  glutIdleFunc(mixedStepLoop);
  glutMainLoop();
  return 0;
}
