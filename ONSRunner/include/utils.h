#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>

void RenderText(SDL_Renderer* renderer, const char* fontPath, const char* text, int x, int y, SDL_Color color, int fontSize);
int CalculateFontSize(int windowWidth, int windowHeight);

#endif // UTILS_H
