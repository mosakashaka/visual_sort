#include <iostream>
#include <stdlib.h>
#include "sortbase.h"

void shuffle(int *numbers, int count);
int drawThread(void *ptr);

int main(int argc, char* argv[]) {
    int count = 100;
    int * numbers = new int[count];
    for (int i = 0; i < count ; i++) {
        numbers[i] = i + 1;
    }
    shuffle(numbers, count);

    Painter *p = Painter::GetPaitner(count);

    BubbleSort *bs = new BubbleSort(p, numbers, count);
    SDL_Thread *thread;
    int threadReturnValue;
    /* Simply create a thread */
    thread = SDL_CreateThread(drawThread, "bs", (void *)bs);
    SDL_DetachThread(thread);
    
    // Return
    int quit = 1;
    do {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            SDL_Log("Event type is %d", event.type);
            quit = 0;
        default:
            SDL_Log("Event type is %d", event.type);
            break;
        }
    } while (quit);

    SDL_WaitThread(thread, &threadReturnValue);

    return 0;
}

void shuffle(int *numbers, int count) {
    int shuffle_count = count * 10;
    int temp = 0;
    for (int i = 0; i < shuffle_count; i++) {
        int index1 = i % count;
        int index2 = rand() % count;
        temp = numbers[index1];
        numbers[index1] = numbers[index2];
        numbers[index2] = temp;
    }
}

int drawThread(void *ptr)
{
    SortBase *bs = (SortBase*)ptr;
    bs->Sort();

    return 0;
}