/***************************************************************
Name: Nathan Festoso
Date : December 10, 2017
***************************************************************/

#include <stdio.h>
#include <string.h>

/***************************************************************
Function name:		Main
Purpose:		Run simulator
In parameters:		-
Out parameters:		int
Version:		1.0
Author:			Nathan Festoso
***************************************************************/
int main() {
	float num;
	int option;
	int done = 0;
	// Calculation variables
	unsigned char* bytes;
	char* binary[33];
	unsigned int exponent;

	do {
		// Menu
		printf("1 - Convert a float\n");
		printf("2 - Quit\n");
		scanf_s("%d", &option);

		if (option == 2) {
			// Quit
			done++;
		}
		else {
			// Get number from user
			printf("\nPlease enter the number to convert: ");
			scanf_s("%f", &num);

			// Float
			printf("\nFloat number is %.6e", num);
			
			// Binary
			bytes = (unsigned char*)&num;
			printf("\nBinary: ");
			
			int b = 0;
			for (int i = 3; i >= 0; i--) {
				int mask = 128;
				for (int j = 1; mask != 0; j++) {
					if ((bytes[i] & mask) == 0) {
						printf("0");
						binary[b] = "0";
					}
					else {
						printf("1");
						binary[b] = "1";
					}
					mask = mask >> 1;
					if (j % 4 == 0) printf(" ");
					b++;
				}
			}
			
			// Big endian
			printf("\nBig-endian Hex: ");
			for (int i = 3; i >= 0; i--) {
				printf("%02x ", bytes[i]);
			}
				
			// Little endian
			printf("\nLittle-endian Hex: ");
			for (int i = 0; i < 4; i++) {
				printf("%02x ", bytes[i]);
			}
			
			// Exponent
			unsigned int* expNum = (unsigned int*)&num;
			exponent = *expNum & 0x7f800000;
			exponent >>= 23;
			printf("\nExponent = %d", exponent);

			// Mantissa
			int wholeNumber = (int)num;
			//double decimal = num - wholeNumber;
			double decimal = 0.5;
			double mantissa = 1.0;
			for (int i = 9; i < 33; i++) {
				if (binary[i] == "1") {
					mantissa += decimal;
				}
				decimal /= 2;
			}
			printf("\nNormalised mantissa (including the hidden bit) = %.7f\n\n", mantissa);
		}

	} while (!done);

	return 0;
}
