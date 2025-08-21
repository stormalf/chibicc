#include "test.h"

typedef int vlc_action_id_t;
typedef struct { int dummy; } intf_thread_t;

#define INTF_ACTION_HANDLER(name) \
    static inline void action_handler_Intf##name(intf_thread_t *intf, vlc_action_id_t action_id)

INTF_ACTION_HANDLER(Default) {
    printf("Default handler: %d\n", action_id);
    ASSERT(42, action_id);
}

INTF_ACTION_HANDLER(Foo) {
    printf("Foo handler: %d\n", action_id);
    ASSERT(42, action_id);
}

typedef void (*handler_t)(intf_thread_t*, vlc_action_id_t);

struct vlc_action {
    handler_t fptr;
};

static struct vlc_action actions[] = {
    { .fptr = action_handler_IntfDefault },
    { .fptr = action_handler_IntfFoo }
};

int main() {
    intf_thread_t i;
    vlc_action_id_t act = 42;

    for (int j = 0; j < 2; j++)
        actions[j].fptr(&i, act);
    printf("OK\n");
    return 0;
}
