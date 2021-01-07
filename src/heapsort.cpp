#include "sortbase.h"

void HeapSort::sortInner() {
    for (int i = count/2 - 1; i >= 0; i--) {
        adjust_node(i, count);
    }
    for (int len = count; len > 1; len--) {
        //swap head and tail
        swap(0, len - 1);
        adjust_node(0, len - 1);
    }
}

void HeapSort::adjust_node(int index, int end) {
    int parent = index;
    while (parent * 2 + 1 < end) {
        int left = parent * 2 + 1;
        int right = parent * 2 + 2;
        int bigger = left;
        if ((right < end) && (compare(left, right) < 0)) {
            bigger = right;
        }
        if (compareAndSwap(bigger, parent) > 0) {
            //continue deal with children
            parent = bigger;
        } else {
            break;
        }
    }
}