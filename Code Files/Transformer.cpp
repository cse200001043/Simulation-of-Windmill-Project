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