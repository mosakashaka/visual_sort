#include <iostream>
#include <stdlib.h>
#include <map>
#include "sortbase.h"

void shuffle(int *numbers, int count);
int drawThread(void *ptr);

int main(int argc, char* argv[]) {
    //init 
    int count = 100;
    int * numbers = new int[count];
    for (int i = 0; i < count ; i++) {
        numbers[i] = i + 1;
    }
    shuffle(numbers, count);

    Painter *p = Painter::GetPaitner(count);

    std::map<std::string, void*> sortMap;
    sortMap["selection"] = new SelectionSort(p, numbers, count);
    sortMap["bubble"] = new BubbleSort(p, numbers, count);
    SDL_Thread *thread;
    int threadReturnValue;
    std::map<std::string, void*>::iterator iter;
  
    for(iter = sortMap.begin(); iter != sortMap.end(); iter++)  {
        thread = SDL_CreateThread(drawThread, iter->first.data(), iter->second);
        

        SDL_Event event;
        int quit = 0;
        int cont = 0;
        while (!quit && !cont) {
            SDL_WaitEvent(&event);
            SDL_Log("Event type is %d", event.type);
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYUP:
                    //if it's enter key
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        cont = 1;
                    }
                    break;
                default:
                    break;
            }
        }
        if (quit) {
            SDL_DetachThread(thread);
            break;
        }
        SDL_WaitThread(thread, &threadReturnValue);
    }

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
    bs->Init();
    bs->Sort();

    return 0;
}