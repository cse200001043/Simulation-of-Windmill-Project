#include <bits/stdc++.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h> 
using namespace std;



#define PI 3.14159265359

/* Global variables */
char title[] = "Windmill Simulation";

//variable used for rotation of windmill blade
GLfloat angleBlade = 0.0f; 

//variables used for rotation for 360 degree view
GLfloat angleWindmill = 0.0f;
GLfloat angleWindmillX = 0.0f;
GLfloat angleWindmillY = 0.0f;
GLfloat angleWindmillZ = 0.0f;

//variables for windspeed and energy
float varWindSpeed = 0;
float varEnergyGenerated = 0;
float varChange = 0;


int angleRotateBlade1 = 0;
int angleRotateBlade2 = 0;
int angleRotateBlade3 = 0;
GLfloat windmillSpeed = 1;
GLfloat windmillSpeed1 = 0;

//variable defining autoMode and manual mode
GLfloat autoMode = 1;
GLint Xaxis = 0;
GLint Yaxis = 0;

int glowHouse = 0;
GLfloat scalefactor = 1.0f;
//the refresh display time interval
int refreshMills = 15;

//variables used to keep track of mouse clicks
int onMouse=0;
int onMouse1=0;
int onMouse2=0;
int onMouse3=0;
int onMouse4=0;
int onMouse21=0;
int onMouse22=0;
int viewNumber = 0;
int totalViews = 6;

//variables for displaying individual objects
int enableWindmill = 0;
int enableHouse = 0;
int enableBackground = 0;
int enableTransformer = 0;
int enableComplete = 1;



GLfloat cloud_pos_x = -10.0f;
GLfloat cloud_pos_y = 5.0f;
GLfloat cloud_speed = 0.02f;
GLfloat cloud_size = 2.0f;
GLfloat cloud_r = 1.0f;
GLfloat cloud_g = 1.0f;
GLfloat cloud_b = 1.0f;
GLfloat cloud_alpha = 0.5f;
int cloud_num_circles = 5;
GLfloat cloud_circle_radius = 0.5f;


GLuint texture[7];


#define GRID_SIZE 500
#define GRID_SPACING 0.1

//2-D matrix used to store heights at point x,z
vector <vector<float>> terrain(GRID_SIZE, vector<float>(GRID_SIZE));

GLfloat position[] = { 0.0, 0.0, 1.0, 0.0 };

//setting up the light
void initLighting()
{
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    if(viewNumber == 0)
    {
      glEnable(GL_LIGHTING);
    }
   //setting up light sources we used 4 of them

    glEnable(GL_LIGHT0);

   //setting the ambient and diffuse component of the light
    GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
   //  GLfloat position[] = { 0.0, 0.0, 100.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT1);

    GLfloat ambient1[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat diffuse1[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat specular1[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat position1[] = { 1.0, 0.0, 0.0, 0.0 };

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);

    glEnable(GL_LIGHT2);

    GLfloat ambient2[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat diffuse2[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat specular2[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat position2[] = { -1.0, 0.0, 0.0, 0.0 };

    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient1);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular1);
    glLightfv(GL_LIGHT2, GL_POSITION, position1);

    

}

//setting up the material properties
void initMaterial()
{
    GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat shininess[] = { 0.0 };

   //  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
   //  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
   //  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
   //  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//function to change material properties of a surface
void materialColor(float r, float g, float b){
   GLfloat ambient[] = { min(r+0.0, 0.3), min(g+0.0, 0.3), min(b+0.0, 0.3), 1.0 };
   if(r + min(r+0.0, 0.3) > 1){
      r = 1 - min(r+0.0, 0.3);
   }
   if(g + min(g+0.0, 0.3)> 1){
      g = 1 - min(g+0.0, 0.3);
   }
   if(b + min(b+0.0, 0.3)> 1){
      b = 1 - min(g+0.0, 0.3);
   }
    GLfloat diffuse[] = { r,g, b, 0.0 };
    GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat shininess[] = { 0.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}


/*Include components from the respective files*/

/*This file contains all basic shapes used further to draw complex objects*/

/*Draw a cone with base radius 0.35 and height 2.5*/
void drawCone(void)
{

   GLdouble base = 0.35;
   GLdouble height = 2.5;
   GLint slices = 50;
   GLint stacks = 50;
   glMatrixMode(GL_MODELVIEW);
   
   glTranslatef(0.0, 0.0, 0.0);
   glColor3f(1, 1, 1);

   // rotation by 90 degrees clockwise about X axis
   glRotatef(-90, 1.0, 0.0, 0.0);

   glScalef(1.0, 1.0, 1.0);

   // built-in function to draw a Cone.
   glutSolidCone(base, height, slices, stacks);

   glFlush();
}

/*Draw a hemisphere with radius R as parameter passes*/
void drawHemisphere(float R)
{
   int i, j;

   glRotatef(90, 1.0, 0.0, 0.0);

   glPolygonMode(GL_FRONT_AND_BACK, GL_FRONT_FACE);

   int p = 60;  // Number of longitudinal slices in the hemisphere.
   int q = 40;  // Number of latitudinal slices in the hemisphere.


   for (j = 0; j < q; j++)
   {
      // draw One latitudinal triangle strip.
      glBegin(GL_TRIANGLE_STRIP);
      for (i = 0; i <= p; i++)
      {
         glVertex3f(R * cos((float)(j + 1) / q * PI / 2.0) * cos(2.0 * (float)i / p * PI),
                    R * sin((float)(j + 1) / q * PI / 2.0),
                    R * cos((float)(j + 1) / q * PI / 2.0) * sin(2.0 * (float)i / p * PI));
         glVertex3f(R * cos((float)j / q * PI / 2.0) * cos(2.0 * (float)i / p * PI),
                    R * sin((float)j / q * PI / 2.0),
                    R * cos((float)j / q * PI / 2.0) * sin(2.0 * (float)i / p * PI));
      }
      glEnd();
   }
}

/*draw cylinder with parameter as radius, height and color of the cylinder*/
void draw_cylinder(GLfloat radius, GLfloat height, GLfloat R, GLfloat G, GLfloat B)
{
   GLfloat x = 0.0;
   GLfloat y = 0.0;
   GLfloat angle = 0.0;
   GLfloat angle_stepsize = 0.1;

   /* Draw the tube */
   glColor3f(R, G, B);
   glBegin(GL_QUAD_STRIP);
   angle = 0.0;
   while (angle < 2 * PI)
   {
      x = radius * cos(angle);
      y = radius * sin(angle);
      glVertex3f(x, y, height);
      glVertex3f(x, y, 0.0);
      angle = angle + angle_stepsize;
   }

   glVertex3f(radius, 0.0, height);
   glVertex3f(radius, 0.0, 0.0);
   glEnd();

   /* Draw the circle on top of cylinder */
   glColor3f(R, G, B);
   glBegin(GL_POLYGON);
   angle = 0.0;
   while (angle < 2 * PI)
   {
      x = radius * cos(angle);
      y = radius * sin(angle);
      glVertex3f(x, y, height);
      angle = angle + angle_stepsize;
   }
   glVertex3f(radius, 0.0, height);
   glEnd();

   /* Draw the circle at the bottom of cylinder */
   glColor3f(R, G, B);
   glBegin(GL_POLYGON);
   angle = 0.0;
   while (angle < 2 * PI)
   {
      x = radius * cos(angle);
      y = radius * sin(angle);
      glVertex3f(x, y, 0.0);
      angle = angle + angle_stepsize;
   }
   glVertex3f(radius, 0.0, 0.0);

   glEnd();
}

/*Draws a cirlce with the given radius and color specified as R, G, B arguments*/
void drawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
   GLfloat x = 0.0;
   GLfloat y = 0.0;
   GLfloat angle = 0.0;
   GLfloat angle_stepsize = 0.1; // this decides the number of parts divided to draw smaller gives better circle
   
   glColor3f(R, G, B);
   glBegin(GL_POLYGON);
   angle = 0.0;
   while (angle < 2 * PI)
   {
      x = radius * cos(angle);
      y = radius * sin(angle);
      glVertex3f(x, y, 0.0);
      angle = angle + angle_stepsize;
   }
   glVertex3f(radius, 0.0, 0.0);

   glEnd();
}

/*Draws a frustum with the given base and top radius, height and color*/
void draw_frustrum(GLfloat radius1, GLfloat radius2, GLfloat height, GLfloat R, GLfloat G, GLfloat B)
{
   GLfloat x1 = 0.0;
   GLfloat y1 = 0.0;
   GLfloat x2 = 0.0;
   GLfloat y2 = 0.0;
   GLfloat angle = 0.0;
   GLfloat angle_stepsize = 0.1;

   //rotate about negative x-axis by 90 degrees anticlockwise
   glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
   glTranslatef(0.0f, 0.0f, -height);

   /** Draw the tube */
   glColor3f(R, G, B);
   glBegin(GL_QUAD_STRIP);
   angle = 0.0;
   while (angle < 2 * PI)
   {
      x1 = radius1 * cos(angle);
      y1 = radius1 * sin(angle);
      x2 = radius2 * cos(angle);
      y2 = radius2 * sin(angle);
      glVertex3f(x1, y1, height);
      glVertex3f(x2, y2, 0.0);
      angle = angle + angle_stepsize;
   }
   glVertex3f(radius1, 0.0, height);
   glVertex3f(radius2, 0.0, 0.0);
   glEnd();

   /** Draw the circle on top of frustum */
   glColor3f(R, G, B);
   glBegin(GL_POLYGON);
   angle = 0.0;
   while (angle < 2 * PI)
   {
      x1 = radius1 * cos(angle);
      y1 = radius1 * sin(angle);
      glVertex3f(x1, y1, height);
      angle = angle + angle_stepsize;
   }
   glVertex3f(radius1, 0.0, height);
   glEnd();

   /** Draw the circle on bottom of frustum */
   glColor3f(R, G, B);
   glBegin(GL_POLYGON);
   angle = 0.0;
   while (angle < 2 * PI)
   {
      x2 = radius2 * cos(angle);
      y2 = radius2 * sin(angle);
      glVertex3f(x2, y2, 0.0);
      angle = angle + angle_stepsize;
   }
   glVertex3f(radius2, 0.0, 0.0);

   glEnd();
}

/*This file contains code for the windmill structure*/

//this function creates a individual blade of windmill
void drawBlade_basic()
{
   glBegin(GL_TRIANGLES); 
   // Define vertices in counter-clockwise (CCW) order with normal pointing out

   // Front Left Top face of blade
   glColor3f(0.0f, 1.0f, 0.0f); // Green
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(0.2f, 0.2f, 0.0f);
   glVertex3f(0.2f, 0.0f, 0.2f);

   // Front Right Top face of blade
   glColor3f(0.0f, 1.0f, 0.0f); // Green
   glVertex3f(0.2f, 0.2f, 0.0f);
   glVertex3f(1.5f, 0.0f, 0.0f);
   glVertex3f(0.2f, 0.0f, 0.2f);

   // Front Right Bottom face of blade
   glColor3f(1.0f, 1.0f, 0.0f); // Yellow
   glVertex3f(0.2f, 0.0f, 0.2f);
   glVertex3f(1.5f, 0.0f, 0.0f);
   glVertex3f(0.2f, -0.2f, 0.0f);

   // Front Left Bottom face of blade
   glColor3f(1.0f, 1.0f, 0.0f); // Yellow
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(0.2f, 0.0f, 0.2f);
   glVertex3f(0.2f, -0.2f, 0.0f);

   // Back Left Top face of blade
   glColor3f(1.0f, 0.0f, 0.0f); // Red
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(0.2f, 0.2f, 0.0f);
   glVertex3f(0.2f, 0.0f, -0.2f);

   // Back Right Top face of blade
   glColor3f(1.0f, 0.0f, 0.0f); // Red
   glVertex3f(0.2f, 0.2f, 0.0f);
   glVertex3f(1.5f, 0.0f, 0.0f);
   glVertex3f(0.2f, 0.0f, -0.2f);

   // Back Right Bottom face of blade
   glColor3f(0.0f, 0.0f, 1.0f); // Blue
   glVertex3f(0.2f, 0.0f, -0.2f);
   glVertex3f(1.5f, 0.0f, 0.0f);
   glVertex3f(0.2f, -0.2f, 0.0f);

   // Back Left Bottom face of blade
   glColor3f(0.0f, 0.0f, 1.0f); // Blue
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(0.2f, 0.0f, -0.2f);
   glVertex3f(0.2f, -0.2f, 0.0f);
   glEnd(); 
}

//orients the raw drawn blade in proper position
void drawBlade()
{
   glPushMatrix();
   glTranslated(0.20f, 0.0f, 0.0f);
   glScalef(1.2f, 1.0f, 1.0f);
   drawBlade_basic();
   glPopMatrix();
}

//function to calculate the rotation angle of the windmill
int calculateRotationAngle(int angle)
{
   //angle should lie between 0 to 90
   angle%=90;
   if(angle<0)angle+=90; //if angle negative add 90
   if(angle>=0 && angle<=45)return angle;
   if(angle>=45 && angle<=90)return (45-(angle-45));
   // if(angle>=90 && angle<=135)return (-(angle-90));
   // if(angle>=135 && angle<=180)return (angle-180);
   // if(angle>=180 && angle<=225)return angle;
   // if(angle>=225 && angle<=270)return angle;
   // if(angle>=270 && angle<=315)return angle;
   // if(angle>=315 && angle<=360)return angle;
   return angle;
}

/*combine windmill parts to create the whole structure at co-ordinate x,y,z*/
void drawWindmill(float x, float y, float z, float sx, float sy, float sz)
{
    glTranslatef(x,y,z); 
   glScalef(sx, sy, sz);
   glRotatef(windmillSpeed1, 0, 1,0);
   glRotatef(180, 0.0f, 1.0f, 0.0f);

   glTranslated(0.0f, 0.0f, -0.5f);

   //drawing three blades and rotating them periodically using global variable angleBlade

   glPushMatrix(); 
   glTranslated(0.0f, 1.0f, 0.0f);
   glRotatef(angleBlade, 0.0f, 0.0f, 1.0f); 
   glRotatef(calculateRotationAngle(angleRotateBlade1), 0.0f, 1.0f, 0.0f);
   // glRotatef(angleBlade, 0.0f, 1.0f, 0.0f);
   drawBlade();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0.0f, 1.0f, 0.0f);
   glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
   glRotatef(angleBlade, 0.0f, 0.0f, 1.0f);
   glRotatef(calculateRotationAngle(angleRotateBlade2), 0.0f, 1.0f, 0.0f);
   drawBlade();
   glPopMatrix();

   glPushMatrix();
   glTranslated(0.0f, 1.0f, 0.0f);
   glRotatef(240.0f, 0.0f, 0.0f, 1.0f);
   glRotatef(angleBlade, 0.0f, 0.0f, 1.0f);
   glRotatef(calculateRotationAngle(angleRotateBlade3), 0.0f, 1.0f, 0.0f);
   drawBlade();
   glPopMatrix();

   //draw the axle
   glPushMatrix();
   glTranslatef(0.0f, 1.0f, 0.0f);
   glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
   glColor3f(0.5, 0, 1);
   drawHemisphere(0.2);
   glPopMatrix();

   //draw the energy tower modeled as a frustum
   glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.5f);
    draw_frustrum(0.1f, 0.4f, 3.0f, 0.10, 0.4f, 0.8f);
    glPopMatrix();

   //drawing the base of the windmill
   
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    draw_cylinder(0.2f, 1.0f, 0.15, 1.0, 0.95);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -1.8f, 0.5f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_cylinder(0.6f, 0.2f, 0.15, 1.0, 0.95);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -1.9f, 0.5f);
    draw_frustrum(0.6f, 0.9f, 0.2f, 0.10, 0.4f, 0.8f);
    glPopMatrix();
}



/*This file contains all structure of transformer*/

/*draw the ring structures of given radius and color*/
void drawRings(GLfloat r, GLfloat R, GLfloat G, GLfloat B)
{

   //we are using the draw_cylinder function defined in the figure.cpp file
   glPushMatrix();
   glTranslated(0.0f, 1.0f, 0.0f);
   glRotated(90,0,1,0);
   draw_cylinder(r, 1, R,G,B);
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.0f, 1.0f, 0.0f);
   draw_cylinder(r, 1, R,G,B);
   glPopMatrix();

   glPushMatrix();
   glTranslated(0.0f, 1.0f, 1.0f);
   glRotated(180,0,1,0);
   draw_cylinder(r, 1, R,G,B);
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.0f, 1.0f, 1.0f);
   glRotated(-90,0,1,0);
   draw_cylinder(r, 1, R,G,B);
   glPopMatrix();
}

/* function to create the outer structute of the object built */
void drawTransformerPipes(float r)
{
   int angle = 6;

   /* using different smaller rectangles to built the complete structure at different angles */
   glPushMatrix();
   glTranslated(0.0f, 1.0f, 0.0f);
   glScaled(1, 1.2, 1.3);
   glRotatef(90+angle, 1.0f, 0.0f, 0.0f);
   glRotatef(-angle, 0.0f, 1.0f, 0.0f);
   draw_cylinder(r, 4, 1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.0f, 1.0f, 0.0f);
   glScaled(1, 1.2, 1.3);
   glRotatef(90+angle, 1.0f, 0.0f, 0.0f);
   glRotatef(angle, 0.0f, 1.0f, 0.0f);
   draw_cylinder(r, 4, 1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(0.0f, 1.0f, 1.0f);
   glScaled(1, 1.2, 1.3);
   glRotatef(90-angle, 1.0f, 0.0f, 0.0f);
   glRotatef(-angle, 0.0f, 1.0f, 0.0f);
   draw_cylinder(r, 4, 1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.0f, 1.0f, 1.0f);
   glScaled(1, 1.2, 1.3);
   glRotatef(90-angle, 1.0f, 0.0f, 0.0f);
   glRotatef(angle, 0.0f, 1.0f, 0.0f);
   draw_cylinder(r, 4, 1,0,0);
   glPopMatrix();


   glPushMatrix();
   glTranslatef(0.0f, 0.0f, 0.0f);
   glTranslatef(0.6f, 0.6f, 0.0f);
   glScalef(1.0f, 1.0f, 1.0f);
   glTranslatef(-0.6f, -0.6f, 0.0f);
   drawRings(r,1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.0f, -1.0f, -0.09f);
   glTranslatef(0.6f, 0.6f, 0.0f);
   glScalef(1.13f, 1.0f, 1.13f);
   glTranslatef(-0.6f, -0.6f, 0.0f);
   drawRings(r,1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.04f, -2.0f, -0.18f);
   glTranslatef(0.6f, 0.6f, 0.0f);
   glScalef(1.35f, 1.0f, 1.35f);
   glTranslatef(-0.6f, -0.6f, 0.0f);
   drawRings(r,1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.06f, -3.0f, -0.25f);
   glTranslatef(0.6f, 0.6f, 0.0f);
   glScalef(1.5f, 1.0f, 1.5f);
   glTranslatef(-0.6f, -0.6f, 0.0f);
   drawRings(r,1,0,0);
   glPopMatrix();

}


/* Making the top of the object with height and the width taken and the r is the radius of the object pipes */
void drawTop(float r)
{
   glPushMatrix();
   glTranslatef(0.87,6.7,0.2);
   glRotated(85,0,1,0);
   draw_cylinder(r,3.5,1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.87,6.7,0.8);
   glRotated(95,0,1,0);
   draw_cylinder(r,3.5,1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.8,7.4,0.5);
   glRotated(-11,0,0,1);
   glRotated(90,0,1,0);
   draw_cylinder(r,3.7,1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(1.6,6.7,0.3);
   glRotated(-11,0,0,1);
   draw_cylinder(r,0.4,1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(1.6,6.7,0.3);
   glRotated(-11,0,0,1);
   glRotated(-68,1,0,0);
   draw_cylinder(r,0.6,1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(1.6,6.7,0.7);
   glRotated(-11,0,0,1);
   glRotated(-110,1,0,0);
   draw_cylinder(r,0.6,1,0,0);
   glPopMatrix();







   glPushMatrix();
   glTranslatef(2.6,6.7,0.3);
   glRotated(-11,0,0,1);
   draw_cylinder(r,0.3,1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(2.6,6.7,0.33);
   glRotated(-11,0,0,1);
   glRotated(-63,1,0,0);
   draw_cylinder(r,0.4,1,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(2.6,6.7,0.67);
   glRotated(-11,0,0,1);
   glRotated(-114,1,0,0);
   draw_cylinder(r,0.4,1,0,0);
   glPopMatrix();



   glPushMatrix();
   glTranslatef(2.6,5.8,0.5);
   glRotated(180,0,1,1);
   draw_cylinder(r,0.9,0,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(2.6,5.9,0.5);
   glRotated(180,0,1,1);
   draw_cylinder(3*r,0.08,1,1,1);
   glPopMatrix();
   
   glPushMatrix();
   glTranslatef(2.6,6.02,0.5);
   glRotated(180,0,1,1);
   draw_cylinder(3*r,0.08,1,1,1);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(2.6,6.14,0.5);
   glRotated(180,0,1,1);
   draw_cylinder(3*r,0.08,1,1,1);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(2.6,6.26,0.5);
   glRotated(180,0,1,1);
   draw_cylinder(3*r,0.08,1,1,1);
   glPopMatrix();
   
   glPushMatrix();
   glTranslatef(2.6,6.38,0.5);
   glRotated(180,0,1,1);
   draw_cylinder(3*r,0.08,1,1,1);
   glPopMatrix();






   glPushMatrix();
   glTranslatef(4.25,5.8,0.5);
   glRotated(180,0,1,1);
   draw_cylinder(r,0.9,0,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(4.25,5.9,0.5);
   glRotated(180,0,1,1);
   draw_cylinder(3*r,0.08,1,1,1);
   glPopMatrix();
   
   glPushMatrix();
   glTranslatef(4.25,6.02,0.5);
   glRotated(180,0,1,1);
   draw_cylinder(3*r,0.08,1,1,1);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(4.25,6.14,0.5);
   glRotated(180,0,1,1);
   draw_cylinder(3*r,0.08,1,1,1);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(4.25,6.26,0.5);
   glRotated(180,0,1,1);
   draw_cylinder(3*r,0.08,1,1,1);
   glPopMatrix();
   
   glPushMatrix();
   glTranslatef(4.25,6.38,0.5);
   glRotated(180,0,1,1);
   draw_cylinder(3*r,0.08,1,1,1);
   glPopMatrix();
   

}


/* Combining all the functions together to make the complete figure as a one */
void drawTransformer(float x, float y, float z, float sx, float sy, float sz, float r)
{
   
   // glLoadIdentity(); // Reset the model-view matrix
   glTranslatef(x, y, z);
   glScalef(sx, sy, sz);
   glScaled(0.5,0.5,0.5);
   //    glRotatef(180, 0.0f, 1.0f, 0.0f);
   glTranslated(0.0f, 0.0f, -0.5f);

   // Body 
   glPushMatrix();
   glTranslated(0.0f, 1.0f, 0.0f);
   glScaled(1, 1.2, 1.3);
   glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
   draw_cylinder(r, 3, 1,1,1);
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.0f, 1.0f, 0.0f);
   glScaled(1, 1.2, 1.3);
   glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
   draw_cylinder(r, 3, 1,1,1);
   glPopMatrix();

   glPushMatrix();
   glTranslated(0.0f, 1.0f, 1.0f);
   glScaled(1, 1.2, 1.3);
   glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
   draw_cylinder(r, 3, 1,1,1);
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.0f, 1.0f, 1.0f);
   glScaled(1, 1.2, 1.3);
   glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
   draw_cylinder(r, 3, 1,1,1);
   glPopMatrix();





   glPushMatrix();
   glTranslatef(0.0f, 3.6f, 0.0f);
   glTranslatef(0.6f, 0.6f, 0.0f);
   glScalef(1.0f, 1.0f, 1.0f);
   glTranslatef(-0.6f, -0.6f, 0.0f);
   drawRings(r,1,1,1);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.0f, 1.2f, 0.0f);
   glTranslatef(0.6f, 0.6f, 0.0f);
   glScalef(1.0f, 1.0f, 1.0f);
   glTranslatef(-0.6f, -0.6f, 0.0f);
   drawRings(r,1,1,1);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.0f, 2.4f, 0.0f);
   glTranslatef(0.6f, 0.6f, 0.0f);
   glScalef(1.0f, 1.0f, 1.0f);
   glTranslatef(-0.6f, -0.6f, 0.0f);
   drawRings(r,1,1,1);
   glColor3f(1,1,1);
   glPopMatrix();

   






   glPushMatrix();
   drawTransformerPipes(r);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0,-2.16,0);
   glScaled(1,1.5,1);
   glTranslatef(0.25,6.4,0.26);
   glScaled(0.5,0.5,0.5);
   drawTransformerPipes(1.6*r);
   glPopMatrix();



   glPushMatrix();
   drawTop(r);
   glPopMatrix();


   glPushMatrix();
   glTranslatef(0.98,0,1);
   glRotatef(180,0,1,0);
   drawTop(r);
   glPopMatrix();
  
}

/*this file contains all functions related to drawing the house*/

//utility function to draw a rectangle with given color with side 1 and center at origin
void drawRectangle(float cx, float cy, float cz)
{
   glBegin(GL_QUADS);
   glColor3f(cx, cy, cz); // Green
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(0.0f, 1.0f, 0.0f);
   glVertex3f(1.0f, 1.0f, 0.0f);
   glVertex3f(1.0f, 0.0f, 0.0f);
   glEnd();
}

//utility function to draw a triangle with given color
void drawTriangle(float cx, float cy, float cz)
{
   glBegin(GL_TRIANGLES);
   glColor3f(cx, cy, cz); // Green
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(1.0f, 1.0f, 0.0f);
   glVertex3f(2.0f, 0.0f, 0.0f);
   glEnd();
}

//utility function to draw a cuboid
void drawCuboid()
{
   glTranslatef(-1,-1,0);

   // Front Face
   glPushMatrix();
   glTranslated(0.0f, 0.0f, 0.0f);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   glScaled(2.0, 2.0, 2.0);
   drawRectangle(0, 0, 1);
   glColor3f(0.0f, 1.0f, 0.0f);
   glPopMatrix();

   // Back Face
   glPushMatrix();
   glTranslated(0.0f, 0.0f, -2.0f);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   glScaled(2.0, 2.0, 2.0);
   drawRectangle(0, 0, 1);
   glColor3f(0.0f, 1.0f, 0.0f);
   glPopMatrix();

   // Top Face
   glPushMatrix();
   glTranslated(0.0f, 2.0f, 0.0f);
   glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
   glScaled(2.0, 2.0, 2.0);
   drawRectangle(0, 1, 0);
   glColor3f(1.0f, 0.0f, 0.0f);
   glPopMatrix();

   // Bottom Face
   glPushMatrix();
   glTranslated(0.0f, 0.0f, 0.0f);
   glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
   glScaled(2.0, 2.0, 2.0);
   drawRectangle(0, 1, 0);
   glPopMatrix();

   // Left Face
   glPushMatrix();
   glTranslated(0.0f, 0.0f, 0.0f);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
   glScaled(2.0, 2.0, 2.0);
   drawRectangle(1, 1, 1);
   glPopMatrix();

   // Right Face
   glPushMatrix();
   glTranslated(2.0f, 0.0f, 0.0f);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
   glScaled(2.0, 2.0, 2.0);
   drawRectangle(1, 1, 1);
   glPopMatrix();
}


void drawWireBoard(float r, float g, float b)
{

   glTranslatef(-1,-1,0);

   // Front Face
   glPushMatrix();
   glTranslated(0.0f, 0.0f, 0.0f);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   glScaled(2.0, 2.0, 2.0);
   drawRectangle(r,g,b);
   glColor3f(r,g,b);
   glPopMatrix();

   // Back Face
   glPushMatrix();
   glTranslated(0.0f, 0.0f, -2.0f);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   glScaled(2.0, 2.0, 2.0);
   drawRectangle(r,g,b);
   glColor3f(r,g,b);
   glPopMatrix();

   // Top Face
   glPushMatrix();
   glTranslated(0.0f, 2.0f, 0.0f);
   glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
   glScaled(2.0, 2.0, 2.0);
   drawRectangle(r,g,b);
   glColor3f(r,g,b);
   glPopMatrix();

   // Bottom Face
   glPushMatrix();
   glTranslated(0.0f, 0.0f, 0.0f);
   glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
   glScaled(2.0, 2.0, 2.0);
   drawRectangle(r,g,b);
   glPopMatrix();

   // Left Face
   glPushMatrix();
   glTranslated(0.0f, 0.0f, 0.0f);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
   glScaled(2.0, 2.0, 2.0);
   drawRectangle(r,g,b);
   glPopMatrix();

   // Right Face
   glPushMatrix();
   glTranslated(2.0f, 0.0f, 0.0f);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
   glScaled(2.0, 2.0, 2.0);
   drawRectangle(r,g,b);
   glPopMatrix();


   glPushMatrix();
   glTranslated(2.0f, 1.4f, -1.0f);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
   glScaled(2.0, 2.0, 2.0);
   if(glowHouse)glColor3f(1,1,0);
   else glColor3f(0,0,0);
   drawHemisphere(0.1);
   glPopMatrix();
}

//function to draw the roof of the house 
void drawRoof()
{

   glTranslatef(-1,-1,0);

   // Front Face
   glBegin(GL_TRIANGLES);
   glColor3f(1,0,0); // Green
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(1.0f, 1.0f, 0.0f);
   glVertex3f(2.0f, 0.0f, 0.0f);
   glEnd();

   // Back Face
   glBegin(GL_TRIANGLES);
   glColor3f(1,0,0); // Green
   glVertex3f(0.0f, 0.0f, -2.0f);
   glVertex3f(1.0f, 1.0f, -2.0f);
   glVertex3f(2.0f, 0.0f, -2.0f);
   glEnd();


   // Bottom Face
   glBegin(GL_QUADS);
   glColor3f(0,1,0); // Green
   glVertex3f(0.0f, 0.0f, -2.0f);
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(2.0f, 0.0f, 0.0f);
   glVertex3f(2.0f, 0.0f, -2.0f);
   glEnd();

   // Left Face
   glBegin(GL_QUADS);
   glColor3f(0,1,0); // Green
   glVertex3f(0.0f, 0.0f, -2.0f);
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(1.0f, 1.0f, 0.0f);
   glVertex3f(1.0f, 1.0f, -2.0f);
   glEnd();

   // Right Face
   glBegin(GL_QUADS);
   glColor3f(0,1,0); // Green
   glVertex3f(1.0f, 1.0f, -2.0f);
   glVertex3f(1.0f, 1.0f, 0.0f);
   glVertex3f(2.0f, 0.0f, 0.0f);
   glVertex3f(2.0f, 0.0f, -2.0f);
   glEnd();
}

//draws the door the of the house with given color
void drawDoor(float cx, float cy, float cz)
{
   glPushMatrix();
   glTranslated(-0.5f, -0.2f, 0.05f);
   glScaled(1.0, 1.5, 1.0);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   drawRectangle(0.6, 0.3, 0.0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(-0.35f, 0.6f, 0.22f);
   glScaled(1.0, 1.5, 1.0);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   glColor3f(0,0,0);
   drawHemisphere(0.08);
   glPopMatrix();
   
   glPushMatrix();
   glTranslated(-0.35f, 0.6f, 0.22f);
   glScaled(1.0, 1.5, 1.0);
   glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
   glColor3f(0,0,0);
   drawHemisphere(0.08);
   glPopMatrix();

   glPushMatrix();
   glTranslated(-0.35f, 0.6f, 0.05f);
   glScaled(1.0, 1.5, 1.0);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   glColor3f(0,0,0);
   draw_cylinder(0.04, 0.1, 0,0,0);
   glPopMatrix();
}

//the window of house through which we see lights inside
void drawWindow()
{
   glPushMatrix();
   glTranslated(1.03f, 0.5f, -0.5f);
   glScaled(1.0, 1, 1.5);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
   if(glowHouse==1)drawRectangle(0.03*varWindSpeed,0.03*varWindSpeed,0);
   else drawRectangle(0,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.05f, 0.5f, -0.5f);
   glScaled(1.0, 1, 0.07);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
   drawRectangle(0,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.05f, 0.5f, -1.2f);
   glScaled(1.0, 1, 0.07);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
   drawRectangle(0,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.05f, 0.5f, -1.94f);
   glScaled(1.0, 1, 0.07);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
   drawRectangle(0,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.05f, 0.5f, -0.5f);
   glScaled(1.0, 0.07, 1.5);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
   drawRectangle(0,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.05f, 1.48f, -0.5f);
   glScaled(1.0, 0.07, 1.5);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
   drawRectangle(0,0,0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(1.05f, 1.0f, -0.5f);
   glScaled(1.0, 0.07, 1.5);
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
   drawRectangle(0,0,0);
   glPopMatrix();
}

//finally combining all above functions we construct our house here at x,y,z cordinate and of required scale
void drawHouse(float x, float y, float z, float sx, float sy, float sz)
{
   glTranslatef(x, y, z);
   glScalef(sx, sy, sz);
   glTranslated(0.0f, 0.0f, -0.5f);

   // walls of house modeled as the cuboid 
   glPushMatrix();
   glTranslated(0.0f, 1.0f, 0.0f);
   glScaled(1, 1.2, 1.3);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   drawCuboid();
   glPopMatrix();

   // Roof of the house
   glPushMatrix();
   glTranslated(0.0f, 3.2f, 0.2f);
   glScaled(1.5, 1.5, 1.5);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   drawRoof();
   glPopMatrix();

   // Door of the house
   glPushMatrix();
   glTranslated(0.0f, 0.0f, 0.0f);
   // glScaled(1.0, 1.5, 1.0);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   drawDoor(1,1,1);
   glPopMatrix();

   // Window
   glPushMatrix();
   glTranslated(0.0f, 0.0f, 0.0f);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   drawWindow();
   glPopMatrix();

   // Ceiling
   glPushMatrix();
   glTranslated(0.0f, 2.2f, 0.23f);
   // glScaled(1.0, 1.5, 1.0);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   if(glowHouse==0)drawCircle(0.4, 0,0,0);
   else drawCircle(0.4, 0.03*varWindSpeed,0.03*varWindSpeed,0);
   glPopMatrix();



   glPushMatrix();
   glTranslated(1.0f, 1.0f, -2.1f);
   glScaled(0.1, 0.2, 0.2);
   glColor3f(0,0,0);
   glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
   drawWireBoard(0,1,1);
   glPopMatrix();
      
}

/*this file creates background including the terrain, mountains, clouds and sun*/

/*This function draws clouds which are basically interlapping of spheres and some extra parts to make it fluffy*/
void drawCloud() { 
    glPushMatrix();
    glTranslatef(-5.0, 5.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);

    // Draw the main cloud body as circular
    glBegin(GL_POLYGON);
    glVertex2f(0.0, 0.0);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * M_PI / 180.0;
        float x = 1.5 * cos(angle);
        float y = sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw the smaller cloud blobs to make it fluffy
    glTranslatef(0.5, 0.5, 0.0);
    for (int i = 0; i < 4; i++) {
        glTranslatef(0.8, -0.3, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(0.0, 0.0);
        for (int j = 0; j < 180; j += 10) {
            float angle = j * M_PI / 180.0;
            float x = 0.4 * cos(angle);
            float y = 0.2 * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }
    glPopMatrix();
}

/*function to draw mountains takes parameters as center of mountain, height and radius*/
void mountain(float x,float z,int mountain_radius,float mountain_height){

    for (int i = min(0, int(x-mountain_radius/GRID_SPACING)); i < max(GRID_SIZE, int(x+mountain_radius/GRID_SPACING)); i++) {
        for (int j = min(0, int(z-mountain_radius/GRID_SPACING)); j < max(GRID_SIZE, int(z+mountain_radius/GRID_SPACING)); j++) {

            // Set the terrain height based on the distance from the center of the mountain
            float center_x = abs(i - x) * GRID_SPACING;
            float center_z = abs(j - z) * GRID_SPACING;
            float distance = sqrt(center_x * center_x + center_z * center_z);
            if (distance < mountain_radius) {
                terrain[i][j] = mountain_height*(mountain_radius - distance)/mountain_radius;
                if(distance < mountain_radius*0.1){
                    //if near the centre create smooth top not pointed
                    terrain[i][j] = mountain_height * (mountain_radius- mountain_radius*0.1) / mountain_radius - 3*mountain_radius*0.1*mountain_radius*0.1 + 3*distance*distance;
                }
            }
        }
    }
}


/*function to intialize the terrain placing mountains at appropriate positions*/
void initTerrain() {

   // ground is created as rough uneven surface using the random function
   for(int i=0;i<GRID_SIZE;i++){
      for(int j=0;j<GRID_SIZE;j++){
         terrain[i][j]=((float)(rand()%1000))/8000;
      }
   }

   // creating mountains
   mountain(165,235,5,8);
   mountain(250,285,5.5,4.5);
   mountain(305,205,5,7);

}


/*function which renders the terrain and mountains using the heights stored in the terrain matrix*/
void drawTerrain() {

    //we use small quads to generate the surface
    glBegin(GL_QUADS);
    for (int i = 0; i < GRID_SIZE - 1; i++) {
        for (int j = 0; j < GRID_SIZE - 1; j++) {
            // Set the color of the terrain based on the height
            float height = terrain[i][j];

            //set the color according to the heights of the terrain will give a realistic view.
            if(height<0.1){
                glColor3f(height/3, height / 2 + 0.2, 0.0);
            }else{
                glColor3f(0, height / 5 + 0.2, 0.0);
            }

            // Draw the terrain quad
            glVertex3f((i) * GRID_SPACING, terrain[i][j], (j ) * GRID_SPACING);
            glVertex3f((i + 1) * GRID_SPACING, terrain[i + 1][j], (j ) * GRID_SPACING);
            glVertex3f((i  + 1) * GRID_SPACING, terrain[i + 1][j + 1], (j + 1) * GRID_SPACING);
            glVertex3f((i ) * GRID_SPACING, terrain[i][j + 1], (j + 1) * GRID_SPACING);
        }
    }
    glEnd();
}


/*Combine the above function to create a background and terrain*/
void drawBackground()
{
    glPushMatrix();
    glTranslatef(-9.0, -2.0, -3.0f);
    drawTerrain();
    glPopMatrix();

    //drawing the sun, modeled as a sphere
    glColor3f(1.0f, 1.0f, 0.0f);  // Set color to yellow
    glPushMatrix();
    glTranslatef(12.0f, 16.0f, 50.0f);  // Move sun back along z-axis
    glutSolidSphere(1.6f, 20, 20);  // inbuilt function to draw a sphere
    glPopMatrix(); 

    glPushMatrix();
    glTranslatef(4.0f, 2.0f, 20.0f);
    drawCloud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20.0f, 2.0f, 20.0f);
    drawCloud();
    glPopMatrix();
}

#include "SOIL.h"




/* Code to load the image and use it as an object in the further process*/
/* We used an image of the settings icon in this to be loaded in the texture variable */
int LoadGLTextures(){
   
    texture[2] = SOIL_load_OGL_texture ( "settings.jpeg",SOIL_LOAD_AUTO, 
                               SOIL_CREATE_NEW_ID,
                               SOIL_FLAG_POWER_OF_TWO | 
                               SOIL_FLAG_MIPMAPS |
                               SOIL_FLAG_COMPRESS_TO_DXT);
    
    if(texture[0]==0 ){
       return false;
    }
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glEnable(GL_TEXTURE_2D);                // Enable Texture Mapping ( NEW )
    glShadeModel(GL_SMOOTH);                // Enable Smooth Shading
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   // Black Background
    glClearDepth(1.0f);                     // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                 // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations
    return true; // Return Success
}






/* It defines a square where the above image will be loaded with the Texture coordinates 
 this can be moved further as to set the position */
void cobweb(){
    glPushMatrix();
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, texture[2] );
    
    glScaled(0.5,0.5,0.5);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);    
             glVertex3f(1,1,0.0);
            glTexCoord2f(0.0f, 1.0f);         
            glVertex3f(1,-1,0.0);
           glTexCoord2f(1.0f, 1.0f);      
            glVertex3f(-1,-1,0.0);
        glTexCoord2f(1.0f, 0.0f);   
        glVertex3f(-1,1,0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}






/* Defining the GL modules that are required for image loading and shading effect along with texture set */
void initGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

      initLighting();
   initMaterial();
   
    LoadGLTextures();
    glClearColor(0.52f, 0.8f, 0.91f, 1.0f);   
   //  glClearColor(1.0, 1.0, 1.0, 1.0); // Background
    glClearDepth(1.0);                // Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LEQUAL);           // The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);          // Enables Depth Testing
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}


/*initialization ends*/

/*function to handle key inputs*/
/* Making some customization with the different keys that will change the global variables as a functionality
of the Project */
void processNormalKeys(unsigned char key, int x, int y)
{
   if(key=='x')
   {
        angleWindmillX -= 1;
   }
   if(key=='X')
   {
        angleWindmillX += 1;
   }
   if(key=='y')
   {
        angleWindmillY -= 1;
   }
   if(key=='Y')
   {
        angleWindmillY += 1;
   }
   if(key=='z')
   {
        angleWindmillZ -= 1;
   }
   if(key=='Z')
   {
        angleWindmillZ += 1;
   }

   if (key == '<')
   {
      scalefactor += scalefactor/10;
   }
   if (key == '>')
   {
      scalefactor -= scalefactor/10;
   }
   if(key == 'A')
   {
      if(windmillSpeed<=45)
      windmillSpeed += windmillSpeed/10;
   }
   if(key == 'a')
   {
      windmillSpeed -= windmillSpeed/10;
   }
   if(key == 'C')
   {
      windmillSpeed1 += 1;
   }
   if(key == 'c')
   {
      windmillSpeed1 -= 1;
   }
   if(key == 'B')
   {
      autoMode = 1-autoMode;
   }
   if(key=='R')
   {
      angleRotateBlade1 += 1;
      angleRotateBlade2 += 1;
      angleRotateBlade3 += 1;
   }
   if(key=='r')
   {
      angleRotateBlade1 -= 1;
      angleRotateBlade2 -= 1;
      angleRotateBlade3 -= 1;
   }
   if(key=='l')
   {
      viewNumber = (viewNumber+1)%totalViews;
      angleWindmillX = 0;
      angleWindmillY = 0;
      angleWindmillZ = 0;
      // angleRotateBlade1 = 0;
      // angleRotateBlade2 = 0;
      // angleRotateBlade3 = 0;
      // windmillSpeed = 1;
      // windmillSpeed1 = 0;
      // autoMode = 1;
      // scalefactor = 1;
   }
   if(key=='j')
   {
      viewNumber = (viewNumber-1+totalViews)%totalViews;
      angleWindmillX = 0;
      angleWindmillY = 0;
      angleWindmillZ = 0;
      // angleRotateBlade1 = 0;
      // angleRotateBlade2 = 0;
      // angleRotateBlade3 = 0;
      // windmillSpeed = 1;
      // windmillSpeed1 = 0;
      // autoMode = 1;
      // scalefactor = 1;
   }
}


/*display function*/


/* Code to make the settings icon with all the different options given to it */
void drawSettingsPart()
{
   glPushMatrix(); 
   glTranslated(-7,3.5,0);
   drawRectangle(1,1,1);
   glPopMatrix();  


    

    /* Loading the settings icon as a image in the viewport */
   glPushMatrix();
   glTranslatef(-6.5,4,0);
   cobweb();
   glEnable(GL_TEXTURE_2D);
   glBindTexture ( GL_TEXTURE_2D, texture[2] );
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

    /* Code to display different settings options */
   if(onMouse == 1)
   {

    /* Code to add text at a given location with defined color and given text */
    glColor3f(0,0,1);
   glRasterPos3f(-6.8,3.1,0.1);
   string text1 = "View";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }


    /* Code to add text at a given location with defined color and given text */
   glColor3f(0,0,1);
   glRasterPos3f(-6.8,2.5,0.1);
   text1 = "Mode";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }


    /* Code to add text at a given location with defined color and given text */
   glColor3f(0,0,1);
   glRasterPos3f(-6.8,1.9,0.1);
   text1 = "Instructions";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }


    /* Code to add text at a given location with defined color and given text */
   glColor3f(0,0,1);
   glRasterPos3f(-6.8,1.3,0.1);
   text1 = "Objects";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }


    /* Code to make the background color for the first added text */
      glPushMatrix(); 
      glTranslated(-7,2.95,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();  


    /* Code to add the partition between the different texts */
      glPushMatrix(); 
      glTranslated(-7,2.9,0);
      glScaled(2,0.05,1);
      drawRectangle(1,1,1);
      glPopMatrix();  
      

      glPushMatrix(); 
      glTranslated(-7,2.35,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();  

      glPushMatrix(); 
      glTranslated(-7,2.3,0);
      glScaled(2,0.05,1);
      drawRectangle(1,1,1);
      glPopMatrix();  


      glPushMatrix(); 
      glTranslated(-7,1.75,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();  

      glPushMatrix(); 
      glTranslated(-7,1.7,0);
      glScaled(2,0.05,1);
      drawRectangle(1,1,1);
      glPopMatrix();  


      glPushMatrix(); 
      glTranslated(-7,1.15,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();  

   } 

   if(onMouse1 == 1)
   {
    glTranslatef(2,0,0);

    /* Code to add text at a given location with defined color and given text */
    glColor3f(0,0,1);
    glRasterPos3f(-6.7,3.1,0.1);
   string text1 = "Front View";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

    /* Code to add text at a given location with defined color and given text */
   glColor3f(0,0,1);
   glRasterPos3f(-6.7,2.5,0.1);
   text1 = "CloseUp View";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

    /* Code to add text at a given location with defined color and given text */
    glColor3f(0,0,1);
   glRasterPos3f(-6.7,1.9,0.1);
   text1 = "Left Side View";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

    /* Code to add text at a given location with defined color and given text */
   glColor3f(0,0,1);
   glRasterPos3f(-6.7,1.3,0.1);
   text1 = "Back View";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

    /* Code to add text at a given location with defined color and given text */
   glColor3f(0,0,1);
   glRasterPos3f(-6.7,0.7,0.1);
   text1 = "Top View";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

    /* Code to add text at a given location with defined color and given text */
   glColor3f(0,0,1);
   glRasterPos3f(-6.7,0.1,0.1);
   text1 = "Hill Side View";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }


    /* Adding the arrow defining which section comes to the right portion */
    glPushMatrix(); 
    glTranslatef(-7,3.3,0);
   glRotatef(-90,0,0,1);
   glScaled(0.1, 0.1, 0.1);
    drawTriangle(0,0,0);
   glPopMatrix();



    glTranslatef(0.13,0,0);
    /* Code to make the background color for the first added text */

    glPushMatrix(); 
      glTranslated(-7,2.95,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();  


    /* Code to add the partition between the different texts */
      glPushMatrix(); 
      glTranslated(-7,2.9,0);
      glScaled(2,0.05,1);
      drawRectangle(1,1,1);
      glPopMatrix();  
      

      glPushMatrix(); 
      glTranslated(-7,2.35,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();  

      glPushMatrix(); 
      glTranslated(-7,2.3,0);
      glScaled(2,0.05,1);
      drawRectangle(1,1,1);
      glPopMatrix();  


      glPushMatrix(); 
      glTranslated(-7,1.75,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();

      glPushMatrix(); 
      glTranslated(-7,1.7,0);
      glScaled(2,0.05,1);
      drawRectangle(1,1,1);
      glPopMatrix();  


      glPushMatrix(); 
      glTranslated(-7,1.15,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();

      glPushMatrix(); 
      glTranslated(-7,1.1,0);
      glScaled(2,0.05,1);
      drawRectangle(1,1,1);
      glPopMatrix();  


      glPushMatrix(); 
      glTranslated(-7,0.55,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();

      glPushMatrix(); 
      glTranslated(-7,0.50,0);
      glScaled(2,0.05,1);
      drawRectangle(1,1,1);
      glPopMatrix();  


      glPushMatrix(); 
      glTranslated(-7,-0.05,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();

    glTranslatef(-0.13,0,0);
      glTranslatef(-2,0,0);
   }

    if(onMouse2 == 1)
   {
    glTranslatef(2,0,0);

    /* Code to add text at a given location with defined color and given text */
    glColor3f(0,0,1);
    glRasterPos3f(-6.7,3.1,0.1);
   string text1 = "Manual";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

    /* Code to add text at a given location with defined color and given text */
   glColor3f(0,0,1);
   glRasterPos3f(-6.7,2.5,0.1);
   text1 = "Auto";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }
/* Adding the arrow defining which section comes to the right portion */
    glPushMatrix(); 
    glTranslatef(-7,2.7,0);
   glRotatef(-90,0,0,1);
   glScaled(0.1, 0.1, 0.1);
    drawTriangle(0,0,0);
   glPopMatrix();

    glTranslatef(0.13,0,0);
    /* Code to make the background color for the first added text */
    glPushMatrix(); 
      glTranslated(-7,2.95,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();  

      glPushMatrix(); 
      glTranslated(-7,2.9,0);
      glScaled(2,0.05,1);
      drawRectangle(1,1,1);
      glPopMatrix();  
      

      glPushMatrix(); 
      glTranslated(-7,2.35,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();  

    glTranslatef(-0.13,0,0);
      glTranslatef(-2,0,0);
   }

   if(onMouse3 == 1)
   {
        /* Adding top level text*/
        glColor3f(0,0,0);
        glRasterPos3f(-2.5,3.1,0.1);
        string text = "Instructions";
        for (int i = 0; i < text.length(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }


        /* Making an array of the text of different lines to be used later */
        vector<string> arr1,arr2;

        arr1.push_back("Press X");
        arr2.push_back("Rotate anti-clockwise about X-axis");
        arr1.push_back("Press x");
        arr2.push_back("Rotate clockwise about X-axis");
        arr1.push_back("Press Y");
        arr2.push_back("Rotate anti-clockwise about Y-axis");
        arr1.push_back("Press y");
        arr2.push_back("Rotate clockwise about Y-axis");
        arr1.push_back("Press Z");
        arr2.push_back("Rotate anti-clockwise about Z-axis");
        arr1.push_back("Press z");
        arr2.push_back("Rotate clockwise about Z-axis");
        

        arr1.push_back("Press <");
        arr2.push_back("Zoom in");
        arr1.push_back("Press >");
        arr2.push_back("Zoom out");


        arr1.push_back("Press B");
        arr2.push_back("Turn on Manual Mode");
        arr1.push_back("Press r");
        arr2.push_back("Blades diverge");
        arr1.push_back("Press R");
        arr2.push_back("Blades converge");
        arr1.push_back("Press A");
        arr2.push_back("Increase the rotation speed of blades");
        arr1.push_back("Press a");
        arr2.push_back("Decrease the rotation speed of blades");
        arr1.push_back("Press C");
        arr2.push_back("Rotation of Head of Windmill from left to right");
        arr1.push_back("Press c");
        arr2.push_back("Rotation of Head of Windmill from right to left");
        arr1.push_back("Press l");
        arr2.push_back("To view from next viewing angle");
        arr1.push_back("Press j");
        arr2.push_back("To view from previous viewing angle");

        float y = 2.5;
        /* Looping around the text to display different lines */
        for(int i=0;i<arr1.size();i++)
        {
            glColor3f(0,0,1);
            glRasterPos3f(-4.5,y,0.1);
            string text1 = arr1[i];
            for (int i = 0; i < text1.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
            }


            glColor3f(0,0,1);
            glRasterPos3f(-3.5,y,0.1);
            text1 = ":";
            for (int i = 0; i < text1.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
            }

            glColor3f(0,0,1);
            glRasterPos3f(-3.1,y,0.1);
            text1 = arr2[i];
            for (int i = 0; i < text1.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
            }

            y -= 0.25;
        }
               
   }

   if(onMouse4 == 1)
   {
    glTranslatef(2,0,0);

    /* Code to add text at a given location with defined color and given text */
    glColor3f(0,0,1);
    glRasterPos3f(-6.7,3.1,0.1);
   string text1 = "Windmill";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

    /* Code to add text at a given location with defined color and given text */
   glColor3f(0,0,1);
   glRasterPos3f(-6.7,2.5,0.1);
   text1 = "House";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

    /* Code to add text at a given location with defined color and given text */
    glColor3f(0,0,1);
   glRasterPos3f(-6.7,1.9,0.1);
   text1 = "Transformer";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

    /* Code to add text at a given location with defined color and given text */
   glColor3f(0,0,1);
   glRasterPos3f(-6.7,1.3,0.1);
   text1 = "Background";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

/* Adding the arrow defining which section comes to the right portion */
    glPushMatrix(); 
    glTranslatef(-7,1.5,0);
   glRotatef(-90,0,0,1);
   glScaled(0.1, 0.1, 0.1);
    drawTriangle(0,0,0);
   glPopMatrix();



    glTranslatef(0.13,0,0);
    /* Code to make the background color for the first added text */
    glPushMatrix(); 
      glTranslated(-7,2.95,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();  

    /* Code to add the paritions between different texts*/
      glPushMatrix(); 
      glTranslated(-7,2.9,0);
      glScaled(2,0.05,1);
      drawRectangle(1,1,1);
      glPopMatrix();  
      

      glPushMatrix(); 
      glTranslated(-7,2.35,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();  

      glPushMatrix(); 
      glTranslated(-7,2.3,0);
      glScaled(2,0.05,1);
      drawRectangle(1,1,1);
      glPopMatrix();  


      glPushMatrix(); 
      glTranslated(-7,1.75,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();

      glPushMatrix(); 
      glTranslated(-7,1.7,0);
      glScaled(2,0.05,1);
      drawRectangle(1,1,1);
      glPopMatrix();  


      glPushMatrix(); 
      glTranslated(-7,1.15,0);
      glScaled(2,0.55,1);
      drawRectangle(1,1,0);
      glPopMatrix();

      
    glTranslatef(-0.13,0,0);
      glTranslatef(-2,0,0);
   }
}

void drawVariables()
{
    glPushMatrix(); 
   glTranslated(4,3.5,0);
   glScaled(4,1,1);
   drawRectangle(0,0,0.1);
   glPopMatrix();  

    /* Code to add text at a given location with defined color and given text */
   glColor3f(0,1,0);
   glRasterPos3f(4.2,4.1,0);
   string text1 = "WindSpeed";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

   glColor3f(0,1,0);
   glRasterPos3f(6.0,4.1,0);
   text1 = ":";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

    /* Displaying the wind speed taking the variable and converting it into string */
   glColor3f(0,1,0);
   glRasterPos3f(6.2,4.1,0);
   text1 = to_string(varWindSpeed);
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

   glColor3f(0,1,0);
   glRasterPos3f(6.2+0.11*(text1.size()),4.1,0);
   text1 = "km/h";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }





    /* Code to add text at a given location with defined color and given text */
   glColor3f(0,1,0);
   glRasterPos3f(4.2,3.7,0);
   text1 = "Energy Generated";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }
   
   glColor3f(0,1,0);
   glRasterPos3f(6.0,3.7,0);
   text1 = ":";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

    /* Displaying the total energy generated by all the windmills taking the variable and converting it into string */
   glColor3f(0,1,0);
   glRasterPos3f(6.2,3.7,0);
   text1 = to_string(varEnergyGenerated);
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

   glColor3f(0,1,0);
   glRasterPos3f(6.2+0.11*(text1.size()),3.7,0);
   text1 = "Watts";
   for (int i = 0; i < text1.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text1[i]);
   }

}


/* Connecting all the wires from the windmill to the transformer and from the transformer to the house */
void drawWires()
{

   glPushMatrix(); 
      glTranslated(-8.5,-1.8,-7.0);
      glRotatef(90,0,1,0);
      draw_cylinder(0.02,5.5,0,0,0);
      glPopMatrix();

   
   glPushMatrix(); 
      glTranslated(-7.0,-1.8,-5.0);
      glRotatef(90,0,1,0);
      draw_cylinder(0.02,4,0,0,0);
      glPopMatrix();

   glPushMatrix(); 
      glTranslated(-3.0,-1.8,-7.0);
      glRotatef(0,0,1,0);
      draw_cylinder(0.02,2,0,0,0);
      glPopMatrix();

   //ground to tower
   glPushMatrix(); 
      glTranslated(-3.0,-1.8,-7.0);
      glRotatef(63,0,0,1);
      glRotatef(90,0,1,0);
      draw_cylinder(0.02,2.62,0,0,0);
      glPopMatrix();
   
   //in tower
   glPushMatrix(); 
      glTranslated(-1.8,0.53,-7.0);
      glRotatef(90,0,1,0);
      draw_cylinder(0.02,1.8,0,0,0);
      glPopMatrix();

   //connecting the house
   glPushMatrix(); 
      glTranslated(0.1,0.53,-7.0);
      glRotatef(90,0,1,0);
      glRotatef(22,0,0,1);
      glRotatef(-35,0,1,0);
      draw_cylinder(0.02,6.5,0,0,0);
      glPopMatrix();
}


/* Main display function connecting all the functionalities together to obtain the final product */
void display()
{
   /* Defining the Wind Speed and the total energy genrated by the windmills to be displaying in the
   home screen */
   if(autoMode == 1)
   {
      varWindSpeed = windmillSpeed*10;
      varEnergyGenerated += varWindSpeed*0.001;
   }
   else
   {
      varWindSpeed = varChange*10;
      varEnergyGenerated += varWindSpeed*0.001;
      varChange = 0;
   }
   // cout<<viewNumber<<"\n";
   // glDisable (GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);
   //  glEnable(GL_LIGHTING);
   //  glShadeModel(GL_SMOOTH);



   glMatrixMode(GL_PROJECTION);
   // gluLookAt(0,0,0,0,0,1,0,0,1000);
   glMatrixMode(GL_MODELVIEW);                         // To operate on model-view matrix
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers


   
   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                // Reset the model-view matrix

   glTranslatef(0.0f, 0.0f, -7.0f); // Move right and into the screen
   glScalef(0.6, 0.6, 0.6);

   /* Displaying the settings part in the code */
   glDisable(GL_LIGHTING);
   drawSettingsPart();
   if(onMouse3 == 0 && enableComplete == 1)
   {
      drawVariables();
   }
   if(viewNumber == 0)
    {
      glEnable(GL_LIGHTING);
    }



   /* Displaying only windmill without anything in the background*/
   if(enableWindmill == 1)
   {
      glScalef(scalefactor, scalefactor, scalefactor);
      glRotatef(angleWindmillX, 1.0f, 0.0f, 0.0f);
      glTranslatef(0,0,-3);
      glRotatef(angleWindmillY, 0.0f, 1.0f, 0.0f);
      glTranslatef(0,0,3);
      glRotatef(angleWindmillZ, 0.0f, 0.0f, 1.0f);

      glDisable(GL_LIGHTING);
      glPushMatrix(); 
      glTranslatef(2,0,0);
      glScaled(2,2,2);
      drawWindmill(-1.0, 0.0, -1.0, 0.5, 0.5, 0.5);
      glPopMatrix();
      glEnable(GL_LIGHTING);
   }

   /* Displaying only house without anything in the background*/
   if(enableHouse == 1)
   {
      glScalef(scalefactor, scalefactor, scalefactor);
      glRotatef(angleWindmillX, 1.0f, 0.0f, 0.0f);
      glTranslatef(0,0,-3);
      glRotatef(angleWindmillY, 0.0f, 1.0f, 0.0f);
      glTranslatef(0,0,3);
      glRotatef(angleWindmillZ, 0.0f, 0.0f, 1.0f);

      glDisable(GL_LIGHTING);

      glPushMatrix(); 
      glTranslatef(-3,0,0);
      glScaled(3,3,3);
      drawHouse(2.0, 0.0, 0.0, 0.5, 0.5, 0.5);
      glPopMatrix();
      glEnable(GL_LIGHTING);
   }

   /* Displaying only transformer without anything in the background*/
   if(enableTransformer == 1)
   {
      glScalef(scalefactor, scalefactor, scalefactor);
      glRotatef(angleWindmillX, 1.0f, 0.0f, 0.0f);
      glTranslatef(0,0,-3);
      glRotatef(angleWindmillY, 0.0f, 1.0f, 0.0f);
      glTranslatef(0,0,3);
      glRotatef(angleWindmillZ, 0.0f, 0.0f, 1.0f);

      glDisable(GL_LIGHTING);
      glPushMatrix(); 
      glTranslatef(-3,-1,-7);
      glScaled(3,3,3);
      drawTransformer(2.0, 0.0, 0.0, 0.5, 0.5, 0.5, 0.05);
      glPopMatrix();
      glEnable(GL_LIGHTING);
   }

   /* Displaying only hills with the sun and clouds without anything in the background*/
   if(enableBackground == 1)
   {
      glScalef(scalefactor, scalefactor, scalefactor);
      glRotatef(angleWindmillX, 1.0f, 0.0f, 0.0f);
      glTranslatef(0,0,-3);
      glRotatef(angleWindmillY, 0.0f, 1.0f, 0.0f);
      glTranslatef(0,0,3);
      glRotatef(angleWindmillZ, 0.0f, 0.0f, 1.0f);

      glDisable(GL_LIGHTING);
      glPushMatrix(); 
      glTranslated(10,0,0);
      glRotatef(170,0,1,0);
      drawBackground();
      glPopMatrix();
      glEnable(GL_LIGHTING);
   }
   

   /* Displaying all the objects together */
   if(onMouse3 == 0 && enableComplete == 1)
   {
      /* Defining the functionalities to rotate about axis and scaling and translating
       the complete scene or the viewport */
      glScalef(scalefactor, scalefactor, scalefactor);
      glRotatef(angleWindmillX, 1.0f, 0.0f, 0.0f);
      glTranslatef(0,0,-3);
      glRotatef(angleWindmillY, 0.0f, 1.0f, 0.0f);
      glTranslatef(0,0,3);
      glRotatef(angleWindmillZ, 0.0f, 0.0f, 1.0f);
      position[2] = position[2]*cos(angleWindmillX*3.14/180);
      glLightfv(GL_LIGHT0, GL_POSITION, position);


      /* Displaying the left close up view */
      if(viewNumber == 1)
      {
         gluLookAt(-3,0,-6, 4,1,-9, 0,1,0);
      }

      /* Displaying the left side view */
      if(viewNumber == 2)
      {
         float x = 0.9;
         glScalef(x, x, x);
         glRotatef(8, 1.0f, 0.0f, 0.0f);
         glTranslatef(0,0,-3);
         glRotatef(35, 0.0f, 1.0f, 0.0f);
         glTranslatef(0,0,3);
         glRotatef(0, 0.0f, 0.0f, 1.0f);
      }

      /* Displaying the back view */
      if(viewNumber == 3)
      {
         float x = 0.8;
         glScalef(x, x, x);
         glRotatef(25, 1.0f, 0.0f, 0.0f);
         glTranslatef(0,0,-3);
         glRotatef(155, 0.0f, 1.0f, 0.0f);
         glTranslatef(0,0,3);
         glRotatef(0, 0.0f, 0.0f, 1.0f);
      }

      /* Displaying the top view */
      if(viewNumber == 4)
      {
         gluLookAt(5,12,-10, 1,0,0, 0,1,0);
      }

      /* Displaying the right side view */
      if(viewNumber == 5)
      {
         float x = 1;
         glScalef(x, x, x);
         glRotatef(30, 1.0f, 0.0f, 0.0f);
         glTranslatef(0,0,-3);
         glRotatef(210, 0.0f, 1.0f, 0.0f);
         glTranslatef(0,0,3);
         glRotatef(0, 0.0f, 0.0f, 1.0f);
      }

      


      

      
      /* Function to call background object */
      glPushMatrix(); 
      glTranslated(10,0,0);
      glRotatef(170,0,1,0);
      drawBackground();
      glPopMatrix();

      /* Function to call windmill object */
      glPushMatrix(); 
      glTranslatef(-5.5,-0.8,-6);
      drawWindmill(-1.0, 0.0, -1.0, 0.5, 0.5, 0.5);
      glPopMatrix();

      /* Function to call 2nd windmill object */
      glPushMatrix(); 
      glTranslatef(-5,-0.8,-6);
      drawWindmill(-2.0, 0.0, 1.0, 0.5, 0.5, 0.5);
      glPopMatrix();

      /* Function to call 3rd windmill object */
      glPushMatrix(); 
      glTranslatef(-5.5,-0.8,-6);
      drawWindmill(-3.0, 0.0, -1.0, 0.5, 0.5, 0.5);
      glPopMatrix();

      /* Function to call 4th windmill object */
      glPushMatrix(); 
      glTranslatef(-5,-0.8,-6);
      drawWindmill(0.0, 0.0, 1.0, 0.5, 0.5, 0.5);
      glPopMatrix();

      /* Function to call house object */
      glPushMatrix(); 
      glTranslatef(4,-1.8,-5);
      glRotatef(-90,0,1,0);
      drawHouse(2.0, 0.0, 0.0, 0.5, 0.5, 0.5);
      glPopMatrix();

      /* Function to call transformer object */
      glPushMatrix(); 
      glTranslatef(-3,-1,-7);
      drawTransformer(2.0, 0.0, 0.0, 0.5, 0.5, 0.5, 0.05);
      glPopMatrix();

      /* Function to call Conecting wires in the Home screen */
      glPushMatrix(); 
      drawWires();
      glPopMatrix();


   }



   // Render a pyramid consists of 4 triangles
   glLoadIdentity(); // Reset the model-view matrix

   glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)

   // Update the rotational angle after each refresh [NEW]
   /* Code to change the view in each frame 
   Rotating the windmill blades */
   if(autoMode==1)angleBlade += windmillSpeed;
   if(autoMode==1)glowHouse=1;
   else glowHouse=0;
}

/* Called back when timer expired [NEW] */
void timer(int value)
{
   glutPostRedisplay();                   // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height)
{ // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0)
      height = 1; // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
   glLoadIdentity();            // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Code to merge the Cursor to the Project */
/* It will detect the cursor movement and will provide the results to be used further in the code */
void motion(int x, int y) {
   /* Detecting the distance the cursor moves in the time interval */
   GLfloat dy = (y - Yaxis);
   GLfloat dx = (x - Xaxis);
   GLfloat difference = sqrt(dx * dx + dy * dy);


   Yaxis = y;
   Xaxis = x;

   /* If the mode is set to be manual then take the values from the above and define the variables 
   to define the windmill speed and total energy generated */
   varChange = 0;
   if(autoMode == 0)
   {
      if(dx<0) angleBlade += difference*0.9*-1;
      if(dx>=0) angleBlade += difference*0.9;
      if(difference>0)glowHouse=1;
      else glowHouse=0;
      varChange = (difference*0.9);
   }

   // else
   // {
   //    if(dy>0)
   //    {
   //       angleWindmillX += 1;
   //    }
   //    if(dy<0)
   //    {
   //       angleWindmillX -= 1;
   //    }

   //    if(dx>0)
   //    {
   //       angleWindmillY += 1;
   //    }
   //    if(dx<0)
   //    {
   //       angleWindmillY -= 1;
   //    }
   // }
  
   display();
}


void mouseClicks(int button, int state, int x, int y) {
   // cout<<x<<" "<<y<<"\n";
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      if(x>=190 && x<=290 && y>=35 && y<=135)
      {
         onMouse = 1-onMouse;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }
      else if(x>=190 && x<=393 && y>=143 && y<=190 && onMouse==1)
      {
         onMouse1 = 1-onMouse1;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }
      else if(x>=190 && x<=393 && y>=206 && y<=250 && onMouse==1)
      {
         onMouse2 = 1-onMouse2;
         onMouse1 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }
      else if(x>=190 && x<=393 && y>=265 && y<=320 && onMouse==1)
      {
         onMouse3 = 1;
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse4 = 0;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }
      else if(x>=190 && x<=393 && y>=332 && y<=384 && onMouse==1)
      {
         onMouse4 = 1 -onMouse4;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }
      else if(x>=413 && x<=617 && y>=145 && y<=188 && onMouse2==1)
      {
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         onMouse21 = 1;
         autoMode = 0;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }
      else if(x>=413 && x<=617 && y>=206 && y<=253 && onMouse2==1)
      {
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         onMouse22 = 1;
         autoMode = 1;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }
      else if(x>=413 && x<=617 && y>=145 && y<=188 && onMouse1==1)
      {
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         onMouse21 = 1;
         viewNumber = 0;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }
      else if(x>=413 && x<=617 && y>=206 && y<=253 && onMouse1==1)
      {
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         onMouse22 = 1;
         viewNumber = 1;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }
      else if(x>=413 && x<=617 && y>=268 && y<=316 && onMouse1==1)
      {
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         onMouse22 = 1;
         viewNumber = 2;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }
      else if(x>=413 && x<=617 && y>=333 && y<=382 && onMouse1==1)
      {
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         onMouse22 = 1;
         viewNumber = 3;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }
      else if(x>=413 && x<=617 && y>=395 && y<=446 && onMouse1==1)
      {
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         onMouse22 = 1;
         viewNumber = 4;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }
      else if(x>=413 && x<=617 && y>=455 && y<=508 && onMouse1==1)
      {
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         onMouse22 = 1;
         viewNumber = 5;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableComplete = 1;
      }else if(x>=413 && x<=617 && y>=145 && y<=188 && onMouse4==1)
      {
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableWindmill = 1;
         enableComplete = 0;
      }
      else if(x>=413 && x<=617 && y>=206 && y<=253 && onMouse4==1)
      {
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableHouse = 1;
         enableComplete = 0;
      }
      else if(x>=413 && x<=617 && y>=268 && y<=316 && onMouse4==1)
      {
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableTransformer = 1;
         enableComplete = 0;
      }
      else if(x>=413 && x<=617 && y>=333 && y<=382 && onMouse4==1)
      {
         onMouse = 0;
         onMouse1 = 0;
         onMouse2 = 0;
         onMouse3 = 0;
         onMouse4 = 0;
         enableWindmill = 0;
         enableHouse = 0;
         enableTransformer = 0;
         enableBackground = 0;
         enableBackground = 1;
         enableComplete = 0;
      }
    }
}


/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char **argv)
{
   glutInit(&argc, argv);                         // Initialize GLUT
   // initStaticObjects();

   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // Enable double buffered mode
   glutInitWindowSize(640, 480);                  // Set the window's initial width & height
   glutInitWindowPosition(50, 50);                // Position the window's initial top-left corner
   glutCreateWindow(title);                       // Create window with the given title
   glutDisplayFunc(display);                      // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);                      // Register callback handler for window re-size event  
   glutMotionFunc(motion);
   glutKeyboardFunc(processNormalKeys);
   glutMouseFunc(mouseClicks);
   initGL();                   // Our own OpenGL initialization
   // includeBulb();
   initTerrain();
   glutTimerFunc(0, timer, 0); // First timer call immediately [NEW]
   glutMainLoop();             // Enter the infinite event-processing loop
   return 0;
}
