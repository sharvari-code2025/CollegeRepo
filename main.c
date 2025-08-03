#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>

#define MAX 100
#define PI 3.14159265358979323846

// Structure for a Point (freckle)
typedef struct {
    float x, y;
} Point;

// Structure for a City with latitude and longitude
typedef struct {
    char name[50];
    float lat, lon;
} City;

// Calculate Euclidean distance (Part A)
float euclideanDistance(Point a, Point b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

// Calculate Haversine distance in km (Part B)
float calculateDistance(float lat1, float lon1, float lat2, float lon2) {
    float dLat = (lat2 - lat1) * PI / 180.0;
    float dLon = (lon2 - lon1) * PI / 180.0;
    lat1 = lat1 * PI / 180.0;
    lat2 = lat2 * PI / 180.0;
    float a = sin(dLat/2) * sin(dLat/2) +
                sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return 6371.0 * c;  // Earth radius in km
}

// Prim's MST (array-based)
void primMST(int n, float graph[MAX][MAX], char labels[][50]) {
    int parent[MAX];
    float key[MAX];
    bool mstSet[MAX];

    for(int i = 0; i < n; i++) {
        key[i] = FLT_MAX;
        mstSet[i] = false;
    }
    key[0] = 0;
    parent[0] = -1;

    for(int count = 0; count < n-1; count++) {
        float min = FLT_MAX;
        int u = -1;

        for(int v = 0; v < n; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v]; u = v;
            }
        }

        mstSet[u] = true;

        for(int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    float total = 0.0;
    printf("\nMinimum Spanning Tree Edges:\n");
    for(int i=1; i<n; i++) {
        printf("%s - %s : %.2f\n", labels[parent[i]], labels[i], graph[i][parent[i]]);
        total += graph[i][parent[i]];
    }
    printf("Total Cost/Ink: %.2f\n", total);
}

// Part A: MST for freckles
void problemA() {
    printf("Part A: MST for Freckles (Points)\n");

    int n = 4;
    Point freckles[] = {{0,0}, {2,3}, {5,2}, {6,6}};
    char labels[4][50] = {"F1", "F2", "F3", "F4"};

    printf("Input Coordinates:\n");
    for (int i=0; i<n; i++) {
        printf("%s: (%.1f, %.1f)\n", labels[i], freckles[i].x, freckles[i].y);
    }

    float graph[MAX][MAX] = {0};
    // Build distance matrix
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i != j){
                graph[i][j] = euclideanDistance(freckles[i], freckles[j]);
            } else {
                graph[i][j] = 0;
            }
        }
    }

    primMST(n, graph, labels);
}

// Part B: MST for cities
void problemB() {
    printf("\nPart B: MST for Cities\n");

    int n = 4;
    City cities[] = {
        {"Nagpur", 21.1466, 79.0888},
        {"Akola", 20.7096, 77.0085},
        {"Amravati", 20.9374, 77.7796},
        {"Chandrapur", 19.9615, 79.2961}
    };
    char labels[4][50];

    printf("Cities:\n");
    for(int i=0; i<n; i++) {
        printf("%s (%.4f, %.4f)\n", cities[i].name, cities[i].lat, cities[i].lon);
        snprintf(labels[i], 50, "%s", cities[i].name);
    }

    float graph[MAX][MAX] = {0};

    // Distance matrix using Haversine formula
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(i != j) {
                graph[i][j] = calculateDistance(cities[i].lat, cities[i].lon, cities[j].lat, cities[j].lon);
            } else {
                graph[i][j] = 0;
            }
        }
    }

    primMST(n, graph, labels);
}

int main() {
    // Run Part A
    problemA();

    // Run Part B
    problemB();

    return 0;
}

