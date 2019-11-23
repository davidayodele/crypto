/*	Title: shift.c
* 	Author: David Ayodele
* 	Date: 1/24/19
*
*
* Refrences:
* [1] http://forums.devshed.com/programming-42/loop-remove-whitespace-char-127422.html 
* [2] https://stackoverflow.com/questions/19896645/how-to-check-if-a-string-is-a-lettera-z-or-a-z-in-c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 256 // Size of String allowed
#define CHAR_SIZE 4 // Size of char

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void nospace(char str[]){
	int i;
	for(i=0; str[i+1]!='\0'; i++)
	    while(isspace(str[i])) {
	    str[i] = str[i+1];
	    i++;
	}
}

int main(int argc, char *argv[]) {
	
	int x, i, j, k;
	char str[MAX_SIZE];
	char str2[MAX_SIZE];
	char str3[MAX_SIZE];
	char str4[MAX_SIZE];
	
	char c[4];
	char c1[4];
	char c2[4];
	int c3;
	
	memset(str,NULL,sizeof(str));
	memset(str2,NULL,sizeof(str2));
	memset(str3,NULL,sizeof(str3));
	
	printf("Enter the plaintext: ");
	gets(str);
	strupr(str);
	nospace(str);
	
	printf("Enter 'D' or 'E' (Decrypt or Encrypt): ");
	fgets(str2, sizeof(str2), stdin);
	while ((strncmp(str2, "D", 1) != 0) && (strncmp(str2, "E", 1) != 0) || strlen(str2) > 2) {
		printf("Error! Please enter 'D' or 'E' (Decrypt or Encrypt): ");
    	fgets(str2, sizeof(str2), stdin);
	}
	
	
	printf("Enter the key (capital letter only): ");
	fgets(str3, sizeof(str3), stdin);
	c3 = (int)str3[0];
	while (isupper(c3) == 0 || strlen(str3) > 2) {
		memset(str3,NULL,sizeof(str3));
		printf("Error! Please enter a capital letter only (you entered: %c ): ", c3);
		fgets(str3, sizeof(str3), stdin);
		c3 = (int)str3[0];
	}
	
	k = c3 - 64;
	for (i = 0; i < strlen(str); i++) {
		x = (int)str[i] - 64; //Convert from ascii to base 26
		
		if (strncmp(str2, "E", 1) == 0){ // If mode is encrypt, shift positive
			j = (int)(x + k)%26;	
		}
		else if (strncmp(str2, "D", 1) == 0){ // If mode is decrypt, shift negative
			j = (int)(x - k)%26;
		}
		str4[i] = j + 64; //Convert from base 26 back to ascii
		printf("\nj[%d] = %d\n", i, j);
		printf("\nx[%d] = %d\n", i, x);
	}
	
	printf("\nPlainext = %s", str);
	printf("\nMode = %s", str2);
	printf("Key = %d/%s", c3, str3);
	printf("\nCiphertext = %s", str4);
	
	return 0;
}
