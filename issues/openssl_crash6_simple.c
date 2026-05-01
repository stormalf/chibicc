typedef unsigned long uint64_t;
typedef unsigned char uint8_t;

int main(void)
{
    uint64_t x = 0;
    uint8_t in[8] = {1,2,3,4,5,6,7,8};
    int i;

    for (i = 0; i < 8; i++)
        x |= ((uint64_t)in[i]) << (8 * i);

    if (((x >> 0) & 0xff) != 1) return 1;
    if (((x >> 8) & 0xff) != 2) return 2;
    if (((x >> 16) & 0xff) != 3) return 3;
    if (((x >> 24) & 0xff) != 4) return 4;
    if (((x >> 32) & 0xff) != 5) return 5;
    if (((x >> 40) & 0xff) != 6) return 6;
    if (((x >> 48) & 0xff) != 7) return 7;
    if (((x >> 56) & 0xff) != 8) return 8;

    return 0;
}
