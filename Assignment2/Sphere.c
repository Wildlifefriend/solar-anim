#include "Sphere.h"
#include <glut.h>
#include <math.h>



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

void drawBasicSphere()
{
    drawSphere(
        (Center) {0,0,0}, 
        1,
        (ColorBlend) { {0.5,0.5,0}, {0,0,1.0} },
        20
    );
}

void drawNormalizedSphere(ColorBlend color, int depth)
{
    drawSphere(
        (Center) {0, 0, 0},
        1,
        color,
        20
    );
}