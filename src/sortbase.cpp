#include "sortbase.h"
#include <stdio.h>
#define SDL_DRAW_WAIT_DELAY_MS 20

SortBase::SortBase(Painter *painter, int* numbers, int count, const char* name){
    this->numbers = new int[count];
    this->count = count;
    for (int i = 0; i < count; i++) {
        this->numbers[i] = numbers[i];
    }
    this->painter = painter;
    this->name = name;
}

void SortBase::init() {
    painter->Clear();
    PainterBar *initialBars = new PainterBar[count];
    for (int i = 0; i < count; i++) {
        initialBars[i].barMode = PainterBarMode::NORMAL;
        initialBars[i].height = numbers[i];
        initialBars[i].index = i;
        initialBars[i].refresh = 0;
    }
    
    //draw initial state
    painter->PaintBars(initialBars, count);
    delete [] initialBars;

    //drawe title
    painter->PaintText(&name, 1);
}

void SortBase::Sort() {
    init();
    sortInner();
    done();
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
    painter->PaintBarsNoFlush(bars, 2);

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
    painter->PaintBarsNoFlush(bars, 2);

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
    painter->PaintBarsNoFlush(bars, 2);

    compare_count++;
    return diff;

}

int SortBase::set(int index, int number) {
    numbers[index] = number;
    
    //highlight
    bars[0].barMode = PainterBarMode::OPERATE;
    bars[0].height = number;
    bars[0].index = index;
    bars[0].refresh = 1;
    painter->PaintBars(bars, 1);
    swap_count++;

    //un-highlight
    bars[0].barMode = PainterBarMode::NORMAL;
    bars[0].height = number;
    bars[0].index = index;
    bars[0].refresh = 0;
    painter->PaintBarsNoFlush(bars, 1);

    swap_count++;
    return 0;
 
}

void SortBase::done() {
    painter->Flush();
    painter->ClearTitleArea();

    //draw result;
    char result[2][100];
    snprintf(result[0], sizeof(result[0]), "[%s]: %d comparations, %d swaps",
        name, compare_count, swap_count);
    snprintf(result[1], sizeof(result[1]), "Press Enter to continue");
    const char * ptr[2];
    ptr[0] = result[0];
    ptr[1] = result[1];
    painter->PaintText(ptr, 2);
}