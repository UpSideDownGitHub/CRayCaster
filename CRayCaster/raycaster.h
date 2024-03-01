#ifndef  RAYCASTER_H_
#define RAYCASTER_H_

#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "Color.h"
#include "Texture.h"

#define mapWidth		10
#define mapHeight		10
#define screenWidth		1280
#define screenHeight	720
#define scale           2
#define halfWidth       (screenWidth / 2)
#define halfHeight      (screenHeight / 2)

#define projWidth       (screenWidth / scale)
#define projHeight      (screenHeight  / scale)
#define projHalfWidth   (projWidth / 2)
#define projHalfHeight  (projHeight / 2)

#define FOV             60
#define halfFOV         (FOV / 2)

#define delay           30
#define incAngle        (double)FOV / (double)projWidth
#define precision       64

#define movementSpeed   0.05
#define rotationSpeed   3.0
#define radius          10

#define birdEyeScale    20
#define rayDrawnPerc    40

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)

#define setDrawColor(renderer, color) (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a))

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
} Player;

typedef struct s_ray {
    float x;
    float y;
} Ray;

bool up, down, left, right;

SDL_Window* window;
SDL_Renderer* renderer;

#endif