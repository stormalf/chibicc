typedef unsigned char uint8_t;

static inline uint8_t value_barrier_8(uint8_t a)
{
    uint8_t r;
    __asm__("" : "=r"(r) : "0"(a));
    return r;
}

int main(void)
{
    return value_barrier_8(7) != 7;
}
