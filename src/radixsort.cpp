#include "sortbase.h"
#include <vector>

void RadixSort::sortInner() {    
    int min = -1, max = -1;
    for (int i = 0; i < count; i++) {
        //draw
        compare(i, i);
        if (-1 == min) {
            min = numbers[i];
        } else if (numbers[i] < min) {
            min = numbers[i];
        }

        if (-1 == max) {
            max = numbers[i];
        } else if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    std::vector<int> buffer[10];
    int modMax = 1;
    int maxTemp = max;
    while (maxTemp > 0) {
        maxTemp /= 10;
        modMax *= 10;
    }
    for (int radix = 10; radix <= modMax; radix *= 10) {
        //sort into buffer based on radix
        int div = radix / 10;
        for (int i = 0; i < count; i++) {
            //draw
            compare(i, i);
            int bufferIndex = (numbers[i] % radix) / div;
            buffer[bufferIndex].push_back(numbers[i]);
        }

        //copy to original array
        int index = 0;
        for (int i = 0; i < sizeof(buffer)/sizeof(buffer[0]); i++) {
            for (std::vector<int>::iterator it = buffer[i].begin();
            it != buffer[i].end();
            it++) {
                set(index++, *it);
            }
            //clear buffer
            buffer[i].clear();
        }

    }
}