



int main() {

#if defined(__i386__) || defined(__x86_64__)
  __asm__ __volatile__("rep; nop;"::: "memory");  /* a.k.a. PAUSE */
#endif

    return 0;
}