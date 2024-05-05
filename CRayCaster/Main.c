#include "raycaster.h"

Color calculateLighting(Color texColor, float dist)
{
    float brightnessModifier = 1.0f - dist / maxDistance < 0.0f ? 0.0f : 1.0f - dist / maxDistance;
    Color finalCol = multiply_color_by_float(texColor, brightnessModifier);
    return finalCol;
}

void drawLine(int x1, int y1, int x2, int y2, Color color) {
    setDrawColor(renderer, color);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawTexture(int x, int wallHeight, int texturePosX, Texture* tex, float dist) {
    float yIncrementer = (wallHeight * 2) / tex->height;
    int y = projHalfHeight - wallHeight;

    for (int i = 0; i < tex->height; i++){
        Color finalColor = calculateLighting(tex->colors[tex->map[i][texturePosX]], dist);
        setDrawColor(renderer, finalColor);
        SDL_RenderDrawLine(renderer, x, y, x, y + yIncrementer);
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
            wall = worldMap[(int)ray.y][(int)ray.x];
        }

        float distance = sqrt(pow(player->x - ray.x, 2) + pow(player->y - ray.y, 2));
        distance *= cos(degreesToRadians(player->angle - rayAngle));

        // MEMORY TEXTURES
        int texturePosX = (int)(memoryTextures[0].width * (ray.x + ray.y)) % memoryTextures[0].width;

        // Calculate screen coordinates of wall
        int wallScreenHeight = (int)(projHalfHeight / distance);
        int wallTop = projHalfHeight - wallScreenHeight / 2;
        int wallBottom = projHalfHeight + wallScreenHeight / 2;

        // Draw Ceiling
        drawLine(rayCount, 0, rayCount, wallTop, blue);
        // Draw Wall
        drawTexture(rayCount, wallScreenHeight, texturePosX, &memoryTextures[0], distance);
        // Draw Floor
        drawLine(rayCount, wallBottom, rayCount, projHeight, green);

        // increment angle
        rayAngle += incAngle;
    }
}

void drawMap(Player *player){
    for (int i = 0; i < mapWidth; i++){
        for (size_t j = 0; j < mapHeight; j++){
            if (worldMap[i][j] == 0)
                setDrawColor(renderer, empty);
            else
                setDrawColor(renderer, wall);
            SDL_Rect rect = { j * birdEyeScale, i * birdEyeScale, birdEyeScale, birdEyeScale };
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    setDrawColor(renderer, playerCol);
    SDL_Rect rect = { player->x * birdEyeScale, player->y * birdEyeScale, birdEyeScale / 2, birdEyeScale / 2};
    SDL_RenderFillRect(renderer, &rect);

    setDrawColor(renderer, red);
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
        if (rayCount % rayDrawnPerc == 0)
            SDL_RenderDrawLine(renderer, player->x * birdEyeScale, player->y * birdEyeScale, ray.x * birdEyeScale, ray.y * birdEyeScale);
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

    // INIT PLAYER
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
            if (event.key.keysym.sym == SDLK_w)
                up = true;
            if (event.key.keysym.sym == SDLK_s)
                down = true;
            if (event.key.keysym.sym == SDLK_a)
                left = true;
            if (event.key.keysym.sym == SDLK_d)
                right = true;
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_w)
                up = false;
            if (event.key.keysym.sym == SDLK_s)
                down = false;
            if (event.key.keysym.sym == SDLK_a)
                left = false;
            if (event.key.keysym.sym == SDLK_d)
                right = false;
            break;
        }

        if (up) {
            double playerCos = cos(degreesToRadians(player.angle)) * movementSpeed;
            double playerSin = sin(degreesToRadians(player.angle)) * movementSpeed;
            double newX = playerCos + player.x;
            double newY = playerSin + player.y;
            int checkX = floor(newX + playerCos * radius);
            int checkY = floor(newY + playerSin * radius);

            if (worldMap[checkY][(int)floor(player.x)] == 0)
                player.y = newY;
            if (worldMap[(int)floor(player.y)][checkX] == 0)
                player.x = newX;
        }
        else if (down) {
            double playerCos = cos(degreesToRadians(player.angle)) * movementSpeed;
            double playerSin = sin(degreesToRadians(player.angle)) * movementSpeed;
            double newX = player.x - playerCos;
            double newY = player.y - playerSin;
            int checkX = floor(newX - playerCos * radius);
            int checkY = floor(newY - playerSin * radius);

            if (worldMap[checkY][(int)floor(player.x)] == 0)
                player.y = newY;
            if (worldMap[(int)floor(player.y)][checkX] == 0)
                player.x = newX;
        }
        if (left){
            player.angle -= rotationSpeed;
            player.angle = (int)player.angle % 360;
        }
        else if (right){
            player.angle += rotationSpeed;
            player.angle = (int)player.angle % 360;
        }

        // CLEAR WINDOW
        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);

        // RENDERING
        rayCasting(&player);
        drawMap(&player);

        // RENDER WINDOW
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}
