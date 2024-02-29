#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "raycaster.h"

// SDL2.lib; SDL2main.lib;

int main(int argc, char* argv) {
	// initilise values
	double posX = initXPos, posY = initYPos;
	double dirX = initXDir, dirY = initYDir;
	double planeX = initPlaneX, planeY = initPlaneY;
	double time = 0;
	double oldTime = 0;

	// setup renderer
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL initialization failed (%s)\n", SDL_GetError());
		return -1;
	}
	if (SDL_CreateWindowAndRenderer(screenWidth, screenHeight, 0, window, renderer) != 0) {
		fprintf(stderr, "Window creation failed (%s)\n", SDL_GetError());
		return -1;
	}

	// main loop
	SDL_bool done;
	done = SDL_FALSE;
	while (!done) {
		for(int x = 0; x < screenWidth; x++){
			// ray pos & Dir
			double cameraX = 2 * x / (double)screenWidth - 1;
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;

			int mapX = (int)posX;
			int mapY = (int)posY;

			double sideDistX;

		}
	}


	return 0;
}
