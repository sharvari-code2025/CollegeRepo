
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate random float data
void generateData(float arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + ((float)rand() / RAND_MAX) * (max - min);
    }
}

// Linear: Find min value
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

// Linear: Find max value
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

// Quadratic: Selection sort
void sort(float arr[], int len) {
    for (int i = 0; i < len; i++) {
        int smallestIndex = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[smallestIndex]) {
                smallestIndex = j;
            }
        }
        float temp = arr[i];
        arr[i] = arr[smallestIndex];
        arr[smallestIndex] = temp;
    }
}

int main() {
    int sizes[] = {100, 10000, 1000000}; // n = 10^2, 10^4, 10^6
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(time(NULL)); // seed random generator

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        float *temperature = (float *)malloc(n * sizeof(float));
        float *pressure = (float *)malloc(n * sizeof(float));

        printf("\n===============================\n");
        printf("For n = %d\n", n);
        printf("===============================\n");

        // --- Generate Data ---
        generateData(temperature, n, 21, 50);
        generateData(pressure, n, 951, 1050);

        // === Task A: Linear Search (Find Min and Max) ===

        clock_t start, end;
        double duration;

        // Temperature (Linear)
        start = clock();
        int tempMinIdx = findMin(temperature, n);
        end = clock();
        duration = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Task-A Linear | Temperature | Time: %lf seconds\n", duration);

        start = clock();
        int tempMaxIdx = findMax(temperature, n);
        end = clock();
        duration = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Task-A Linear | Temperature (Max) | Time: %lf seconds\n", duration);

        // Pressure (Linear)
        start = clock();
        int pressMinIdx = findMin(pressure, n);
        end = clock();
        duration = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Task-A Linear | Pressure | Time: %lf seconds\n", duration);

        start = clock();
        int pressMaxIdx = findMax(pressure, n);
        end = clock();
        duration = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Task-A Linear | Pressure (Max) | Time: %lf seconds\n", duration);

        // === Task B: Quadratic (Sort) ===

        // Temperature
        start = clock();
        sort(temperature, n);
        end = clock();
        duration = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Task-B Quadratic | Temperature (Sort) | Time: %lf seconds\n", duration);

        // Pressure
        start = clock();
        sort(pressure, n);
        end = clock();
        duration = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Task-B Quadratic | Pressure (Sort) | Time: %lf seconds\n", duration);

        // Clean up
        free(temperature);
        free(pressure);
    }

    return 0;
}
