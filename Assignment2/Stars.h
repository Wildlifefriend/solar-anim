#ifndef STARS
#define STARS

#define NUM_STARS 500
#define TWINKLE_STAR_MIN 0.5f
#define TWINKLE_STAR_MAX 2.0f

typedef struct
{
    float x, y, z;
    float r, g, b;
    float phase;
    float twinklepeed;
    float brightness;
} Star;

float frandRange(float min, float max);
void initStars();
void updateStars();
void drawStars();

#endif //!STARS