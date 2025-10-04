#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 8
#define COLS 8
#define EMPTY ' '
#define WALL '#'
#define START 'S'
#define END 'E'
#define SEEN '.'
#define PATH 'X'
#define WEIGHT '*'

#define CLEAR_SCREEN() printf("\033[H\033[J")
#define DELAY 200000

char grid[ROWS][COLS + 1] = {
    "########",
    "#S     #",
    "### ***#",
    "#   **##",
    "#  ##E #",
    "#    # #",
    "# #    #",
    "########"
};

void print_grid() {
    CLEAR_SCREEN();
    for (int i = 0; i < ROWS; i++) {
        printf("%s\n", grid[i]);
    }
    usleep(DELAY);
}

int get_tile_cost(char tile) {
    switch (tile) {
        case EMPTY: return 1;
        case WEIGHT: return 5;
        case WALL: return -1;
        default: return 0;
    }
}

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

typedef struct Point {
    int x;
    int y;
} Point;

// Код за BFS алгоритъм

typedef struct Node {
    Point point;
    struct Node *parent;
} Node;

typedef struct Queue {
    Node* nodes[ROWS * COLS];
    int front;
    int rear;
} Queue;

void enqueue(Queue* q, Node* node) {
    q->nodes[q->rear ++] = node;
}

Node* dequeue(Queue* q) {
    return q->nodes[q->front++];
}

int is_empty(Queue* q) {
    return q->front == q->rear;
}

void bfs() {
    int visited[ROWS][COLS] = {0};
    Queue q = {
        .front = 0,
        .rear = 0
    };

    Point start;
    Point end;
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j ++) {
            if (grid[i][j] == START) {
                start.x = i;
                start.y = j;
            }
            if (grid[i][j] == END) {
                end.x = i;
                end.y = j;
            }
        }
    }

    Node* start_node = (Node*)malloc(sizeof(Node));
    start_node->point = start;
    start_node->parent = NULL;
    enqueue(&q, start_node);
    visited[start.x][start.y] = 1;
    Node* end_node = NULL;

    while(!is_empty(&q)) {
        Node* current = dequeue(&q);
        int x = current->point.x;
        int y = current->point.y;

        if(grid[x][y] != END && grid[x][y] != START) {
            grid[x][y] = SEEN;
            print_grid();
        }

        if(x == end.x && y == end.y) {
            end_node = current;
            break;
        }

        for(int d = 0; d < 4; d ++) {
            int new_x = x + dx[d];
            int new_y = y + dy[d];

            if(new_x >= 0 && new_x < ROWS && new_y >= 0 && new_y < COLS && !visited[new_x][new_y] &&
               (grid[new_x][new_y] == EMPTY || grid[new_x][new_y] == END || grid[new_x][new_y] == WEIGHT)) {
                visited[new_x][new_y] = 1;
                grid[new_x][new_y] = SEEN;

                Node* next = (Node*)malloc(sizeof(Node));
                next->point.x = new_x;
                next->point.y = new_y;
                next->parent = current;
                enqueue(&q, next);
            }
        }
    }

    grid[start.x][start.y] = START;
    grid[end.x][end.y] = END;
    Node* path = end_node->parent;
    while(path && grid[path->point.x][path->point.y] != START) {
        grid[path->point.x][path->point.y] = PATH;
        print_grid();
        path = path->parent;
    }

    Node* node = end_node;
    while (node != NULL) {
        Node* prev = node->parent;
        free(node);
        node = prev;
    }

    while (!is_empty(&q)) {
        free(dequeue(&q));
    }
}

// До тук BFS


// Код за A* алгоритъм

typedef struct ANode {
    Point point;
    struct ANode* parent;
    int weight;
    int total;
} ANode;

typedef struct priority_queue {
    ANode* nodes[ROWS * COLS];
    int size;
} PriorityQueue;

void push(PriorityQueue* pq, ANode* node) {
    pq->nodes[pq->size++] = node;
}

ANode* pop(PriorityQueue* pq) {
    int best = 0;
    for (int i = 1; i < pq->size; i++)
        if (pq->nodes[i]->total < pq->nodes[best]->total)
            best = i;
    ANode* res = pq->nodes[best];
    pq->nodes[best] = pq->nodes[--pq->size];
    return res;
}

int heuristic(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void a_star() {
    int visited[ROWS][COLS] = {0};
    PriorityQueue pq = {.size = 0};
    Point start, end;

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] == START)  {
                start.x = i;
                start.y = j; 
            }
            if (grid[i][j] == END) {
                end.x = i;
                end.y = j;
            }
        }

    ANode* startNode = malloc(sizeof(ANode));
    startNode->point = start;
    startNode->parent = NULL;
    startNode->weight = 0;
    startNode->total = heuristic(start, end);
    push(&pq, startNode);

    ANode* endNode = NULL;

    while(pq.size > 0) {
        ANode* current = pop(&pq);

        visited[current->point.x][current->point.y] = 1;

        int x = current->point.x;
        int y = current->point.y;

        if(grid[x][y] != START && grid[x][y] != END) {
            grid[x][y] = SEEN;
            print_grid();
        }

        if(x == end.x && y == end.y) {
            endNode = current;
            break;
        }

        for(int d = 0; d < 4; d ++) {
            int new_x = x + dx[d];
            int new_y = y + dy[d];

            if (new_x >= 0 && new_x < ROWS && new_y >= 0 && new_y < COLS &&
                    !visited[new_x][new_y] &&
                    (grid[new_x][new_y] == EMPTY || grid[new_x][new_y] == END || grid[new_x][new_y] == WEIGHT)) {

                ANode* neighbor = malloc(sizeof(ANode));

                neighbor->point.x = new_x;
                neighbor->point.y = new_y;

                neighbor->parent = current;
                neighbor->weight = current->weight + get_tile_cost(grid[new_x][new_y]);
                neighbor->total = neighbor->weight + heuristic(neighbor->point, end);

                push(&pq, neighbor);
            }
        }
    }
    if (endNode) {
        ANode* path = endNode->parent;
        while (path && grid[path->point.x][path->point.y] != START) {
            grid[path->point.x][path->point.y] = PATH;
            print_grid();
            path = path->parent;
        }
    }

    ANode* node = endNode;
    while (node != NULL) {
        ANode* prev = node->parent;
        free(node);
        node = prev;
    }

    for (int i = 0; i < pq.size; i++) {
        free(pq.nodes[i]);
    }
}

// До тук A* алгоритъм

// Код за Dijkstra алгоритъм

typedef struct DNode {
    Point point;
    struct DNode* parent;
    int weight;
    int total;
} DNode;

typedef struct {
    DNode* nodes[ROWS * COLS];
    int size;
} DQueue;

void dpush(DQueue* dq, DNode* node) {
    dq->nodes[dq->size++] = node;
}

DNode* dpop(DQueue* dq) {
    int best = 0;
    for (int i = 1; i < dq->size; i++)
        if (dq->nodes[i]->total < dq->nodes[best]->total)
            best = i;
    DNode* res = dq->nodes[best];
    dq->nodes[best] = dq->nodes[--dq->size];
    return res;
}

void dijkstra() {
    int visited[ROWS][COLS] = {0};
    DQueue dq = {.size = 0};
    Point start, end;

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] == START) {
                start.x = i;
                start.y = j;
            }
            if (grid[i][j] == END) {
                end.x = i;
                end.y = j;
            }
        }

    DNode* startNode = malloc(sizeof(DNode));
    startNode->point = start;
    startNode->parent = NULL;
    startNode->weight = 0;
    startNode->total = 0;
    dpush(&dq, startNode);


    DNode* endNode = NULL;

    while (dq.size > 0) {
        DNode* current = dpop(&dq);

        visited[current->point.x][current->point.y] = 1;

        int x = current->point.x;
        int y = current->point.y;

        if (grid[x][y] != START && grid[x][y] != END) {
            grid[x][y] = SEEN;
            print_grid();
        }

        if (x == end.x && y == end.y) {
            endNode = current;
            break;
        }

        for (int d = 0; d < 4; d++) {
            int new_x = x + dx[d];
            int new_y = y + dy[d];
            if (new_x >= 0 && new_x < ROWS && new_y >= 0 && new_y < COLS &&
                !visited[new_x][new_y] &&
                (grid[new_x][new_y] == EMPTY || grid[new_x][new_y] == END || grid[new_x][new_y] == WEIGHT)) {
                DNode* neighbor = malloc(sizeof(DNode));
                neighbor->point.x = new_x;
                neighbor->point.y = new_y;
                neighbor->parent = current;
                neighbor->weight = current->weight + get_tile_cost(grid[new_x][new_y]);
                neighbor->total = neighbor->weight;
                dpush(&dq, neighbor);
            }
        }
    }

    if (endNode) {
        DNode* path = endNode->parent;
        while (path && grid[path->point.x][path->point.y] != START) {
            grid[path->point.x][path->point.y] = PATH;
            print_grid();
            path = path->parent;
        }
    }

    DNode* node = endNode;
    while (node != NULL) {
        DNode* prev = node->parent;
        free(node);
        node = prev;
    }
    for (int i = 0; i < dq.size; i++) {
        free(dq.nodes[i]);
    }
}

// До тук Dijkstra алгоритъм

int main() {
    print_grid();
    int choice;
    printf("Choose algorithm:\n");
    printf("1. BFS\n");
    printf("2. A*\n");
    printf("3. Dijkstra\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            bfs();
            break;
        case 2:
            a_star();
            break;
        case 3:
            dijkstra();
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
    return 0;
}