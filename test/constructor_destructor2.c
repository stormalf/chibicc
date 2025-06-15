#include <stdio.h>


// Attributes defined BEFORE declarations
__attribute__((constructor(200))) void ctor2(void);
__attribute__((constructor(100))) void ctor1(void);
__attribute__((destructor(200))) void dtor2(void);
__attribute__((destructor(100))) void dtor1(void);


void before_main_low(void) __attribute__((constructor(500)));
void before_main_high(void) __attribute__((constructor(400)));

void after_main_low(void) __attribute__((destructor(500)));
void after_main_high(void) __attribute__((destructor(400)));


// Attributes defined AFTER declarations
void ctor3(void) __attribute__((constructor(300)));
void dtor3(void) __attribute__((destructor(300)));

void ctor1(void) {
    printf("Constructor 100 (first)\n");
}
void ctor2(void) {
    printf("Constructor 200 (second)\n");
}
void ctor3(void) {
    printf("Constructor 300 (third)\n");
}

void dtor1(void) {
    printf("Destructor 100 (first)\n");
}
void dtor2(void) {
    printf("Destructor 200 (second)\n");
}
void dtor3(void) {
    printf("Destructor 300 (last)\n");
}


void before_main_low(void) {
    printf("Constructor with priority 500 (runs fifth)\n");
}

void before_main_high(void) {
    printf("Constructor with priority 400 (runs fourth)\n");
}

void after_main_low(void) {
    printf("Destructor with priority 500 (runs fifth)\n");
}

void after_main_high(void) {
    printf("Destructor with priority 400 (runs fourth)\n");
}

int main(void) {
    printf("Inside main()\n");
    return 0;
}
