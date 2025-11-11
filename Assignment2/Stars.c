#include <time.h>
#include <stdlib.h>
#include <glut.h>
#include "Stars.h"

static Star stars[NUM_STARS];

float frandRange(float min, float max) {
    return min + (float)rand() / RAND_MAX * (max - min);
}

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

void updateStars()
{
    for (int i = 0; i < NUM_STARS; i++)
    {
        stars[i].brightness += stars[i].twinkleSpeed * ((rand() % 2) ? 1 : -1);
        if (stars[i].brightness > 1.0f) stars[i].brightness = 1.0f;
        if (stars[i].brightness < 0.5f) stars[i].brightness = 0.5f;
    }
}

void drawStars()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST); //helps to draw all the stars behind

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