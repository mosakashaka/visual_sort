#include "sortbase.h"

void QuickSort::sortInner() {
    quick_sort(0, count - 1);
}

void QuickSort::quick_sort(int l, int r) {
    if (l >= r) {
        return;
    }
    int i = l, j = r;
    while (i < j) {
        while ((compare(i,j) <= 0) && (i < j)) {
            j--;
        }
        if (i < j) {
            swap(i++,j);
        }
        while ((compare(i,j) <= 0) && (i < j)) {
            i++;
        }
        if (i < j) {
            swap(i,j--);
        }
    }
    quick_sort(l, i - 1);
    quick_sort(i + 1, r);
}