#include <stdio.h>
#include <string.h>
#include <inttypes.h>
void memcpy1(void *, void *, int );
int main(int argc, char **argv) {
 char source[] = "sampathsmagicmemcpy";  // 21 bytes (20 letters + '\0')
    char dest[100];
 
    // void * memcpy ( void * destination, const void * source, size_t num );
    memcpy(dest, source, strlen(source) + 1);
    printf("Source: %s. Destination: %s\n", source, dest);
 
    strcpy(source, "sampathsmagicmemcpy");
    memcpy1(dest, source, strlen(source) + 1);
    printf("Source: %s. Destination: %s\n", source, dest);
 
    return 0;
}
void memcpy1(void* dest, void* src, int size)
{
    char *pdest = (char*) dest;
    char *psrc = (char*) src;

    int loops = (size / sizeof(long));
    for(int index = 0; index < loops; ++index)
    {
        *((long*)pdest) = *((long*)psrc);
        pdest += sizeof(long);
        psrc += sizeof(long);
    }

    loops = (size % sizeof(long));
    for (int index = 0; index < loops; ++index)
    {
        *pdest = *psrc;
        ++pdest;
        ++psrc;
    }
}