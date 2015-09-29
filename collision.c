#include <stdio.h>
#include <string.h>
#include "crc.h"
#include <time.h>

//part1 x = 0 & y = 1146140826 CRC(x) = CRC(y) = 0xf4dbdf21 in 168.57 seconds
//part2 x = 759d98f165838aee96af8ba1da9b6a07 & y = 1343622642 CRC(x) = CRC(y) = 0xebf09b06 in
//197.05 seconds
int main(void) {
    static char str[] = "759d98f165838aee96af8ba1da9b6a07";
    char col[30];
    int test = 0;
    crc_t crc1;
    crc_t crc2;
    clock_t t = clock();
    
    crc1 = crc_init();
    crc1 = crc_update(crc1, (unsigned char *)str, strlen(str));
    crc1 = crc_finalize(crc1);
    do {
        test++;
        sprintf(col, "%d", test);
        crc2 = crc_init();
        crc2 = crc_update(crc2, (unsigned char *)col, strlen(col));
        crc2 = crc_finalize(crc2);
    } while(((unsigned long) crc1 != (unsigned long)crc2));

    t = clock() - t;
    printf("%s: 0x%lx = %s: 0x%lx\n", str,(unsigned long)crc1, col, (unsigned long) crc2);
    printf("%f\n", ((float)t)/CLOCKS_PER_SEC);
    return 0;
}
