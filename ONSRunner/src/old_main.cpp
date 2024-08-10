#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

const int MENU_ITEMS = 4;

int CalculateFontSize(int windowWidth, int windowHeight) {
    return std::min(windowWidth, windowHeight) / 20;  // Adjust the divisor to change scaling behavior
}

void RenderText(SDL_Renderer* renderer, const char* fontPath, const char* text, int x, int y, SDL_Color color, int fontSize) {
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if (!font) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect destRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}


int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Resizable Window", 100, 100, 640, 480, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    const char* fontPath = "assets/VT323-Regular.ttf"; // Update with the path to your font file
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    const char* menuItems[MENU_ITEMS] = {"NEW GAME", "LOAD GAME", "OPTIONS", "EXIT"};
    int selectedItem = 0;
    bool running = true;
    SDL_Event event;

    while (running) {
        SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_w:
                    selectedItem--;
                    if (selectedItem < 0) selectedItem = MENU_ITEMS - 1;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    selectedItem++;
                    if (selectedItem >= MENU_ITEMS) selectedItem = 0;
                    break;
                case SDLK_RETURN:
                    if (selectedItem == 3) {  // Exit option
                        running = false;
                    } else {
                        std::cout << "Selected: " << menuItems[selectedItem] << std::endl;
                    }
                    break;
            }
        } else if (e.type == SDL_WINDOWEVENT) {
            if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                windowWidth = e.window.data1;
                windowHeight = e.window.data2;
            }
        }
    }

    int fontSize = CalculateFontSize(windowWidth, windowHeight);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < MENU_ITEMS; ++i) {
        SDL_Color color = (i == selectedItem) ? SDL_Color{255, 0, 0} : SDL_Color{255, 255, 255};

        // Calculate position dynamically based on font size
        int textWidth, textHeight;
        TTF_SizeText(TTF_OpenFont(fontPath, fontSize), menuItems[i], &textWidth, &textHeight);

        int x = (windowWidth - textWidth) / 2;
        int y = (windowHeight - MENU_ITEMS * textHeight) / 2 + i * (textHeight + 10);  // Add padding

        RenderText(renderer, fontPath, menuItems[i], x, y, color, fontSize);
    }

    SDL_RenderPresent(renderer);
}

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

