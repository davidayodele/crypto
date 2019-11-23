/*
Ayodele, David
INFSCI 2170
HW 8 Pb 8
4/5/19

must compile with: gcc rsa_ex.c -lm (-lm needed for sqrt)


References: 
[1] https://codereview.stackexchange.com/questions/156477/c-program-to-count-number-of-lines-in-a-file
[2] https://www.youtube.com/channel/UC4qyGwNwWA3kg4AyD61y82A
*/
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define bigint long long

void rewind(FILE *f);  // to reset current position to beginning of file

off_t get_file_length( FILE *file ) {
    fpos_t position; // fpos_t may be a struct and store multibyte info
    off_t length; // off_t is integral type, perhaps long long

    fgetpos( file, &position ); // save previous position in file

    fseeko( file, 0, SEEK_END ); // seek to end
    length = ftello( file ); // determine offset of end

    fsetpos( file, &position ); // restore position

    return length;
}

int file_lines(FILE *in_file) {
    #define SIZE 1024
    //const char filename[] = "test";
    
    char buffer[SIZE + 1], lastchar = '\n';
    char *c;
    size_t bytes;
    int lines = 0;
    /*
    if (NULL == (in_file = fopen(filename, "r"))) {
        perror(filename);
        return EXIT_FAILURE;
    }
    */
    while ((bytes = fread(buffer, 1, sizeof(buffer) - 1, in_file))) {
        lastchar = buffer[bytes - 1];
        for (c = buffer; (c = memchr(c, '\n', bytes - (c - buffer))); c++) {
            lines++;
        }
    }
    if (lastchar != '\n') {
        lines++;  /* Count the last line even if it lacks a newline */
    }
    if (ferror(in_file)) {
        fclose(in_file);
        return EXIT_FAILURE;
    }

    return lines;
}

int get_int_count(FILE *file) {
    rewind(file);
    int i = 0;
    int count = 0;
    while(!feof(file)) {
      if (fscanf (file, "%d", &i)) {        
        count++;
      }
    }
    return count;
}

void get_file_contents(FILE *file) {
    rewind(file);
    int i = 0;
    int factor = -1;
    while(!feof(file)) {
      if (fscanf (file, "%d", &i)) {        
        if (factor < i) { 
          printf ("%d\n", i);
        }
      }
      factor = i;    
    }
}

int factorize2 (n) {
    int i, j, count, totient;
    char ch[sizeof(bigint)];
    //factors = []; // initialize array for factors
    FILE *f = fopen("factors.txt", "a+"); // create file (in append mode) for factors
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    
    //count2 = 0; // initialize counter for factors list
    
    for (i = 2; i <= n; i++) { // starting from 2 until sqrt(n)[not working], once i > sqrt(n) all the prime factors have been seen (since if n has an integer root, all subsequent factors must divisible by that root (since n can be represented by additions of only that root, i.e. the root is a foundational unit of the number))
            count = 0; // initialize counter for i          
            if (n % i == 0) { // if i divides n then...             
                //count2++; // move to next index of array (store only unique factors)
        fprintf(f, "%d", i); // store factor
              fprintf(f, "\n");
                while (n % i == 0) { //increment the count, replace n with itself divided by i, and repeat until i does not divide n
                    count++; 
                    n /= i; // n = n / i, replace n with itself divided by i                
                }
            }           
    }

    rewind(f);
  totient = file_lines(f); // (int)(get_file_length(f)/2.0);
    printf("There are %d prime factors: \n", totient); // will include new line chars so divide by 2 and round up
    get_file_contents(f);

    if (n < 0) {
        factorize2(0 - n);
    }
    fclose(f);
}
        

int main() {
    clock_t tic = clock();
    
    #define LINE_MAX 256
    char buf[LINE_MAX];
    char *end;

    char *p, c[128];
    int r, s, t, x, y, z;

    //int ciph1[][] = { {12423,11524,7243,7459,14303,6127,10964,16399}, {9792,13629,14407,18817,18830,13556,3159,16647}, {5300,13951,81,8986,8007,13167,10022,17213}, {2264,961,17459,4101,2999,14569,17183,15827}, {12693,9553,18194,3830,2664,13998,12501,18873}, {12161,13071,16900,7233,8270,17086,9792,14266}, {13236,5300,13951,8850,12129,6091,18110,3332}, {15061,12347,7817,7946,11675,13924,13892,18031}, {2620,6276,8500,201,8850,11178,16477,10161}, {3533,13842,7537,12259,18110,44,2364,15570}, {3460,9886,8687,4481,11231,7547,11383,17910}, {12867,13203,5102,4742,5053,15407,2976,9330}, {12192,56,2471,15334,841,13995,17592,13297}, {2430,9741,11675,424,6686,738,13874,8168}, {7913,6246,14301,1144,9056,15967,7328,13203}, {796,195,9872,16979,15404,14130,9105,2001}, {9792,14251,1498,11296,1105,4502,16979,1105}, {56,4118,11302,5988,3363,15827,6928,4191}, {4277,10617,874,13211,11821,3090,18110,44}, {2364,15570,3460,9886,9988,3798,1158,9872}, {16979,15404,6127,9872,3652,14838,7437,2540}, {1367,2512,14407,5053,1521,297,10935,17137}, {2186,9433,13293,7555,13618,13000,6490,5310}, {18676,4782,11374,446,4165,11634,3846,14611}, {2364,6789,11634,4493,4063,4576,17955,7965}, {11748,14616,11453,17666,925,56,4118,18031}, {9522,14838,7437,3880,11476,8305,5102,2999}, {18628,14326,9175,9061,650,18110,8720,15404}, {2951,722,15334,841,15610,2443,11056,2186} }; 

    //int ciph2[][] = { {6340,8309,14010,8936,27358,25023,16481,25809}, {23614,7135,24996,30590,27570,26486,30388,9395}, {27584,14999,4517,12146,29421,26439,1606,17881}, {25774,7647,23901,7372,25774,18436,12056,13547}, {7908,8635,2149,1908,22076,7372,8686,1304}, {4082,11803,5314,107,7359,22470,7372,22827}, {15698,30317,4685,14696,30388,8671,29956,15705}, {1417,26905,25809,28347,26277,7897,20240,21519}, {12437,1108,27106,18743,24144,10685,25234,30155}, {23005,8267,9917,7994,9694,2149,10042,27705}, {15930,29748,8635,23645,11738,24591,20240,27212}, {27486,9741,2149,29329,2149,5501,14015,30155}, {18154,22319,27705,20321,23254,13624,3249,5443}, {2149,16975,16087,14600,27705,19386,7325,26277}, {19554,23614,7553,4734,8091,23973,14015,107}, {3183,17347,25234,4595,21498,6360,19837,8463}, {6000,31280,29413,2066,369,23204,8425,7792}, {25973,4477,30989,0,0,0,0,0} };
    
    printf("Please enter an integer, N: ");
    while (fgets(c, sizeof(c), stdin)) {
        x = strtol(c, &p, 10);
        if (p == c || *p != '\n') {
            printf("Please enter an integer, N: ");
        } else break;
    }
    factorize2(x);

    /*
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
    */
    clock_t toc = clock();
     
    printf("Elapsed time: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC); // CLOCKS_PER_SEC defined in time.h
    return 0;
}



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