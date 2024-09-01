#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

extern std::string loadMenuNavText;
extern std::string mainMenuNavText;
extern std::string creditsNavText;

extern std::string engineCreditsText;

void RenderText(SDL_Renderer* renderer, const char* fontPath, const char* text, int x, int y, SDL_Color color, int fontSize);
void RenderNavHelperText(int windowWidth, int windowHeight, const char* fontPath, SDL_Renderer* renderer, std::string navText);
int CalculateFontSize(int windowWidth, int windowHeight, int fontSizeScaleModifier);
int CalculateFontSize(int windowWidth, int windowHeight);
std::vector<std::string> WrapText(const std::string& text, TTF_Font* font, int maxWidth);

#endif // UTILS_H
