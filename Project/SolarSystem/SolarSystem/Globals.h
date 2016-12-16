#ifndef SS_GLOBALS_H 
#define SS_GLOBALS_H

/* SolarSystemGlobals.h
 * Gaurav Bhatt
 * Contains global variables and declarations.
 */

const GLfloat PI = 3.1415926535;
const GLfloat TO_RADIANS = PI/180.0;

// Window Position/Resizing Constants
const GLint INIT_WINDOW_POSITION[2] = { 250, 250 };
const GLfloat ASPECT_RATIO = 1.5;


// Lighting settings
const GLfloat LIGHT_0_POSITION[]    = { 1.0, 0.0, 0.0, 0.0};
const GLfloat LIGHT_1_POSITION[]    = { -1.0, 0.0, 0.0, 0.0};
const GLfloat LIGHT_2_POSITION[]    = { 0.0, 0.0, 1.0, 0.0};
const GLfloat LIGHT_3_POSITION[]    = { 0.0, 0.0, -1.0, 0.0};
const GLfloat LIGHT_AMBIENT[]       = { 0.8, 0.8, 0.8, 1.0};
const GLfloat LIGHT_DIFFUSE[]       = { 0.9, 0.9, 0.9, 1.0};
const GLfloat LIGHT_SPECULAR[]      = { 1.0, 1.0, 1.0, 1.0};
const GLfloat LIGHT_MODEL_AMBIENT[] = { 0.2, 0.2, 0.2, 1.0};

const GLfloat MOON_ORBIT_RADIUS = 0.30;
const GLfloat EARTH_ROTATION    = 1.00;
const GLfloat LUNAR_CYCLE       = 30.0;

const GLfloat MAXIMUM_VIEWER_DISTANCE    = 20;
const GLfloat MINIMUM_VIEWER_DISTANCE    = 2;
const GLfloat INITIAL_VIEWER_DISTANCE    = 10;
const GLfloat VIEWER_DISTANCE_INCREMENT  = 0.1;
const GLfloat INITIAL_VIEWER_AZIMUTH     = 0.0;
const GLfloat INITIAL_VIEWER_ZENITH      = PI / 2.0;
const GLfloat VIEWER_ANGLE_INCREMENT     = PI / 60.0;

// Radius of the planets
// Values are not accurate.
const GLfloat MOON_RADIUS =     0.04;
const GLfloat MERCURY_RADIUS =	0.10;
const GLfloat VENUS_RADIUS =	0.18;
const GLfloat EARTH_RADIUS =    0.18;
const GLfloat MARS_RADIUS = 	0.30;
const GLfloat JUPITER_RADIUS = 	0.60;
const GLfloat SATURN_RADIUS = 	0.50;
const GLfloat URANUS_RADIUS = 	0.30;
const GLfloat NEPTUNE_RADIUS = 	0.30;
const GLfloat PLUTO_RADIUS = 	0.05;
const GLfloat SUN_RADIUS = 		1.00;

// Relatively values of the distance of planet from the centre
// Values are not accurate. 
const GLfloat MERCURY_ORBIT_RADIUS = 1.5;
const GLfloat VENUS_ORBIT_RADIUS =	 2.0;
const GLfloat EARTH_ORBIT_RADIUS =   2.8;
const GLfloat MARS_ORBIT_RADIUS = 	 3.7;
const GLfloat JUPITER_ORBIT_RADIUS = 5.5;
const GLfloat SATURN_ORBIT_RADIUS =  8.0;
const GLfloat URANUS_ORBIT_RADIUS =	 9.5;
const GLfloat NEPTUNE_ORBIT_RADIUS = 10.5;
const GLfloat PLUTO_ORBIT_RADIUS = 	 11.5;


// Approximate values to show the rotation of the planets
// Values are not accurate. 
const GLfloat MERCURY_ROTATION_DUR = 59;
const GLfloat VENUS_ROTATION_DUR=	 140;
const GLfloat MARS_ROTATION_DUR= 	 30;
const GLfloat JUPITER_ROTATION_DUR=  0.4;
const GLfloat SATURN_ROTATION_DUR=   0.4;
const GLfloat URANUS_ROTATION_DUR=	 -0.7;
const GLfloat NEPTUNE_ROTATION_DUR=  0.7;
const GLfloat PLUTO_ROTATION_DUR= 	 -6;


// Approximate values of the orbit duration of all the planets. 
// Its some random number to show the movement if the planets.
// Its in relatively increasing order but not exactly accurate.
const GLfloat MERCURY_ORBIT_DUR = 88;
const GLfloat VENUS_ORBIT_DUR = 150;
const GLfloat EARTH_ORBIT_DUR = 365;
const GLfloat MARS_ORBIT_DUR = 400;
const GLfloat JUPITER_ORBIT_DUR = 1000;
const GLfloat SATURN_ORBIT_DUR = 2000;
const GLfloat URANUS_ORBIT_DUR = 3000;
const GLfloat NEPTUNE_ORBIT_DUR = 3500;
const GLfloat PLUTO_ORBIT_DUR = 4000;

// IDs for textures
GLuint SunTexture = 0;
GLuint MercuryTexture = 1;
GLuint VenusTexture = 2;
GLuint EarthTexture = 3;
GLuint MoonTexture = 4;
GLuint MarsTexture = 5;
GLuint JupiterTexture = 6;
GLuint SaturnTexture = 7;
GLuint UranusTexture = 8;
GLuint NeptuneTexture = 9;
GLuint PlutoTexture = 10;
GLuint RingTexture = 11;
GLuint SkyTexture = 12;

#endif