#include "lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Node *init_node(const char *npc_line) {
    Node *node = (Node *)malloc(sizeof(Node));
    if(node == NULL) {
        printf("Error allocating memory!\n");
        exit(1);
    }
    node->NPC_lines = strdup(npc_line);
    node->possible_Player_Lines = NULL;
    node->possible_Player_Lines_size = 0;
    node->nextStep = NULL;
    node->nextStep_size = 0;
    node->requirements = NULL;
    node->requirements_size = 0;
    return node;
}

void add_choice(Node *node, const char *player_line, Requirement *requirements, int requirements_size) {
    node->possible_Player_Lines_size++;
    char **temp = (char**)realloc(node->possible_Player_Lines, node->possible_Player_Lines_size * sizeof(char *));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    node->possible_Player_Lines = temp;
    node->possible_Player_Lines[node->possible_Player_Lines_size - 1] = strdup(player_line);

    node->requirements_size = requirements_size;
    node->requirements = malloc(node->requirements_size * sizeof(Requirement));

    for (int i = 0; i < requirements_size; i++) {
        node->requirements[i].item_name = strdup(requirements[i].item_name);
        node->requirements[i].required_count = requirements[i].required_count;
    }
}

void add_next_step(Node *node, Node *next_npc) {
    node->nextStep_size++;
    Node **temp = (Node**)realloc(node->nextStep, node->nextStep_size * sizeof(Node *));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    node->nextStep = temp;
    node->nextStep[node->nextStep_size - 1] = next_npc;
}

void add_requirement(Node *node, const char *item_name, int required_count) {
    node->requirements_size++;
    Requirement *temp = (Requirement*)realloc(node->requirements, node->requirements_size * sizeof(Requirement));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    node->requirements = temp;
    node->requirements[node->requirements_size - 1].item_name = strdup(item_name);
    node->requirements[node->requirements_size - 1].required_count = required_count;
}

void add_item_to_inventory(Inventory *inventory, const char *item_name, int count) {
    for (int i = 0; i < inventory->size; i++) {
        if (strcmp(inventory->items[i].name, item_name) == 0) {
            inventory->items[i].count += count;
            return;
        }
    }
    inventory->size++;
    inventory->items = realloc(inventory->items, inventory->size * sizeof(Item));
    inventory->items[inventory->size - 1].name = strdup(item_name);
    inventory->items[inventory->size - 1].count = count;
}

int check_inventory(Inventory *inventory, const char *item_name, int required_count) {
    for (int i = 0; i < inventory->size; i++) {
        if (strcmp(inventory->items[i].name, item_name) == 0) {
            return inventory->items[i].count >= required_count;
        }
    }
    return 0;
}

void play_dialogue(Node *root, Inventory *inventory) {
    Node *cur = root;
    int choice;

    while (cur) {
        printf("\nNPC: %s\n", cur->NPC_lines);

        if (cur->possible_Player_Lines_size == 0) {
            printf("No player options available. Exiting dialogue.\n");
            exit(1);
        }

        for (int i = 0; i < cur->possible_Player_Lines_size; i++) {
            printf("Option %d -> %s\n", i + 1, cur->possible_Player_Lines[i]);
        }

        while (1) {
            printf("\nChoose an option (1-%d): ", cur->possible_Player_Lines_size);
            if (scanf("%d", &choice) != 1 || choice < 1 || choice > cur->possible_Player_Lines_size) {
                printf("Invalid choice! Please try again.\n");
                while (getchar() != '\n');
            } else {
                break;
            }
        }

        if (cur->requirements_size > 0) {
            Requirement req = cur->requirements[choice - 1];
            if (!check_inventory(inventory, req.item_name, req.required_count)) {
                printf("You do not meet the requirements for this choice (%s: %d needed). Exiting...\n", req.item_name, req.required_count);
            }
        }

        if (choice <= cur->nextStep_size) {
            cur = cur->nextStep[choice - 1];
        } else {
            printf("No further dialogue. Returning to root.\n");
            cur = root;
        }
    }
}

void free_node(Node *node) {
    if (node) {
        free(node->NPC_lines);
        for (int i = 0; i < node->possible_Player_Lines_size; i++) {
            free(node->possible_Player_Lines[i]);
        }
        free(node->possible_Player_Lines);

        for (int i = 0; i < node->nextStep_size; i++) {
            free_node(node->nextStep[i]);
        }
        free(node->nextStep);
        free(node);
    }
}