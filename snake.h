#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>

#ifndef SNAKE_H
#define SNAKE_H
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TILE_SIZE 16

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point body[500];  
    int length;
    Point direction;
} Snake;

void initSnake(Snake* snake);
void moveSnake(Snake* snake);
void renderSnake(SDL_Renderer* renderer, Snake* snake, SDL_Texture* snakeTexture);
void handleInput(Snake* snake, SDL_Event* e);
bool checkCollision(Snake* snake);
void growSnake(Snake* snake);
bool checkFoodCollision(Snake* snake, Point* food);
void renderFood(SDL_Renderer* renderer, Point* food, SDL_Texture* foodTexture);
void placeFood(Point* food);
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int width, int height);

#endif
