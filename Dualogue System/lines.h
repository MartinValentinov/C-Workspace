#ifndef LINE_H
#define LINE_H

typedef struct Item {
    char *name;
    int count;
} Item;

typedef struct Inventory {
    Item *items;
    int size;
} Inventory;

typedef struct Requirement {
    char *item_name;
    int required_count;
} Requirement;

typedef struct Node {
    char *NPC_lines;
    char **possible_Player_Lines;
    int possible_Player_Lines_size;
    struct Node **nextStep;
    int nextStep_size;
    Requirement *requirements;
    int requirements_size;
} Node;

Node* init_node(const char*);
void add_choice(Node *, const char *, Requirement *, int);
void add_next_step(Node *, Node *);
void add_item_to_inventory(Inventory *, const char *, int);
int check_inventory(Inventory *, const char *, int);
void play_dialogue(Node*, Inventory*);

void free_node(Node*);

#endif