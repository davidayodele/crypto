


/*
list_head->next->val = 2;
list_head->next->next = NULL;

void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}
*/


off_t get_file_length( FILE *file ) {
    fpos_t position; // fpos_t may be a struct and store multibyte info
    off_t length; // off_t is integral type, perhaps long long

    fgetpos( file, &position ); // save previous position in file

    fseeko( file, 0, SEEK_END ); // seek to end
    length = ftello( file ); // determine offset of end

    fsetpos( file, &position ); // restore position

    return length;
}

factorize2 (n) {
	//factors = []; // initialize array for factors
	FILE *f = fopen("factors", "a"); // create file (in append mode) for factors
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	
	count2 = 0; // initialize counter for factors array
	
	for (i = 2; i <= math.sqrt(n); i++) { // starting from 2 until sqrt(n), once i > sqrt(n) all the prime factors have been seen (since if n has an integer root, all subsequent factors must divisible by that root (since n can be represented by additions of only that root, i.e. the root is a foundational unit of the number))
			fprintf(f, i); // store factor
			count = 0; // initialize counter for i			
			if (n % i == 0) { // if i divides n then...				
				count2++; // move to next index of array (store only unique factors)
				while (n % i == 0) { increment the count, replace n with itself divided by i, and repeat until i does not divide n
					count++; 
					n /= i;					
				}
			}			
		}
		printf("There are %d prime factors and %d is a prime factor. /n", get_file_length(f), fgetc(f));  
	}
	if (n = 1 || n = 0) {
		printf("The number is %d", n);
	}

	if (n < 0) {
		factorize2(0 - n);
	}
	fclose(f);	
}


/* Python pseudo
import math

primes = []

def isPrime(n):
	global primes
	for divisor in primes:
		if divisor > math.sqrt(n):
			break;

		if n % divisor == 0: // n is not prime
		return false;

	primes.append(n)	
	return true;




def factorize(n):
	pfactors = []
	divisor = 2
	while n > 1:
		if isPrime(divisor):
			if n % divisor == 0:
				n = n / divisor
				pfactors.append(divisor)
			else:
				divisor += 1
		else:
			divisor += 1



typedef struct node {
    int val;
    struct node* next; // feedback definition of node
} node_t;
*/
