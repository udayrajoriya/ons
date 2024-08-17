#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <SDL2/SDL.h>

enum class ScreenState {
    MAIN_MENU,
    GAME,
    LOAD_MENU,
    SAVE_MENU,
    PAUSE_MENU,
    CREDITS,
    EXIT
};

void HandleMainMenu(SDL_Renderer* renderer, SDL_Window* window, ScreenState& currentScreen);
void HandleGameScreen(SDL_Renderer* renderer, SDL_Window* window, ScreenState& currentScreen);
void HandleLoadMenu(SDL_Renderer* renderer, SDL_Window* window, ScreenState& currentScreen);
void HandleCredits(SDL_Renderer* renderer, SDL_Window* window, ScreenState& currentScreen);

#endif // SCREEN_MANAGER_H
