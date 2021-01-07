
#ifndef PAINTER_H
#define PAITNER_H 1

extern "C" {
#include "SDL.h"
#include "SDL_ttf.h"
}

typedef enum PainterBarMode {
    NORMAL,
    HIGHLIGHT,
    OPERATE
}PainterBarMode;

typedef struct PainterBar {    
    int index;
    int height;
    int barMode;
    int refresh;
}PainterBar;

class Painter {
    private:
        static int _systemInit;
        static Painter *instance;
        SDL_Window *win = 0;
        SDL_Renderer *ren = 0;

        TTF_Font *font;

        int bars =  -1;
        int bar_width = -1;
        int bar_height_step = -1;
        int w = 0;
        int h = 0;

        const int MARGIN_LEFT = 30;
        const int MARGIN_RIGHT = 30;
        const int MARGIN_TOP = 50;

        int SCREEN_WIDTH_MAX;
        int SCREEN_HEIGHT_MAX;

        Painter();
        int init(int barCount);
        int paintBar(PainterBar *bar);
        int clearRect(int x, int y, int w, int h);

    public:
        static Painter* GetPaitner(int barCount);
        ~Painter();
        int PaintBars(PainterBar *bars, int count);
        int PaintBarsNoFlush(PainterBar *bars, int count);
        int Clear();
        int ClearTitleArea();
        int Flush();
        int PaintText(const char** lines, int count);

};


#endif