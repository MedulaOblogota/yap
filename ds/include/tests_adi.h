#ifndef TEST_H
#define TEST_H

#include <stdio.h> /* fprintf */
#include <string.h>

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define CYN "\x1B[36m"
#define RESET "\x1B[0m"
#define YEL  "\033[33m"
#define BOLD   "\033[1m\033[30m"

#define MAX_MSG_LEN 100

typedef enum {FAILED, PASSED} test_res_t;

test_res_t Check(int condition, char *msg, int only_error)
{
    char success_msg[MAX_MSG_LEN] = "Success in ";
    char error_msg[MAX_MSG_LEN] = "Error in ";

    if (condition)
    {
        if (!only_error)
        {
            strcat(success_msg, msg);

            if (strlen(success_msg) > MAX_MSG_LEN)
            {
                puts("Msg is too long! Aborting");
                return (FAILED);
            }
            printf(GRN "%s\n" RESET, success_msg);
        }

        return (PASSED);
    }
    else
    {
        strcat(error_msg, msg);
        if (strlen(success_msg) > MAX_MSG_LEN)
        {
            puts("Msg is too long! Aborting");
            return (FAILED);
        }
        printf(RED "%s\n" RESET, error_msg);

        return (FAILED);
    }
}

static int ResCmp(int expected_res, int res)
{
    return (expected_res == res);
}

#endif /*TEST_H*/
