#include "utils.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>

std::string loadMenuNavText = "Use [Up]/[Down]/[W]/[S] Keys to navigate, [Enter] to select";
std::string mainMenuNavText = "Use [Up]/[Down]/[W]/[S] Keys to navigate, [Enter] to select";
std::string creditsNavText = "Use [Esc] to return to the Main Menu";

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

// Render the navigation text at the bottom
void RenderNavHelperText(int windowWidth, int windowHeight, const char* fontPath, SDL_Renderer* renderer, std::string navText) {
    int fontSizeScaleModifier = 30;
    TTF_Font* font = TTF_OpenFont(fontPath, CalculateFontSize(windowWidth, windowHeight, fontSizeScaleModifier));
    SDL_Color navColor = {200, 200, 200};
    int navTextWidth, navTextHeight;
    TTF_SizeText(font, navText.c_str(), &navTextWidth, &navTextHeight);
    int navTextX = (windowWidth - navTextWidth) / 2;  // Center the text horizontally
    int navTextY = windowHeight - navTextHeight - 10;  // 10 pixels from the bottom
    RenderText(renderer, fontPath, navText.c_str(), navTextX, navTextY, navColor, TTF_FontHeight(font));
}

int CalculateFontSize(int windowWidth, int windowHeight) {
    return std::min(windowWidth, windowHeight) / 20;
}

int CalculateFontSize(int windowWidth, int windowHeight, int fontSizeScaleModifier) {
    return std::min(windowWidth, windowHeight) / fontSizeScaleModifier;
}

// Function to break text into lines based on the width of the window
std::vector<std::string> WrapText(const std::string& text, TTF_Font* font, int maxWidth) {
    std::vector<std::string> lines;
    std::string currentLine;
    std::string word;
    size_t pos = 0;

    while (pos < text.size()) {
        // Find the next space or end of text
        size_t nextSpace = text.find(' ', pos);

        if (nextSpace == std::string::npos) nextSpace = text.size();

        word = text.substr(pos, nextSpace - pos);
        pos = nextSpace + 1;

        std::string testLine = currentLine.empty() ? word : currentLine + " " + word;

        int textWidth, textHeight;
        TTF_SizeText(font, testLine.c_str(), &textWidth, &textHeight);

        if (textWidth > maxWidth) {
            if (!currentLine.empty()) {
                lines.push_back(currentLine);
            }
            currentLine = word;
        } else {
            currentLine = testLine;
        }
    }

    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    return lines;
}