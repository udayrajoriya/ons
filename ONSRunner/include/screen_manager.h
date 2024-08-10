#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <SDL2/SDL.h>

enum class ScreenState {
    MAIN_MENU,
    GAME,
    EXIT
};

void HandleMainMenu(SDL_Renderer* renderer, SDL_Window* window, ScreenState& currentScreen);
void HandleGameScreen(SDL_Renderer* renderer, SDL_Window* window, ScreenState& currentScreen);

#endif // SCREEN_MANAGER_H
