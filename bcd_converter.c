/*
*
*	@author Albert Pernia Vazquez
*
*	GitHub account: Albertpv95
*/
#include <stdio.h>
#include <stdlib.h>

#define DIMENSION(x) (sizeof(x) / sizeof((x)[0]))

/*A matrix or "conversion table" from decimal to binary */
const int dec_to_binary[10][4] = {	// 10 --> we convert digits from 0 to 9   | 4 --> this digits are represented with 4 bits

	{0, 0, 0, 0},	// 0
	{0, 0, 0, 1},	// 1
	{0, 0, 1, 0},	// 2
	{0, 0, 1, 1},	// 3
	{0, 1, 0, 0},	// 4
	{0, 1, 0, 1},	// 5
	{0, 1, 1, 0},	// 6
	{0, 1, 1, 1},	// 7
	{1, 0, 0, 0},	// 8
	{1, 0, 0, 1}	// 9
};

typedef struct {

	size_t size;		// the dimension of the array
	int *number;		// in binary format

} BCD;


/**
* Function: calculate_length
* --------------------------
*
*	Counts the total of digits of a number
*
*	@param : the number which we want to know the total of digits
*
*	@return : the total of digits of a number
*/
int calculate_length(int number) {
	int tmp = number;
	int length = 0;

	while(tmp != 0) {

		length++;
		tmp /= 10;
	}

	return length;
}

/**
* Function: decimal_to_bcd
* ------------------------
*
*	Converts a number in decimal format to bcd.
*
*	@param number : the number to convert
*	
*	@return : a BCD type containing the number converted and the size of it
*/
BCD decimal_to_BCD(int number) {
	int length, i, j, bit;				// the digits of the number to convert, each digit equals 4 bits
	int *digits = NULL;					//  each digit of the number to convert
	int aux;
	BCD bcd;							// the bcd type to return

	length = calculate_length(number);	
	bcd.size = (size_t) length * 4;		// each number equals 4 bits, so the bcd size will be the digits of the number * 4

	bcd.number = (int*) malloc(sizeof(int)*(length*4));
	digits = (int*) malloc(sizeof(int)*length);

	if(bcd.number != NULL && digits != NULL) {
	
		for(i = length - 1; i >= 0; i--) {		// we start from the end to get the digits in order
			
			digits[i] = number % 10;
			number /= 10;
		}

		number = 0;						// reuse of number, but know as a counter (4 by 4) 

		for(i = 0; i < length; i++) {	// for each digit, we assign the binary conversion of a value between 0 and 9 to the bcd

			bit = 0;
			
			for(j = 0; j < 4; j++) { 	// we have the data in a matrix so we need to go over the 4 values

				bcd.number[number + j] = dec_to_binary[digits[i]][bit];
				bit++;
			}

			number += 4;
		}
	}

	free(digits);

	return bcd;
}

/*
* Procedure : print_bcd
* ---------------------
*
*	Prints a bcd number in binary format.
*
*	@param bcd : the number to print
*/
void print_bcd(BCD bcd) {
	int i;
	char *str = (char*) malloc(sizeof(bcd.size+1));

	if(str != NULL) {
	
		for(i = 0; i < bcd.size; i++) {

			str[i] = bcd.number[i] + '0'; // itoa
		}
	}

	printf("%s\n", str);

	free(str);
}

/*
* Function : bcd_to_string
* ------------------------
*
*	Takes a bcd number into a string
*
*	@param bcd : the number to convert 
*
*	@return : the number in string format
*/
char* bcd_to_string(BCD bcd) {
	int i;
	char *str = (char*) malloc(sizeof(bcd.size+1));

	if(str != NULL) {
	
		for(i = 0; i < bcd.size; i++) {

			str[i] = bcd.number[i] + '0'; // itoa
		}
	}

	return str;
}

int get_multiple_of_two(int m) {
	int i, value = 1;

	for(i = 0; i < m; i++) {

		value *= 2;		
	}

	return value;
}


/**
* Function: bcd_to_decimal
* ------------------------
*
*	Converts a bcd number into the decimal format.
*
*	@param bcd : the bcd number to convert
*
*	@return : the bcd number converted to decimal
*/
int bcd_to_decimal(BCD bcd) {
	int i;
	int mult = 0, value = 0;

	for(i = bcd.size - 1; i >= 0; i--) {

		value += bcd.number[i] * get_multiple_of_two(mult);
		mult++;
	}

	return value;
}


int main(void) {

	int number = 0;
	BCD bcd;

	do {

		printf("Number? ");
		scanf("%d", &number);

		bcd = decimal_to_BCD(number);

		if(bcd.number != NULL) {
		
			print_bcd(bcd);
			printf("BCD to decimal: %d\n", bcd_to_decimal(bcd));
		}

	} while(number >= 0);

	return 0;

}
