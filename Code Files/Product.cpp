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

#include "Figure.cpp"
#include "Windmill.cpp"
#include "Transformer.cpp"
#include "House.cpp"
#include "Background.cpp"
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


#include "Settings.cpp"


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
