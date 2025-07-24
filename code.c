#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generates random float data between min and max
void generateData(float arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + ((float)rand() / RAND_MAX) * (max - min);
    }
}

// Finds the minimum value in the array and returns its index
int findMin(float arr[], int n) {
    float min = arr[0];
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// Finds the maximum value in the array and returns its index
int findMax(float arr[], int n) {
    float max = arr[0];
    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

// Simple linear search to find the index of the first value >= target
int linearSearch(float arr[], int n, float target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] >= target) {
            return i;
        }
    }
    return -1;
}

// Selection sort in ascending order
void sort(float arr[], int len) {
    for (int i = 0; i < len; i++) {
        int smallestIndex = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[smallestIndex]) {
                smallestIndex = j;
            }
        }
        // Swap
        float temp = arr[i];
        arr[i] = arr[smallestIndex];
        arr[smallestIndex] = temp;
    }
}

// Binary search to find the index of the first value >= target
int findWithBinary(float arr[], int len, float target) {
    sort(arr, len);  // Ensure array is sorted

    int low = 0, high = len - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] >= target) {
            if (mid == 0 || arr[mid - 1] < target) {
                return mid;
            }
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

int main() {
    int n = 10001;
    float temperature[n];
    float pressure[n];

    // Seed random generator
    srand(time(NULL));

    generateData(temperature, n, 21, 50);
    generateData(pressure, n, 951, 1050);

    clock_t start, end;
    double duration;

    // Example: Find minimum pressure
    start = clock();
    int minPressureIndex = findMin(pressure, n);
    end = clock();

    duration = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Minimum pressure value: %.2f at index %d\n", pressure[minPressureIndex], minPressureIndex);
    printf("Time taken to find minimum pressure = %lf seconds\n", duration);

    // Example: Find maximum temperature
    start = clock();
    int maxTempIndex = findMax(temperature, n);
    end = clock();

    duration = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Maximum temperature value: %.2f at index %d\n", temperature[maxTempIndex], maxTempIndex);
    printf("Time taken to find maximum temperature = %lf seconds\n", duration);

    return 0;
}
