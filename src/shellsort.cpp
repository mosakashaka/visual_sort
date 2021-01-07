#include "sortbase.h"

void ShellSort::sortInner() {
    int gap;
    for (gap = count >> 1; gap > 0; gap >>=1) {
        for (int i = gap; i < count; i++) {
            for (int j = i-gap; j >=0; j-=gap) {
                if (compareAndSwap(j, j+gap) <= 0) {
                    break;
                }
            }
        }
    }
}