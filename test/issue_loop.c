typedef union
{
  //__extension__ unsigned long long int __value64;
  
  unsigned long long int __value64;
  struct
  {
    unsigned int __low;
    unsigned int __high;
  } __value32;
} __atomic_wide_counter;



 int main(int argc, char **argv)
 {
        return 0;
 }