#include "utils.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::string loadMenuNavText = "Use [Up]/[Down]/[W]/[S] Keys to navigate, [Enter] to select";
std::string mainMenuNavText = "Use [Up]/[Down]/[W]/[S] Keys to navigate, [Enter] to select";
std::string creditsNavText = "Use [Esc] to return to the Main Menu";

std::string engineCreditsText = "\nMade with Orbital Narrative System\nhttps://ons.com";

void RenderText(SDL_Renderer* renderer, const char* fontPath, const char* text, int x, int y, SDL_Color color, int fontSize) {
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if (!font) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return;
    }

    // Split the text into lines
    std::string strText(text);
    std::stringstream ss(strText);
    std::string line;
    int offsetY = 0;

    while (std::getline(ss, line, '\n')) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, line.c_str(), color);
        if (!surface) {
            std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
            TTF_CloseFont(font);
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(surface);
            TTF_CloseFont(font);
            return;
        }

        SDL_Rect destRect = { x, y + offsetY, surface->w, surface->h };
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);

        offsetY += surface->h;  // Move the y position down for the next line

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

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
    size_t pos = 0;

    while (pos < text.size()) {
        // Check for newline characters
        if (text[pos] == '\n') {
            if (!currentLine.empty()) {
                lines.push_back(currentLine);
                currentLine.clear();
            }
            lines.push_back("");  // Add an empty line to represent the newline character
            ++pos;
            continue;
        }

        // Find the next space or end of text
        size_t nextSpace = text.find(' ', pos);
        size_t nextNewLine = text.find('\n', pos);

        if (nextSpace == std::string::npos) nextSpace = text.size();
        if (nextNewLine != std::string::npos && nextNewLine < nextSpace) nextSpace = nextNewLine;

        std::string word = text.substr(pos, nextSpace - pos);
        pos = nextSpace;

        if (pos < text.size() && text[pos] == ' ') {
            ++pos; // Skip the space
        }

        // Check if adding the word would exceed maxWidth
        std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
        int textWidth, textHeight;
        TTF_SizeText(font, testLine.c_str(), &textWidth, &textHeight);

        if (textWidth > maxWidth) {
            if (!currentLine.empty()) {
                lines.push_back(currentLine); // Push the current line
            }
            currentLine = word; // Start a new line with the current word
        } else {
            currentLine = testLine;
        }
    }

    // Push any remaining text in the current line to the vector
    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    return lines;
}
