#include <stdio.h>
#include <stdlib.h>

typedef struct State {
    int val;
    struct State *prev;
} State;

// Recursive function that mimics addstate() in Vim's regex engine
void addstate(State **cur, int depth, int limit) {
    if (depth > limit) {
        return;
    }

    // Allocate state on heap to simulate Vim's match state
    State *s = malloc(sizeof(State));
    s->val = depth;
    s->prev = *cur;
    *cur = s;

    // Recursive call
    addstate(cur, depth + 1, limit);
}

// Traverse the list without freeing (to mimic crash potential)
void traverse(State *s) {
    while (s) {
        // Dereference state
        printf("state depth=%d\n", s->val);
        s = s->prev;
    }
}

int main() {
    State *cur = NULL;

    // Simulate deep recursion like Vim regex pattern
    //addstate(&cur, 1, 100000); // increase if no crash
    addstate(&cur, 1, 87249); // it works fine with 87248 and crashes with 87249

    traverse(cur);

    return 0;
}
