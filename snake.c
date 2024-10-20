#include "snake.h"

void initSnake(Snake* snake)
{
    snake->length = 1;
    snake->body[0].x = SCREEN_WIDTH / (2 * TILE_SIZE);
    snake->body[0].y = SCREEN_HEIGHT / (2 * TILE_SIZE);
    snake->direction.x = 1;
    snake->direction.y = 0;
}

void moveSnake(Snake* snake)
{
    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i] = snake->body[i - 1];
    }
    snake->body[0].x += snake->direction.x;
    snake->body[0].y += snake->direction.y;
}

void renderSnake(SDL_Renderer* renderer, Snake* snake, SDL_Texture* snakeTexture)
{
    for (int i = 0; i < snake->length; i++)
    {
        renderTexture(renderer, snakeTexture, snake->body[i].x * TILE_SIZE, snake->body[i].y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    }
}

void handleInput(Snake* snake, SDL_Event* e)
{
    if (e->type == SDL_KEYDOWN) 
    {
        switch (e->key.keysym.sym) 
        {
            case SDLK_UP:
                if (snake->direction.y == 0) 
                {
                    snake->direction.x = 0;
                    snake->direction.y = -1;
                }

                break;

            case SDLK_DOWN:
                if (snake->direction.y == 0) 
                {
                    snake->direction.x = 0;
                    snake->direction.y = 1;
                }

                break;

            case SDLK_LEFT:
                if (snake->direction.x == 0) 
                {
                        snake->direction.x = -1;
                        snake->direction.y = 0;
                }

                break;

            case SDLK_RIGHT:
                if (snake->direction.x == 0) 
                {
                    snake->direction.x = 1;
                    snake->direction.y = 0;
                }
                break;
        }
    }
}

bool checkCollision(Snake* snake)
{
    if (snake->body[0].x - 2 < 0 || snake->body[0].x + 2 >= SCREEN_WIDTH / TILE_SIZE ||
        snake->body[0].y - 2 < 0 || snake->body[0].y + 2 >= SCREEN_HEIGHT / TILE_SIZE)
    {
        return true;
    }

    for (int i = 0; i < snake->length; i++)
    {
        if (snake->body[0].x == snake->body[i].x && snake->body[0].y == snake->body[i].y)
        {
            return true;
        }
    }

    return false;
}

void growSnake(Snake* snake)
{
    snake->length++;
}

bool checkFoodCollision(Snake* snake, Point* food)
{
    if (snake->body[0].x == food->x && snake->body[0].y == food->y)
    {
        return true;
    }
    return false;
}

void renderFood(SDL_Renderer* renderer, Point* food, SDL_Texture* foodTexture)
{
    renderTexture(renderer, foodTexture, food->x * TILE_SIZE, food->y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}

void placeFood(Point* food)
{
    food->x = rand() % (SCREEN_WIDTH / TILE_SIZE);
    food->y = rand() % (SCREEN_HEIGHT / TILE_SIZE);
}

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) 
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) 
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } 
    else 
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;  
}

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int width, int height) 
{
    SDL_Rect renderQuad = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}
