#ifndef TEXTURE_H_ 
#define TEXTURE_H_ 

#include "Color.h"

#define bitmapHeight	8
#define bitmapWidth		8

typedef struct s_texture {
	int width;
	int height;
	int map[bitmapWidth][bitmapHeight];
	Color colors[2];
} Texture;

Texture texture1 = { 8, 8, {
        {1,1,1,1,1,1,1,1 },
        {0,0,0,1,0,0,0,1},
        {1,1,1,1,1,1,1,1},
        {0,1,0,0,0,1,0,0},
        {1,1,1,1,1,1,1,1},
        {0,0,0,1,0,0,0,1},
        {1,1,1,1,1,1,1,1},
        {0,1,0,0,0,1,0,0} 
    }, 
    {{255, 241, 232, 255}, {94, 195, 199, 255}}
};

#endif // !COLOR_H_