#ifndef SPHERE
#define SPHERE

typedef float ColorBlend[2][3];
typedef double Center[3];

void interpColor(double phi, ColorBlend color);
void drawSphere(Center center, double radius, ColorBlend color, int depth);
void drawBasicSphere();
void drawNormalizedSphere(ColorBlend color, int depth);

#endif // !SPHERE


