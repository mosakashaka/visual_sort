#include "sortbase.h"
#define SDL_DRAW_WAIT_DELAY_MS 20

SortBase::SortBase(Painter *painter, int* numbers, int count){
    this->numbers = new int[count];
    this->count = count;
    PainterBar *initialBars = new PainterBar[count];
    for (int i = 0; i < count; i++) {
        this->numbers[i] = numbers[i];
        initialBars[i].barMode = PainterBarMode::NORMAL;
        initialBars[i].height = numbers[i];
        initialBars[i].index = i;
        initialBars[i].refresh = 0;
    }
    this->painter = painter;
    
    //draw initial state
    painter->PaintBars(initialBars, count);
    delete [] initialBars;
}

SortBase::~SortBase() {
    if (numbers) {
        delete []numbers;
        numbers = 0;
    }
}

int SortBase::compare(int index1, int index2) {
    bars[0].barMode = PainterBarMode::HIGHLIGHT;
    bars[0].height = numbers[index1];
    bars[0].index = index1;
    bars[0].refresh = 0;
    bars[1].barMode = PainterBarMode::HIGHLIGHT;
    bars[1].height = numbers[index2];
    bars[1].index = index2;
    bars[1].refresh = 0;
    painter->PaintBars(bars, 2);
    //SDL_Delay(SDL_DRAW_WAIT_DELAY_MS);

    int diff = numbers[index1] - numbers[index2];
    bars[0].barMode = PainterBarMode::NORMAL;
    bars[1].barMode = PainterBarMode::NORMAL;
    painter->PaintBars(bars, 2);

    compare_count++;
    return diff;
}
int SortBase::swap(int index1, int index2) {

    //swap
    int diff = numbers[index1] - numbers[index2];
    numbers[index1] -= diff;
    numbers[index2] += diff;
    bars[0].barMode = PainterBarMode::OPERATE;
    bars[0].height = numbers[index1];
    bars[0].index = index1;
    bars[0].refresh = 1;
    bars[1].barMode = PainterBarMode::OPERATE;
    bars[1].height = numbers[index2];
    bars[1].index = index2;
    bars[1].refresh = 1;
    painter->PaintBars(bars, 2);
    //SDL_Delay(SDL_DRAW_WAIT_DELAY_MS);

    //un-highlight
    bars[0].barMode = PainterBarMode::NORMAL;
    bars[0].height = numbers[index1];
    bars[0].index = index1;
    bars[0].refresh = 0;
    bars[1].barMode = PainterBarMode::NORMAL;
    bars[1].height = numbers[index2];
    bars[1].index = index2;
    bars[1].refresh = 0;
    painter->PaintBars(bars, 2);

    swap_count++;
    return diff;

}

int SortBase::compareAndSwap(int index1, int index2) {

    //compare
    bars[0].barMode = PainterBarMode::HIGHLIGHT;
    bars[0].height = numbers[index1];
    bars[0].index = index1;
    bars[0].refresh = 0;
    bars[1].barMode = PainterBarMode::HIGHLIGHT;
    bars[1].height = numbers[index2];
    bars[1].index = index2;
    bars[1].refresh = 0;
    painter->PaintBars(bars, 2);
    //SDL_Delay(SDL_DRAW_WAIT_DELAY_MS);

    //swap
    int diff = numbers[index1] - numbers[index2];
    if (diff > 0) {
        numbers[index1] -= diff;
        numbers[index2] += diff;
        bars[0].barMode = PainterBarMode::OPERATE;
        bars[0].height = numbers[index1];
        bars[0].index = index1;
        bars[0].refresh = 1;
        bars[1].barMode = PainterBarMode::OPERATE;
        bars[1].height = numbers[index2];
        bars[1].index = index2;
        bars[1].refresh = 1;
        painter->PaintBars(bars, 2);
        //SDL_Delay(SDL_DRAW_WAIT_DELAY_MS);
        swap_count++;
    }

    //un-highlight
    bars[0].barMode = PainterBarMode::NORMAL;
    bars[0].height = numbers[index1];
    bars[0].index = index1;
    bars[0].refresh = 0;
    bars[1].barMode = PainterBarMode::NORMAL;
    bars[1].height = numbers[index2];
    bars[1].index = index2;
    bars[1].refresh = 0;
    painter->PaintBars(bars, 2);

    compare_count++;
    return diff;

}