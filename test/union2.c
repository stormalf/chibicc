#include <stdio.h>

enum DataType {
    INT,
    FLOAT,
    CHAR
};

union MyUnion {
    int i;
    float f;
    char c;
    enum DataType type;
};

struct Employee {
    char name[30];
    union {
        int employeeID;
        float salary;
    } info;
};

union SpaceSaving {
    int i;
    char c;
};

void printUnion(union MyUnion u) {
    printf("Value: %d\n", u.i);

}

union Flags {
    struct {
        unsigned int flag1 : 1;
        unsigned int flag2 : 1;
        unsigned int flag3 : 1;

    } bits;
    unsigned int all_flags;
};

union Number {
    int integer;
    float floating;
};

union Data {
    int *ip;
    float *fp;
};

typedef union {
    int i;
    float f;
    char c;
} NewUnion;


union FunctionPointer {
    int (*add) (int, int);
    int (*substract) (int, int);
};

int add(int a, int b) {
    return a + b;
}

int substract (int a, int b ) {
    return a - b;

}
union Color {
    unsigned int rgba;
    struct {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    } components;
};

union Money {
    float dollars;
    float euros;
    float yen;
};


int main() {
    union MyUnion u;
    u.type = FLOAT;
    switch (u.type) {
    case INT:

        u.i = 42;
        printf("Value of i: %d\n", u.i);
        printUnion(u);
        break;
    case FLOAT:
        u.f = 3.14;
        printf("Value of f: %f\n", u.f);
        break;
    case CHAR:
        u.c = 'A';
        printf("Value of c: %c\n", u.c);
        break;
    }


    struct Employee emp;
    strcpy(emp.name, "John");
    emp.info.employeeID = 101;
    printf("Name: %s, Employee ID: %d\n", emp.name, emp.info.employeeID);
    emp.info.salary = 50000.0;
    printf("Name: %s, Salary: %.2f\n", emp.name, emp.info.salary);

    printf("Size of spacesaving: %lu\n", sizeof(union SpaceSaving));



    union Flags flags;
    flags.bits.flag1 = 1;
    flags.bits.flag2 = 0;
    flags.bits.flag3 = 1;

    printf("Flag 1 : %d, Flag2 : %d, Flag 3 : %d\n", flags.bits.flag1, flags.bits.flag2, flags.bits.flag3);
    printf("All flags: %u\n", flags.all_flags);

    union Number numbers[5];
    for (int i = 0; i < 5; i++) {
        numbers[i].integer = i;
        printf("Integer: %d, Float: %f\n", numbers[i].integer, numbers[i].floating);
    }

    union Data data;
    int num = 42;
    data.ip = &num;
    printf("Value: %d\n", *(data.ip));
    float pi = 3.14;
    data.fp = &pi;
    printf("Value: %f\n", *(data.fp));

    NewUnion nu;
    nu.i = 42;
    printf("Value of i : %d\n", nu.i);
    nu.f = 3.14;
    printf("Value of f : %f\n", nu.f);
    nu.c = 'A';
    printf("Value of c : %c\n", nu.c);

    union FunctionPointer fp;
    fp.add = add;
    printf("Add: %d\n", fp.add(5, 3));
    fp.substract = substract;
    printf("Substract: %d\n", fp.substract(5, 3));

    union Color red;
    red.components.r = 255;
    red.components.g = 0;
    red.components.b = 0;
    red.components.a = 255;
    printf("red: rgba(%u, %u, %u, %u)\n", red.components.r, red.components.g, red.components.b, red.components.a);

    union Money money;
    money.dollars = 100.0;
    printf("$100 in dollars: %.2f\n", money.dollars);
    money.euros = money.dollars * 0.85;
    printf("$100 in euros: €%.2f\n", money.euros);
    money.yen = money.dollars * 110.56;
    printf("$100 in yen: y%.2f\n", money.yen);
    return 0;
}