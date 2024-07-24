 #define OSSL_DEPRECATED(since)           __attribute__((deprecated("Since OpenSSL " # since)))

 OSSL_DEPRECATED("1.1.0") void myfunc(void)   {
    return;
 }

 int main() 
 {
    
    return 0;
 }