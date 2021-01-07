#include "sortbase.h"

void CountSort::sortInner() {
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

    int * count_arr = new int[max - min + 1];
    memset(count_arr, 0, (max - min + 1) * sizeof(int));
    for (int i = 0; i < count; i++) {
        //draw
        compare(i,i);

        count_arr[numbers[i] - min]++;
    }

    int index = 0;
    for (int i = 0;i <= max - min; i++) {
        while (count_arr[i] > 0) {
            set(index++, i + min);
            count_arr[i] -= 1;
        }
    }

    delete [] count_arr;
}