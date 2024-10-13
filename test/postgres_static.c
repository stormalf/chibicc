#include <stdio.h>
#include <assert.h>


#ifndef __cplusplus
#ifdef HAVE__STATIC_ASSERT
#define StaticAssertDecl(condition, errmessage) \
	_Static_assert(condition, errmessage)
#define StaticAssertStmt(condition, errmessage) \
	do { _Static_assert(condition, errmessage); } while(0)
#define StaticAssertExpr(condition, errmessage) \
	((void) ({ StaticAssertStmt(condition, errmessage); true; }))
#else							/* !HAVE__STATIC_ASSERT */
#define StaticAssertDecl(condition, errmessage) \
	extern void static_assert_func(int static_assert_failure[(condition) ? 1 : -1])
#define StaticAssertStmt(condition, errmessage) \
	((void) sizeof(struct { int static_assert_failure : (condition) ? 1 : -1; }))
#define StaticAssertExpr(condition, errmessage) \
	StaticAssertStmt(condition, errmessage)
#endif							/* HAVE__STATIC_ASSERT */
#else							/* C++ */
#if defined(__cpp_static_assert) && __cpp_static_assert >= 200410
#define StaticAssertDecl(condition, errmessage) \
	static_assert(condition, errmessage)
#define StaticAssertStmt(condition, errmessage) \
	static_assert(condition, errmessage)
#define StaticAssertExpr(condition, errmessage) \
	({ static_assert(condition, errmessage); })
#else							/* !__cpp_static_assert */
#define StaticAssertDecl(condition, errmessage) \
	extern void static_assert_func(int static_assert_failure[(condition) ? 1 : -1])
#define StaticAssertStmt(condition, errmessage) \
	do { struct static_assert_struct { int static_assert_failure : (condition) ? 1 : -1; }; } while(0)
#define StaticAssertExpr(condition, errmessage) \
	((void) ({ StaticAssertStmt(condition, errmessage); }))
#endif							/* __cpp_static_assert */
#endif							/* C++ */



// Simulate the StaticAssertExpr macro (usually provided by PostgreSQL or a similar project)
//#define StaticAssertExpr(condition, message) _Static_assert(condition, message)


// Forward declaration of the AllocSetContextCreateInternal function
void* AllocSetContextCreateInternal(void* parent, const char* name, int size);

#ifdef HAVE__BUILTIN_CONSTANT_P
#define AllocSetContextCreate(parent, name, ...) \
	(StaticAssertExpr(__builtin_constant_p(name), \
					  "memory context names must be constant strings"), \
	 AllocSetContextCreateInternal(parent, name, __VA_ARGS__))
#else
#define AllocSetContextCreate \
	AllocSetContextCreateInternal
#endif

// Implementation of AllocSetContextCreateInternal function
void* AllocSetContextCreateInternal(void* parent, const char* name, int size) {
    printf("Context created: name = %s, size = %d\n", name, size);
    return NULL;
}

int main(void) {
    // Define some parent context (NULL in this example)
    void* parent_context = NULL;

    // Use the macro with a constant string name
    AllocSetContextCreate(parent_context, "MyConstantContext", 1024);

    // Use the macro with a non-constant name (will trigger a static assertion if HAVE__BUILTIN_CONSTANT_P is defined)
    const char* non_constant_name = "MyDynamicContext";
    // AllocSetContextCreate(parent_context, non_constant_name, 2048); // Uncommenting this will cause a compile-time error

    return 0;
}
