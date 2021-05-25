#ifndef TEST_H_
#define TEST_H_

#include <stdio.h> /* fprintf */

#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define RESET "\033[0m"

typedef enum {TEST_FAIL, TEST_PASS} TestResult;

#define REQUIRE(cond) \
do{\
	if (!(cond)) {\
		fprintf(stderr, RED"\nAssertion failed at %s : %d %s" RESET, \
			__FILE__, __LINE__,#cond); \
		return TEST_FAIL;\
	}\
}while(0)


#define RUN_TEST(test) \
do { \
	fprintf(stderr, "Running "#test"... \n"); \
	if (test() == TEST_PASS) { \
		fprintf(stderr, GRN"[Ok]\n" RESET); \
	} else { \
		fprintf(stderr, RED"[Failed]\n" RESET); \
	} \
} while(0)

#define SIZEOFARR(arr) (sizeof(arr)/sizeof(arr[0]))
#endif /* TEST_H_ */
