#include "homework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static void memoryError() {
    printf("Memory allocation error\n");
    exit(1);
}

Edge* createEdge(int price, int index) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    if (!newEdge) {
        memoryError();
    }

    newEdge->price = price;
    newEdge->index = index;
    newEdge->next = NULL;
    return newEdge;
}
void addEdge(City* city, int price, int index) {
    Edge* newEdge = createEdge(price, index);
    newEdge->next = city->adjList;
    city->adjList = newEdge;
}

unsigned int hash(const char* key) {
    unsigned int sum = 0;
    
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }

    return sum % (MAX_CITIES + 3);
}

void addToCityMap(Graph* graph, const char* name, int index) {
    unsigned int hashIndex = hash(name);
    CityMapEntry* newEntry = (CityMapEntry*)malloc(sizeof(CityMapEntry));
    if (!newEntry) {
        memoryError();
    }

    strcpy(newEntry->name, name);
    newEntry->index = index;
    newEntry->next = graph->cityMap[hashIndex];
    graph->cityMap[hashIndex] = newEntry;
}

int getCityIndex(Graph* graph, const char* name) {
    unsigned int hashIndex = hash(name);
    CityMapEntry* entry = graph->cityMap[hashIndex];

    while (entry != NULL) {
        if (strcmp(entry->name, name) == 0) {
            return entry->index;
        }
        entry = entry->next;
    }
    return -1;
}

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        memoryError();
    }

    graph->numCities = 0;
    for (int i = 0; i < MAX_CITIES; i++) {
        graph->cities[i].adjList = NULL;
    }
    for (int i = 0; i < MAX_CITIES + 3; i++) {
        graph->cityMap[i] = NULL;
    }
    return graph;
}

PathList* createPathList(int capacity) {
    PathList* list = (PathList*)malloc(sizeof(PathList));
    if (!list) {
        memoryError();
    }

    list->paths = (Path**)malloc(capacity * sizeof(Path*));
    if (!list->paths) {
        free(list);
        memoryError();
    }

    list->count = 0;
    list->capacity = capacity;
    return list;
}

void addPathToList(PathList* list, Path* path) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->paths = (Path**)realloc(list->paths, list->capacity * sizeof(Path*));
        if (!list->paths) {
            memoryError();
        }
    }
    list->paths[list->count] = path;
    list->count++;
}

void addCity(Graph* graph, const char* name) {
    if (graph->numCities >= MAX_CITIES) {
        printf("Maximum number of cities reached\n");
        return;
    }

    strcpy(graph->cities[graph->numCities].name, name);
    graph->cities[graph->numCities].adjList = NULL;
    addToCityMap(graph, name, graph->numCities);
    graph->numCities++;
}

void addCityToGraph(Graph* graph, const char* name) {
    if (getCityIndex(graph, name) != -1) {
        printf("City already exists\n");
        return;
    }
    if (graph->numCities >= MAX_CITIES) {
        printf("Maximum number of cities reached\n");
        return;
    }
    addCity(graph, name);
}

void addEdgeToGraph(Graph* graph, const char* fromCity, const char* toCity, int price) {
    int from = getCityIndex(graph, fromCity);
    if (from == -1) {
        printf("City %s not found\n", fromCity);
        return;
    }
    int to = getCityIndex(graph, toCity);
    if (to == -1) {
        printf("City %s not found\n", toCity);
        return;
    }
    addEdge(&graph->cities[from], price, to);
}

static void dfs(Graph* graph, int current, int end, int* visited, Path* currentPath, PathList* resultList, int maxStops, int maxPrice) {
    if (currentPath->totalStops > maxStops || currentPath->totalPrice > maxPrice) {
        return;
    }

    if(current == end) {
        Path* newPath = (Path*)malloc(sizeof(Path));
        if (!newPath) {
            memoryError();
        }
        newPath->length = currentPath->length;
        newPath->totalStops = currentPath->totalStops;
        newPath->totalPrice = currentPath->totalPrice;
        newPath->cities = (int*)malloc((currentPath->length + 1) * sizeof(int));
        if (!newPath->cities) {
            free(newPath);
            memoryError();
        }

        for(int i = 0; i < currentPath->length; i++) {
            newPath->cities[i] = currentPath->cities[i];
        }
        addPathToList(resultList, newPath);
        return;
    }

    visited[current] = 1;
    Edge* edge = graph->cities[current].adjList;
    while (edge != NULL) {
        if (!visited[edge->index]) {
            currentPath->cities[currentPath->length] = edge->index;
            currentPath->length++;
            currentPath->totalStops += 1;
            currentPath->totalPrice += edge->price;

            dfs(graph, edge->index, end, visited, currentPath, resultList, maxStops, maxPrice);

            currentPath->length--;
            currentPath->totalStops -= 1;
            currentPath->totalPrice -= edge->price;
        }
        edge = edge->next;
    }
    visited[current] = 0;
}

void findShortestPath(Graph* graph, const char* startCity, const char* endCity, PathList* resultPaths, int maxStops, int maxPrice) {
    int start = getCityIndex(graph, startCity);
    if (start == -1) {
        printf("City %s not found\n", startCity);
        return;
    }
    int end = getCityIndex(graph, endCity);
    if (end == -1) {
        printf("City %s not found\n", endCity);
        return;
    }

    int* visited = (int*)calloc(graph->numCities, sizeof(int));
    if (!visited) {
        memoryError();
    }

    Path* currentPath = (Path*)malloc(sizeof(Path));
    if (!currentPath) {
        free(visited);
        memoryError();
    }
    
    currentPath->cities = (int*)malloc(graph->numCities * sizeof(int));
    if (!currentPath->cities) {
        free(currentPath);
        free(visited);
        memoryError();
    }

    currentPath->length = 1;
    currentPath->totalStops = 0;
    currentPath->totalPrice = 0;
    currentPath->cities[0] = start;

    dfs(graph, start, end, visited, currentPath, resultPaths, maxStops, maxPrice);

    free(currentPath->cities);
    free(currentPath);
    free(visited);
}

static int comparePaths(const void* a, const void* b) {
    Path* pathA = *(Path**)a;
    Path* pathB = *(Path**)b;

    if (pathA->totalPrice != pathB->totalPrice) {
        return pathA->totalPrice - pathB->totalPrice;
    }
    return pathA->length - pathB->length;
}

void printPaths(const PathList* list, Graph* graph) {
    if (list->count == 0) {
        printf("No paths found\n");
        return;
    }

    qsort(list->paths, list->count, sizeof(Path*), comparePaths);

    for (int i = 0; i < list->count; i++) {
        Path* path = list->paths[i];
        printf("Path %d: ", i + 1);
        for (int j = 0; j < path->length; j++) {
            int current = path->cities[j];
            printf("%s", graph->cities[current].name);
            if (j < path->length - 1) {
                int next = path->cities[j + 1];
                Edge* edge = graph->cities[current].adjList;
                while (edge != NULL && edge->index != next) {
                    edge = edge->next;
                }
                if (edge) {
                    printf(" --%d--> ", edge->price);
                } else {
                    printf(" --> ");
                }
            }
        }
        printf(" Total cost: %d\n", path->totalPrice);
    }
}

void freeGraph(Graph* graph) {
    if (!graph) return;
    for (int i = 0; i < graph->numCities; i++) {
        Edge* it = graph->cities[i].adjList;
        while (it) {
            Edge* temp = it;
            it = it->next;
            free(temp);
        }
    }
    for (int i = 0; i < MAX_CITIES + 3; i++) {
        CityMapEntry* entry = graph->cityMap[i];
        while (entry) {
            CityMapEntry* temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
    free(graph);
}

void freePathList(PathList* list) {
    if (!list) return;
    for (int i = 0; i < list->count; i++) {
        free(list->paths[i]->cities);
        free(list->paths[i]);
    }
    free(list->paths);
    free(list);
}