#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include "screen_manager.h"
#include "utils.h"

void HandleCredits(SDL_Renderer* renderer, SDL_Window* window, ScreenState& currentScreen) {
    const char* fontPath = "assets/VT323-Regular.ttf";
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    SDL_Color color = {255, 255, 255};

    TTF_Font* font = TTF_OpenFont(fontPath, CalculateFontSize(windowWidth, windowHeight));
    if (!font) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return;
    }

    std::string fullText = "Your text goes here...\nWhat is up you people?";
    std::vector<std::string> lines = WrapText(fullText, font, windowWidth - 20);  // 20 pixels padding
    size_t currentPage = 0;
    size_t maxLinesPerPage = (windowHeight - 20) / (TTF_FontHeight(font) + 5);  // 5 pixels padding

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
                currentScreen = ScreenState::EXIT;
                break;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                    currentScreen = ScreenState::MAIN_MENU;
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    // Move to the next page if there is more text
                    if ((currentPage + 1) * maxLinesPerPage < lines.size()) {
                        ++currentPage;
                    } else {
                        //running = false;
                        // currentScreen = ScreenState::MAIN_MENU;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        int y = 20;
        for (size_t i = currentPage * maxLinesPerPage; i < std::min((currentPage + 1) * maxLinesPerPage, lines.size()); ++i) {
            RenderText(renderer, fontPath, lines[i].c_str(), 10, y, color, TTF_FontHeight(font));
            y += TTF_FontHeight(font) + 5;  // 5 pixels padding between lines
        }

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
}
