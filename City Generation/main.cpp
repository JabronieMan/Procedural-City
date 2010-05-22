/* main.cpp
*/

#include "MyUtil.h"
#include "City.h"

using namespace std;

// Window Params
#define DEFAULT_WINDOW_WIDTH 1600
#define DEFAULT_WINDOW_HEIGHT 900

// Control Constants
#define MOUSE_SENSITIVITY 0.005
#define MOVEMENT_SPEED 0.1

#define STREETS 1

Camera cam;
Vec2 mouse;

//Building build;
//Building build2;
vector<Building> city = vector<Building>();

void buildCity()
{
	GLint bID = 1010;
	for(int i = BUILD_WIDTH / 2; i < CITY_WIDTH; i += (BUILD_WIDTH + STREET_WIDTH))
	{
		for(int j = BUILD_DEPTH / 2; j < CITY_DEPTH; j += (BUILD_DEPTH + STREET_WIDTH))
		{
			city.push_back(Building(STANDARD, BUILD_WIDTH, BUILD_DEPTH, Trans4x4(i, j), bID));
			bID++;
		}
	}
}

void drawCity()
{
	for(size_t i = 0; i < city.size(); i++)
	{
		city[i].draw();
	}
	glCallList(STREETS);
}


void createStreets(int index)
{
	GLUquadric *qobj = gluNewQuadric();
	gluQuadricNormals( qobj, GL_TRUE );
	glNewList( index, GL_COMPILE );
	glDisable( GL_LIGHTING );  // Use simple draw color.

	

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

	drawCity();

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
	double speed = MOVEMENT_SPEED;
	if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{
		speed *= 5;
	}
	switch(key)
	{
		case 'w':
		case 'W':
			moveForward(cam, speed);
			break;
		case 's':
		case 'S':
			moveForward(cam, -speed);
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
	glClearColor( 0.10, 0.10, 0.10, 0.0 ); // clear window.

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
	glMaterial( GL_DIFFUSE  , Color(0.1,0.1,0.1) );
	glMaterial( GL_SPECULAR , Color(1,1,1)  );
	glMaterial( GL_SHININESS, 100 );

	createStreets(STREETS);
	buildCity();

	glutMainLoop();
	return 0;
}

