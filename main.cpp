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
int map[10][10][3]; // 1 -walls  2 - player 3 - red obj zone[1]/red caixa[0]...

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
	map[0][1][0] = 3;
	map[0][2][0] = 3;
	map[0][3][0] = 3;
	map[0][4][0] = 3;
	map[0][5][0] = 3;
	map[0][6][0] = 3;
	map[0][7][0] = 3;
	map[0][8][0] = 3;
	map[0][9][0] = 3;
	
	map[1][9][0] = 3;
	map[2][9][0] = 3;
	map[3][9][0] = 3;
	map[4][9][0] = 3;
	map[5][9][0] = 3;
	map[6][9][0] = 3;
	map[7][9][0] = 3;
	map[8][9][0] = 3;
	map[9][9][0] = 3;
	map[0][9][0] = 3;
	
	map[9][0][0] = 3;
	map[9][1][0] = 3;
	map[9][2][0] = 3;
	map[9][3][0] = 3;
	map[9][4][0] = 3;
	map[9][5][0] = 3;
	map[9][6][0] = 3;
	map[9][7][0] = 3;
	map[9][8][0] = 3;
	map[9][9][0] = 3;
	
	map[1][0][0] = 3;
	map[2][0][0] = 3;
	map[3][0][0] = 3;
	map[4][0][0] = 3;
	map[5][0][0] = 3;
	map[6][0][0] = 3;
	map[7][0][0] = 3;
	map[8][0][0] = 3;
	map[9][0][0] = 3;
}

void InitLight(){
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 100.0 };
   GLfloat light_position[] = { 9.0, -4.0, 10.0, 1.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
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

void createFloor(){
	for(i=0;i<10;i++){
 		for(j=0;j<10;j++){
	 			point a;
				point b;
				a.x= (side*j);
				a.y= -0.5;
				a.z= (side*i);
				b.x= (side*(j+1));
				b.y= 0.0;
				b.z= (side*(i+1));
				drawCubicShape(a,b);
		}	
	}
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
     InitLight();
     createFloor();
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
     glutDisplayFunc(display);
     glutIdleFunc(display);//since the cube is gonna be moving, openGL needs to change whats going on in the program, so it will use Idle
     glutReshapeFunc(reshape);
     glutMainLoop();
     return 0;
} 

