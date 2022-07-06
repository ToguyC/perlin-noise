#ifndef UTILITIES_H_

#include <math.h>
#include <stdlib.h>

typedef struct _rgb {
    float R, G, B;
} rgb_t;

rgb_t hsv2rgb(float H, float S, float V);

#endif // !UTILITIES_H_
