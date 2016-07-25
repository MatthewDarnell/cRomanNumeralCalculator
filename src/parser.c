#include <stdio.h>

#include <stdlib.h>
#include "parser.h"

const short NUM_VALID_SYMBOLS = 7;
const char valid_symbols[] = {
    'I',
    'V',
    'X',
    'L',
    'C',
    'D',
    'M'
};

enum NUMERALS {
    I = 1,
    V = 5,
    X = 10,
    L = 50,
    C = 100,
    D = 500,
    M = 1000
} ;

static int _isValidSymbol(const char a)
{
    int i;
    for(i=0; i<NUM_VALID_SYMBOLS; i++){
        if(a == valid_symbols[i]){
            return 0;
        }
    }
    return -1;
}

/*
	Parses a roman numeral string for most basic validity checks

    @param numeral = the input string
    @param len     = the length of 'numeral'
    @returns =
        0 for valid
        < 0 for invalid
*/
int naiveParse(const char *numeral, size_t len)
{
    //ISVALID -> checks 3 consecutive symbol max, correct symbol set
    int i;
    unsigned short duplicate_count = 0;
    char temp = numeral[0];
    for(i=0; i<len; i++){
        char num = numeral[i];
        if(_isValidSymbol(num) < 0){
            //fprintf(stderr, "Invalid Number! (%s)\n", numeral);
            return -1;
        }
        if(temp == num){
            duplicate_count++;
            if(duplicate_count > 3){
                //fprintf(stderr, "Invalid Number! (%s)\n", numeral);
                return -1;
            }
        }
        else{
            temp = num;
            duplicate_count = 0;
        }
    }
    //printf("<%s> is a valid Roman Numeral\n", numeral);
    return 0;
}

	/*
		Algorithm (after confirming basic isValidNumeral() == 0):
			Read 3 symbols at a time
				Left symbol should be Most significant
				If not the final chunk, can't have more than 1 addition/subtraction value:
					MCM => M is msb, CM is subtraction 1000 - 100 => 1900
					LXI => INVALID: LX is 50 + 60 + 1
				Next 2 symbols can be added (XI) or subtracted (IX) notation
			Repeat, subsequent 3 symbol chunks should never have a most significat symbol larger than a previous chunk
			If the final chunk, subtraction value has to be GREATER than the addition value AND
			the subtraction value must be less than HALF of the middle, largest value:
				VXI => invalid (6) V = 1/2 of X
				LCV	=> invlalid (55) L = 1/2 of C
				CMX => valid (910) C = 1/10 of M
	

*/
