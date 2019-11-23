/*
Ayodele, David
INFSCI 2170
HW 8 Pb 8
4/5/19

must compile with: g++  

References: 
[1] https://codereview.stackexchange.com/questions/156477/c-program-to-count-number-of-lines-in-a-file
[2] https://stackoverflow.com/questions/41902471/how-to-use-fgets-to-read-a-file-line-by-line
[3] https://www.youtube.com/channel/UC4qyGwNwWA3kg4AyD61y82A
*/
#include <ctime>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>

#define bigint long long

typedef struct {
    char let;
    int num;
} csvdata_t;

void rewind(FILE *fp);  // to reset current position to beginning of file

int get_file_lines(FILE *fp) {
    #define MAX 300
    
    char lastchar = '\n';
    char *c;
    int i;
    csvdata_t data;
    size_t bytes;
    int lines = 0;
    char line[MAX];
    
    char msg[MAX], * fgets_rv;
    
      while ((fgets_rv = fgets(msg, sizeof(msg), fp))) {
        assert(fgets_rv == msg);
        lines++;
    }
    
    if (ferror(fp)) {
        //fclose(file);
        return EXIT_FAILURE;
    }

    return lines;
}


void get_factor_file_contents(FILE *file, bigint* factors) {
    rewind(file);
    bigint i = 0;
    int n = 0;
    
    bigint factor = -1;
    while(!feof(file)) {
      if (fscanf (file, "%lld", &i)) {
        if (factor < i) { 
          printf ("%lld\n", i);
          factors[n] = i;
          n++;
        }
      }
      factor = i;    
    }
}

void get_file_contents(FILE *file, int* arr) {
    rewind(file);
    bigint i = 0;
    int n = 0;
    while(!feof(file)) {
        if (fscanf (file, "%lld", &i)) {
            arr[n] = i;
            n++;
        }
    }
}

void get_csvfile_contents(FILE *file, int arr[29][8]) {
    rewind(file);
    bigint i = 0;
    char c[1];
    char d[1];
    int m = 0;
    int n = 0;
    
    for (n = 0; n < 29; n++) {
        for (m = 0; m < 8; m++) {
            fscanf(file, " %d", &arr[n][m]);    
        }
    }
}

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

int gccd(int x, int y, int &a, int &b) {
    if (y == 0) {
        a = 1;
        b = 0;
        assert(a*x + b*y == x);
        return x;
    } else {
        int a_t, b_t;
        int r = gccd(y, x % y, a_t, b_t); // given initial values, feedsback into itself, substituting the 2nd parameter, y,  with the remainder each time until the remainder = 0 or 1 (the base case)
        // code below not reached until y = 0 or y = 1 (the base case).
        // if y = 0, a is set to 1 and b is set to 0 and we exit
        // if y = 1, we have found at least one common factor and we cascade up the stack performing the operations below each time until the assertion no longer holds
        a = b_t; // use b_t as the new a
        b = a_t - b_t * (x / y); // subtract from a_t a fraction of b_t, the fraction (x/y), and use this as the new b 
        assert(a * x + b * y == r); // check if r satisfies the relationship, and store result in r if so
        return r;
    }
}

bigint factorize (bigint n) {
    bigint i, j, count, totient; // totient will store euler's totient
    
    FILE *f = fopen("factors.txt", "a+"); // create file (in append mode) for factors
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    
    for (i = 2; i <= n; i++) { // starting from 2 until n
        count = 0; // initialize counter for i          
        if (n % i == 0) { // if i divides n then...              
            fprintf(f, "%lld", i); // store factor
            fprintf(f, "\n");  // go to next line
            while (n % i == 0) { // increment the count, replace n with itself divided by i, and repeat until i does not divide n
                count++; 
                n /= i; // n = n / i, replace n with itself divided by i                
            }
        }           
    }

    rewind(f);
    totient = get_file_lines(f); 
    printf("There are %lld prime factors: \n", totient);
    bigint factors[totient];
    get_factor_file_contents(f, factors);

    if (n < 0) {
        factorize(0 - n);
    }
    fclose(f);
}
        

int main(int datac, char *datav[]) {
    clock_t tic = clock();
    
    #define LINE_MAX 256
    char buf[LINE_MAX];
    char *end;

    char *p; 
    char c[128];
    
    int n_ciph1 = 18923;
    int b_ciph1 = 1261;
    int b_ciph1_inv = 0;
    int a_ciph1;
    // convention is [row][col]
    int ciph1[29][8] = { {12423,11524,7243,7459,14303,6127,10964,16399}, {9792,13629,14407,18817,18830,13556,3159,16647}, {5300,13951,81,8986,8007,13167,10022,17213}, {2264,961,17459,4101,2999,14569,17183,15827}, {12693,9553,18194,3830,2664,13998,12501,18873}, {12161,13071,16900,7233,8270,17086,9792,14266}, {13236,5300,13951,8850,12129,6091,18110,3332}, {15061,12347,7817,7946,11675,13924,13892,18031}, {2620,6276,8500,201,8850,11178,16477,10161}, {3533,13842,7537,12259,18110,44,2364,15570}, {3460,9886,8687,4481,11231,7547,11383,17910}, {12867,13203,5102,4742,5053,15407,2976,9330}, {12192,56,2471,15334,841,13995,17592,13297}, {2430,9741,11675,424,6686,738,13874,8168}, {7913,6246,14301,1144,9056,15967,7328,13203}, {796,195,9872,16979,15404,14130,9105,2001}, {9792,14251,1498,11296,1105,4502,16979,1105}, {56,4118,11302,5988,3363,15827,6928,4191}, {4277,10617,874,13211,11821,3090,18110,44}, {2364,15570,3460,9886,9988,3798,1158,9872}, {16979,15404,6127,9872,3652,14838,7437,2540}, {1367,2512,14407,5053,1521,297,10935,17137}, {2186,9433,13293,7555,13618,13000,6490,5310}, {18676,4782,11374,446,4165,11634,3846,14611}, {2364,6789,11634,4493,4063,4576,17955,7965}, {11748,14616,11453,17666,925,56,4118,18031}, {9522,14838,7437,3880,11476,8305,5102,2999}, {18628,14326,9175,9061,650,18110,8720,15404}, {2951,722,15334,841,15610,2443,11056,2186} }; 

    int n_ciph2 = 31313;
    int b_ciph2 = 4913;
    int ciph2[18][8] = { {6340,8309,14010,8936,27358,25023,16481,25809}, {23614,7135,24996,30590,27570,26486,30388,9395}, {27584,14999,4517,12146,29421,26439,1606,17881}, {25774,7647,23901,7372,25774,18436,12056,13547}, {7908,8635,2149,1908,22076,7372,8686,1304}, {4082,11803,5314,107,7359,22470,7372,22827}, {15698,30317,4685,14696,30388,8671,29956,15705}, {1417,26905,25809,28347,26277,7897,20240,21519}, {12437,1108,27106,18743,24144,10685,25234,30155}, {23005,8267,9917,7994,9694,2149,10042,27705}, {15930,29748,8635,23645,11738,24591,20240,27212}, {27486,9741,2149,29329,2149,5501,14015,30155}, {18154,22319,27705,20321,23254,13624,3249,5443}, {2149,16975,16087,14600,27705,19386,7325,26277}, {19554,23614,7553,4734,8091,23973,14015,107}, {3183,17347,25234,4595,21498,6360,19837,8463}, {6000,31280,29413,2066,369,23204,8425,7792}, {25973,4477,30989,0,0,0,0,0} };
    
    /*#### RSA STEPS (3 STEPS) ####*/
    /*
    Bob publishes n = 11413 and b = 3533 in a directory. Suppose Alice wants to encrypt the plaintext 9726 to send to Bob. She will compute 9726^3533 mod 11413 = 5761
    and send the ciphertext 5761 over the channel. When Bob receives the ciphertext 5761, he uses his secret decryption exponent to compute 5761^6597 mod 11413 = 9726.
    */
    factorize(n_ciph1); // STEP 1) Generate p & q
    FILE *f = fopen("factors.txt", "r+"); // create/open file (in read mode) for factors
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    
    FILE *f2 = fopen("deciphs.txt", "a+"); // create file (in append mode) for decipher vals
    if (f2 == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    
    FILE *f3 = fopen("decihptext.txt", "a+"); // create file (in append mode) for decipher text
    if (f3 == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    
    bigint r, s, t, x, y, z;
    int i, j, k, l, m, n, a_coeff, b_coeff, a2, b2, lines;

    lines = get_file_lines(f);
    bigint factors[lines];
    get_factor_file_contents(f, factors); // p & q now stored in array as factors[0] and factors[1], file can be discarded
    
    printf("\nfactors array contents: %lld\n", factors[0]); // verify array contents
    
    // Given b, we compute b^-1, Bob's secret key,then using p-1 and q-1 we set the result to a (since b^-1 mod (p-1)(q-1) = a)
    t = (factors[0] - 1)*(factors[1] - 1);
    r = gccd(b_ciph1, t, a_coeff, b_coeff);  // STEP 2) computing b^-1 and storing in a_coeff, soln to x*b mod (p-1)(q-1) = 1, x = a_coeff = b^-1 mod (p-1)(q-1)
    if (a_coeff < 0) {
        a2 = t + a_coeff;
        printf("a_coeff = %d changed to %d", a_coeff, a2);
    } else {
        a2 = a_coeff;
        b2 = b_coeff;
    }
    b_ciph1_inv = a2; // storing b^-1 in b_ciph1_inv
    a_ciph1 = b_ciph1_inv % ((factors[0]-1)*(factors[1]-1)); // storing b^-1 mod (p-1)(q-1) in a_ciph1
    //printf("\na = %d\n", a_ciph1);
    //printf("%d\n", (int)(sizeof(ciph1)/sizeof(*ciph1))); // row count => col size (29)
    //printf("%d\n\n", (int)(sizeof(ciph1[29])/sizeof(*ciph1[29]))); // col count => row size (8)
    
    for (i = 0; i < (int)(sizeof(ciph1)/sizeof(*ciph1)); i++) {
        printf("%d\n",ciph1[i][0]); // cols are from 0 to 7 not 0 to 8, rows are from 0 to 28 not 29.
    }
    
    for (i = 0; i < (int)(sizeof(ciph1)/sizeof(*ciph1)); i++) { // iterate through rows (from 0 to col size)
        for (j = 0; j < (int)(sizeof(ciph1[29])/sizeof(*ciph1[29])); j++) { // iterate through cols (from 0 to row size)
            fprintf(f2, " %lld", mod_pow(ciph1[i][j],a_ciph1,n_ciph1));  // STEP 3) computing and storing val of ciph^a mod n in file (comma delimited)
        }
        fprintf(f2, "\n");  // will separate transposed rows with two line breaks
    }

    int deciphs[29][8]; // create 2d array for decipher vals
    
    get_csvfile_contents(f2,deciphs);
    printf("deciphs[0][0] = %d\n", deciphs[0][0]);
    /*#### END RSA STEPS #### */
    
    /*#### TEXT CONVERSION ####*/
    int c1_int10, c1_int26, c2_int10, c2_int26, c3_int10, c3_int26;
    char c1, c2, c3;
    for (i = 0; i < sizeof(deciphs)/sizeof(*deciphs); i++) { // 29
        for (j = 0; j < sizeof(deciphs[29])/sizeof(*deciphs[29]); j++){ // 8
            c1_int26 = deciphs[i][j] % 26; // From base 10, find new 1st order val by taking remainder of num w/ base 26
            c1 = 65 + c1_int26; // converting to ascii char by adding 65 and storing as char
            c2_int10 = (deciphs[i][j] - c1_int26)/26; // subtract 1st order val from base 10 num and div by base 26 to get 2nd order val in base 10
            c2_int26 = c2_int10 % 26; // From base 10, find 2nd order val by taking remainder w/ base 26
            c2 = 65 + c2_int26; // converting to ascii by adding 65 and storing as char
            c3_int10 = (c2_int10 - c2_int26)/26; // subtract 2nd order val from base 10 and div by base 26 to get 3rd order in base 10
            c3_int26 = c3_int10 % 26; // From base 10, find 3rd order val by taking remainder w/ base 26
            c3 = 65 + c3_int26; // converting to ascii by adding 65 and storing as char
            
            fprintf(f3, "%c%c%c", c1, c2, c3); // storing blocks of deciph text in file
        }
        fprintf(f3, "\n");  // go to next line
    }
    printf("txt block1 = %c %c %c\n", c1, c2, c3);
    
    /*#### END TEXT CONVERSION ####*/
    
    printf("deciphs[0][0] = %d\n", deciphs[0][0]);
    
    fclose(f);
    fclose(f2);
    fclose(f3);
    remove("factors.txt");
    remove("deciphs.txt");
    
    clock_t toc = clock();
    printf("Elapsed time: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC); // CLOCKS_PER_SEC defined in time.h
    return 0;
}
