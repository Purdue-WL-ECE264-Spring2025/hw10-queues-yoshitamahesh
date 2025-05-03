#include "queue.h"
#include "tile_game.h"
#include "linked_list.h"

void enqueue(struct queue *q, struct game_state state) {
    insert_at_head(&q -> data, serialize(state));
}

struct game_state dequeue(struct queue *q) { 
    return deserialize(remove_from_tail(&q -> data)); 
}

//function to check end_state and current state
bool check_end(struct game_state current, struct game_state end_state) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(current.tiles[i][j] != end_state.tiles[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

//function to store visited states
bool check_visited(struct game_state current, struct linked_list *visited) {
    current.num_steps = 0;
    size_t current_val = serialize(current);

    struct list_node *n = visited-> head;
    while (n != NULL) {
        if(current_val == n -> value) {
            return 0;
        }
        n = n->next;
    }
    return 1;

}

int number_of_moves(struct game_state start) { 
    struct queue queue;
    struct linked_list visited = { .head = NULL };
    queue.data.head = NULL;

    struct game_state end_state = {
        .tiles = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15}},
        .empty_row = 3, 
        .empty_col = 3, 
        .num_steps = 0
    };

    enqueue(&queue, start);
    while(queue.data.head != NULL) {
        struct game_state cur = dequeue(&queue);
        if(check_end(cur, end_state)) { // check how to set end_state
            free_list(queue.data);
            free_list(visited);
            return cur.num_steps;
        }
        if(cur.empty_row != 3) { //check move up
            struct game_state copy = cur;
            move_up(&copy);

            if(check_visited(copy, &visited)) {
                enqueue(&queue, copy);
                copy.num_steps = 0;
                insert_at_head(&visited, serialize(copy)); 
            }
        }
        if(cur.empty_row != 0) { //check move down
            struct game_state copy = cur;
            move_down(&copy);

            if(check_visited(copy, &visited)) {
                enqueue(&queue, copy); 
                copy.num_steps = 0;
                insert_at_head(&visited, serialize(copy));
            }
        }
        if(cur.empty_col != 0) { //check move right
            struct game_state copy = cur;
            move_right(&copy);

            if(check_visited(copy, &visited)) {
                enqueue(&queue, copy); 
                copy.num_steps = 0;
                insert_at_head(&visited, serialize(copy));
            }
        }
        if(cur.empty_col != 3) { //check move left
            struct game_state copy = cur;
            move_left(&copy);

            if(check_visited(copy, &visited)) {
                enqueue(&queue, copy); 
                copy.num_steps = 0;
                insert_at_head(&visited, serialize(copy));
            }
        }
    }
    return -1;
}

