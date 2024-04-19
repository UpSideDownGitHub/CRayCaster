#pragma once

#include "Color.h"

#define bitmapHeight	8
#define bitmapWidth		8

typedef struct s_texture {
	int width;
	int height;
    Color colors[2];
    int map[bitmapWidth][bitmapHeight];
} Texture;

Texture memoryTextures[1] = { 
    { 8, 8, {{100, 100, 100, 255}, {150, 150, 150, 150}} ,
    {
        {1,1,1,1,1,1,1,1},
        {0,0,0,1,0,0,0,1},
        {1,1,1,1,1,1,1,1},
        {0,1,0,0,0,1,0,0},
        {1,1,1,1,1,1,1,1},
        {0,0,0,1,0,0,0,1},
        {1,1,1,1,1,1,1,1},
        {0,1,0,0,0,1,0,0}
    }}

};