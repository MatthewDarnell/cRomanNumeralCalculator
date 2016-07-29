#include <stdio.h>
#include <string.h>
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

//Convert a char to an enum NUMERALS
static int _charToNUMERALS(const char symbol, enum NUMERALS *out)
{
    switch(symbol) {
      case 'I':
          *out = I;
          break;
      case 'V':
          *out = V;
          break;
      case 'X':
          *out = X;
          break;
      case 'L':
          *out = L;
          break;
      case 'C':
          *out = C;
          break;
      case 'D':
          *out = D;
          break;
      case 'M':
          *out = M;
          break;
      default:
          return -1;
    }
    return 0;
}

//Gets the largest value of a chunk. i.e. CML -> M
//returns the index of the largest, from [0, len)
static int _getLargestValue(const enum NUMERALS *in, size_t len)
{
  int i, retVal = -1;
  enum NUMERALS n = I;
  for(i=0; i<len; i++){
      if(in[i] >= n){
          n = in[i];
          retVal = i;
      }
  }
  return retVal;
}

int stringToEnum(const char *string, enum NUMERALS *out)
{
    int i;
    for(i=0; i<strlen(string); i++){
        _charToNUMERALS(string[i], &(out[i]));
    }
    return 0;
}

int getChunkSize(const enum NUMERALS *n, size_t len)
{
    if(len <= 0){
        return -1;
    }
    int retVal = -1;
    if(len >= 2){
        const enum NUMERALS a = n[0],
                            b = n[1];
        //MCM   XCIX
        if((a > b) || (a == b))
            retVal = 1; //
        else if(a < b)
            retVal = 2;
    }
    else{
        retVal = 1;
    }
    return retVal;
}

int getChunkValue(const enum NUMERALS *n, size_t len)
{
    if(len < 2){
        return n[0];
    }
    else{
        const enum NUMERALS a = n[0], b = n[1];
        if(a >= b){
            return a+b;
        }
        else if(a < b){
            return b-a;
        }
    }
    return -2;
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
        if((temp == num) && (num != 'M')){ //ok for many M values, as it's the max
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
    @param string => the string to parseNonFinalChunk
    @param out    => pointer to returned array of enum NUMERALS
*/
int parseNonFinalChunk(const char *string, enum NUMERALS *out)
{
    size_t len = strlen(string);
    if(len != 3)
        return -1;
    int i;
    for(i=0; i<len; i++){
         _charToNUMERALS(string[i], &(out[i])); //Convert the character to the appropriate enum
    }
    return _getLargestValue(out, len);
}

/*
    @param array => the input array of NUMERALS
    @param len   => then length of array, max value is 3
    @return      => the total value of the chunk. (i.e. MCM ret. 1900), < 0 if invalid array
*/
int analyzeChunk(const enum NUMERALS *array, size_t len)
{
    if(len < 0 || len > 2)
        return -1;

    int retVal = 0;

    int largestIndex = _getLargestValue(array, len);

    //fprintf(stderr, "%d\n", largestIndex);

    if(largestIndex > 0){
        if( (array[largestIndex-1] != array[largestIndex]) && (array[largestIndex-1] > array[largestIndex] / 10)) //CM ok as C=1/10 of M, same with IX. VX, DM NOT ok. MM ok though
            return -2;
    }

    retVal = getChunkValue(array, len);
    return retVal;

}

int analyze(const char *val)
{
    //fprintf(stderr, "Analyzing <%s>\n", val);
    int i = 0, retVal = 0;
    size_t len = strlen(val);

    if(naiveParse(val, len) != 0 ){
        return -1;
    }
    enum NUMERALS array[len];

    for(i=0; i<len; i++)
        _charToNUMERALS(val[i], &(array[i]));
    i = 0;
    int chunk_size = 0, chunk_value = 0, max_chunk_value = 1000; //M = 1000 is the largest value we are handling
    while (i < len){
        chunk_size = getChunkSize(array+i, len-i);
        chunk_value = getChunkValue(array+i, chunk_size);
        if(chunk_value > max_chunk_value){ //Subsequent chunks cannot be larger than previous ones
            return -1;
        }
        if( (chunk_value == max_chunk_value) && (chunk_value == 5 || chunk_value == 50 || chunk_value == 500) ){ //If	the	numeral	is V, L or D you can't have more than one ("D" +	"D"	= "M" not “DD”)
            return -1;
        }
        max_chunk_value = chunk_value;
        //fprintf(stderr, "i=(%d)\tchunk_size= %d\tchunk_value = %d\n", i, chunk_size, chunk_value);
        retVal += chunk_value;
        i += chunk_size;
    }
    //fprintf(stderr, "Value of <%s> = %d\n", val, retVal);

    return retVal;
}

/*
    @param one => roman numeral input
    @param two => roman numeral input
    @return    => the total value of the sum of both inputs
*/
int addNumerals(const char *one, const char *two)
{
    int dOne = analyze(one);
    if(dOne < 0){
        return -1;
    }
    int dTwo = analyze(two);
    if (dTwo < 0){
        return -1;
    }
    //fprintf(stderr, "%s + %s = %d\n", one, two, dOne + dTwo);
    return dOne + dTwo;
}

/*
    @param one => roman numeral input
    @param two => roman numeral input
    @return    => the total value of the difference of both inputs (one-two) , or -1 if negative number or invalid (0 is invalid)
*/
int subtractNumerals(const char *one, const char *two)
{
    int dOne = analyze(one);
    if(dOne < 0){
        return -1;
    }
    int dTwo = analyze(two);
    if (dTwo < 0){
        return -1;
    }
    int subtractVal = dOne - dTwo;
    //fprintf(stderr, "%s + %s = %d\n", one, two, dOne + dTwo);
    return subtractVal > 0 ? (subtractVal) : -1;
}


void enumToChar(const enum NUMERALS n, char *out)
{
    switch(n) {
      case I:
          *out = 'I';
          break;
      case V:
          *out = 'V';
          break;
      case X:
          *out = 'X';
          break;
      case L:
          *out = 'L';
          break;
      case C:
          *out = 'C';
          break;
      case D:
          *out = 'D';
          break;
      case M:
          *out = 'M';
          break;
      default:
          return;
    }
}
