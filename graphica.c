#include "graphica.h"
#include "config.h"

// Инициализация графика
void initGraphData(GraphData* graphData) {
    for (int i = 0; i < MAX_POINTS; i++) {
        graphData->time[i] = -1.0f;
        graphData->value1[i] = 0.0f;
        graphData->value2[i] = 0.0f;
        graphData->value3[i] = 0.0f;
        graphData->value4[i] = 0.0f;
    }
    graphData->index = 0;
}

// Обновление графика
void updateGraphData(GraphData* graphData, float currentTime, float v1, float v2, float v3, float v4) {
    graphData->time[graphData->index] = currentTime;
    graphData->value1[graphData->index] = v1;
    graphData->value2[graphData->index] = v2;
    graphData->value3[graphData->index] = v3;
    graphData->value4[graphData->index] = v4;
    graphData->index = (graphData->index + 1) % MAX_POINTS;
}

// Рисование текста
void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color textColor = {225, 225, 225, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    if (!surface) return;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
// Оси и сетка
void drawGridAndAxes(SDL_Renderer* renderer, TTF_Font* font, float timeOffset, float minY, float maxY, int x_offset, int y_offset, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    for (int i = 0; i <= 10; i++) {
        int x = x_offset + (i * width) / 10;
        int y = y_offset + (i * height) / 10;
        SDL_RenderDrawLine(renderer, x, y_offset, x, y_offset + height);
        SDL_RenderDrawLine(renderer, x_offset, y, x_offset + width, y);

        char label[16];
        snprintf(label, sizeof(label), "%.f", timeOffset + (i * 1.0f));
        drawText(renderer, font, label, x - 10, y_offset + height + 2);

        float yValue = maxY - i * (maxY - minY) / 10.0f;
        snprintf(label, sizeof(label), "%.f", yValue);
        drawText(renderer, font, label, x_offset - 40, y - 10);
    }

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderDrawLine(renderer, x_offset, y_offset + height, x_offset + width, y_offset + height);
    SDL_RenderDrawLine(renderer, x_offset, y_offset, x_offset, y_offset + height);
}
// Отрисовка графа
void drawGraph(SDL_Renderer* renderer, GraphData* graphData, float timeOffset, float minY, float maxY, int x_offset, int y_offset, int width, int height, int graphType) {
    for (int i = 1; i < MAX_POINTS; i++) {
        if (graphData->time[i] < 0 || graphData->time[i - 1] < 0) continue;

        float t1 = graphData->time[i - 1] - timeOffset;
        float t2 = graphData->time[i] - timeOffset;

        if (t2 < 0 || t1 > 10.0f || fabsf(graphData->time[i] - graphData->time[i - 1]) > 1.0f) continue;

        int x1 = x_offset + (int)(t1 * (width / 10.0f));
        int x2 = x_offset + (int)(t2 * (width / 10.0f));

        float *val = NULL;
        SDL_Color color;

        switch (graphType) {
            case 1: val = graphData->value1; color = (SDL_Color){255, 0, 0, 255}; break;
            case 2: val = graphData->value2; color = (SDL_Color){0, 255, 0, 255}; break;
            case 3: val = graphData->value3; color = (SDL_Color){0, 0, 255, 255}; break;
            case 4: val = graphData->value4; color = (SDL_Color){255, 255, 0, 255}; break;
        }

        float v1 = val[i - 1];
        float v2 = val[i];

        int y1 = y_offset + height - (int)((v1 - minY) * height / (maxY - minY));
        int y2 = y_offset + height - (int)((v2 - minY) * height / (maxY - minY));

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}
void CalculateOffset(GraphData graphData,float* yOffset, int i, float visibleYRange){
    float *valArray = NULL;
    switch (i+1){
        case 1: valArray = graphData.value1; break;
        case 2: valArray = graphData.value2; break;
        case 3: valArray = graphData.value3; break;
        case 4: valArray = graphData.value4; break;
    }
    int lastIdx = (graphData.index - 1 + MAX_POINTS) % MAX_POINTS;
    float val = valArray[lastIdx];

    if (val > yOffset[i] + visibleYRange) {
        yOffset[i] = val - visibleYRange;
    } else if (val < yOffset[i]) {
        yOffset[i] = val;
    }
}
