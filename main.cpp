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
bool walkFrame = true;

float redMaterial[3] = {1.0,0.0,0.0};
float greenMaterial[3] = {0.0,1.0,0.0};
float blueMaterial[3] = {0.0,0.0,1.0};
float wMaterial[3] = {1.0,1.0,1.0};
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
	
	map[1][9][1] = 1;
	map[2][9][1] = 1;
	map[3][9][1] = 1;
	map[4][9][1] = 1;
	map[5][9][1] = 1;
	map[6][9][1] = 1;
	map[7][9][1] = 1;
	map[8][9][1] = 1;
	map[9][9][1] = 1;
	map[0][9][1] = 1;
	map[4][4][1] = 0;
	map[5][5][1] = 0;
	map[5][4][1] = 2;
	
	
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
	
	map[1][0][1] = 1;
	map[2][0][1] = 1;
	map[3][0][1] = 1;
	map[4][0][1] = 1;
	map[5][0][1] = 1;
	map[6][0][1] = 1;
	map[7][0][1] = 1;
	map[8][0][1] = 1;
	map[9][0][1] = 1;
	map[4][2][1] = 3;
	map[4][3][1] = 3;
	
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			if(map[i][j][1]==2){
				playerx=i;
				playerz=j;
			}
}
			

void InitLight(){
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 100.0 };
   GLfloat light_position[] = { 20.0, 5.0, 20.0, 1.0 };
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
      glVertex3f( b.x, b.y, a.z);
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

void createWall(){
	for(i=0;i<10;i++){
 		for(j=0;j<10;j++){
 			if(map[i][j][1] == 1){
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
		}	
	}
}

void createCubes(){
	for(i=0;i<10;i++){
 		for(j=0;j<10;j++){
 			if(map[i][j][1] == 3){
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
		}	
	}
}

void playermodel(point center,int direction){
	glPushMatrix();
	glTranslatef(center.x,center.y + 1.3,center.z);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redMaterial);
	glutSolidCube(0.5);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blueMaterial);
	point a;
	point b;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wMaterial);
	a.x = center.x-0.2;
    a.y = center.y+0.5;
    a.z = center.z-0.2;
    b.x = center.x+0.2;
    b.z = center.z +0.2;
    b.y = 1;
    drawCubicShape(b,a);
	if(walkFrame){
		a.x = center.x;
		a.y = center.y;
		a.z = center.z;
		b.x = center.x-0.2;
		b.z = center.z-0.2;
		b.y = 0.5;
		drawCubicShape(a,b);
		a.x = center.x;
		a.y = center.y;
		a.z = center.z;
		b.x = center.x+0.2;
		b.z = center.z+0.2;
		b.y = 0.5;
		drawCubicShape(a,b);
		walkFrame = false;
	}else{
		a.x = center.x;
		a.y = center.y;
		a.z = center.z;
		b.x = center.x+0.2;
		b.z = center.z-0.2;
		b.y = 0.5;
		drawCubicShape(a,b);
		a.x = center.x;
		a.y = center.y;
		a.z = center.z;
		b.x = center.x-0.2;
		b.z = center.z+0.2;
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
     float eyeX = 5.0 + 10.0*cos(3.14)*sin(angle);
	 float eyeY = 10.0 + 10.0*sin(3.14)*sin(angle);
	 float eyeZ = 5.0 + 10.0*cos(angle);
	 angle+=0.02;
	 if (angle>360)
	 	angle=0;
     gluLookAt(eyeX,eyeY,eyeZ,5.0,0.0,5.0,0.0,1.0,0.0); //sets where camera looks
     InitLight();
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redMaterial);
     createFloor();
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blueMaterial);
     createWall();
	 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, greenMaterial);
     createCubes();
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wMaterial);
     createPlayer();
     printf(" %d , %d ", playerx,playerz);
     glutSwapBuffers(); //switches between 1st and 2nd buffers
}

bool isCaixa(int xdirection, int zdirection){
	if((map[playerx + xdirection][playerz + zdirection][1]==3)||(map[playerx + xdirection][playerz + zdirection][1]==4)||
	(map[playerx + xdirection][playerz + zdirection][1]==5)||(map[playerx + xdirection][playerz + zdirection][1]==6))
		return true;
	return false;
}

void keyboard(unsigned char Key, int x, int y)
{
	switch(Key)
	{
		case 'd':
			playerd=4;
			if(isCaixa(-1,0)){
				if(map[playerx-2][playerz][1]==0){
					map[playerx-2][playerz][1]=3;
					map[playerx-1][playerz][1]=2;
					map[playerx][playerz][1]=0;
					playerx-=1;
					printf("memes");
				}
			}
			else if(map[playerx-1][playerz][1]==0){
					map[playerx-1][playerz][1]=2;
					map[playerx][playerz][1]=0;
					playerx-=1;
					printf("memes");
				}
			break;
			
		case 'w':
			playerd=3;
			if(isCaixa(0,-1)){
				if(map[playerx][playerz-2][1]==0){
					map[playerx][playerz-2][1]=3;
					map[playerx][playerz-1][1]=2;
					map[playerx][playerz][1]=0;
					playerz-=1;
					printf("memes");
				}
			}
			else if(map[playerx][playerz-1][1]==0){
					map[playerx][playerz-1][1]=2;
					map[playerx][playerz][1]=0;
					playerz-=1;
					printf("memes");
				}
			break;
			
		case 's':
			playerd=1;
			if(isCaixa(0,1)){
				if(map[playerx][playerz+2][1]==0){
					map[playerx][playerz+2][1]=3;
					map[playerx][playerz+1][1]=2;
					map[playerx][playerz][1]=0;
					playerz+=1;
					printf("memes");
				}
			}
			else if(map[playerx][playerz+1][1]==0){
					map[playerx][playerz+1][1]=2;
					map[playerx][playerz][1]=0;
					playerz+=1;
					printf("memes");
				}
			break;
		case 'a':
			playerd=2;
			if(isCaixa(1,0)){
				if(map[playerx+2][playerz][1]==0){
					map[playerx+2][playerz][1]=3;
					map[playerx+1][playerz][1]=2;
					map[playerx][playerz][1]=0;
					playerx+=1;
					printf("memes");
				}
			}
			else if(map[playerx+1][playerz][1]==0){
					map[playerx+1][playerz][1]=2;
					map[playerx][playerz][1]=0;
					playerx+=1;
					printf("memes");
				}
			break;
	}	
	glutPostRedisplay();
}

int main(int argc, char** argv){
	 variable_setup();
     glutInit(&argc,argv); //initializes argc and argv's
     glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);//tells openGL to display double buffers, RedGreenBlueAlpha, and depth of light
     glutInitWindowSize(1000,800);//sets window size to 500pixels by 500pixels
     glutInitWindowPosition(100,100);//sets the window to top left of screen
     glutCreateWindow("Spinning Cube");//sets a caption on the window
     glutKeyboardFunc(keyboard);
     glutDisplayFunc(display);
     glutReshapeFunc(reshape);
     glutMainLoop();
     return 0;
} 

