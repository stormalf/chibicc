#include <stdio.h>
#include <stddef.h>
#include "test.h"

typedef struct {
    int id;
    double balance;
    struct {
        int year;
        int month;
        int day;
    } date;
} Account;

typedef union {
    int int_val;
    double double_val;
    char str[8];
} DataUnion;

typedef struct {
    char name[10];
    Account accounts[2];
    DataUnion data;
} Customer;

int main() {
    // Simple offsets in Account struct
    printf("Offset of 'id' in Account: %zu\n", offsetof(Account, id));
    ASSERT(0, offsetof(Account, id));
    printf("Offset of 'balance' in Account: %zu\n", offsetof(Account, balance));
    ASSERT(8, offsetof(Account, balance));
    printf("Offset of 'date.year' in Account: %zu\n", offsetof(Account, date.year));
    ASSERT(16, offsetof(Account, date.year));
    printf("Offset of 'date.month' in Account: %zu\n", offsetof(Account, date.month));
    ASSERT(20, offsetof(Account, date.month));
    printf("Offset of 'date.day' in Account: %zu\n", offsetof(Account, date.day));
    ASSERT(24, offsetof(Account, date.day));

    // Offsets in Customer struct
    printf("Offset of 'name' in Customer: %zu\n", offsetof(Customer, name));
    ASSERT(0, offsetof(Customer, name));
    printf("Offset of 'accounts[0].id' in Customer: %zu\n", offsetof(Customer, accounts[0].id));
    ASSERT(16, offsetof(Customer, accounts[0].id));
    printf("Offset of 'accounts[1].balance' in Customer: %zu\n", offsetof(Customer, accounts[1].balance));
    ASSERT(56, offsetof(Customer, accounts[1].balance));
    printf("Offset of 'data.int_val' in Customer: %zu\n", offsetof(Customer, data.int_val));
    ASSERT(80, offsetof(Customer, data.int_val));
    printf("Offset of 'data.double_val' in Customer: %zu\n", offsetof(Customer, data.double_val));
    ASSERT(80, offsetof(Customer, data.double_val));
    printf("Offset of 'data.str[3]' in Customer: %zu\n", offsetof(Customer, data.str[3]));
    ASSERT(83, offsetof(Customer, data.str[3]));

    // Testing offsetof with nested arrays
    typedef struct {
        int matrix[2][3];
    } MatrixHolder;

    printf("Offset of 'matrix[1][2]' in MatrixHolder: %zu\n", offsetof(MatrixHolder, matrix[1][2]));
    ASSERT(20, offsetof(MatrixHolder, matrix[1][2]));

    return 0;
}
