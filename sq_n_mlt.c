/*
Ayodele, David
INFSCI 2170
HW 8 Pb 7
4/5/19
*/
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define bigint long long

bigint bigpow(bigint x, bigint y) 
{ 
    int result = 1;     // result when y = 0 
   
    while (y > 0) 
    { 
        if (y & 1) { // binary and with 1 will be 1 if y is odd (ends in 1)
            result = result*x; // multiply (the base) only
        }
        y = y>>1; // otherwise y = y/2 (or we could increase y by 2 but this 
                  // would require starting with y = 1, here we start with the largest y)
        x = x*x;  // square the base 
    } // repeat until y is too small to enter loop
    return result; 
}

int main(int datac, char *datav[]) {
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

	r = bigpow(x,y);
    printf("%d ^ %d = %d\n", x, y, r);
    
    clock_t toc = clock();
     
    printf("Elapsed time: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC); // CLOCKS_PER_SEC defined in time.h
	return 0;
}
