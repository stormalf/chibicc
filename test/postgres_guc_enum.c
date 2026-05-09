#include "test.h"
#include <stdbool.h>

struct config_generic {
  const char *name;
};

struct config_enum_entry {
  const char *name;
  int val;
  bool hidden;
};

struct config_enum {
  struct config_generic gen;
  int *variable;
  int boot_val;
  const struct config_enum_entry *options;
  void *check_hook;
  void *assign_hook;
  void *show_hook;
  int reset_val;
  void *reset_extra;
};

static const struct config_enum_entry isolation_level_options[] = {
  {"serializable", 1, false},
  {"repeatable read", 2, false},
  {"read committed", 3, false},
  {"read uncommitted", 4, false},
  {NULL, 0, false}
};

static int DefaultXactIsoLevel;

static struct config_enum ConfigureNamesEnum[] = {
  {
    {"default_transaction_isolation"},
    &DefaultXactIsoLevel,
    3,
    isolation_level_options,
    NULL, NULL, NULL,
    0,
    NULL
  },
  {{NULL}, NULL, 0, NULL, NULL, NULL, NULL, 0, NULL}
};

static int config_enum_lookup_by_name(struct config_enum *record, const char *value) {
  const struct config_enum_entry *entry = record->options;
  for (; entry && entry->name; entry++) {
    if (!strcmp(entry->name, value))
      return entry->val;
  }
  return -1;
}

int main(void) {
  ASSERT(1, config_enum_lookup_by_name(&ConfigureNamesEnum[0], "serializable") == 1);
  ASSERT(1, config_enum_lookup_by_name(&ConfigureNamesEnum[0], "read committed") == 3);
  printf("OK\n");
  return 0;
}
