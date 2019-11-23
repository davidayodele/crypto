/*
Ayodele, David
INFSCI 2170
HW 6 Pb 2
3/18/19
*/
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

/*int a, b;*/

int gccd(int x, int y, int &a, int &b) {
	if (y == 0) {
		a = 1;
		b = 0;
		assert(a*x + b*y == x);
		return x;
	} else {
		int a_t, b_t;
		int r = gccd(y, x % y, a_t, b_t);
		a = b_t;
		b = a_t - b_t * (x / y);
		assert(a * x + b * y == r);
		return r;
	}
}


int main() {
	#define LINE_MAX 256
	char buf[LINE_MAX];
	char *end;

	char *p, c[128];
	int s, t, x, y;
	
	
	printf("Please enter an integer: ");
    while (fgets(c, sizeof(c), stdin)) {
        x = strtol(c, &p, 10);
        if (p == c || *p != '\n') {
            printf("Please enter an integer: ");
        } else break;
    }
    
	printf("Please enter another integer: ");
	while (fgets(c, sizeof(c), stdin)) {
        y = strtol(c, &p, 10);
        if (p == c || *p != '\n') {
            printf("Please enter an integer: ");
        } else break;
    }
	
	int r = gccd(x, y, s, t);
	printf("%d * %d + %d * %d = %d\n", s, x, t, y, r);
	printf("a = %d\n b = %d\n", s, t);

	return 0;
}
