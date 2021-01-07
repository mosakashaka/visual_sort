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

        virtual void sortInner() = 0;

        int compare(int index1, int index2);
        int swap(int index1, int index2);
        int compareAndSwap(int index1, int index2);

        int set(int index, int number);

        void done();

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

class QuickSort : public SortBase {
    private:
        void quick_sort(int l, int r);
    protected:
        void sortInner();
    public:
        QuickSort(Painter *painter, int* numbers, int count)
            : SortBase(painter, numbers, count, "Quick Sort"){};
};

class InsertionSort : public SortBase {
    protected:
        void sortInner();
    public:
        InsertionSort(Painter *painter, int* numbers, int count)
            : SortBase(painter, numbers, count, "Insertion Sort"){};
};

class ShellSort : public SortBase {
    protected:
        void sortInner();
    public:
        ShellSort(Painter *painter, int* numbers, int count)
            : SortBase(painter, numbers, count, "Shell Sort"){};
};

class MergeSort : public SortBase {
    protected:
        void sortInner();
    public:
        MergeSort(Painter *painter, int* numbers, int count)
            : SortBase(painter, numbers, count, "Merge Sort"){};
};

class HeapSort : public SortBase {
    private:
        void adjust_node(int index, int end);
    protected:
        void sortInner();
    public:
        HeapSort(Painter *painter, int* numbers, int count)
            : SortBase(painter, numbers, count, "Heap Sort"){};
};

class CountSort : public SortBase {
    private:
        void adjust_node(int index, int end);
    protected:
        void sortInner();
    public:
        CountSort(Painter *painter, int* numbers, int count)
            : SortBase(painter, numbers, count, "Counting Sort"){};
};

#endif