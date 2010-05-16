/* main.cpp
*/

#include "MyUtil.h"
#include "City.h"

using namespace std;

// Window Params
#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

// Control Constants
#define MOUSE_SENSITIVITY 0.005
#define MOVEMENT_SPEED 0.1

Camera cam;
Vec2 mouse;

Building build;

void make_grid(int index)
{
	GLUquadric *qobj = gluNewQuadric();
	gluQuadricNormals( qobj, GL_TRUE );
	glNewList( index, GL_COMPILE );
	glDisable( GL_LIGHTING );  // Use simple draw color.

	glColor3f(0, 0, 0);
	bool black = true;
	for(int i = -10; i <=10; i++)
	{
		for(int j = -10; j <= 10; j++)
		{
			glPushMatrix();
			glMultMatrix(Trans4x4(i, j));
			glutSolidCube(1.0);
			glPopMatrix();
			if(black)
			{
				glColor3f( 1, 1, 1 );
				black = false;
			}
			else
			{
				glColor3f( 0, 0, 0 );
				black = true;
			}
		}
	}

	glEndList();
	gluDeleteQuadric(qobj);
}

//Does all the drawing 
void display( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear frame buffer

	// Set up the viewing frustum.  Zooming will be performed here by changing the size
	// of the XY extent of the frustum.
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum( -cam.halfWidth, cam.halfWidth, -cam.halfHeight, cam.halfHeight, cam.zNear, cam.zFar );

	
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	calculateCameraRotation(cam);
	gluLookAt(cam);

	glEnable( GL_LIGHTING );
	glEnable( GL_NORMALIZE );

	//glCallList(1);

	build.draw();

	glFlush();
	glutSwapBuffers();
}
// This is the function that we will tell OpenGL to call
// whenever a mouse button is pressed or released.
void mouse_button( int button, int state, int xPos, int yPos )
{
	glutPostRedisplay();
}

// Alters the scene based on mouse motion
// Depends on if anything is selected
void mouse_motion( int x, int y )
{
	double deltaX = x - mouse.x;
	double deltaY = y - mouse.y;
	
	// Camera Rotation
	rotateHorizontal(cam, MOUSE_SENSITIVITY * deltaY);
	rotateVertical(cam, MOUSE_SENSITIVITY * deltaX);
	
	mouse = Vec2(x, y);
	glutPostRedisplay();
}

// This is the function that we will tell OpenGL to call
// whenever a key on the keyboard is pressed.
void key_press( unsigned char key, int x, int y )
{
	switch(key)
	{
		case 'w':
		case 'W':
			moveForward(cam, MOVEMENT_SPEED);
			break;
		case 's':
		case 'S':
			moveForward(cam, -MOVEMENT_SPEED);
			break;
		case 'q':
		case 'Q':
			exit(0);
	
	}
	glutPostRedisplay();
}

// Process "special" key-press events.  This includes the arrow keys, the
// "home" key, and the "PageUp" and "PageDown" keys.  Notice that the first
// argument is an "int" rather than an "unsighed char".
// Currently not used, but may be used for "Bonus" questions.
void special_key_press( int key, int x, int y ) 
{
	 switch( key )
	 {
		 case up_arrow_key:
		 break;

		 case down_arrow_key: 
		 break;

		 case left_arrow_key:
		 break;

		 case right_arrow_key:
		 break;
	 }
	 glutPostRedisplay();
}

//Just keep track of where the mouse was last
//Used for keyboard key stroke based deletion
void mouse_passive_motion( int x, int y )
{
	mouse = Vec2(x, y);
}

int main( int argc, char** argv )
{
	// Seed the random number generator, this only should happen once
	srand (time(NULL));

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize( DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT );
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow( "Welcome to Polyville" );
	glClearColor( 0.20, 0.30, 0.50, 0.0 ); // clear window.

	glutDisplayFunc( display );
	glutMouseFunc( mouse_button );
	glutMotionFunc( mouse_motion );
	glutKeyboardFunc( key_press );
	glutSpecialFunc( special_key_press );
	glutPassiveMotionFunc( mouse_passive_motion );

	static float white[] = { 0.8, 0.8, 0.8, 1.0 };

	glEnable( GL_DEPTH_TEST ); // Turn on depth buffering.

	glEnable( GL_LIGHT0 );
	glLightfv( GL_LIGHT0, GL_AMBIENT , white );
	glLightfv( GL_LIGHT0, GL_DIFFUSE , white );
	glLightfv( GL_LIGHT0, GL_SPECULAR, white );

	set_light_position( GL_LIGHT0, Vec3( 2, 3, 5 ) );

	glMaterial( GL_AMBIENT  , Color(0.2,0.1,0.1) );
	glMaterial( GL_DIFFUSE  , Color(0.8,0.4,0.1) );
	glMaterial( GL_SPECULAR , Color(1,1,1)  );
	glMaterial( GL_SHININESS, 100 );

	build = Building(STANDARD, 8, 8, Mat4x4::Identity(), 10);

	//make_grid(1);

	glutMainLoop();
	return 0;
}

