#ifndef _H_PARSER_
#define _H_PARSER_


enum NUMERALS {
    I = 1,
    V = 5,
    X = 10,
    L = 50,
    C = 100,
    D = 500,
    M = 1000
} ;



/*
    @param numeral = the input string
    @param len     = the length of 'numeral'
    @returns =
        0 for valid
        < 0 for invalid
*/
int stringToEnum(const char *string, enum NUMERALS *out);
int getChunkSize(const enum NUMERALS *n, size_t len);
int getChunkValue(const enum NUMERALS *n, size_t len);
int naiveParse(const char *numeral, size_t len);
int analyzeChunk(const enum NUMERALS *array, size_t len);
int analyze(const char *val);
int parseNonFinalChunk(const char *string, enum NUMERALS *out);
void enumToChar(const enum NUMERALS n, char *out);
#endif //_H_PARSER_
