#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <parser.h>
#include <check.h>

/*
    Naive parser (symbol validation, can't have more than 3 consecutive identical symbols)
*/
START_TEST(test_naiveParse)
{
    printf("Naive Parsing Test(s)\n");
    const int num_tests = 5;
    const char *test_cases[] = {
        "IIIVIXLCMMMIVI", //really invalid, but naively ok
        "IIIIVICML",
        "IIVLMCMMXXGII",
        "IVIVIVEIF#IH#FH(#H",
        "MCMXCV"
    };
    const int isValidCase[] = { //lookup table for the validity of each string in test_cases (0=valid, <0=invalid)
        0,
        -1,
        -1,
        -1,
        0
    };
    int i;
    for(i=0; i<num_tests; i++){
        ck_assert_int_eq(naiveParse(test_cases[i], strlen(test_cases[i])), isValidCase[i]);
    }
}
END_TEST


START_TEST(test_getChunkSize)
{
    printf("Get Chunk Size Test(s)\n");
    const int num_tests = 5;
    enum NUMERALS test_cases[5][5];
    stringToEnum("MCM", test_cases[0]);
    stringToEnum("IX", test_cases[1]);
    stringToEnum("IV", test_cases[2]);
    stringToEnum("MC", test_cases[3]);
    stringToEnum("CL", test_cases[4]);

    const size_t lens[5] = {
        3,
        2,
        2,
        2,
        2
    };
    const int isValidCase[] = {
        1,
        2,
        2,
        1,
        1
    };
    int i;
    for(i=0; i<num_tests; i++){
        ck_assert_int_eq(getChunkSize(test_cases[i], lens[i]), isValidCase[i]);
    }
}
END_TEST


START_TEST(test_getChunkValue)
{
    printf("Get Chunk Value Test(s)\n");
    const int num_tests = 5;
    enum NUMERALS test_cases[5][5];
    stringToEnum("MCM", test_cases[0]);
    stringToEnum("IX", test_cases[1]);
    stringToEnum("IV", test_cases[2]);
    stringToEnum("MC", test_cases[3]);
    stringToEnum("CL", test_cases[4]);

    const size_t lens[5] = {
        1,
        2,
        2,
        1,
        1
    };
    const int isValidCase[] = {
        1000,
        9,
        4,
        1000,
        100
    };
    int i;
    for(i=0; i<num_tests; i++){
        ck_assert_int_eq(getChunkValue(test_cases[i], lens[i]), isValidCase[i]);
    }
}
END_TEST

START_TEST(test_analyze)
{
    printf("Analyze Roman Numeral String Test(s)\n");
    const int num_tests = 10;
    const char *test_cases[10] = {
        "MCM",
        "MMMMCMXCIX",
        "IIII",
        "IIIVIXLCMMMIVI",
        "MDCIX",
        "LXX",
        "CM",
        "XCV",
        "MCD",
        "LII"
    };

    const int isValidCase[] = {
        1900,
        4999,
        -1,
        -1,
        1609,
        70,
        900,
        95,
        1400,
        52
    };
    int i;
    for(i=0; i<num_tests; i++){
        ck_assert_int_eq(analyze(test_cases[i]), isValidCase[i]);
    }
}
END_TEST
//Suite for parsing roman numeral values
Suite *parsing_suite()
{
    Suite *s;
    TCase *tc;

    s = suite_create("Parsing");
    tc = tcase_create("Core");

    tcase_add_test(tc, test_naiveParse);
    tcase_add_test(tc, test_getChunkSize);
    tcase_add_test(tc, test_getChunkValue);
    tcase_add_test(tc, test_analyze);
    suite_add_tcase(s, tc);

    return s;
}

#ifdef PARSING
int main()
{
    int dFailed = 0;
    Suite *suite;
    SRunner *sr;

    suite = parsing_suite();
    sr = srunner_create(suite);
    srunner_run_all(sr, CK_NORMAL);
    dFailed = srunner_ntests_failed(sr);
    srunner_free(sr);


    return dFailed==0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
#endif
