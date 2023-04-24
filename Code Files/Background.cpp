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