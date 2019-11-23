/*
Ayodele, David
INFSCI 2170
HW 8 Pb 3
4/5/19
*/
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

#define bigint long long

/*int a, b;*/

int fst_pow(int a, int N) {
	if (N == 0) { 
		return 1; // will be reached if N is even at end of feedback
	} else if (N == 1){ 
		return a; // will be reached if N is odd at end of feedback 
	} else {
		int split = fst_pow(a, N/2); // feedback within feedback
		if (N % 2 == 0) { 
			return split*split; // will be reached if N is even at end of feedback
		} else {
			return split*a*split; // will be reached if N is odd at end of feedback
		}
	}
}

template <typename T>
T modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}


bigint modular_pow(bigint a, bigint N, int M)
{
    bigint result = 1;
    while (N > 0)
    {
        if (N % 2 == 1)
            result = (result * a) % M;
        N = N >> 1; // Same as div by 2
        a = (a * a) % M;
    }
    return result;
}



int pow_mod(int a, int N, int M) {
	if (N%2 == 0) { 
		return ( (pow_mod(a, N/2, M) % M) * (pow_mod(a, N/2, M) % M) ) % M; // feedback split * split mod M
	} else { 
		return ( (pow_mod(a, N/2, M) % M) * a * (pow_mod(a, N/2, M) % M) ) % M; // will be reached if N is odd at end of feedback 
	}
}

int main() {
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
    
	printf("Please enter another integer, N ");
	while (fgets(c, sizeof(c), stdin)) {
        y = strtol(c, &p, 10);
        if (p == c || *p != '\n') {
            printf("Please enter an integer, N ");
        } else break;
    }

    printf("Please enter a modulus integer, M: ");
	while (fgets(c, sizeof(c), stdin)) {
        z = strtol(c, &p, 10);
        if (p == c || *p != '\n') {
            printf("Please a modulus integer, M: ");
        } else break;
    }
	
	r = pow_mod(x,y,z);
    printf("%d ^ %d mod %d = %d\n", x, y, z, r);

    //r = fst_pow(x,y);
	//printf("%d ^ %d = %d\n", x, y, r);

	//int r = gccd(x, y, s, t);
	
	//printf("a = %d\n b = %d\n", s, t);

	return 0;
}
