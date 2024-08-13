
#define pg_attribute_no_sanitize_address() __attribute__((no_sanitize("address")))
#define pg_attribute_noreturn() __attribute__((noreturn))

void expr_yyerror(char * yyscanner, const char *message) pg_attribute_noreturn();

void expr_yyerror(char * yyscanner, const char *message) {
    return;
}

typedef struct
{
	const char *name;
	void		(*main_fn) (char *startup_data, int startup_data_len) pg_attribute_noreturn();
	int		shmem_attach;
} child_process_kind;


pg_attribute_no_sanitize_address()
static inline int
fasthash_accum_cstring_aligned(char *hs, const char *str)
{
	const char *const start = str;
	return 0;
}


int main() {

    return 0;
}