#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

void RenderText(SDL_Renderer* renderer, const char* fontPath, const char* text, int x, int y, SDL_Color color, int fontSize);
int CalculateFontSize(int windowWidth, int windowHeight);
std::vector<std::string> WrapText(const std::string& text, TTF_Font* font, int maxWidth);

#endif // UTILS_H
