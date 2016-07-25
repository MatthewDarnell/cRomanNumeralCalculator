#include <stdio.h>
#include <stdlib.h>
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

//Suite for parsing roman numeral values
Suite *parsing_suite()
{
	Suite *s;
	TCase *tc;

	s = suite_create("Parsing");
	tc = tcase_create("Core");

	tcase_add_test(tc, test_naiveParse);
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






