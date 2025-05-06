#include "physics.h"
#include "graphica.h"
#include "config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <math.h>

#define padding 50
#define halfW (WINDOW_WIDTH - 3 * padding) / 2 
#define halfH (WINDOW_HEIGHT - 3 * padding) / 2 

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow("Relay Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSerif-Bold.ttf", 12);
    load_config("config");

    GraphData graphData;
    double dt = TIME_INTERVAL;
    float minY, maxY;
    float currentTime = 0.0f, timeOffset = 0.0f;
    float yOffset[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    char *values[4] = {"I1", "I2","T","F"};
    const float visibleYRange = 10.0f;
    
    initGraphData(&graphData);

    SDL_Event e;
    int quit = 0;
    int firstCircuitClosed = 1;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = 1;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_i) {
                    firstCircuitClosed = 1; // Замыкаем первую цепь
                } else if (e.key.keysym.sym == SDLK_o) {
                    firstCircuitClosed = 0; // Размыкаем первую цепь
                }
            }
        }
        // Симуляция в зависимости от состояния первой цепи
        if (firstCircuitClosed) {
            rk4_step(&I1, &T1, &T2, &x, &v, dt);
        }else {
            I1 = 0.0; // Обнуляем ток в первой цепи
            rk4_step(&I1, &T1, &T2, &x, &v, dt);
        }
        double Fmag = F_magnetic(I1);

        updateGraphData(&graphData, currentTime, I1, I2(T2, I1, x), T1 - 293.0, Fmag);
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);
    
        currentTime += dt;
        if (currentTime > 10.0f) timeOffset = currentTime - 10.0f;

        for (int i = 0; i < 4; i++) {
            CalculateOffset(graphData, yOffset, i, visibleYRange);

            int x = padding + (padding + halfW)*(i % 2);
            int y = padding + (padding + halfH)*(i > 1);

            drawGridAndAxes(renderer, font, timeOffset, yOffset[i], yOffset[i] + visibleYRange, x, y, halfW, halfH);
            drawGraph(renderer, &graphData, timeOffset, yOffset[i], yOffset[i] + visibleYRange, x, y, halfW, halfH, i + 1);
            drawText(renderer, font, values[i], x + 5, y + 5);
        } 
        SDL_RenderPresent(renderer);
        SDL_Delay((int)(dt * 1000));
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
