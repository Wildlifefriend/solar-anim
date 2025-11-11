#include "Sphere.h"
#include <glut.h>
#include <math.h>
#include <time.h>

typedef struct
{
    float x, y, z;
    float r, g, b;
    float phase;
    float twinkleSpeed;
    float brightness;
} Star;

static Star stars[NUM_STARS];

void interpColor(double phi, ColorBlend color)
{
    float t = (phi + 80.0) / 160.0;
    /*
    * this is used to get each section of the sphere longitude that we colour in,
    * adding by 80 puts it in the positive range, and then dividing by 160 puts it
    * in range of 0->1 which is used for linear interpolation
    */
    float r = (1 - t) * color[0][0] + t * color[1][0];
    float g = (1 - t) * color[0][1] + t * color[1][1];
    float b = (1 - t) * color[0][2] + t * color[1][2];
    glColor3f(r, g, b);
}

// Given a center point, which in this case of the Assignment will always be 0,0,0 a radius which wil also always be 1, 
// and a colour to blend from 1 end to the other, and a depth value in which it will give the sphere detail, it will draw a sphere
void drawSphere(Center center, double radius, ColorBlend color, int depth)
{
    double x, y, z, thet, phi;
    double c = 3.14159 / 180.0; // degrees → radians

    double cx = center[0];
    double cy = center[1];
    double cz = center[2];

    glColor3fv(color[1]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(cx, cy, cz + radius);  // north pole

    z = sin(c * 80.0);
    for (thet = -180.0; thet <= 180.0; thet += 180.0/depth)
    {
        x = sin(c * thet) * cos(c * 80.0);
        y = cos(c * thet) * cos(c * 80.0);
        glVertex3d(cx + radius * x, cy + radius * y, cz + radius * z);
    }
    glEnd();

    glColor3fv(color[0]); //set to the bottom colour
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(cx, cy, cz - radius);  // south pole

    z = -sin(c * 80.0);
    for (thet = -180.0; thet <= 180.0; thet += 180.0/depth)
    {
        x = sin(c * thet) * cos(c * 80.0);
        y = cos(c * thet) * cos(c * 80.0);
        glVertex3d(cx + radius * x, cy + radius * y, cz + radius * z);
    }
    glEnd();

    for (phi = -80.0; phi <= 80.0; phi += 80.0/depth)
    {
        interpColor(phi, color);
        glBegin(GL_QUAD_STRIP);
        for (thet = -180.0; thet <= 180.0; thet += 180.0/depth)
        {
            // top of the quad strip band
            x = sin(c * thet) * cos(c * phi);
            y = cos(c * thet) * cos(c * phi);
            z = sin(c * phi);
            glVertex3d(cx + radius * x, cy + radius * y, cz + radius * z);

            // bottom of the quad strip band
            x = sin(c * thet) * cos(c * (phi + 20.0));
            y = cos(c * thet) * cos(c * (phi + 20.0));
            z = sin(c * (phi + 20.0));
            glVertex3d(cx + radius * x, cy + radius * y, cz + radius * z);
        }
        glEnd();
    }
}

// Create a sphere with no given values
void drawBasicSphere()
{
    drawSphere(
        (Center) {0,0,0}, 
        1,
        (ColorBlend) { {0.5,0.5,0}, {0,0,1.0} },
        20
    );
}

// Creates a sphere give a blend of colours, and the details depth of the sphere wanted
void drawNormalizedSphere(ColorBlend color, int depth)
{
    drawSphere(
        (Center) {0, 0, 0},
        1,
        color,
        20
    );
}

// Used as a helper function for determining random values for the stars
float frandRange(float min, float max) {
    return min + (float)rand() / RAND_MAX * (max - min);
}

// initializes star structure which are used to draw in the night sky, with coordinates generated, a colour value which is similar to white, and a default brightness which changes depending on the twinkle value
void initStars()
{
    float range = 100.0f;
    for (int i = 0; i < NUM_STARS; i++) {
        // Place them FAR away in 3D space (outside -10..10 range)
        stars[i].x = frandRange(-range, range);
        stars[i].y = frandRange(-range, range);
        stars[i].z = frandRange(-range, -50.0f); // keep them behind the solar system

        // Random base color (mostly whiteish)
        stars[i].r = 0.8f + 0.2f * ((float)rand() / RAND_MAX);
        stars[i].g = 0.8f + 0.2f * ((float)rand() / RAND_MAX);
        stars[i].b = 0.8f + 0.2f * ((float)rand() / RAND_MAX);

        stars[i].brightness = 1.0f;
        stars[i].twinkleSpeed = 0.02f + 0.03f * ((float)rand() / RAND_MAX);
    }
}

// Used to update the brightness and make the stars twinkle
void updateStars()
{
    for (int i = 0; i < NUM_STARS; i++)
    {
        stars[i].brightness += stars[i].twinkleSpeed * ((rand() % 2) ? 1 : -1);
        if (stars[i].brightness > 1.0f) stars[i].brightness = 1.0f;
        if (stars[i].brightness < 0.5f) stars[i].brightness = 0.5f;
    }
}

// Draws all the stars initialized by initStars()
void drawStars()
{
    glDisable(GL_LIGHTING);

    glPushAttrib(GL_ENABLE_BIT | GL_POINT_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glPointSize(1.5f);

    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_STARS; i++)
    {
        glColor3f(stars[i].r * stars[i].brightness,
            stars[i].g * stars[i].brightness,
            stars[i].b * stars[i].brightness);
        glVertex3f(stars[i].x, stars[i].y, stars[i].z);
    }
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glPopAttrib();
}

// Given the radius at which the desired planets radius is translated by, it calculates the circular radius and draws it showing what path the planets follow
// Only works for circular orbits
void drawOrbitRing(float radius)
{
    int segments = 100;
    glBegin(GL_LINE_LOOP);

    glColor3f(1, 1, 1);
    for (int i = 0; i < segments; i++)
    {
        float angle = 2.0f * 3.14159f * i / segments; //does the a calc to get 2pi and then uses the i and segments to find which angle it currently needs to find the point for
        float x = radius * cos(angle);
        float z = radius * sin(angle);
    
        glVertex3f(x, 0.0f, z);
    }

    glEnd();
}