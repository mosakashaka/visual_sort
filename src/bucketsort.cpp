#include "sortbase.h"
#include <vector>

#define BUCKET_STEP 5

void BucketSort::sortInner() {
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

    int bucket_count = (max - min + 1) / BUCKET_STEP;
    std::vector<int> *buckets = new std::vector<int>[bucket_count];
    for (int i = 0; i < count; i++) {
        //draw
        compare(i,i);

        buckets[(numbers[i] - min)/BUCKET_STEP].push_back(numbers[i]);
    }

    int index = 0;
    for (int i = 0; i < bucket_count; i++) {
        //draw buckets status
        int bucket_start = index;
        for (std::vector<int>::iterator it = buckets[i].begin();
            it != buckets[i].end(); 
            it++) {
            set(index++, *it);
        }
        //sort bucket
        if (index > bucket_start + 1) {
            sort_range(bucket_start, index);
        }
    }

    delete [] buckets;
}

void BucketSort::sort_range(int begin, int end) {
    //just do bubble
    for (int i = end - 1; i > 0; i--) {
        for (int j = begin; j < i ; j++) {
            compareAndSwap(j, j+1);
        }
    }
}