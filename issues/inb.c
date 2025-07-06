#include <stdio.h>

// Inline assembly function definition
static __inline unsigned char inb(unsigned short int __port)
{
    unsigned char _v;
    __asm__ __volatile__ ("inb %w1,%0" : "=a" (_v) : "Nd" (__port));
    return _v;
}

int main()
{
    unsigned short port = 0x60; // Example: PS/2 keyboard data port
    unsigned char value;

    // WARNING: inb reads I/O ports, requires root or specific permissions,
    // and should only be used on bare-metal, kernel modules, or with proper permissions.
    value = inb(port);

    printf("Value read from port 0x%x is 0x%x\n", port, value);
    return 0;
}
