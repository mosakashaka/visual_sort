#include <iostream>
#include <stdlib.h>
#include <map>
#include "sortbase.h"

void shuffle(int *numbers, int count);
int drawThread(void *ptr);
int* getUserSelection(std::map<int, void*> *sortMap, Painter *p, int* selectionCount);

const char * hint[] = {
    "0 - All",
    "1 - Bubble Sort",
    "2 - Selection Sort",
    "3 - Quick Sort",
    "4 - Insertion Sort",
    "5 - Shell Sort"
};

int main(int argc, char* argv[]) {
    //init 
    int count = 100;
    int * numbers = new int[count];
    for (int i = 0; i < count ; i++) {
        numbers[i] = i + 1;
    }
    shuffle(numbers, count);

    Painter *p = Painter::GetPaitner(count);

    std::map<int, void*> sortMap;
    sortMap[1] = new BubbleSort(p, numbers, count);
    sortMap[2] = new SelectionSort(p, numbers, count);
    sortMap[3] = new QuickSort(p, numbers, count);
    sortMap[4] = new InsertionSort(p, numbers, count);
    sortMap[5] = new ShellSort(p, numbers, count);

    int selectionCount = 0;
    int* selection = getUserSelection(&sortMap, p, &selectionCount);
    if (!selectionCount || !selection) {
        return 0;
    }

    SDL_Thread *thread;
    int threadReturnValue;
    std::map<std::string, void*>::iterator iter;
  
    for(int i = 0; i < selectionCount; i++)  {
        thread = SDL_CreateThread(drawThread, ((SortBase *)sortMap[selection[i]])->GetName(), sortMap[selection[i]]);
        

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
    if (selection) {
        delete [] selection;
        selection = 0;
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

int* getUserSelection(std::map<int, void*> *sortMap, Painter *p, int* selectionCount) {
    //paint hints
    p->Clear();
    p->PaintText(hint, sizeof(hint)/sizeof(char*));
    
    SDL_Event event;
    int quit = 0;
    int hasKey = 0;
    int* keys = 0;
    while (!quit && !hasKey) {
        SDL_WaitEvent(&event);
        SDL_Log("Event type is %d", event.type);
        switch (event.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYUP: 
            {
                int number = event.key.keysym.sym - '0';
                if (number == 0) {
                    //user choose all
                    keys = new int[sortMap->size()];
                    int i = 0;
                    for (std::map<int, void*>::iterator it = sortMap->begin(); 
                        it != sortMap->end(); 
                        it++,i++) {
                            keys[i] = it->first;
                    }
                    *selectionCount = i;
                    hasKey = 1;
                    break;
                } else if (number > 0) {
                    if (sortMap->find(number) != sortMap->end()) {
                        keys = new int[1];
                        keys[0] = number;
                        *selectionCount = 1;
                        hasKey = 1;
                        break;
                    }
                }
            }
                break;
            default:
                break;
        }
    }

    return keys;
}

int drawThread(void *ptr)
{
    SortBase *bs = (SortBase*)ptr;
    bs->Sort();

    return 0;
}