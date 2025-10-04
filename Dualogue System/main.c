#include "lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_line() {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        return strdup(buffer);
    }
    return NULL;
}

int main() {
    int N, M, K;

    printf("\nEnter the number of NPC lines: ");
    scanf("%d", &N);
    getchar();

    Node *npc_lines[N + 1];
    for (int i = 0; i <= N; i++) {
        npc_lines[i] = NULL;
    }

    printf("\nEnter NPC lines (format: <Parent number> <NPC Line>):\n");
    for (int i = 1; i <= N; i++) {
        int parent;
        scanf("%d", &parent);
        getchar();
        char *npc_line = read_line();

        Node *newNode = init_node(npc_line);
        npc_lines[i] = newNode;

        if (parent == 0) {
            if (npc_lines[0] == NULL) {
                npc_lines[0] = newNode;
            } else {
                add_next_step(npc_lines[0], newNode);
            }
        } else if (parent > 0 && npc_lines[parent]) {
            add_next_step(npc_lines[parent], newNode);
        } else {
            printf("Error: Parent node %d is not initialized!\n", parent);
            free(newNode);
            npc_lines[i] = NULL;
        }
    }

    printf("\nEnter the number of player lines: ");
    scanf("%d", &M);
    getchar();

    Node *player_lines[M + 1];
    for (int i = 0; i <= M; i++) {
        player_lines[i] = NULL;
    }

    printf("\nEnter Player lines (format: <Parent number> <Player Line> <num of requirements> [<item_name> <required_count> for each requirement]):\n");
    for (int i = 1; i <= M; i++) {
        int parent;
        scanf("%d", &parent);
        getchar();
        char *player_line = read_line();

        int num_requirements;
        scanf("%d", &num_requirements);
        getchar();

        Requirement *requirements = NULL;
        if (num_requirements > 0) {
            requirements = malloc(num_requirements * sizeof(Requirement));
            for (int j = 0; j < num_requirements; j++) {
                char item_name[100];
                int required_count;
                scanf("%s %d", item_name, &required_count);
                getchar();

                requirements[j].item_name = strdup(item_name);
                requirements[j].required_count = required_count;
            }
        }

        Node *newNode = init_node(player_line);
        player_lines[i] = newNode;

        if (parent > 0 && npc_lines[parent]) {
            add_choice(npc_lines[parent], player_line, requirements, num_requirements);
        }

        if (num_requirements > 0) {
            for (int j = 0; j < num_requirements; j++) {
                free(requirements[j].item_name);
            }
            free(requirements);
        }
    }

    printf("\nEnter number of additional links: ");
    scanf("%d", &K);
    getchar();

    printf("\nEnter additional links (format: <Parent number> <Player number>):\n");
    for (int i = 1; i <= K; i++) {
        int parent, player;
        scanf("%d %d", &parent, &player);
        getchar();

        if (parent < 1 || parent > N || player < 1 || player > M) {
            printf("Invalid parent/player indices.\n");
            continue;
        }

        Node *parentNode = npc_lines[parent];
        Node *playerNode = player_lines[player];

        if (parentNode && playerNode) {
            add_next_step(parentNode, playerNode);
        }
    }

    Inventory inventory = {NULL, 0};

    printf("\nEnter the number of items to add to the inventory: ");
    int num_items;
    scanf("%d", &num_items);
    getchar();

    for (int i = 0; i < num_items; i++) {
        char item_name[100];
        int count;
        printf("Enter item name and count (format: <name> <count>): ");
        scanf("%s %d", item_name, &count);
        getchar();
        add_item_to_inventory(&inventory, item_name, count);
    }

    if (npc_lines[0]) {
        play_dialogue(npc_lines[0], &inventory);
    }

    for (int i = 1; i <= N; i++) {
        free_node(npc_lines[i]);
    }
    for (int i = 1; i <= M; i++) {
        free_node(player_lines[i]);
    }
    free(inventory.items);

    return 0;
}