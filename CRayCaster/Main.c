#include "raycaster.h"

// include things
// SDL2.lib; SDL2main.lib; Shell32.lib;
// tutorial being used
// https://github.com/vinibiavatti1/RayCastingTutorial/wiki/Utilities

void drawLine(int x1, int y1, int x2, int y2, Color color) {
    setDrawColor(renderer, color);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawTexture(int x, int wallHeight, int texturePosX, Texture* tex) {
    int yIncrementer = (wallHeight * 2) / tex->height;
    int y = projHalfHeight - wallHeight;

    for (int i = 0; i < tex->height; i++){
        setDrawColor(renderer, tex->colors[tex->map[i][texturePosX]]);
        SDL_RenderDrawLine(renderer, x, y, x, 
            y + yIncrementer);
        y += yIncrementer;
    }
}

void rayCasting(Player *player) {
    double rayAngle = player->angle - halfFOV;

    for (int rayCount = 0; rayCount < projWidth; rayCount++) {
        Ray ray = { player->x, player->y };
        float rayCos = cos(degreesToRadians(rayAngle)) / precision;
        float raySin = sin(degreesToRadians(rayAngle)) / precision;
        
        int wall = 0;
        while (wall == 0) {
            ray.x += rayCos;
            ray.y += raySin;
            wall = worldMap[(int)floor(ray.y)][(int)floor(ray.x)];
        }

        float distance = sqrt(pow(player->x - ray.x, 2) +
            pow(player->y - ray.y, 2));
        distance *= cos(degreesToRadians(rayAngle - player->angle));
        float wallHeight = projHalfHeight / distance;

        
        // TODO change the texture code to make it so you can  have more
        // than 1 texture on different walls
        int texturePosX = (int)floor((int)(texture1.width * (ray.x + ray.y)) % texture1.width);


        // Calculate screen coordinates of wall
        int wallScreenHeight = (int)(projHalfHeight / distance);
        int wallTop = projHalfHeight - wallScreenHeight / 2;
        int wallBottom = projHalfHeight + wallScreenHeight / 2;

        // Draw wall
        drawLine(rayCount, 0, rayCount, wallTop, blue);
        //drawLine(rayCount, wallTop, rayCount, wallBottom, red);
        drawTexture(rayCount, wallHeight, texturePosX, &texture1);
        drawLine(rayCount, wallBottom, rayCount, projHeight, green);

        // increment angle
        rayAngle += incAngle;
    }
}

int main(int argc, char* argv) {

	bool quit = false;
	SDL_Event event;

    // INIT WINDOW
	SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
    SDL_RenderSetScale(renderer, scale, scale);

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
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_w: {
                    double playerCos = cos(degreesToRadians(player.angle)) * movementSpeed;
                    double playerSin = sin(degreesToRadians(player.angle)) * movementSpeed;
                    double newX = playerCos + player.x;
                    double newY = playerSin + player.y;

                    if (worldMap[(int)floor(newY)][(int)floor(newX)] == 0) {
                        player.x = newX;
                        player.y = newY;
                    }
                    break;
                }
                case SDLK_s: {
                    double playerCos = cos(degreesToRadians(player.angle)) * movementSpeed;
                    double playerSin = sin(degreesToRadians(player.angle)) * movementSpeed;
                    double newX = player.x - playerCos;
                    double newY = player.y - playerSin;

                    if (worldMap[(int)floor(newY)][(int)floor(newX)] == 0) {
                        player.x = newX;
                        player.y = newY;
                    }
                    break;
                }
                case SDLK_a:
                    player.angle -= rotationSpeed;
                    break;
                case SDLK_d:
                    player.angle += rotationSpeed;
                    break;
            }
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
