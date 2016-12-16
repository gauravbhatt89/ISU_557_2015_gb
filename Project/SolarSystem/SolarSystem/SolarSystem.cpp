/* SolarSystem.cpp
 * Gaurav Bhatt 
 * Main file contains the structure of the program 
 */

// INCLUDES
#include <stdlib.h>
#include "SolarSystem.h"
#include "glut.h"
#include <math.h>
#include "Globals.h"
#include <SOIL.h>
#include <iostream>

float lx = 0.0f, lz = 0.0f;
float angle = 0.0f;
bool upView = false;
float deltaAngle = 0.0f;
int xOrigin = -1;

// The main function
int main(int argc, char** argv)
{
	glutInit (&argc, argv);

	// Set up the display window.
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH );
    glutInitWindowPosition( INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1] );
	glutInitWindowSize( currWindowSize[0], currWindowSize[1] );
    glutCreateWindow( "557: Solar System" );

	// Callbacks
	glutReshapeFunc( ResizeWindow );
	glutKeyboardFunc( KeyPress );
	glutSpecialFunc( SpecialKeyPress );
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glutDisplayFunc( Display );
	glutTimerFunc( 20, Timer, 1 );
	glViewport(0, 0, currWindowSize[0], currWindowSize[1]);

	// Set up standard lighting, shading, and depth testing.
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);							
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	glEnable(GL_NORMALIZE);
	glCullFace(GL_BACK);	
	glEnable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	SetLights();

	// Set up all texture maps and texture-mapped objects.
	CreateTextures();
	glutMainLoop();
	return 0;
}

void KeyPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition)
{
	char pressedChar = char(pressedKey);
	switch(pressedKey)
	{

		case '+': {
						EarthDayIncrement *= 2.0;
						if (EarthDayIncrement > 10.0)
							EarthDayIncrement = 10.0;
						break;
				  }
		case '-': {		
						EarthDayIncrement *= 0.5;
						if (EarthDayIncrement < 0.01)
							EarthDayIncrement = 0.01;
						break;
				  }
		case 'z': {
						ViewerDistance -= VIEWER_DISTANCE_INCREMENT;
						if (ViewerDistance < MINIMUM_VIEWER_DISTANCE)
							ViewerDistance = MINIMUM_VIEWER_DISTANCE;
						break; 
				  }
		case 'Z': {
						ViewerDistance += VIEWER_DISTANCE_INCREMENT;
						if (ViewerDistance > MAXIMUM_VIEWER_DISTANCE)
							ViewerDistance = MAXIMUM_VIEWER_DISTANCE;
						break; 
				  }
		case 's': {
			upView = true;
			Zenith += VIEWER_ANGLE_INCREMENT;
		}

		case 'd': {
			upView = true;
			Azimuth += VIEWER_ANGLE_INCREMENT;
		}
	}
}


void SpecialKeyPress(int pressedKey, int mouseXPosition, int mouseYPosition)
{
	glutIgnoreKeyRepeat(false);
	switch(pressedKey)
	{
		case GLUT_KEY_RIGHT: { 
			upView = false;
								angle += 0.01f;
								lx = sin(angle);
								lz = -cos(angle);
								break; 
							 }
		case GLUT_KEY_LEFT:  { 
			upView = false;
								angle -= 0.01f;
								lx = sin(angle);
								lz = -cos(angle);
								break; 
							 }
		case GLUT_KEY_UP:    { 
			upView = false;
								LOOK_AT_POSITION[0] += lx * 0.1f;
								LOOK_AT_POSITION[2] += lz * 0.1f;
								break; 
							 }
		case GLUT_KEY_DOWN:  { 
			upView = false;
								LOOK_AT_POSITION[0] -= lx * 0.1f;
								LOOK_AT_POSITION[2] -= lz * 0.1f;
								break; 
							 }
	}
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
	if (button == 3) {
		LOOK_AT_POSITION[0] += lx * 0.1f;
		LOOK_AT_POSITION[2] += lz * 0.1f;
	}
	if (button == 4) {
		// Zoom out
		LOOK_AT_POSITION[0] -= lx * 0.1f;
		LOOK_AT_POSITION[2] -= lz * 0.1f;
	}
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

void Timer(int value)
{
	CurrentEarthRotation += EarthDayIncrement;
	EarthDaysTranspired += EarthDayIncrement;
	if (EarthDaysTranspired == EARTH_ORBIT_DUR)
		EarthDaysTranspired = 0;
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

// Sets up lighting, camera angle and draw functions.
void Display()
{
	
	// Initialize lighting.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LIGHT_MODEL_AMBIENT);	
	glEnable(GL_LIGHTING);
	
	// Set up the properties of the viewing camera.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (upView) {
		// Position and orient viewer.
		gluLookAt(LOOK_AT_POSITION1[0] + ViewerDistance * sin(Zenith) * sin(Azimuth),
			LOOK_AT_POSITION1[1] + ViewerDistance * cos(Zenith),
			LOOK_AT_POSITION1[2] + ViewerDistance * sin(Zenith) * cos(Azimuth),
			LOOK_AT_POSITION1[0], LOOK_AT_POSITION1[1], LOOK_AT_POSITION1[2],
			0.0, 1.0, 0.0f);		
	}
	else {
		// Position and orient viewer.
		gluLookAt(LOOK_AT_POSITION[0], LOOK_AT_POSITION[1], LOOK_AT_POSITION[2],
			LOOK_AT_POSITION[0] + lx, LOOK_AT_POSITION[1], LOOK_AT_POSITION[2] + lz,
			0.0, 1.0, 0.0f);
	}

	// Render scene. Draw everything
	UpdateLight();
	//drawSky();
	drawSun();
	drawEarthAndMoon();
	drawPlanets();
	drawSaturnRing();

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glutSwapBuffers();
	glFlush();
}

GLuint loadTexture(char * filename) {
	GLuint texture = 0;
	char path[30] = "Textures\\";

	strcat(path, filename);
	texture = SOIL_load_OGL_texture(path,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		0);

	if (texture == NULL) {
		printf("Failed to load texture: %s\n",filename);
		exit(0); 
	}
	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //GL_REPEAT to fix the line bug, to see the bug, change it to GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	printf("Successfully loaded texture: %s\n", filename);
	return texture;
}


// Create the textures associated with all texture-mapped objects being displayed. //
void CreateTextures()
{
	SkyTexture = loadTexture("galaxy.bmp");
	EarthTexture = loadTexture("earth.bmp");
	MoonTexture = loadTexture("moon.bmp");
	SunTexture = loadTexture("sun.bmp");
	MercuryTexture = loadTexture("mercury.bmp");
	VenusTexture = loadTexture("venus.bmp");
	MarsTexture = loadTexture("mars.bmp");
	JupiterTexture = loadTexture("jupiter.bmp");
	SaturnTexture = loadTexture("saturn.bmp");
	UranusTexture = loadTexture("uranus.bmp");
	NeptuneTexture = loadTexture("neptune.bmp");
	PlutoTexture = loadTexture("pluto.bmp");
	RingTexture = loadTexture("ring.bmp");	
	return;
}

// Draw all the planets.
void drawPlanets(){
	drawPlanet(MERCURY_ORBIT_DUR, MERCURY_ORBIT_RADIUS,
			MERCURY_ROTATION_DUR, MercuryTexture, MERCURY_RADIUS);
	drawPlanet(VENUS_ORBIT_DUR, VENUS_ORBIT_RADIUS,
			VENUS_ROTATION_DUR, VenusTexture, VENUS_RADIUS);
	drawPlanet(MARS_ORBIT_DUR, MARS_ORBIT_RADIUS,
			MARS_ROTATION_DUR, MarsTexture, MARS_RADIUS);
	drawPlanet(JUPITER_ORBIT_DUR, JUPITER_ORBIT_RADIUS,
			JUPITER_ROTATION_DUR, JupiterTexture, JUPITER_RADIUS);
	drawPlanet(SATURN_ORBIT_DUR, SATURN_ORBIT_RADIUS,
			SATURN_ROTATION_DUR, SaturnTexture, SATURN_RADIUS);
	drawPlanet(URANUS_ORBIT_DUR, URANUS_ORBIT_RADIUS,
			URANUS_ROTATION_DUR, UranusTexture, URANUS_RADIUS);
	drawPlanet(NEPTUNE_ORBIT_DUR, NEPTUNE_ORBIT_RADIUS,
			NEPTUNE_ROTATION_DUR, NeptuneTexture, NEPTUNE_RADIUS);
	drawPlanet(PLUTO_ORBIT_DUR, PLUTO_ORBIT_RADIUS,
			PLUTO_ROTATION_DUR, PlutoTexture, PLUTO_RADIUS);

}

// Set the two lights to illuminate the scene. //
void SetLights()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT,  LIGHT_AMBIENT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);

	glLightfv(GL_LIGHT1, GL_AMBIENT,  LIGHT_AMBIENT);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);
	
	glLightfv(GL_LIGHT2, GL_AMBIENT,  LIGHT_AMBIENT);
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT2, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT2, GL_POSITION, LIGHT_2_POSITION);

	glLightfv(GL_LIGHT3, GL_AMBIENT,  LIGHT_AMBIENT);
	glLightfv(GL_LIGHT3, GL_DIFFUSE,  LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT3, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT3, GL_POSITION, LIGHT_3_POSITION);
}

// Enable the scene's lighting. //
void UpdateLight()
{
	glPushMatrix();
		glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);
		glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);
		glLightfv(GL_LIGHT2, GL_POSITION, LIGHT_2_POSITION);
		glLightfv(GL_LIGHT3, GL_POSITION, LIGHT_3_POSITION);
	glPopMatrix();
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

// Window-reshaping callback, adjusting the viewport to be as large  //
// as possible within the window, without changing its aspect ratio. //
void ResizeWindow(GLsizei w, GLsizei h)
{
	currWindowSize[0] = w;
	currWindowSize[1] = h;
	if (ASPECT_RATIO > w/h)
	{
		currViewportSize[0] = w;
		currViewportSize[1] = w / ASPECT_RATIO;
	}
	else
	{
		currViewportSize[1] = h;
		currViewportSize[0] = h * ASPECT_RATIO;
	}

	glViewport(0.5*(w-currViewportSize[0]), 0.5*(h-currViewportSize[1]), currViewportSize[0], currViewportSize[1]);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//Draws the texture-mapped earth and moon. //
void drawEarthAndMoon()
{
	GLfloat MoonRevolution = EarthDaysTranspired / LUNAR_CYCLE;
	GLfloat EarthRevolution = EarthDaysTranspired / EARTH_ORBIT_DUR;
	GLUquadricObj* quadro = gluNewQuadric();							
	gluQuadricNormals(quadro, GLU_SMOOTH);		
	gluQuadricTexture(quadro, GL_TRUE);			
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(-EARTH_RADIUS, 0.0, 0.0);
		glRotatef(360.0 * EarthRevolution, 0.0, 1.0, 0.0);
		glTranslatef(EARTH_RADIUS, 0.0, 0.0);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glPushMatrix();
				glRotatef( 360.0 * (EarthDaysTranspired/EARTH_ORBIT_DUR), 0.0, 1.0, 0.0);
				glTranslatef(EARTH_ORBIT_RADIUS, 0.0, 0.0 );
				glRotatef( 360.0 * CurrentEarthRotation, 0.0, 1.0, 0.0 );
				glRotatef( 90.0, 1.0, 0.0, 0.0 );
				glBindTexture(GL_TEXTURE_2D, EarthTexture);
				gluSphere(quadro, EARTH_RADIUS, 48, 48);
			glPopMatrix();
			glRotatef( 360.0 * (EarthDaysTranspired/EARTH_ORBIT_DUR), 0.0, 1.0, 0.0);
			glTranslatef(EARTH_ORBIT_RADIUS, 0.0, 0.0 );
			glRotatef( 360.0 * MoonRevolution, 0.0, 1.0, 0.0 );
			glTranslatef( MOON_ORBIT_RADIUS  , 0.0, 0.0 );
			glBindTexture(GL_TEXTURE_2D, MoonTexture);
			gluSphere(quadro, MOON_RADIUS, 48, 48);
		glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}

//GLUquadric * quadric;

/* No Easy way to do it as of now. I will update this code later */
void drawSky(void) {
	/*
	quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	
	gluQuadricTexture(quadric, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, SkyTexture);
				gluSphere(quadric, 1000, 48, 48);
			glPushMatrix();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadric);
	*/
}

//Function to draw and texture map the sun at the origin
void drawSun()
{
	GLUquadric* quadro = gluNewQuadric();		
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricDrawStyle(quadro, GLU_FILL);
	
	gluQuadricTexture(quadro, GL_TRUE);
	
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glPushMatrix();
				glRotatef( -90.0, 1.0, 0.0, 0.0 );
				glBindTexture(GL_TEXTURE_2D, SunTexture);
				gluSphere(quadro, SUN_RADIUS, 48, 48);
			glPopMatrix();
		glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}


//Draw Rings
void drawSaturnRing()
{
	GLUquadricObj* quadro = gluNewQuadric();							
	gluQuadricNormals(quadro, GLU_SMOOTH);		
	gluQuadricTexture(quadro, GL_TRUE);			
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		GLfloat Revolution = EarthDaysTranspired / SATURN_ORBIT_DUR;
		glTranslatef(-SATURN_RADIUS, 0.0, 0.0);
		glRotatef(360.0 * Revolution, 0.0, 1.0, 0.0);
		glTranslatef(SATURN_RADIUS, 0.0, 0.0);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glPushMatrix();
				glRotatef( 360.0 * (EarthDaysTranspired/SATURN_ORBIT_DUR), 0.0, 1.0, 0.0);
				glTranslatef(SATURN_ORBIT_RADIUS, 0.0, 0.0 );
				glRotatef( -90.0, 1.0, 0.0, 0.0 );
				glBindTexture(GL_TEXTURE_2D, RingTexture);
				glScalef(1,1,.02);
				gluSphere(quadro, SATURN_RADIUS*2, 48, 48);
			glPopMatrix();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}


void drawPlanet(GLfloat orbitDuration,
		GLfloat orbitRadius, GLfloat rotationDuration, GLuint texturename, GLfloat radius)
{
	GLUquadricObj* quadro = gluNewQuadric();							
	gluQuadricNormals(quadro, GLU_SMOOTH);		
	gluQuadricTexture(quadro, GL_TRUE);			
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();

			GLfloat Revolution = EarthDaysTranspired / orbitDuration;
			glTranslatef(-radius, 0.0, 0.0);
			glRotatef(360.0 * Revolution, 0.0, 1.0, 0.0);
			glTranslatef(radius, 0.0, 0.0);
		
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glPushMatrix();
				//glRotatef( inclination, 0.0, 0.0, 1.0);
				glRotatef( 360.0 * (EarthDaysTranspired/orbitDuration), 0.0, 1.0, 0.0);
				glTranslatef(orbitRadius, 0.0, 0.0 );
				glRotatef( 360.0 * (CurrentEarthRotation/rotationDuration), 0.0, 1.0, 0.0 );
				glRotatef( -90.0, 1.0, 0.0, 0.0 );
				glBindTexture(GL_TEXTURE_2D, texturename);
				gluSphere(quadro, radius, 48, 48);
			glPopMatrix();
		glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}


