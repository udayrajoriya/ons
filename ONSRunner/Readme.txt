ONSRunner
==========

ONSRunner is a tool designed to help you create an executable for your project, allowing testing and distribution.

Build Instructions
-------------------
1) Visit the SDL2 releases page (https://github.com/libsdl-org/SDL/releases/) and download the latest version of "SDL2-devel-<version>-mingw.zip".
2) Extract the zip file to a temporary directory.
3) Navigate to the extracted temporary directory, then inside the x86_64-w64-mingw32 folder.
4) Copy the bin, include, and lib directories into the "ONSRunner" directory.
5) Visit the SDL2-TTF releases page (https://github.com/libsdl-org/SDL_ttf/releases) and download the latest version of "SDL2_ttf-devel-<version>-mingw.zip".
6) Extract the zip file to a temporary directory.
7) Navigate to the extracted temporary directory, then inside the x86_64-w64-mingw32 folder.
8) Copy the bin, include, and lib directories into the "ONSRunner" directory.
9) Create a directory called "assets" within the "ONSRunner" directory.
10) Download the font VT323 from https://fonts.google.com/specimen/VT323.
11) Extract the downloaded zip to a temporary directory.
12) Copy "VT323-Regular.ttf" from the extracted zip into the "assets" directory inside "ONSRunner" directory.
13) Create a directory called "distribute" within the "ONSRunner" directory.
14) Copy the "assets" directory into the "distribute" directory.
15) Copy "SDL2_ttf.dll" and "SDL2.dll" from the bin directory into the "distribute" directory.
16) If using VSCode to build, open the ".vscode/launch.json" file and update value of "miDebuggerPath" if MINGW is installed at a different location.
17) Navigate to the src directory and open main.cpp in VSCode.
18) Press Ctrl + Shift + B to build the project.
19) To run the project, goto the distribute directory and execute the main.exe file or alternatively from VS Code itself, press F5.