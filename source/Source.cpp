#include <SDL.h>
#include <cstdio>
#include "Game.h"
#include <exception>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include "../dependencies/XML/rapidxml.hpp"
#include "../dependencies/XML/rapidxml_utils.hpp"
#include "../dependencies/XML/rapidxml_iterators.hpp"
#include "../dependencies/XML/rapidxml_print.hpp"
#include <SDL_ttf.h>





int main(int argc, char* args[]) {

    TTF_Init();

    auto game = Game();
    try {
        game.Init();

        auto lastTime = std::chrono::system_clock::now();
        while (game.IsRunning()) {
            auto current = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsedSeconds = current - lastTime;
            game.HandleEvents();

            game.Update(elapsedSeconds.count());

            game.Render();
            lastTime = current;
        }

        game.Release();
    }
    catch (std::exception& exception) {
        fprintf(stderr, "%s", exception.what());
        SDL_Quit();
        return -1;
    }

    return 0;
}