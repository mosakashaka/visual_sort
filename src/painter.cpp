// SDL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "painter.h"
#include <iostream>

#define FONT_FILE "arial.ttf"
#define FONT_SIZE 16

static const unsigned char BG_R = 255;
static const unsigned char BG_G = 255;
static const unsigned char BG_B = 255;
static const unsigned char BG_A = SDL_ALPHA_OPAQUE;

static const unsigned char NORMAL_R = 0;
static const unsigned char NORMAL_G = 125;
static const unsigned char NORMAL_B = 200;
static const unsigned char NORMAL_A = SDL_ALPHA_OPAQUE;

static const unsigned char HIGHLIGHT_R = 200;
static const unsigned char HIGHLIGHT_G = 0;
static const unsigned char HIGHLIGHT_B = 125;
static const unsigned char HIGHLIGHT_A = SDL_ALPHA_OPAQUE;

static const unsigned char OPERATE_R = 125;
static const unsigned char OPERATE_G = 200;
static const unsigned char OPERATE_B = 0;
static const unsigned char OPERATE_A = SDL_ALPHA_OPAQUE;

int Painter::_systemInit = 0;
Painter * Painter::instance = 0;

Painter::Painter() {

};

Painter::~Painter() {
    if (ren) {
        SDL_DestroyRenderer(ren);
        ren = 0;
    }
    if (win) {
        SDL_DestroyWindow(win);
        win = 0;
    }
    SDL_Quit();


    if (font) {
        TTF_CloseFont(font);
        font = 0;
    }
    TTF_Quit();
}

Painter * Painter::GetPaitner(int barCount) {
    if (!instance) {
        instance = new Painter();
    }
    instance->init(barCount);

    return instance;
}

int Painter::init(int barCount) {
            if (!_systemInit) {
                if (SDL_Init(SDL_INIT_VIDEO)) {
                    exit(101);
                }
                if(TTF_Init()==-1) {
                    exit(201);
                }
                font=TTF_OpenFont(FONT_FILE, FONT_SIZE);
                if(!font) {
                    exit(202);
                }
                _systemInit = 1;
            }

            if (barCount <= 1) {
                throw "Invalid bar cound" + barCount;
            }
            if (barCount != bars) {
                if (ren) {
                    SDL_DestroyRenderer(ren);
                    ren = 0;
                }
                if (win) {
                    SDL_DestroyWindow(win);
                    win = 0;
                }
                bars = barCount;

                //caclulate actual window size
                SDL_Rect rect;
                SDL_GetDisplayBounds(0, &rect);
                SCREEN_WIDTH_MAX = rect.w - 200;
                SCREEN_HEIGHT_MAX = rect.h - 100;

                int wStep = 1;
                while ((wStep +1)*bars + MARGIN_LEFT + MARGIN_RIGHT <= SCREEN_WIDTH_MAX) {
                    wStep++;
                }
                bar_width = wStep;
                w = bars * bar_width + MARGIN_LEFT + MARGIN_RIGHT;

                int hStep = 1;
                while ((hStep +1)*bars + MARGIN_TOP <= SCREEN_HEIGHT_MAX) {
                    hStep++;
                }
                bar_height_step = hStep;
                h = bar_height_step * bars + MARGIN_TOP;

                win = SDL_CreateWindow("Sorting", 
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                w, h, SDL_WINDOW_SHOWN);
                std::cout << "windows size:" << w << "*" << h << std::endl;

                if (win == nullptr) {
                    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
                    throw "SDL_CreateWindow Error";
                    return 1;
                }

                ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                if (ren == nullptr) {
                    SDL_DestroyWindow(win);
                    std::cout << "SDL_CreateRender Error: " << SDL_GetError() << std::endl;
                    throw "SDL_CreateRender Error";
                    SDL_Quit();
                    return 1;
                }
            }

            clearRect(0, 0, w, h);
            SDL_RenderPresent(ren);

            return 0;
};


int Painter::clearRect(int x, int y, int w, int h) {
    if (!ren) {
        std::cout << "SDL no render" << std::endl;
        throw "SDL no render";
    }
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_SetRenderDrawColor(ren,   
                         BG_R,     
                         BG_G,     
                         BG_B,     
                         BG_A);     
    SDL_RenderFillRects(ren, &rect, 1);
    return 0;
}

int Painter::Clear() {
    clearRect(0, 0, w, h);
    return 0;
}

int Painter::ClearTitleArea() {
    clearRect(0, 0, w, MARGIN_TOP);
    SDL_RenderPresent(ren);
    return 0;
}

int Painter::Flush() {
    SDL_RenderPresent(ren);
    return 0;
}

int Painter::PaintBars(PainterBar *bars, int count) {
    PaintBarsNoFlush(bars, count);
    SDL_RenderPresent(ren);
    return 0;
}

int Painter::PaintBarsNoFlush(PainterBar *bars, int count) {
    int i = 0;
    while (i < count) {
        paintBar(bars + i);
        i++;
    }
    return 0;
}

int Painter::paintBar(PainterBar *bar) {
    //calculate bar offset
    if (bar->index >= bars) {
        std::cout << "Invalid bar index:" << bar->index << std::endl;
        throw "Invalid bar index";
    }
    if ((bar->height * bar_height_step) > (h - MARGIN_TOP)) {
        std::cout << "Invalid bar height:" << bar->height << std::endl;
        throw "Invalid bar height";
    }
    int barX = MARGIN_LEFT + bar_width * bar->index;
    int barW = bar_width;
    int barH = bar->height * bar_height_step;
    int barY = h - barH;

    if (bar->refresh) {
        SDL_SetRenderDrawColor(ren,   
                        BG_R,     
                        BG_G,     
                        BG_B,     
                        BG_A);
                         
        SDL_Rect rect;
        rect.x = barX;
        rect.y = MARGIN_TOP;
        rect.w = barW;
        rect.h = h - barH - MARGIN_TOP;    
        SDL_RenderFillRects(ren, &rect, 1);
    }

    unsigned char r,g,b,a;
    switch (bar->barMode) {
        case PainterBarMode::HIGHLIGHT:
            r = HIGHLIGHT_R;
            g = HIGHLIGHT_G;
            b = HIGHLIGHT_B;
            a = HIGHLIGHT_A;
            break;
        case PainterBarMode::OPERATE:
            r = OPERATE_R;
            g = OPERATE_G;
            b = OPERATE_B;
            a = OPERATE_A;
            break;
        case PainterBarMode::NORMAL:
            r = NORMAL_R;
            g = NORMAL_G;
            b = NORMAL_B;
            a = NORMAL_A;
            //fallthrough
        default:
            break;
    }
    SDL_SetRenderDrawColor(ren,   
                         r,     
                         g,     
                         b,     
                         a); 
                         
    SDL_Rect rect;
    rect.x = barX;
    rect.y = barY;
    rect.w = barW;
    rect.h = barH;    
    return SDL_RenderFillRects(ren, &rect, 1);
}

int Painter::PaintText(const char** lines, int count) {
    SDL_Color fontColor = {30, 30, 30};
    int fontW, fontH;
    for (int i = 0; i < count; i++) {
        TTF_SizeUTF8(font, lines[i], &fontW, &fontH);
        SDL_Surface * surface =  TTF_RenderText_Solid(font, lines[i], fontColor);
        SDL_Texture* message = SDL_CreateTextureFromSurface(ren, surface); 
        SDL_Rect messageRect; //create a rect
        messageRect.x = MARGIN_LEFT;  //controls the rect's x coordinate 
        messageRect.y = FONT_SIZE * i + 10; // controls the rect's y coordinte
        messageRect.w = fontW; // controls the width of the rect
        messageRect.h = fontH; // controls the height of the rect

        SDL_RenderCopy(ren, message, NULL, &messageRect); 

        //Don't forget to free your surface and texture
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(message);
    }
    SDL_RenderPresent(ren);
    return 0;
}