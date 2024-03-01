#ifndef COLOR_H_
#define COLOR_H_

typedef struct s_color {
	int r;
	int g;
	int b;
	int a;
} Color;

Color red = { 255,0,0,255 };
Color green = { 0,255,0,255 };
Color blue = { 0,0,255,255 };

Color empty = { 200,200,200,255 };
Color wall = { 10,10,10,255 };
Color playerCol = { 100,100,0,255 };

#endif // !COLOR_H_
