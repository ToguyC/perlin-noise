// @see: https://gist.github.com/nowl/828013

#ifndef PERLIN_H_

/**
 * @brief Seed the perlin noise function
 * 
 * @param s Seed
 */
void pseed(int s);

/**
 * @brief Generate perlin noise at a given point
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param freg Perlin frequency
 * @param depth Perlin depth
 *
 * @returns Perlin value
 */
float perlin2d(float x, float y, float freq, int depth);

#endif // !PERLIN_H_
