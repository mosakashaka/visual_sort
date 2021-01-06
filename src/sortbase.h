#ifndef SORT_BASE_H
#define SORT_BASE_H 1

#include "painter.h"

class SortBase {
    private:
        Painter *painter;
        PainterBar bars[2];
        int swap_count = 0;
        int compare_count = 0;
    
    protected:
        int count = 0;
        int *numbers;

        int compare(int index1, int index2);
        int swap(int index1, int index2);
        int compareAndSwap(int index1, int index2);

        SortBase(Painter *painter, int* numbers, int count);
        ~SortBase();

    public:
        virtual void Sort() = 0;
};

class BubbleSort : public SortBase {
    public:
        void Sort();
        BubbleSort(Painter *painter, int* numbers, int count)
            : SortBase(painter, numbers, count){};
};

#endif