#include "sortbase.h"

void BubbleSort::sortInner() {
    for (int i = count - 1; i > 0; i--) {
        int changed = 0;
        for (int j = 0; j < i; j++) {
            if (compareAndSwap(j, j+1) > 0) {
                changed = 1;
            }
        }
        if (!changed) {
            break;
        }
    }
}