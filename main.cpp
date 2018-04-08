#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

GLfloat angle = 0;

//for reshaping the window
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

void cube(){
     glColor3f(1.0,0.0,0.0); //sets the color of the cube to red
     glRotatef(angle,1.0,1.0,1.0); //rotates the cube
     glutSolidCube(2); //draws the cube
}

//then we need to display something on the window we want to create
void display(void){
     glClearDepth(1); //clears the depth
     glClearColor(0.0,0.0,0.0,1.0);//clears the window color to black
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity(); //loads matrix identity
     gluLookAt(0.0,0.0,60.0,0.0,0.0,0.0,0.0,1.0,0.0); //sets where camera looks
     cube(); //displays the cube function
     glutSwapBuffers(); //switches between 1st and 2nd buffers
     angle+=0.1;
     if (angle>=360){ //this is checked in case that the float gets too big for c++ to handle, therefore preventing a crash
          angle = 0;
     }
}

int main(int argc, char** argv){ // type this if using MSVC++
     glutInit(&argc,argv); //initializes argc and argv's
     glutInitDisplayMode (GL_DOUBLE | GL_RGBA | GL_DEPTH);//tells openGL to display double buffers, RedGreenBlueAlpha, and depth of light
     glutInitWindowSize(500,500);//sets window size to 500pixels by 500pixels
     glutInitWindowPosition(0,0);//sets the window to top left of screen
     glutCreateWindow("Spinning Cube");//sets a caption on the window
     InitLight();//turns on the "lights"
     glutDisplayFunc(display);
     glutIdleFunc(display);//since the cube is gonna be moving, openGL needs to change whats going on in the program, so it will use Idle
     glutReshapeFunc(reshape);
     glutMainLoop();
     return 0;
} 

