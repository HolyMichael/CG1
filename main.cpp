#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

struct point {
  float x;
  float y;
  float z;
};
int playerx;
int playerz;
int playerd=1;
int objectives;
bool flagRenderBoxes=true;
bool walkFrame = true;
float cameraHeight=15.0;
float cameraCenter=10.0;
int currLevel = 1;

float floorMaterial[4] = {1.0,0.4,0.4,1.0};
float wallMaterial[4] = {1.0,0.2,0.2,1.0};
float redMaterial[3] = {1.0,0.4,0.4};
float greenMaterial[3] = {0.0,1.0,0.0};
float blueMaterial[3] = {0.0,0.0,1.0};
float wMaterial[3] = {1.0,1.0,1.0};
int i, j, k, falalag=1;
float height = 1.0;
float side = 1.0001;
int map[10][10][2]; /* 1 -walls  2 - player 
3 - green obj zone[0]/green caixa[1] 
4 - blue obj zone[0]/blue caixa[1]
11 - green key
12 - blue key
21 - green door
22 - blue door
31 - portal*/


void reshape(int w, int h){
     //Set a view port, and make w and h into floats that openGL understands
     glViewport(0,0,(GLsizei)w,(GLsizei)h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(60,(GLsizei)w/(GLsizei)h,1.0,100.0);
     glMatrixMode(GL_MODELVIEW);
}

void testLevel(){
	memset(map, 0, sizeof map);
	objectives = 3000;
	map[4][5][1] = 31;
	map[4][2][1] = 3;
	map[6][4][1] = 2;
	map[8][7][1] = 31;
		
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			if(map[i][j][1]==2){
				playerx=i;
				playerz=j;
			}
}

void level1(){
	memset(map, 0, sizeof map);
	objectives=2;
	currLevel=1;
	map[0][0][1] = 1;
	map[0][1][1] = 1;
	map[0][2][1] = 1;
	map[0][3][1] = 1;
	map[0][4][1] = 1;
	map[0][5][1] = 1;
	map[0][6][1] = 1;
	map[0][7][1] = 1;
	map[0][8][1] = 1;
	map[0][9][1] = 1;
	
	map[1][0][1] = 1;
	map[1][1][1] = 1;
	map[1][4][1] = 1;
	map[1][5][1] = 1;
	map[2][3][1] = 31;//pls remove after TODO
	map[5][6][1] = 31;//pls remove after TODO
	map[1][8][1] = 1;
	map[1][9][1] = 1;
	
	map[2][0][1] = 1;
	map[2][2][1] = 3;
	map[2][4][1] = 1;
	map[2][5][1] = 1;
	map[2][7][0] = 3;
	map[2][9][1] = 1;
	
	map[3][0][1] = 1;
	map[3][4][1] = 1;
	map[3][5][1] = 1;
	map[3][9][1] = 1;
	
	map[4][0][1] = 1;
	map[4][1][1] = 1;
	map[4][5][1] = 2;
	map[4][8][1] = 1;
	map[4][9][1] = 1;
	
	map[5][0][1] = 1;
	map[5][1][1] = 1;
	map[5][8][1] = 1;
	map[5][9][1] = 1;
	
	map[6][0][1] = 1;
	map[6][4][1] = 1;
	map[6][5][1] = 1;
	map[6][9][1] = 1;
	
	map[7][0][1] = 1;
	map[7][2][1] = 4;
	map[7][4][1] = 1;
	map[7][5][1] = 1;
	map[7][7][0] = 4;
	map[7][9][1] = 1;
	
	map[8][0][1] = 1;
	map[8][1][1] = 1;
	map[8][4][1] = 1;
	map[8][5][1] = 1;
	map[8][8][1] = 1;
	map[8][9][1] = 1;
		
	map[9][0][1] = 1;
	map[9][1][1] = 1;
	map[9][2][1] = 1;
	map[9][3][1] = 1;
	map[9][4][1] = 1;
	map[9][5][1] = 1;
	map[9][6][1] = 1;
	map[9][7][1] = 1;
	map[9][8][1] = 1;
	map[9][9][1] = 1;
	
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			if(map[i][j][1]==2){
				playerx=i;
				playerz=j;
			}
}

void level2(){
	memset(map, 0, sizeof map);
	currLevel=2;
	objectives=4;
	map[0][0][1] = 1;
	map[0][1][1] = 1;
	map[0][2][1] = 1;
	map[0][3][1] = 1;
	map[0][4][1] = 1;
	map[0][5][1] = 1;
	map[0][6][1] = 1;
	map[0][7][1] = 1;
	map[0][8][1] = 1;
	map[0][9][1] = 1;
	
	map[1][0][1] = 1;
	map[1][9][1] = 1;
	
	map[2][0][1] = 1;
	map[2][2][1] = 1;
	map[2][3][1] = 1;
	map[2][4][1] = 3;
	map[2][6][1] = 1;
	map[2][7][1] = 1;
	map[2][9][1] = 1;
	
	map[3][0][1] = 1;
	map[3][2][1] = 1;
	map[3][3][0] = 3;
	map[3][6][1] = 1;
	map[3][7][0] = 3;
	map[3][9][1] = 1;
	
	map[4][0][1] = 1;
	map[4][2][1] = 4;
	map[4][3][1] = 4;
	map[4][5][1] = 2;
	map[4][9][1] = 1;
	
	map[5][0][1] = 1;
	map[5][2][1] = 3;
	map[5][7][0] = 4;
	map[5][9][1] = 1;
	
	map[6][0][1] = 1;
	map[6][2][1] = 1;
	map[6][3][0] = 4;
	map[6][6][1] = 1;
	map[6][7][1] = 1;
	map[6][9][1] = 1;
	
	map[7][0][1] = 1;
	map[7][2][1] = 1;
	map[7][3][1] = 1;
	map[7][6][1] = 1;
	map[7][7][1] = 1;
	map[7][9][1] = 1;
	
	map[8][0][1] = 1;
	map[8][9][1] = 1;
		
	map[9][0][1] = 1;
	map[9][1][1] = 1;
	map[9][2][1] = 1;
	map[9][3][1] = 1;
	map[9][4][1] = 1;
	map[9][5][1] = 1;
	map[9][6][1] = 1;
	map[9][7][1] = 1;
	map[9][8][1] = 1;
	map[9][9][1] = 1;
	
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			if(map[i][j][1]==2){
				playerx=i;
				playerz=j;
			}
}

void level3(){
	memset(map, 0, sizeof map);
	currLevel=3;
	objectives=2;
	map[0][0][1] = 1;
	map[0][1][1] = 1;
	map[0][2][1] = 1;
	map[0][3][1] = 1;
	map[0][4][1] = 1;
	map[0][5][1] = 1;
	map[0][6][1] = 1;
	map[0][7][1] = 1;
	map[0][8][1] = 1;
	map[0][9][1] = 1;
	
	map[1][0][1] = 1;
	map[1][1][1] = 1;
	map[1][2][1] = 1;
	map[1][3][1] = 1;
	map[1][4][1] = 1;
	map[1][5][1] = 1;
	map[1][6][1] = 1;
	map[1][7][1] = 1;
	map[1][8][1] = 1;
	map[1][9][1] = 1;
	
	map[2][0][1] = 1;
	map[2][1][1] = 1;
	map[2][2][1] = 1;
	map[2][3][1] = 1;
	map[2][4][1] = 1;
	map[2][5][1] = 1;
	map[2][6][1] = 1;
	map[2][7][1] = 1;
	map[2][8][1] = 1;
	map[2][9][1] = 1;
	
	map[3][0][1] = 1;
	map[3][1][1] = 1;
	map[3][2][0] = 3;
	map[3][6][1] = 2;
	map[3][8][1] = 1;
	map[3][9][1] = 1;
	
	map[4][0][1] = 1;
	map[4][1][1] = 1;
	map[4][4][1] = 3;
	map[4][8][1] = 1;
	map[4][9][1] = 1;
	
	map[5][0][1] = 1;
	map[5][1][1] = 1;
	map[5][2][1] = 4;
	map[5][3][1] = 1;
	map[5][4][1] = 1;
	map[5][5][1] = 1;
	map[5][6][1] = 1;
	map[5][8][1] = 1;
	map[5][9][1] = 1;
	
	map[6][0][1] = 1;
	map[6][1][1] = 1;
	map[6][3][1] = 1;
	map[6][4][0] = 4;
	map[6][8][1] = 1;
	map[6][9][1] = 1;
	
	map[7][0][1] = 1;
	map[7][8][1] = 1;
	map[7][9][1] = 1;
	
	map[8][0][1] = 1;
	map[8][4][1] = 1;
	map[8][5][1] = 1;
	map[8][8][1] = 1;
	map[8][9][1] = 1;
		
	map[9][0][1] = 1;
	map[9][1][1] = 1;
	map[9][2][1] = 1;
	map[9][3][1] = 1;
	map[9][4][1] = 1;
	map[9][5][1] = 1;
	map[9][6][1] = 1;
	map[9][7][1] = 1;
	map[9][8][1] = 1;
	map[9][9][1] = 1;
	
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			if(map[i][j][1]==2){
				playerx=i;
				playerz=j;
			}
}

void level4(){
	memset(map, 0, sizeof map);
	currLevel=4;
	objectives=1;
	map[0][0][1] = 1;
	map[0][1][1] = 1;
	map[0][2][1] = 1;
	map[0][3][1] = 1;
	map[0][4][1] = 1;
	map[0][5][1] = 1;
	map[0][6][1] = 1;
	map[0][7][1] = 1;
	map[0][8][1] = 1;
	map[0][9][1] = 1;
	
	map[1][0][1] = 1;
	map[1][4][1] = 21;
	map[1][8][1] = 1;
	map[1][9][1] = 1;
	
	map[2][0][1] = 1;
	map[2][4][1] = 1;
	map[2][5][1] = 1;
	map[2][6][1] = 1;
	map[2][8][1] = 1;
	map[2][9][1] = 1;
	
	map[3][0][1] = 1;
	map[3][2][1] = 11;
	map[3][4][1] = 1;
	map[3][5][0] = 3;
	map[3][6][1] = 1;
	map[3][4][1] = 1;
	map[3][8][1] = 1;
	map[3][9][1] = 1;
	
	map[4][0][1] = 1;
	map[4][4][1] = 1;
	map[4][6][1] = 1;
	map[4][7][1] = 31;
	map[4][8][1] = 1;
	map[4][9][1] = 1;
	
	map[5][0][1] = 1;
	map[5][4][1] = 1;
	map[5][6][1] = 1;
	map[5][7][1] = 1;
	map[5][8][1] = 1;
	map[5][9][1] = 1;
	
	map[6][0][1] = 1;
	map[6][4][1] = 1;
	map[6][9][1] = 1;
	
	map[7][0][1] = 1;
	map[7][4][1] = 1;
	map[7][6][1] = 3;
	map[7][8][1] = 31;
	map[7][9][1] = 1;
	
	map[8][0][1] = 1;
	map[8][1][1] = 2;
	map[8][4][1] = 1;
	map[8][9][1] = 1;
		
	map[9][0][1] = 1;
	map[9][1][1] = 1;
	map[9][2][1] = 1;
	map[9][3][1] = 1;
	map[9][4][1] = 1;
	map[9][5][1] = 1;
	map[9][6][1] = 1;
	map[9][7][1] = 1;
	map[9][8][1] = 1;
	map[9][9][1] = 1;
	
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			if(map[i][j][1]==2){
				playerx=i;
				playerz=j;
			}
}

void level5(){
	memset(map, 0, sizeof map);
	currLevel=5;
	objectives=3;
	map[0][0][1] = 1;
	map[0][1][1] = 1;
	map[0][2][1] = 1;
	map[0][3][1] = 1;
	map[0][4][1] = 1;
	map[0][5][1] = 1;
	map[0][6][1] = 1;
	map[0][7][1] = 1;
	map[0][8][1] = 1;
	map[0][9][1] = 1;
	
	map[1][0][1] = 1;
	map[1][1][1] = 1;
	map[1][2][1] = 1;
	map[1][3][1] = 1;
	map[1][4][1] = 1;
	map[1][5][1] = 1;
	map[1][6][1] = 1;
	map[1][7][1] = 1;
	map[1][8][1] = 1;
	map[1][9][1] = 1;
	
	map[2][0][1] = 1;
	map[2][1][1] = 1;
	map[2][2][1] = 1;
	map[2][3][1] = 1;
	map[2][4][1] = 1;
	map[2][5][1] = 1;
	map[2][6][1] = 1;
	map[2][7][1] = 1;
	map[2][8][1] = 1;
	map[2][9][1] = 1;
	
	map[3][0][1] = 1;
	map[3][1][1] = 1;
	map[3][2][1] = 1;
	map[3][3][1] = 1;
	map[3][4][1] = 1;
	map[3][5][1] = 1;
	map[3][6][1] = 1;
	map[3][7][1] = 1;
	map[3][8][1] = 1;
	map[3][9][1] = 1;
	
	map[4][0][1] = 1;
	map[4][1][1] = 11;
	map[4][3][1] = 31;
	map[4][4][1] = 1;
	map[4][5][1] = 31;
	map[4][8][0] = 4;
	map[4][9][1] = 1;
	
	map[5][0][1] = 1;
	map[5][1][1] = 1;
	map[5][2][1] = 3;
	map[5][3][1] = 1;
	map[5][4][1] = 1;
	map[5][5][1] = 1;
	map[5][6][1] = 21;
	map[5][9][1] = 1;
	
	map[6][0][1] = 1;
	map[6][1][0] = 3;
	map[6][4][1] = 1;
	map[6][5][1] = 1;
	map[6][6][1] = 1;
	map[6][9][1] = 1;
	
	map[7][0][1] = 1;
	map[7][1][1] = 1;
	map[7][2][1] = 1;
	map[7][6][1] = 1;
	map[7][7][1] = 4;
	map[7][9][1] = 1;
	
	map[8][0][1] = 1;
	map[8][1][1] = 1;
	map[8][2][1] = 1;
	map[8][3][1] = 2;
	map[8][8][1] = 1;
	map[8][9][1] = 1;
	
	map[9][0][1] = 1;
	map[9][1][1] = 1;
	map[9][2][1] = 1;
	map[9][3][1] = 1;
	map[9][4][1] = 1;
	map[9][5][1] = 1;
	map[9][6][1] = 1;
	map[9][7][1] = 1;
	map[9][8][1] = 1;
	map[9][9][1] = 1;
	
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			if(map[i][j][1]==2){
				playerx=i;
				playerz=j;
			}
}	

void switchLevel(){
	printf("\ncurrlevel is %d\n",currLevel);
	if(currLevel==5)
		currLevel==1;
	switch (currLevel){
		case 1:
			level1();
			break;
		case 2:
			level2();
			break;
		case 3: 
			level3();
			break;
		case 4: 
			level4();
			break;
		case 5: 
			level5();
			break;
	}
}	

void animationFadeIn(int time){
	cameraHeight-=.5;
	cameraCenter+=.5;
	gluLookAt(5.0,cameraHeight,cameraCenter,5.0,0.0,5.0,0.0,1.0,0.0);
	if(cameraHeight<15){
		glutPostRedisplay();
		falalag=1;
	}
	else{
		glutTimerFunc(100, animationFadeIn, 0);
		glutPostRedisplay();
	}
	
}	

void animationFadeOut(int time){
	cameraHeight+=.5;
	cameraCenter-=.5;
	gluLookAt(5.0,cameraHeight,cameraCenter,5.0,0.0,5.0,0.0,1.0,0.0);
	falalag=0;
	if(cameraHeight>20){
		switchLevel();
		glutTimerFunc(100, animationFadeIn, 0);
	}
	else{
		glutTimerFunc(100, animationFadeOut, 0);
		glutPostRedisplay();
	}
	
}

void InitLight(){
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 10.0 };
   GLfloat light_position[] = { 10.0, 5.0, 10.0, 1.0 };
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
	
      // top face 
      glNormal3f(0,1,0);
      glVertex3f( b.x, b.y, a.z);
      glNormal3f(0,1,0);
      glVertex3f( a.x, b.y, a.z);
      glNormal3f(0,1,0);
      glVertex3f( a.x, b.y, b.z);
      glNormal3f(0,1,0);
      glVertex3f( b.x, b.y, b.z);
      // bottom face (0.0,1,0.0);
      glNormal3f(0,-1,0);
      glVertex3f( b.x, a.y, b.z); //top righty
      glNormal3f(0,-1,0);
      glVertex3f( a.x, a.y, b.z); //top lefty
      glNormal3f(0,-1,0);
      glVertex3f( a.x, a.y, a.z); //bottom lefty
      glNormal3f(0,-1,0);
      glVertex3f( b.x, a.y, a.z); //bottom righty
 
      // Front face 
      glNormal3f(0,0,-1);
      glVertex3f( b.x, a.y, a.z);
      glNormal3f(0,0,-1);
      glVertex3f( a.x, a.y, a.z);
      glNormal3f(0,0,-1);
      glVertex3f( a.x, b.y, a.z);
      glNormal3f(0,0,-1);
      glVertex3f( b.x, b.y, a.z);
 
      // Back face
      glNormal3f(0,0,1);
      glVertex3f( b.x, b.y, b.z);
      glNormal3f(0,0,1);
      glVertex3f( a.x, b.y, b.z);
      glNormal3f(0,0,1);
      glVertex3f( a.x, a.y, b.z);
      glNormal3f(0,0,1);
      glVertex3f( b.x, a.y, b.z);
 
      // Left face 
      glNormal3f(-1,0,0);
      glVertex3f( a.x, a.y, a.z);
      glNormal3f(-1,0,0);
      glVertex3f( a.x, a.y, b.z);
      glNormal3f(-1,0,0);
      glVertex3f( a.x, b.y, b.z);
      glNormal3f(-1,0,0);
      glVertex3f( a.x, b.y, a.z);
 
      // Right face
      glNormal3f(1,0,0);
      glVertex3f( b.x,  a.y, b.z);
      glNormal3f(1,0,0);
      glVertex3f( b.x,  a.y, a.z);
      glNormal3f(1,0,0);
      glVertex3f( b.x, b.y, a.z);
      glNormal3f(1,0,0);
      glVertex3f( b.x, b.y, b.z);
   glEnd();  // End of drawing color-cube
}

void createFloor(){
	for(i=0;i<10;i++){
 		for(j=0;j<10;j++){
 			if(map[i][j][0]==3){
 				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, greenMaterial);
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
			else if(map[i][j][0]==4){
 				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blueMaterial);
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
			else{
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floorMaterial);
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
}

void createWall(){
	for(i=0;i<10;i++){
 		for(j=0;j<10;j++){
 			if(map[i][j][1] == 1){
	 			point a;
				point b;
				a.x= (side*j) -0.001;
				a.y= -.5;
				a.z= (side*i) -0.001;
				b.x= (side*(j+1) + 0.001);
				b.y= height*1.2;
				b.z= (side*(i+1)+0.001);
				drawCubicShape(a,b);
			}
		}	
	}
}

void createCubes(){
	for(i=0;i<10;i++){
 		for(j=0;j<10;j++){
 			if(map[i][j][1] == 3){
 				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, greenMaterial);
	 			point a;
				point b;
				a.x= (side*j);
				a.y= 0.0;
				a.z= (side*i);
				b.x= (side*(j+1));
				b.y= height*1.2;
				b.z= (side*(i+1));
				drawCubicShape(a,b);
			}
			if(map[i][j][1] == 4){
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blueMaterial);
	 			point a;
				point b;
				a.x= (side*j);
				a.y= 0.0;
				a.z= (side*i);
				b.x= (side*(j+1));
				b.y= height*1.2;
				b.z= (side*(i+1));
				drawCubicShape(a,b);
			}
			if(map[i][j][1] == 21){
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, greenMaterial);
	 			point a;
				point b;
				a.x= (side*j) -0.1;
				a.y= -.5;
				a.z= (side*i) -0.1;
				b.x= (side*(j+1) + 0.1);
				b.y= height*1.5;
				b.z= (side*(i+1)+0.1);
				drawCubicShape(a,b);
			}
			if(map[i][j][1] == 11){
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, greenMaterial);
	 			point a;
				point b;
				a.x= (side*j) +0.2;
				a.y= +.2;
				a.z= (side*i) +0.2;
				b.x= (side*(j+1) - 0.2);
				b.y= height*0.6;
				b.z= (side*(i+1) - 0.2);
				drawCubicShape(a,b);
			}
			if(map[i][j][1] == 22){
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blueMaterial);
	 			point a;
				point b;
				a.x= (side*j) -0.1;
				a.y= -.5;
				a.z= (side*i) -0.1;
				b.x= (side*(j+1) + 0.1);
				b.y= height*1.5;
				b.z= (side*(i+1)+0.1);
				drawCubicShape(a,b);
			}
			if(map[i][j][1] == 12){
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blueMaterial);
	 			point a;
				point b;
				a.x= (side*j) +0.2;
				a.y= +.2;
				a.z= (side*i) +0.2;
				b.x= (side*(j+1) - 0.2);
				b.y= height*0.6;
				b.z= (side*(i+1) - 0.2);
				drawCubicShape(a,b);
			}
			if(map[i][j][1] == 31){
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blueMaterial);
	 			point a;
				point b;
				a.x= (side*j) +0.2;
				a.y= +.2;
				a.z= (side*i) +0.2;
				b.x= (side*(j+1) - 0.2);
				b.y= height*0.6;
				b.z= (side*(i+1) - 0.2);
				drawCubicShape(a,b);
			}
		}	
	}
}

void playermodel(point center,int direction){
	point a,b;
	a.x=center.x -0.3;
	a.y=center.y +1;
	a.z=center.z -0.3;
	b.x=center.x +0.3;
	b.y=center.y + 1.5;
	b.z=center.z +0.3;
	drawCubicShape(a,b);
	a.x = center.x-0.2;
    a.y = center.y+0.5;
    a.z = center.z-0.2;
    b.x = center.x+0.2;
    b.z = center.z+0.2;
    b.y = 1;
    drawCubicShape(a,b);
	if(walkFrame){ //legs
		a.x = center.x-0.2;
		a.y = center.y;
		a.z = center.z;
		b.x = center.x;
		b.z = center.z-0.2;
		b.y = 0.5;
		drawCubicShape(a,b);
		a.x = center.x;
		a.y = center.y;
		a.z = center.z+0.2;
		b.x = center.x+0.2;
		b.z = center.z;
		b.y = 0.5;
		drawCubicShape(a,b);
		walkFrame = false;
	}else{
		a.x = center.x-0.2;
		a.y = center.y;
		a.z = center.z+.2;
		b.x = center.x;
		b.z = center.z;
		b.y = 0.5;
		drawCubicShape(a,b);
		a.x = center.x;
		a.y = center.y;
		a.z = center.z;
		b.x = center.x+0.2;
		b.z = center.z-0.2;
		b.y = 0.5;
		drawCubicShape(a,b);
		walkFrame=true;
	}
	b.y = 0.6;
	a.y = center.y+0.4;
	switch(direction){
		case 1:
			a.x = center.x+0.4;
			a.z = center.z-0.1;
			b.x = center.x+0.6;
			b.z = center.z+0.1;
			break;
		case 2:
			a.z = center.z+0.4;
			a.x = center.x-0.1;
			b.z = center.z+0.6;
			b.x = center.x+0.1;
			break;
		case 3:
			a.x = center.x-0.4;
			a.z = center.z+0.1;
			b.x = center.x-0.6;
			b.z = center.z-0.1;
			break;
		case 4:
			a.z = center.z-0.4;
			a.x = center.x+0.1;
			b.z = center.z-0.6;
			b.x = center.x-0.1;
			break;
	}
	
	drawCubicShape(a,b);
}
void createPlayer(){
	for(i=0;i<10;i++){
 		for(j=0;j<10;j++){
 			if(map[i][j][1] == 2){
 				point a;
 				a.x=j+.5;
 				a.y=0;
 				a.z=i+.5;
 				playermodel(a,playerd);
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
     /*float eyeX = 5.0 + 10.0*cos(3.14)*sin(angle);
	 float eyeY = 10.0 + 10.0*sin(3.14)*sin(angle);
	 float eyeZ = 5.0 + 10.0*cos(angle);*/
     gluLookAt(5.0,cameraHeight,cameraCenter,5.0,0.0,5.0,0.0,1.0,0.0); //sets where camera looks
     InitLight();
     createFloor();
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wallMaterial);
     createWall();
     if(flagRenderBoxes){
     	createCubes();
    }
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wMaterial);
     createPlayer();
     printf(" %d , %d ", playerx,playerz);
     glutSwapBuffers(); //switches between 1st and 2nd buffers
}

int walkInto(int xdirection, int zdirection, int x, int z){
	return map[x + xdirection][z + zdirection][1];
}

bool isCaixa(int target){
	if(target==3 || target==4)
		return true;
	return false;
}

bool isVictory(){
	int vic=0;
	for(i=0;i<10;i++)
 		for(j=0;j<10;j++)
 			if(map[i][j][0]!=0)
 				if(map[i][j][0] == map[i][j][1])
 					vic++;
 	if(vic==objectives){
 		if(falalag==1)
 			currLevel++;
 		glutTimerFunc(100, animationFadeOut, 0);
 		return true;
 	}
 	else
 		return false;
}

void openDoor(int color){
	for(i=0;i<10;i++)
		for(j=0;j<10;j++){
			if(map[i][j][1]==(color+10)){
				map[i][j][1]=0;
				printf("removing door");
			}
		}
}

bool pjW(int posx, int posz){
	if(walkInto(-1,0, posx, posz) == 0){
				playerx = posx-1;
				playerz = posz;
				playerd = 4;
				return true;
			}
	else if(isCaixa(walkInto(-1,0, posx, posz))){
		if(walkInto(-1,0, posx-1, posz)==0){
			map[posx-2][posz][1]=map[posx-1][posz][1];
			playerx = posx-1;
			playerz = posz;
			playerd = 4;
			return true;
		}
	}
	return false;
}

bool pjA(int posx, int posz){
	if(walkInto(0,-1, posx, posz) == 0){
				playerx = posx;
				playerz = posz-1;
				playerd = 3;
				return true;
			}
	else if(isCaixa(walkInto(0,-1, posx, posz))){
		if(walkInto(0,-1, posx, posz-1)==0){
			map[posx][posz-2][1]=map[posx][posz-1][1];
			playerx = posx;
			playerz = posz-1;
			playerd = 3;
			return true;
		}
	}
	return false;
}

bool pjS(int posx, int posz){
	if(walkInto(1,0, posx, posz) == 0){
				playerx = posx+1;
				playerz = posz;
				playerd = 2;
				return true;
			}
	else if(isCaixa(walkInto(1,0, posx, posz))){
		if(walkInto(1,0, posx+1, posz)==0){
			map[posx+2][posz][1]=map[posx+1][posz][1];
			playerx = posx+1;
			playerz = posz;
			playerd = 2;
			return true;
		}
	}
	return false;
}

bool pjD(int posx, int posz){
	if(walkInto(0,+1, posx, posz) == 0){
				playerx = posx;
				playerz = posz+1;
				playerd = 1;
				return true;
			}
	else if(isCaixa(walkInto(0,+1, posx, posz))){
		if(walkInto(0,+1, posx, posz+1)==0){
			map[posx][posz+2][1]=map[posx][posz+1][1];
			playerx = posx;
			playerz = posz+1;
			playerd = 1;
			return true;
		}
	}
	return false;
}

bool pjcW(int posx, int posz, int obj){
	if(walkInto(-1,0, posx, posz) == 0){
		map[posx-1][posz][1]=obj;
		return true;
	}
	return false;
}

bool pjcA(int posx, int posz, int obj){
	if(walkInto(0,-1, posx, posz) == 0){
		map[posx][posz-1][1]=obj;
		return true;
	}
	return false;
}

bool pjcS(int posx, int posz, int obj){
	if(walkInto(1,0, posx, posz) == 0){
		map[posx+1][posz][1]=obj;
		return true;
	}
	return false;
}

bool pjcD(int posx, int posz, int obj){
	if(walkInto(0,+1, posx, posz) == 0){
		map[posx][posz+1][1]=obj;
		return true;
	}
	return false;
}

bool caixaPortaliJumpi(int obj,int x, int y){
	int posx, posz;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++){
			if(map[i][j][1] == (31) && (i != x || j != y)){
				posx = i;
				posz = j;
			}
		}
	switch(playerd){
		case 1:
			if(pjcD(posx, posz, obj));
			else if(pjcS(posx, posz, obj));
			else if(pjcA(posx, posz, obj));
			else if(pjcW(posx, posz, obj));
			break;
		case 2:
			if(pjcS(posx, posz, obj));
			else if(pjcA(posx, posz, obj));
			else if(pjcW(posx, posz, obj));
			else if(pjcD(posx, posz, obj));
			break;
		case 3:
			if(pjcA(posx, posz, obj));
			else if(pjcW(posx, posz, obj));
			else if(pjcD(posx, posz, obj));
			else if(pjcS(posx, posz, obj));
			break;
		case 4:
			if(pjcW(posx, posz, obj));
			else if(pjcD(posx, posz, obj));
			else if(pjcS(posx, posz, obj));
			else if(pjcA(posx, posz, obj));
			break;
	}
	
}
void portaliJumpi(int obj){
	int posx, posz;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++){
			if(map[i][j][1] == (31) && (i != playerx || j != playerz)){
				printf("Fodasse");
				posx = i;
				posz = j;
			}		
		}
	switch(playerd){
		case 1:
			if(pjD(posx, posz));
			else if(pjS(posx, posz));
			else if(pjA(posx, posz));
			else if(pjW(posx, posz));
			else
				playerz-=1;
			break;
		case 2:
			if(pjS(posx, posz));
			else if(pjA(posx, posz));
			else if(pjW(posx, posz));
			else if(pjD(posx, posz));
			else
				playerx-=1;
			break;
		case 3:
			if(pjA(posx, posz));
			else if(pjW(posx, posz));
			else if(pjD(posx, posz));
			else if(pjS(posx, posz));
			else
				playerz+=1;
			break;
		case 4:
			if(pjW(posx, posz));
			else if(pjD(posx, posz));
			else if(pjS(posx, posz));
			else if(pjA(posx, posz));
			else
				playerx+=1;
			break;
	}
	map[playerx][playerz][1]=2;
}

void keyboard(unsigned char Key, int x, int y)
{
		switch(Key)
		{
			case 'W': case 'w':
				playerd=4;
				if(isCaixa(walkInto(-1,0, playerx, playerz))){
					if(map[playerx-2][playerz][1]==0){
						map[playerx-2][playerz][1]=map[playerx-1][playerz][1];
						map[playerx-1][playerz][1]=2;
						map[playerx][playerz][1]=0;
						playerx-=1;
					}
					else if(map[playerx-2][playerz][1]==31){
						caixaPortaliJumpi(map[playerx-1][playerz][1], playerx-2, playerz);
						map[playerx][playerz][1] = 0;
						map[playerx-1][playerz][1] = 2;
						playerx-=1;
					}
				}
				else if(walkInto(-1,0, playerx, playerz)==0){
					map[playerx-1][playerz][1]=2;
					map[playerx][playerz][1]=0;
					playerx-=1;
				}
				else if(walkInto(-1,0, playerx, playerz)==11 || walkInto(-1,0, playerx, playerz)==12){
					openDoor(walkInto(-1,0, playerx, playerz));
					map[playerx][playerz][1]=0;
					playerx-=1;
					map[playerx][playerz][1]=2;
				}
				else if(walkInto(-1,0, playerx, playerz)==31){
					map[playerx][playerz][1] = 0;
					playerx-=1;
					portaliJumpi(walkInto(-1,0, playerx, playerz));
				}
				break;
			case 'a': case 'A':
				playerd=3;
				if(isCaixa(walkInto(0,-1, playerx, playerz))){
					if(map[playerx][playerz-2][1]==0){
						map[playerx][playerz-2][1]=map[playerx][playerz-1][1];
						map[playerx][playerz-1][1]=2;
						map[playerx][playerz][1]=0;
						playerz-=1;
					}
					else if(map[playerx][playerz-2][1]==31){
						caixaPortaliJumpi(map[playerx][playerz-1][1], playerx, playerz-2);
						map[playerx][playerz][1] = 0;
						map[playerx][playerz-1][1] = 2;
						playerz-=1;
					}
				}
				else if(walkInto(0,-1, playerx, playerz)==0){
					map[playerx][playerz-1][1]=2;
					map[playerx][playerz][1]=0;
					playerz-=1;
				}
				else if(walkInto(0,-1, playerx, playerz)==11 || walkInto(0,-1, playerx, playerz)==12){
					openDoor(walkInto(0,-1, playerx, playerz));
					map[playerx][playerz][1]=0;
					playerz-=1;
					map[playerx][playerz][1]=2;
				}
				else if(walkInto(0,-1, playerx, playerz)==31){
					map[playerx][playerz][1] = 0;
					playerz-=1;
					portaliJumpi(walkInto(0,-1, playerx, playerz));
				}
				break;
			case 'd': case 'D':
				playerd=1;
				if(isCaixa(walkInto(0,1, playerx, playerz))){
					if(map[playerx][playerz+2][1]==0){
						map[playerx][playerz+2][1]=map[playerx][playerz+1][1];
						map[playerx][playerz+1][1]=2;
						map[playerx][playerz][1]=0;
						playerz+=1;
					}
					else if(map[playerx][playerz+2][1]==31){
						caixaPortaliJumpi(map[playerx][playerz+1][1], playerx, playerz+2);
						map[playerx][playerz][1] = 0;
						map[playerx][playerz+1][1] = 2;
						playerz+=1;
					}
				}
				else if(walkInto(0,1, playerx, playerz)==0){
					map[playerx][playerz+1][1]=2;
					map[playerx][playerz][1]=0;
					playerz+=1;
				}
				else if(walkInto(0,1, playerx, playerz)==11 || walkInto(0,1, playerx, playerz)==12){
					openDoor(walkInto(0,1, playerx, playerz));
					map[playerx][playerz][1]=0;
					playerz+=1;
					map[playerx][playerz][1]=2;
				}
				else if(walkInto(0,1, playerx, playerz)==31){
					map[playerx][playerz][1] = 0;
					playerz+=1;
					portaliJumpi(walkInto(0,1, playerx, playerz));
				}
				break;
			case 's': case 'S':
				playerd=2;
				if(isCaixa(walkInto(1,0, playerx, playerz))){
					if(map[playerx+2][playerz][1]==0){
						map[playerx+2][playerz][1]=map[playerx+1][playerz][1];
						map[playerx+1][playerz][1]=2;
						map[playerx][playerz][1]=0;
						playerx+=1;
					}
					else if(map[playerx+2][playerz][1]==31){
						caixaPortaliJumpi(map[playerx+1][playerz][1], playerx+2, playerz);
						map[playerx][playerz][1] = 0;
						map[playerx+1][playerz][1] = 2;
						playerx+=1;
					}
				}
				else if(walkInto(1,0, playerx, playerz)==0){
					map[playerx+1][playerz][1]=2;
					map[playerx][playerz][1]=0;
					playerx+=1;
				}
				else if(walkInto(1,0, playerx, playerz)==11 || walkInto(1,0, playerx, playerz)==12){
					openDoor(walkInto(1,0, playerx, playerz));
					map[playerx][playerz][1]=0;
					playerx+=1;
					map[playerx][playerz][1]=2;
				}
				else if(walkInto(1,0, playerx, playerz)==31){
					map[playerx][playerz][1] = 0;
					playerx+=1;
					portaliJumpi(walkInto(1,0, playerx, playerz));
				}
				break;
			case 'r': case 'R':
				switchLevel();
				break;
			case 't': case 'T':
				if(flagRenderBoxes)
					flagRenderBoxes=false;
				else
					flagRenderBoxes=true;
				break;
			case '1':
				level1();
				break;
			case '2':
				level2();
				break;
			case '3':
				level3();
				break;
			case '4':
				level4();
				break;
			case '5':
				level5();
				break;
			case 'y': case 'Y':
				cameraHeight+=1.0;
				cameraCenter-=1.0;
				gluLookAt(5.0,cameraHeight,cameraCenter,5.0,0.0,5.0,0.0,1.0,0.0);
				printf("%.2f, %.2f", cameraHeight, cameraCenter);
				break;
			case 'h': case 'H':
				cameraHeight-=1.0;
				cameraCenter+=1.0;
				gluLookAt(5.0,cameraHeight,cameraCenter,5.0,0.0,5.0,0.0,1.0,0.0);
				break;
		}	
	if(isVictory())
		glutTimerFunc(100, animationFadeOut, 0);
	glutPostRedisplay();
}

int main(int argc, char** argv){
	 switchLevel();
     glutInit(&argc,argv); //initializes argc and argv's
     glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);//tells openGL to display double buffers, RedGreenBlueAlpha, and depth of light
     glutInitWindowSize(1000,800);//sets window size to 500pixels by 500pixels
     glutInitWindowPosition(100,100);//sets the window to top left of screen
     glutCreateWindow("Sandokan 3 cuecas e 1 sutia");//sets a caption on the window
     glutKeyboardFunc(keyboard);
     glutDisplayFunc(display);
     glutReshapeFunc(reshape);
     glutMainLoop();
     return 0;
} 

