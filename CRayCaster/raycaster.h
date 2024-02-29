#ifndef  RAYCASTER_H_
#define RAYCASTER_H_

#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define mapWidth		10
#define mapHeight		10
#define screenWidth		640
#define screenHeight	480
#define halfWidth       (screenWidth / 2)
#define halfHeight      (screenHeight / 2)

#define FOV             60
#define halfFOV         (FOV / 2)

#define delay           30
#define incAngle        (FOV / screenWidth)
#define precision       64


#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)

int worldMap[mapWidth][mapHeight] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

typedef struct s_player {
    float x;
    float y;
    float angle;
} t_player;

SDL_Window* window;
SDL_Renderer* renderer;

#endif