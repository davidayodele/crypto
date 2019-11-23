/*
Ayodele, David
INFSCI 2170
HW 8 Pb 3
4/5/19
*/
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define bigint long long

bigint mod_pow(bigint a, bigint N, bigint M) {
    bigint result = 1; // default when N = 0 
    while (N > 0) {
        if (N % 2 == 1) {
            result = (result * a) % M; // if N is odd, mult result by a only (the mult case in square and mult)
        }
        N = N >> 1; // N = N/2
        a = (a * a) % M; // mult base by itself (square) then take mod
    }
    return result;
}

int main() {
    clock_t tic = clock();
    
    #define LINE_MAX 256
    char buf[LINE_MAX];
    char *end;

    char *p, c[128];
    int r, s, t, x, y, z;
    
    printf("Please enter an integer, a: ");
    while (fgets(c, sizeof(c), stdin)) {
        x = strtol(c, &p, 10);
        if (p == c || *p != '\n') {
            printf("Please enter an integer, a: ");
        } else break;
    }
    
    printf("Please enter another integer, N: ");
    while (fgets(c, sizeof(c), stdin)) {
        y = strtol(c, &p, 10);
        if (p == c || *p != '\n') {
            printf("Please enter an integer, N: ");
        } else break;
    }

    printf("Please enter a modulus integer, M: ");
    while (fgets(c, sizeof(c), stdin)) {
        z = strtol(c, &p, 10);
        if (p == c || *p != '\n') {
            printf("Please a modulus integer, M: ");
        } else break;
    }
    
    r = mod_pow(x,y,z);
    printf("%d ^ %d mod %d = %d\n", x, y, z, r);
    
    clock_t toc = clock();
     
    printf("Elapsed time: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC); // CLOCKS_PER_SEC defined in time.h
    return 0;
}




