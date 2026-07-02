// Test: liveness analysis should detect variable read through struct member access

struct entry {
  struct entry *next;
  int value;
};

static inline int dict_iterate(struct entry *head) {
  struct entry *p_entry;
  struct entry *p_next;
  for (p_entry = head; p_entry; p_entry = p_next) {
    p_next = p_entry->next;
    if (p_entry->value == 42)
      return 1;
  }
  return 0;
}

int main(void) {
  struct entry e = {0, 0};
  return dict_iterate(&e);
}
