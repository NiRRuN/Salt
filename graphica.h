#ifndef GRAPHICA_H
#define GRAPHICA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_POINTS 600
#define TIME_INTERVAL (1.0f/60.0f)

typedef struct {
    float time[MAX_POINTS];
    float value1[MAX_POINTS];
    float value2[MAX_POINTS];
    float value3[MAX_POINTS];
    float value4[MAX_POINTS];
    int index;
} GraphData;

void initGraphData(GraphData* graphData);

void updateGraphData(GraphData* graphData, float currentTime, float v1, float v2, float v3, float v4);

void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);

void drawGridAndAxes(SDL_Renderer* renderer, TTF_Font* font, float timeOffset, float minY, float maxY, int x_offset, int y_offset, int width, int height);

void drawGraph(SDL_Renderer* renderer, GraphData* graphData, float timeOffset, float minY, float maxY, int x_offset, int y_offset, int width, int height, int graphType);

void CalculateOffset(GraphData graphData,float* yOffset, int i, float visibleYRange);
#endif
