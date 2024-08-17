#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "screen_manager.h"
#include "utils.h"

const int MENU_ITEMS = 6;

void HandleMainMenu(SDL_Renderer* renderer, SDL_Window* window, ScreenState& currentScreen) {
    const char* fontPath = "assets/VT323-Regular.ttf";
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    const char* menuItems[MENU_ITEMS] = {"ONS RUNNER", "NEW GAME", "ゲームをロード", "OPTIONS", "CREDITS", "EXIT"};
    int selectedItem = 1;
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT || currentScreen == ScreenState::EXIT) {
                running = false;
                currentScreen = ScreenState::EXIT;
                break;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_w:
                        selectedItem--;
                        if (selectedItem < 1) selectedItem = MENU_ITEMS - 1;
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        selectedItem++;
                        if (selectedItem >= MENU_ITEMS) selectedItem = 1;
                        break;
                    case SDLK_RETURN:
                        if (selectedItem == 5) {  // Exit option
                            currentScreen = ScreenState::EXIT;
                            running = false;
                        } else if (selectedItem == 1) {  // New Game option
                            currentScreen = ScreenState::GAME;
                            return;  // Exit the menu handling function to switch screens
                        } else if (selectedItem == 2) {  // Load Game option
                            currentScreen = ScreenState::LOAD_MENU;
                            return;  // Exit the menu handling function to switch screens
                        } else if (selectedItem == 3) {  // Load Game option
                            currentScreen = ScreenState::LOAD_MENU;
                            return;  // Exit the menu handling function to switch screens
                        } else if (selectedItem == 4) {  // Credits
                            currentScreen = ScreenState::CREDITS;
                            return;  // Exit the menu handling function to switch screens
                        }
                        break;
                }
            } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                windowWidth = event.window.data1;
                windowHeight = event.window.data2;
            }
        }

        int menuItemFontSize = CalculateFontSize(windowWidth, windowHeight);
        int titleFontSize = menuItemFontSize + 20;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        int fontSize;

        for (int i = 0; i < MENU_ITEMS; ++i) {
            if(i == 0) {
                fontSize = titleFontSize;
            }
            else {
                fontSize = menuItemFontSize;
            }
            SDL_Color color = (i == selectedItem) ? SDL_Color{255, 0, 0} : SDL_Color{255, 255, 255};
            int textWidth, textHeight;
            TTF_SizeText(TTF_OpenFont(fontPath, fontSize), menuItems[i], &textWidth, &textHeight);
            int x = (windowWidth - textWidth) / 2;
            int y = (windowHeight - MENU_ITEMS * textHeight) / 2 + i * (textHeight + 10);
            RenderText(renderer, fontPath, menuItems[i], x, y, color, fontSize);
        }

        RenderNavHelperText(windowWidth, windowHeight, fontPath, renderer, mainMenuNavText);

        SDL_RenderPresent(renderer);
    }
}
