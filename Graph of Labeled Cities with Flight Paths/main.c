#include "homework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Graph* graph = createGraph();
    PathList* paths = createPathList(10);

    char** cities = (char**)malloc(4 * sizeof(char*));
    for (int i = 0; i < 4; i++) {
        cities[i] = (char*)malloc(MAX_CHARACTERS * sizeof(char));
    }
    strcpy(cities[0], "Sofia");
    strcpy(cities[1], "Paris");
    strcpy(cities[2], "London");
    strcpy(cities[3], "New York");

    for(int i = 0; i < 4; i++) {
        addCity(graph, cities[i]);
    }
    for(int i = 0; i < 4; i++) {
        free(cities[i]);
    }
    free(cities);
    
    addEdgeToGraph(graph, "Sofia", "Paris", 2);
    addEdgeToGraph(graph, "Paris", "London", 4);
    addEdgeToGraph(graph, "London", "New York", 8);
    addEdgeToGraph(graph, "New York", "Sofia", 10);
    addEdgeToGraph(graph, "Sofia", "London", 5);
    addEdgeToGraph(graph, "Paris", "New York", 6);
    addEdgeToGraph(graph, "London", "Paris", 3);
    addEdgeToGraph(graph, "New York", "London", 7);
    addEdgeToGraph(graph, "Sofia", "New York", 20);

    printf("Enter start destination city: ");
    char startCity[MAX_CHARACTERS];
    scanf("%s", startCity);
    printf("Enter end destination city: ");
    char endCity[MAX_CHARACTERS];
    scanf("%s", endCity);
    printf("Enter max stops: ");
    int maxStops;
    scanf("%d", &maxStops);
    printf("Enter max price: ");
    int maxPrice;
    scanf("%d", &maxPrice);

    findShortestPath(graph, startCity, endCity, paths, maxStops, maxPrice);

    printPaths(paths, graph);
    freePathList(paths);
    freeGraph(graph);
    return 0;
}