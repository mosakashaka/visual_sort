#ifndef SORT_BASE_H
#define SORT_BASE_H 1

#include "painter.h"

class SortBase {
    private:
        Painter *painter;
        PainterBar bars[2];
        int swap_count = 0;
        int compare_count = 0;
        const char* name;
    
        void init();

    protected:
        int count = 0;
        int *numbers;

        int compare(int index1, int index2);
        int swap(int index1, int index2);
        int compareAndSwap(int index1, int index2);
        void done();
        virtual void sortInner() = 0;

        SortBase(Painter *painter, int* numbers, int count, const char* name);
        ~SortBase();

    public:
        void Sort();
        const char* GetName() { return name; }
};

class BubbleSort : public SortBase {
    protected:
        void sortInner();
    public:
        BubbleSort(Painter *painter, int* numbers, int count)
            : SortBase(painter, numbers, count, "Bubble Sort"){};
};

class SelectionSort : public SortBase {
    protected:
        void sortInner();
    public:
        SelectionSort(Painter *painter, int* numbers, int count)
            : SortBase(painter, numbers, count, "Selection Sort"){};
};

#endif