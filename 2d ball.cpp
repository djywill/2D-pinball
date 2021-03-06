#include"stdafx.h"
#include <glut.h>
#include <stdio.h>

GLfloat AD[2];
//width and height of the arena's unit
GLfloat X;
//Proportion of the arena
GLfloat R;
//Radius of the ball
GLfloat P_width, P_height;
//width and height of the ball's unit
GLfloat ball_speed;
GLfloat ballPos[2];            // ball position
GLfloat ballDir[2] = { 1, 1 };	// direction the ball will move 
GLfloat BD[2];		/* The dimensions of the ball and the arena. The right vertical wall of the arena is at position AD[0] */
GLfloat paddlePos[2];//position of paddle, the second element is just for the extended function
GLfloat paddleSpeed, paddleDir;//paddle speed and paddle direction
GLfloat changecolor;//change the color of the Arena

GLUquadricObj *quadratic;
//Storage for Our Quadratic Objects 

GLboolean pressedK = GL_FALSE, pressedL = GL_FALSE;//record the state of the key
GLboolean animated = GL_TRUE;//pause and resume the game
GLboolean controlcolor = GL_TRUE;//chang the model of Arena

GLint hp;//Life of the game

void  pingPongArena();//Pre diclear
void pingPongHp();//Pre diclear

				  //Function for init the pingPong game
void pingPongInit() {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	AD[0] = 0.2;
	AD[1] = 0.3;
	//initilization of the array

	X = 2;
	//initilization of the proportion

	P_width = 0.1 * 2 * X*AD[0];
	P_height = 0.0125 * 2 * X*AD[1];
	//BD[0]=0.1*2*X*AD[0];
	//BD[1]=0.0125*2*X*AD[1];

	R = 0.0125 * 2 * X*(AD[0] + AD[1]);
	//initilization of the ball's radius

	BD[0] = BD[1] = R;
	//initilization of the ball's dimensions

	ball_speed = 0.02;//speed of the ball

	ballPos[0] = 0; ballPos[1] = 0;
	//current position of the ball

	paddlePos[0] = 0;
	//initilization of the paddle positon

	paddleSpeed = 0.02;//initilization of the paddlt's speed
	paddleDir = 0;//initilization of the paddlt's direction
	hp = 5;//Life of the player
	changecolor = 0;//Changing color  
					//GUI of the game
	printf(" -----Welcome to pingPong Game------\n");
	printf("|Options                     Control|\n");
	printf("|k                    Panel to right|\n");
	printf("|l                     Panel to left|\n");
	printf("|s                     Ball speed up|\n");
	printf("|f                    Ball slow down|\n");
	printf("|r                           Restart|\n");
	printf("|Mouse Right         Pause and start|\n");
	printf("|Esc                            Quit|\n");
	printf(" -----------Good Luck---------------\n");
	printf(" >>     Five times per player     << \n");
}
//Count the times in game
void looselife() {
	printf("Loose a life\n");
	hp--;//Count the lift of the player
	changecolor = changecolor + 0.2;
	if (hp == 0) {
		printf("-------------Game Lost---------------\n");
		printf(">>Would you like to play again?\n");
		printf(">>'r' to replay and Esc to quit\n");
		animated = GL_TRUE;//Reset the value of pause control
	}
}

void pingPongPositions()
{
	if (animated) return;//pause and resume the game
	int i;

	/* move ball. You should do so by updating the variable ballPos. In the code below we move the ball
	vertically by 0.0001. */

	ballPos[0] += ball_speed * ballDir[0];
	ballPos[1] += 0.43*ball_speed * ballDir[1];

	paddlePos[0] += paddleSpeed * paddleDir;
	//moving of the paddle
	if (paddlePos[0]>X*AD[0] - 2 * 0.5*P_width) {
		paddlePos[0] = X * AD[0] - 2 * 0.5*P_width;
		//boundary limit on right
	}
	else if (paddlePos[0]<-X * AD[0] + 2 * 0.5*P_width) {
		paddlePos[0] = -X * AD[0] + 2 * 0.5*P_width;
		//boundary limit on left
	}

	if (pressedK)
		paddleDir = -1;//Paddle's direction change to the left
	else if (pressedL)
		paddleDir = 1;//Paddle's direction change to the right
	else
		paddleDir = 0;//Paddlt's moving stop
					  //pingPongHp();
					  //those can decied the direction and speed of the ball

					  /* detect wall collision. In the code below we check the vertical coordinates (i = 1)
					  We check if the upper wall is reached (ballPos[i] > AD[i] - BD[i]). If so then we reposition the ball
					  at the right place as shown in the lecture, and change the direction of the move. Note that the ball
					  has dimensions BD and therefore the reflection should be on the line AD[i] - BD[i]
					  */
					  /*
					  though for to achieve the reflection of each wall,because the wall are semmetry in math,
					  i.e:ceil and right wall; bottem and left wall.
					  */
	for (i = 0; i<2; i++) {
		//collision happened in the ceiling and right wall
		if (ballPos[i] > X*AD[i] - BD[i]) {
			ballPos[i] = X * AD[i] - BD[i] - (ballPos[i] + (BD[i] - X * AD[i]));
			//Set up the new position when collision happened
			ballDir[i] = -ballDir[i];
			//relection in y direction when the ball touch the upper wall
		}
		/* We check if the ball has reached the bottom wall. If so we stop the ball (ballPos[i] = -AD[i] + BD[i])
		*/
		//and,what's more,whether the ball reached the left wall.
		if (ballPos[i] < -X * AD[i] + BD[i]) {
			ballPos[i] = -X * AD[i] + BD[i];
			ballDir[i] = -ballDir[i];
			//relection in x snd y direction when the ball touch the upper wall
			if (i == 1) looselife();//Reduse the value of life when the ball touch the bottom
		}
	}//end of for()

	 //collision and reflection happened at the upper and down sufferces of the paddle
	if (ballPos[0]>paddlePos[0] - 2 * 0.5*P_width&&ballPos[0]<paddlePos[0] + 2 * 0.5*P_width) {
		//Reflection at upper sufferce of the paddle
		if (ballPos[1]<-0.8*AD[1] * X + 0.5*P_height + BD[0] && ballPos[1]>-0.8*AD[1] * X + 0.5*P_height) {
			ballPos[1] = -0.8*AD[1] * X + 0.5*P_height + BD[0];
			//Set up the new position when collision happened
			ballDir[1] = -ballDir[1];
		}
		//Reflection at lower sufferce of the paddle
		else if (ballPos[1]>-0.8*AD[1] * X - 0.5*P_height - BD[0] && ballPos[1]<-0.8*AD[1] * X - 0.5*P_height) {
			ballPos[1] = -0.8*AD[1] * X - 0.5*P_height - BD[0];
			//Set up the new position when collision happened
			ballDir[1] = -ballDir[1];
		}
	}


	//collision and reflection happened at the right and left sufferces of the paddle
	if (ballPos[0]>paddlePos[0] + 2 * 0.5*P_width&&ballPos[0]<paddlePos[0] + 2 * 0.5*P_width + BD[0]) {
		//Reflection at right sufferce of the paddle
		if (ballPos[1]>-0.8*AD[1] * X - 0.5*P_height - BD[0] && ballPos[1]<-0.8*AD[1] * X + 0.5*P_height + BD[0]) {
			ballPos[1] = -0.8*AD[1] * X;
			ballPos[0] = paddlePos[0] + 2 * 0.5*P_width + BD[0];
			//Set up the new position when collision happened
			ballDir[0] = -ballDir[0];
		}
		//Reflection at left sufferce of the paddle
		else if (ballPos[1]>-0.8*AD[1] * X - 0.5*P_height - BD[0] && ballPos[1]<-0.8*AD[1] * X + 0.5*P_height + BD[i]) {
			ballPos[1] = -0.8*AD[1] * X;
			ballPos[0] = paddlePos[0] - 2 * 0.5*P_width - BD[0];
			//Set up the new position when collision happened
			ballDir[0] = -ballDir[0];
		}
	}
	//pingPongPaddle();
	//pingPongArena();
	glutPostRedisplay();
	//call the Idle function again and again
}



void pingPongBall() {
	glColor3f(0, 0, 0);

	quadratic = gluNewQuadric();
	//Creat a pointer to the quadric object

	gluDisk(quadratic, 0.0, R, 32, 32);
	//Draw a disk,Parameters are:inner r,outter r,slics,ring	
}

//Creat the paddle
void pingPongPaddle() {

	glColor3f(1.0, 0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-2 * 0.5*P_width, -0.8*AD[1] * X + 0.5*P_height);
	//glVertex2f(-0.5*BD[0],-0.8*AD[1]*X+0.5*BD[1]);
	glVertex2f(2 * 0.5*P_width, -0.8*AD[1] * X + 0.5*P_height);
	//glVertex2f(0.5*BD[0],-0.8*AD[1]*X+0.5*BD[1]);      
	glVertex2f(2 * 0.5*P_width, -0.8*AD[1] * X - 0.5*P_height);
	//glVertex2f(0.5*BD[0],-0.8*AD[1]*X-0.5*BD[1]);      
	glVertex2f(-2 * 0.5*P_width, -0.8*AD[1] * X - 0.5*P_height);
	//glVertex2f(-0.5*BD[0],-0.8*AD[1]*X-0.5*BD[1]);    
	glEnd();
}

//Creat the arena
void pingPongArena() {
	glShadeModel(GL_FLAT);
	//printf("hihihiiamtesting\n");
	//using the color model FLAT
	glColor3f(changecolor, 0.75 - changecolor, 0.0);

	glBegin(GL_POLYGON);
	glVertex2f(-AD[0] * X, AD[1] * X);
	glVertex2f(AD[0] * X, AD[1] * X);
	glVertex2f(AD[0] * X, -AD[1] * X);
	glVertex2f(-AD[0] * X, -AD[1] * X);
	glEnd();
}

//Another display model
void pingPongArenaSmooth() {
	glShadeModel(GL_SMOOTH);

	glBegin(GL_POLYGON);
	glColor3f(0.2 + changecolor, 0.8 - changecolor, 0);
	glVertex2f(-AD[0] * X, AD[1] * X);
	glColor3f(0.3 + changecolor, 0, 0.9 - changecolor);
	glVertex2f(AD[0] * X, AD[1] * X);
	glColor3f(0 + changecolor, 0, 1 - changecolor);
	glVertex2f(AD[0] * X, -AD[1] * X);
	glColor3f(0 + changecolor, 1 - changecolor, 0);
	glVertex2f(-AD[0] * X, -AD[1] * X);
	glEnd();
}
//Draw the player's life bar
void pingPongHp() {
	glShadeModel(GL_FLAT);
	//printf("hihihiiamtesting\n");
	//using the color model FLAT
	glColor3f(0.6, 0.6, 0.6);

	glBegin(GL_POLYGON);
	glVertex2f(-AD[0] * X + 2 * changecolor*AD[0] * X, AD[1] * X + P_height);
	glVertex2f(AD[0] * X, AD[1] * X + P_height);
	glVertex2f(AD[0] * X, AD[1] * X - 0.5*P_height);
	glVertex2f(-AD[0] * X + 2 * changecolor*AD[0] * X, AD[1] * X - 0.5*P_height);
	glEnd();
}

//Callback function 
void pingPongDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//Convert the matrix to unit matrix

	pingPongHp();

	if (controlcolor)
		pingPongArena();
	else
		pingPongArenaSmooth();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(paddlePos[0], 0, 0);
	//though multiply dx,dy,dz to change the current matrix
	pingPongPaddle();

	glMatrixMode(GL_MODELVIEW);//set up current matrix mode
	glLoadIdentity();
	glTranslatef(ballPos[0], ballPos[1], 0);
	//Change the current matrix

	pingPongBall();


	glutSwapBuffers();
	//used when the mode is double buffer
}

void pingPongKeyDown(unsigned char key, int x, int y) {
	//Pressing ESC
	if (key == 27)
		exit(0);
	//Pressing K 
	else if (key == 'k') {
		pressedK = GL_TRUE;
		pressedL = GL_FALSE;
		paddleDir = -1;
	}
	//Pressing L
	else if (key == 'l') {
		paddleDir = 1;
		pressedL = GL_TRUE;
		pressedK = GL_FALSE;
	}
	else if (key == 's'&&ball_speed>0) {
		ball_speed -= 0.001;
	}
	else if (key == 'f') {
		ball_speed += 0.001;
	}
	else if (key == 'c') {
		controlcolor = !controlcolor;
		//Change the Arena of the game
	}
	//Replay the game
	else if (key == 'r') {
		pingPongInit();
		animated = !animated;
	}
	else //Check whether the key unusible in game is pressed
		printf("Pressing key < %c > does nothing \n", key);
}

void pingPongKeyUp(unsigned char key, int x, int y) {
	//printf("Pressing key < %c > is released \n",key);
	//Releasing K
	if (key == 'k') {
		pressedK = GL_FALSE;//Reset the state of direction controler
		pressedL = GL_FALSE;//Reset the state of direction controler
		paddleDir = 0;
	}
	//Releasing L
	else if (key == 'l') {
		paddleDir = 0;
		pressedL = GL_FALSE;//Reset the state of direction controler
		pressedK = GL_FALSE;//Reset the state of direction controler
	}
}

void pingPongMouse(int button, int state, int x, int y) {
	//Pause and resume the game
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		animated = !animated;
}
//main function
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	char *argv[] = { "hello ", " " };
	int argc = 2; // must/should match the number of strings in argv
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Ping Pong Game");
	glutDisplayFunc(pingPongDisplay);
	glutKeyboardFunc(pingPongKeyDown);
	glutKeyboardUpFunc(pingPongKeyUp);
	glutIdleFunc(pingPongPositions);
	glutMouseFunc(pingPongMouse);

	//glutSpecialFunc(pingPongKey);

	pingPongInit();
	glutMainLoop();
	return 0;
}