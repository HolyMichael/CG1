#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

struct point {
  float x;
  float y;
  float z;
};

int i, j, k;
float height = 1.0;
float side = 1.0;

float angle;
int map[10][10][2]; // 1 -walls  2 - player 3 - red obj zone[1]/red caixa[0]...

void reshape(int w, int h){
     //Set a view port, and make w and h into floats that openGL understands
     glViewport(0,0,(GLsizei)w,(GLsizei)h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(60,(GLsizei)w/(GLsizei)h,1.0,100.0);
     glMatrixMode(GL_MODELVIEW);
}

void variable_setup(){
	memset(map, 0, sizeof map);
	map[0][0][0] = 3;
	map[9][9][0] = 3;
	map[9][0][0] = 3;
	map[0][9][0] = 3;
	map[4][5][0] = 3;
	map[5][4][0] = 3;
	map[4][4][0] = 3;
	map[5][5][0] = 3;
}

void InitLight(){
	 GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 0.5 };
	 glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
     glEnable(GL_DEPTH_TEST); //Tests the depth of space
     glEnable(GL_LIGHTING); //turns the "lights" on
     glEnable(GL_LIGHT1); //allows light #0 out of about 8 lights to shine
     glEnable(GL_COLOR_MATERIAL); //allows color to appear when object is lit
     
}

void drawCubicShape(point a, point b){
	glBegin(GL_QUADS);
      // Top face 
      glVertex3f( b.x, a.y, b.z); //top righty
      glVertex3f( a.x, a.y, b.z); //top lefty
      glVertex3f( a.x, a.y, a.z); //bottom lefty
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

void createLife(){
	for(i=0;i<10;i++){
 		for(j=0;j<10;j++){
 			if(map[i][j][0] == 3){
	 			point a;
				point b;
				a.x= (side*j);
				a.y= 0.0;
				a.z= (side*i);
				b.x= (side*(j+1));
				b.y= height;
				b.z= (side*(i+1));
				drawCubicShape(a,b);
			}
			/*glRotatef(angle,1.0,0.0,0.0);
		    angle+=0.3;
			if(angle >= 360)
			 	angle = 0;*/ 
		}	
	}
}

//then we need to display something on the window we want to create
void display(void){
     glClearDepth(1); //clears the depth
     glClearColor(0.0,0.0,0.0,1.0);//clears the window color to black
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity(); //loads matrix identity
     gluLookAt(-2.0,10.0,12.0,5.0,0.0,5.0,0.0,1.0,0.0); //sets where camera looks
     //glColor3f(1.0,0.0,0.0);
     createLife();
     glutSwapBuffers(); //switches between 1st and 2nd buffers
}

int main(int argc, char** argv){
	 variable_setup();
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

