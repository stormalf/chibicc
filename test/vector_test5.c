
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <nmmintrin.h>
typedef float float4a1 __attribute__((__vector_size__(16), __aligned__(1)));
typedef float float4;


#define JSONLEX_FREE_STRUCT			(1 << 0)
#define JSONLEX_FREE_STRVAL			(1 << 1)
typedef struct JsonLexContext
{
	const char *input;
	size_t		input_length;
	int			input_encoding;
	const char *token_start;
	const char *token_terminator;
	const char *prev_token_terminator;
	bool		incremental;
	//JsonTokenType token_type;
	int			lex_level;
	//bits32		flags;
	int			line_number;	/* line number, starting from 1 */
	const char *line_start;		/* where that line starts within input */
	//JsonParserStack *pstack;
	//JsonIncrementalState *inc_state;
	//StringInfo	strval;
	//StringInfo	errormsg;
} JsonLexContext;


bool
IsValidJsonNumber(const char *str, size_t len)
{
	bool		numeric_error;
	size_t		total_len;
	JsonLexContext dummy_lex;

	if (len <= 0)
		return false;

	dummy_lex.incremental = false;

	/*
	 * json_lex_number expects a leading  '-' to have been eaten already.
	 *
	 * having to cast away the constness of str is ugly, but there's not much
	 * easy alternative.
	 */
	if (*str == '-')
	{
		dummy_lex.input = str + 1;
  }
}

// static __inline__ float4a1
// _mm_setzero_ps(void)
// {
//   return __extension__ (float4a1){ 0, 0, 0, 0 };
// }

// /* Convert the four signed 32-bit values in A and B to SPFP form.  */
// extern __inline void
// _mm_cvtpi32x2_ps(float4a1 __A, float4a1 __B)
// {
//   float4a1 __zero = (float4a1) _mm_setzero_ps ();
  
// }



int main(void)
{

	return 0;
}