#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <parser.h>
#include <check.h>


//int stringToEnum(const char *string, enum NUMERALS *out)
START_TEST(test_stringToEnum)
{
    printf("String to Enum Test(s)\n");

    enum NUMERALS nums[3];
    memset(nums, 0, 3 * sizeof(enum NUMERALS));
    stringToEnum("MCM", nums);
    ck_assert(nums[0] = 1000 && nums[1] == 100 && nums[2] == 1000);

    memset(nums, 0, 3 * sizeof(enum NUMERALS));
    stringToEnum("XVI", nums);
    ck_assert(nums[0] = 10 && nums[1] == 5 && nums[2] == 1);

    memset(nums, 0, 3 * sizeof(enum NUMERALS));
    stringToEnum("IV", nums);
    ck_assert(nums[0] = 1 && nums[1] == 5);

    memset(nums, 0, 3 * sizeof(enum NUMERALS));
    stringToEnum("DLM", nums);
    ck_assert(nums[0] = 500 && nums[1] == 50 && nums[2] == 1000);

    memset(nums, 0, 3 * sizeof(enum NUMERALS));
    stringToEnum("IVX", nums);
    ck_assert(nums[0] = 1 && nums[1] == 5 && nums[2] == 10);
}
END_TEST

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
    const int num_tests = 17;
    const char *test_cases[17] = {
        "MCM",
        "MMMMCMXCIX",
        "IIII",
        "IIIVIXLCMMMIVI",
        "MDCIX",
        "LXX",
        "CM",
        "XCV",
        "MCD",
        "LII",
        "II",
        "VV",
        "XX",
        "LL",
        "CC",
        "DD",
        "MM"
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
        52,
        2,
        -1,
        20,
        -1,
        200,
        -1,
        2000
    };
    int i;
    for(i=0; i<num_tests; i++){
        ck_assert_int_eq(analyze(test_cases[i]), isValidCase[i]);
    }
}
END_TEST

START_TEST(test_addNumerals)
{
    printf("Roman Numeral Addition Test(s)\n");

    ck_assert_int_eq(addNumerals( "MMMMCMXCIX" , "I" ), 5000 );
    ck_assert_int_eq(addNumerals( "XCIX" , "CM" ), 999 );
    ck_assert_int_eq(addNumerals( "XL" , "X" ), 50 );
    ck_assert_int_eq(addNumerals( "MDC" , "XCVI" ), 1696 );
    ck_assert_int_eq(addNumerals( "XXXVII" , "X" ), 47 );
    ck_assert_int_eq(addNumerals( "XIV" , "MC" ), 1114 );
    ck_assert_int_eq(addNumerals( "III" , "V" ), 8 );
    ck_assert_int_eq(addNumerals( "XXV" , "L" ), 75 );
    ck_assert_int_eq(addNumerals( "VII" , "XV" ), 22 );
    ck_assert_int_eq(addNumerals( "X" , "X" ), 20 );
    ck_assert_int_eq(addNumerals( "XLV" , "V" ), 50 );
    ck_assert_int_eq(addNumerals( "MMXVI" , "V" ), 2021);
    ck_assert_int_eq(addNumerals( "MCMXCI" , "IX" ), 2000 );
    ck_assert_int_eq(addNumerals( "I" , "I" ), 2);
    ck_assert_int_eq(addNumerals( "V" , "V" ), 10 );

}
END_TEST

START_TEST(test_subtractNumerals)
{
    printf("Roman Numeral Subtraction Test(s)\n");

    ck_assert_int_eq(subtractNumerals( "MMMMCMXCIX" , "I" ), 4998 );
    ck_assert_int_eq(subtractNumerals( "CM" , "XCIX" ), 801 );
    ck_assert_int_eq(subtractNumerals( "XL" , "X" ), 30 );
    ck_assert_int_eq(subtractNumerals( "MDC" , "XCVI" ), 1504 ); //1600 - 96
    ck_assert_int_eq(subtractNumerals( "XXXVII" , "X" ), 27 );
    ck_assert_int_eq(subtractNumerals( "MC" , "XIV" ), 1086 );
    ck_assert_int_eq(subtractNumerals( "V" , "III" ), 2 );
    ck_assert_int_eq(subtractNumerals( "L" , "XXV" ), 25 );
    ck_assert_int_eq(subtractNumerals( "VII" , "XV" ), -1 );
    ck_assert_int_eq(subtractNumerals( "X" , "X" ), -1 );
    ck_assert_int_eq(subtractNumerals( "XLV" , "V" ), 40 );
    ck_assert_int_eq(subtractNumerals( "MMXVI" , "V" ), 2011);
    ck_assert_int_eq(subtractNumerals( "MCMXCI" , "IX" ), 1982 );
    ck_assert_int_eq(subtractNumerals( "I" , "I" ), -1);
    ck_assert_int_eq(subtractNumerals( "V" , "V" ), -1 );

}
END_TEST
//Suite for parsing roman numeral values
Suite *parsing_suite()
{
    Suite *s;
    TCase *tc;

    s = suite_create("Parsing");
    tc = tcase_create("Core");

    tcase_add_test(tc, test_stringToEnum);
    tcase_add_test(tc, test_naiveParse);
    tcase_add_test(tc, test_getChunkSize);
    tcase_add_test(tc, test_getChunkValue);
    tcase_add_test(tc, test_analyze);
    tcase_add_test(tc, test_addNumerals);
    tcase_add_test(tc, test_subtractNumerals);
    suite_add_tcase(s, tc);

    return s;
}

#ifdef PARSING
int main(int argc, char *argv[])
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
