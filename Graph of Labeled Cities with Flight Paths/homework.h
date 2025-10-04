#ifndef HOMEWORK_H
#define HOMEWORK_H

#define MAX_CHARACTERS 100
#define MAX_CITIES 100
#define MAX_EDGES 1000

typedef struct Edge {
    int price;
    int index;
    struct Edge* next;
} Edge;

typedef struct City {
    char name[MAX_CHARACTERS];
    Edge* adjList;
} City;

typedef struct CityMapEntry {
    char name[MAX_CHARACTERS];
    int index;
    struct CityMapEntry* next;
} CityMapEntry;

typedef struct Graph {
    City cities[MAX_CITIES];
    int numCities;
    CityMapEntry* cityMap[MAX_CITIES + 3];
} Graph;

typedef struct Path {
    int* cities;
    int length;
    int totalStops;
    int totalPrice;
} Path;

typedef struct PathList {
    Path** paths;
    int count;
    int capacity;
} PathList;

unsigned int hash(const char* key);
void addToCityMap(Graph* graph, const char* name, int index);
int getCityIndex(Graph* graph, const char* name);

Edge* createEdge(int price, int index);
void addEdge(City* city, int price, int index);
Graph* createGraph();

PathList* createPathList(int capacity);
void addPathToList(PathList* list, Path* path);

void addCity(Graph* graph, const char* name);
void addCityToGraph(Graph* graph, const char* name);
void addEdgeToGraph(Graph* graph, const char* fromCity, const char* toCity, int price);

void findShortestPath(Graph* graph, const char* startCity, const char* endCity, PathList* resultPaths, int maxStops, int maxPrice);

void printPaths(const PathList* list, Graph* graph);
void freePathList(PathList* list);

void freeGraph(Graph* graph);

#endif