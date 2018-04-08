#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

struct point {
  float x;
  float y;
  float z;
};

float angle;

void reshape(int w, int h){
     //Set a view port, and make w and h into floats that openGL understands
     glViewport(0,0,(GLsizei)w,(GLsizei)h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(60,(GLsizei)w/(GLsizei)h,1.0,100.0);
     glMatrixMode(GL_MODELVIEW);
}

void InitLight(){
     glEnable(GL_DEPTH_TEST); //Tests the depth of space
     glEnable(GL_LIGHTING); //turns the "lights" on
     glEnable(GL_LIGHT0); //allows light #0 out of about 8 lights to shine
     glEnable(GL_COLOR_MATERIAL); //allows color to appear when object is lit
     
}

void drawCubicShape(point a, point b){
	glBegin(GL_QUADS);
      // Top face 
      glVertex3f( b.x, a.y, b.z); //top righty
      glVertex3f( a.x, a.y, b.z);  //top lefty
      glVertex3f( a.x, a.y, a.z);   //bottom lefty
      glVertex3f( b.x, a.y, a.z); //bottom righty
 
      // Bottom face 
      glVertex3f( b.x, b.y, a.z);
      glVertex3f( a.x, b.y, a.z);
      glVertex3f( a.x, b.y, b.z);
      glVertex3f( b.x, b.y, b.z);
 
      // Front face 
      glVertex3f( b.x, a.y, a.z);
      glVertex3f( a.x, a.y, a.z);
      glVertex3f( a.x, b.y, a.z);
      glVertex3f( b.x, b.y, a.z);
 
      // Back face
      glVertex3f( b.x, b.y, b.z);
      glVertex3f( a.x, b.y, b.z);
      glVertex3f( a.x, a.y, b.z);
      glVertex3f( b.x, a.y, b.z);
 
      // Left face 
      glVertex3f( a.x, a.y, a.z);
      glVertex3f( a.x, a.y, b.z);
      glVertex3f( a.x, b.y, b.z);
      glVertex3f( a.x, b.y, a.z);
 
      // Right face
      glVertex3f( b.x,  a.y, b.z);
      glVertex3f( b.x,  a.y, a.z);
      glVertex3f( b.x, b.y, b.z);
      glVertex3f( b.x, b.y, b.z);
   glEnd();  // End of drawing color-cube
}

//then we need to display something on the window we want to create
void display(void){
     glClearDepth(1); //clears the depth
     glClearColor(0.0,0.0,0.0,1.0);//clears the window color to black
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity(); //loads matrix identity
     gluLookAt(0.0,5.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0); //sets where camera looks
     //glColor3f(1.0,0.0,0.0);
     point a;
     a.x = 0.0;
     a.y = 5.0;
     a.z = 1.0;
     point b;
     b.x = 1.0;
     b.y = 0.0;
     b.z = 0.0;
     glRotatef(angle,1.0,0.0,0.0);
     drawCubicShape(a,b); //displays the cube function
     angle+=0.3;
	 if(angle >= 360)
	 	angle = 0; 
     glutSwapBuffers(); //switches between 1st and 2nd buffers
}

int main(int argc, char** argv){ 
     glutInit(&argc,argv); //initializes argc and argv's
     glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);//tells openGL to display double buffers, RedGreenBlueAlpha, and depth of light
     glutInitWindowSize(500,500);//sets window size to 500pixels by 500pixels
     glutInitWindowPosition(100,100);//sets the window to top left of screen
     glutCreateWindow("Spinning Cube");//sets a caption on the window
     InitLight();//turns on the "lights"
     glutDisplayFunc(display);
     glutIdleFunc(display);//since the cube is gonna be moving, openGL needs to change whats going on in the program, so it will use Idle
     glutReshapeFunc(reshape);
     glutMainLoop();
     return 0;
} 

