#include "sortbase.h"

void HeapSort::sortInner() {
    for (int len = count; len > 1; len--) {
        for (int i = len/2 - 1; i >= 0; i--) {
            //
            compareAndSwap(2 * i + 1, i);
            //if only one child
            if (2 * i + 2 < len) {
                compareAndSwap(2 * i + 2, i);
            }
        }
        //swap head and tail
        swap(0, len - 1);
    }
}