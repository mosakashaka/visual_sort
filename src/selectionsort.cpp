#include "sortbase.h"

void SelectionSort::Sort() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i+1; j < count ; j++) {
            compareAndSwap(i,j);
        }
    }
}