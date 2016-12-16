#pragma once
#include "glut.h"
#include "Globals.h"

// Function Declarations
void KeyPress(unsigned char pressedKey, int xPos, int yPos);
void SpecialKeyPress(int pressedKey, int xPos, int yPos);
void Timer(int value);
void Display();
void mouseMove(int x, int y);
void mouseButton(int button, int state, int x, int y);
void CreateTextures();
void SetLights();
void UpdateLight();
void ResizeWindow(GLsizei w, GLsizei h);
void drawEarthAndMoon();
void drawSun();
void drawSaturnRing();
void drawPlanets();
void drawPlanet(GLfloat orbitDuration,
	GLfloat orbitRadius, GLfloat rotationDuration, GLuint texturename, GLfloat radius);
void drawSky(void);

//Global Variables
GLfloat Azimuth = INITIAL_VIEWER_AZIMUTH; // 0
GLfloat Zenith = INITIAL_VIEWER_ZENITH;  // pi/2

// Variables to keep track of current day status.
GLfloat CurrentEarthRotation = 0.00;
GLfloat EarthDaysTranspired = 0.00;
GLfloat EarthDayIncrement = 0.01;

GLint currWindowSize[2] = { 750, 750 / ASPECT_RATIO };
GLint currViewportSize[2] = { 750, 750 / ASPECT_RATIO };

GLfloat ViewerDistance = INITIAL_VIEWER_DISTANCE;

// Initial Camera positions
const GLfloat LOOK_AT_POSITION1[] = { 0.0, 1.0, 0.0 };
GLfloat LOOK_AT_POSITION[] = { 0.0, 1.0, 10.0 };