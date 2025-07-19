
#include "test.h"


// Attributes defined BEFORE declarations
__attribute__((constructor(200))) void ctor2();
__attribute__((constructor(100))) void ctor1();
__attribute__((destructor(200))) void dtor2();
__attribute__((destructor(100))) void dtor1();

int step = 0;

void before_main_low () __attribute__((constructor(500))) ;
void before_main_high() __attribute__((constructor(400))) ;

void  after_main_low() __attribute__((destructor(500)))  ;
void after_main_high() __attribute__((destructor(400)))  ;

// Attributes defined AFTER declarations
void ctor3() __attribute__((constructor(300)));
void dtor3() __attribute__((destructor(300)));

void ctor1() {
    printf("Constructor 100 (first)\n");
    step += 100;
    ASSERT(100, step);
}
void ctor2() {
    printf("Constructor 200 (second)\n");
    step += 100;
    ASSERT(200, step);
}
void ctor3() {
    printf("Constructor 300 (third)\n");
    step += 100;
    ASSERT(300, step);
}

void dtor1() {
    printf("Destructor 100 (first)\n");
    step -= 100;
    ASSERT(0, step);
}
void dtor2() {
    printf("Destructor 200 (second)\n");
    step -= 100;
    ASSERT(100, step);
}
void dtor3() {
    printf("Destructor 300 (last)\n");
    step -= 100;
    ASSERT(200, step);

}


void before_main_low(void) {
    printf("Constructor with priority 500 (runs fifth)\n");
    step += 100;
    ASSERT(500, step);
}

void before_main_high(void) {
    printf("Constructor with priority 400 (runs fourth)\n");
    step += 100;
    ASSERT(400, step);
}

void after_main_low(void) {
    printf("Destructor with priority 500 (runs fifth)\n");
    step -= 100;
    ASSERT(400, step);


}

void after_main_high(void) {
    printf("Destructor with priority 400 (runs fourth)\n");
    step -= 100;
    ASSERT(300, step);

}

int main(void) {
    printf("Inside main()\n");
    return 0;
}
