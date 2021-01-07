#include "sortbase.h"

void MergeSort::sortInner() {
    int * bak = new int[count];
    for (int seg = 1; seg < count; seg += seg) {
        for (int start = 0; start < count; start += seg * 2) {
            int low = start, 
                mid = (start + seg) < count ? (start + seg) : count,
                high = (start + seg * 2) < count ? (start + seg * 2) : count;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;

            int i = start;
            while ((start1 < end1) && (start2 < end2)) {
                if (compare(start1, start2) <= 0) {
                    bak[i++] = numbers[start1++];
                } else {
                    bak[i++] = numbers[start2++];
                }
            }
            while (start1 < end1) {
                bak[i++] = numbers[start1++];
            }
            while (start2 < end2) {
                bak[i++] = numbers[start2++];
            }

            //paint
            for (int j = start; j < i; j++) {
                set(j, bak[j]);
            }
        }
    }
    delete [] bak;
}