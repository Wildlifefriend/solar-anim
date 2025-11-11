#ifndef SPHERE
#define SPHERE

#define NUM_STARS 500
#define TWINKLE_STAR_MIN 0.5f
#define TWINKLE_STAR_MAX 2.0f

typedef float ColorBlend[2][3];
typedef double Center[3];

void interpColor(double phi, ColorBlend color);
void drawSphere(Center center, double radius, ColorBlend color, int depth);
void drawBasicSphere();
void drawNormalizedSphere(ColorBlend color, int depth);

float frandRange(float min, float max);
void initStars();
void updateStars();
void drawStars();

void drawOrbitRing(float radius);

#endif // !SPHERE


