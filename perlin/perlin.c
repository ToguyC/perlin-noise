#include "perlin.h"
#include <stdio.h>

static int SEED = 0;

static int hash[] = {208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
                     185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
                     9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
                     70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
                     203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
                     164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
                     228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
                     232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
                     193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
                     101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
                     135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
                     114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219,
                     24,242,231,134,80,140,93,95,114,193,160,157,110,235,92,243,66,28,202,224,
                     26,175,6,44,71,94,179,49,196,16,211,82,32,236,52,238,234,59,81,137,125,45,
                     18,109,181,39,216,65,218,159,53,241,88,29,73,150,190,221,154,75,1,118,130,67,
                     12,57,203,232,107,199,78,133,215,177,141,25,158,50,17,85,34,20,201,227,131,9,
                     195,139,165,58,151,230,210,194,187,214,176,173,138,207};

void pseed(int s) {
    SEED = s;
}

int noise2(int x, int y)
{
    int tmp = hash[(y + SEED) % 356];
    return hash[(tmp + x) % 356];
}

int noise3(int x, int y, int z) {
    int tmp = hash[(z + SEED) % 356];
    tmp = hash[(tmp + y) % 356];
    return hash[(tmp + x) % 356];
}

float lin_inter(float x, float y, float s)
{
    return x + s * (y-x);
}

float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3-2*s));
}

float noise2d(float x, float y)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise2(x_int, y_int);
    int t = noise2(x_int+1, y_int);
    int u = noise2(x_int, y_int+1);
    int v = noise2(x_int+1, y_int+1);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);
    return smooth_inter(low, high, y_frac);
}

float noise3d(float x, float y, float z) {
    int x_int = x;
    int y_int = y;
    int z_int = z;
    
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    float z_frac = z - z_int;

    int v1 = noise3(x_int, y_int, z_int);
    int v2 = noise3(x_int + 1, y_int, z_int);
    int v3 = noise3(x_int, y_int + 1, z_int);
    int v4 = noise3(x_int + 1, y_int + 1, z_int);
    int v5 = noise3(x_int, y_int, z_int + 1);
    int v6 = noise3(x_int + 1, y_int, z_int + 1);
    int v7 = noise3(x_int, y_int + 1, z_int + 1);
    int v8 = noise3(x_int + 1, y_int + 1, z_int + 1);

    float i1 = smooth_inter(v1, v2, x_frac);
    float i2 = smooth_inter(v3, v4, x_frac);
    float i3 = smooth_inter(v5, v6, x_frac);
    float i4 = smooth_inter(v7, v8, x_frac);

    float j1 = smooth_inter(i1, i2, y_frac);
    float j2 = smooth_inter(i3, i4, y_frac);

    return smooth_inter(j1, j2, z_frac);
}

float perlin2d(float x, float y, float freq, int depth)
{
    float xa = x*freq;
    float ya = y*freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    int i;
    for(i=0; i<depth; i++)
    {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin/div;
}

float perlin3d(float x, float y, float z, float freq, float depth)
{
    float xa = x*freq;
    float ya = y*freq;
    float za = z*freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    int i;
    for(i=0; i<depth; i++)
    {
        div += 256 * amp;
        fin += noise3d(xa, ya, za) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
        za *= 2;
    }

    return fin/div;
}
