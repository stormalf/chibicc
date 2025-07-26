
#if defined(__CLASSIC_C__)
    int main(argc, argv)
      int argc;
      char* argv[];
#else
    int main(int argc, char* argv[])
#endif

    { (void)argv; return argc-1;}