#include "sortbase.h"

void InsertionSort::sortInner() {
    for (int i = 1; i < count; i++) {
        for (int j = i-1; j >=0; j--) {
            if (compareAndSwap(j, j+1) <= 0) {
                break;
            }
        }
    }
}