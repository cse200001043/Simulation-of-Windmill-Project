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