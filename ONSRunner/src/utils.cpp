#include "utils.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>

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

int CalculateFontSize(int windowWidth, int windowHeight) {
    return std::min(windowWidth, windowHeight) / 20;
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