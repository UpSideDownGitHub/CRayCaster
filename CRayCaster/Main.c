#include "raycaster.h"

// include things
// SDL2.lib; SDL2main.lib; Shell32.lib;
// tutorial being used
// https://github.com/vinibiavatti1/RayCastingTutorial/wiki/Utilities

void drawLine(int x1, int y1, int x2, int y2, Color color) {
    setDrawColor(renderer, color);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void rayCasting(Player *player) {
    float rayAngle = player->angle - halfFOV;

    for (int rayCount = 0; rayCount < screenWidth; rayCount++){
        Ray ray = { player->x, player->y };
        double rayCos = cos(degreesToRadians(rayAngle)) / precision;
        double raySin = sin(degreesToRadians(rayAngle)) / precision;
        
        int wall = 0;
        while (wall == 0) {
            ray.x += rayCos;
            ray.y += raySin;
            wall = worldMap[(int)floor(ray.y)][(int)floor(ray.x)];
        }

        double distance = sqrt(pow(player->x - ray.x, 2) + 
            pow(player->y - ray.y, 2));
        double wallHeight = floor(halfHeight / distance);

        drawLine(rayCount, 0, 
            rayCount, halfHeight - wallHeight, blue);
        drawLine(rayCount, halfHeight - wallHeight,
            rayCount, halfHeight + wallHeight, red);
        drawLine(rayCount, halfHeight + wallHeight,
            rayCount, screenHeight, green);

        // increment angle
        rayAngle += incAngle;
    }
}

int main(int argc, char* argv) {

	bool quit = false;
	SDL_Event event;

    // INIT WINDOW
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("SDL2 line drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

    Player player = { 2, 2, 90};

    while (!quit)
    {
        SDL_Delay(delay);
        
        // INPUT
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }

        // CLEAR WINDOW
        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);

        // RENDERING
        //Color color = { 0,0,0,255 };
        //drawLine(0, 100, 0, 100, color);
        rayCasting(&player);

        // RENDER WINDOW
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}
