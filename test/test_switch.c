#include <stdio.h>
#include <stdint.h>

typedef unsigned int Oid;

// Match PostgreSQL OID definitions
#define BOOLOID 16
#define CHAROID 18
#define NAMEOID 19
#define INT8OID 20
#define INT2OID 21
#define INT4OID 23
#define TEXTOID 25
#define OIDOID 26
#define REGPROCOID 24
#define REGPROCEDUREOID 2202
#define REGOPEROID 2203
#define REGOPERATOROID 2204
#define REGCLASSOID 2205
#define REGTYPEOID 2206
#define REGCOLLATIONOID 4191
#define REGCONFIGOID 3734
#define REGDICTIONARYOID 3769
#define REGROLEOID 4096
#define REGNAMESPACEOID 4089
#define REGDATABASEOID 6456
#define OIDVECTOROID 30

static const char *GetTypeName(Oid keytype) {
    switch (keytype) {
        case BOOLOID: return "BOOL";
        case CHAROID: return "CHAR";
        case NAMEOID: return "NAME";
        case INT2OID: return "INT2";
        case INT4OID: return "INT4";
        case TEXTOID: return "TEXT";
        case OIDOID:
        case REGPROCOID:
        case REGPROCEDUREOID:
        case REGOPEROID:
        case REGOPERATOROID:
        case REGCLASSOID:
        case REGTYPEOID:
        case REGCOLLATIONOID:
        case REGCONFIGOID:
        case REGDICTIONARYOID:
        case REGROLEOID:
        case REGNAMESPACEOID:
        case REGDATABASEOID:
            return "OID variant";
        case OIDVECTOROID:
            return "OIDVECTOR";
        default:
            return "UNSUPPORTED";
    }
}

int main(void) {
    // Test all the expected types
    Oid test_types[] = {16, 18, 19, 20, 21, 23, 25, 26, 24, 30};
    const char *expected[] = {"BOOL", "CHAR", "NAME", "UNSUPPORTED", "INT2", "INT4", "TEXT", "OID variant", "OID variant", "OIDVECTOR"};
    
    int failures = 0;
    for (int i = 0; i < 10; i++) {
        const char *result = GetTypeName(test_types[i]);
        printf("Type %u: %s (expected: %s) %s\n", test_types[i], result, expected[i],
               (result == expected[i] || (result[0] == expected[i][0] && result[1] == expected[i][1])) ? "OK" : "FAIL");
    }
    
    // Also test that type 20 (INT8OID) falls to default
    printf("\nCritical test: type 20 (INT8OID) = %s (should be UNSUPPORTED)\n", GetTypeName(20));
    printf("Critical test: type 23 (INT4OID) = %s (should be INT4)\n", GetTypeName(23));
    printf("Critical test: type 26 (OIDOID) = %s (should be OID variant)\n", GetTypeName(26));
    
    return 0;
}
