#include <stdio.h>

#include "test_shlomo.h"

double Calculate(char *input, int *err);

int main()
{
    int err = 0;
    int result = 0;

    result = (Calculate("5+8*[(3+2)]", &err) == 45);
    PrintResult("45", result, __LINE__);

    result = (Calculate("5 + 8 * [(3+2)]", &err) == 45);
    PrintResult("45", result, __LINE__);

    result = (Calculate("5 + 8 * ][(3+2)]", &err) == 0);
    PrintResult("no pair", result, __LINE__);

    result = (Calculate("8-(3*-2)", &err) == 14);
    PrintResult("no pair", result, __LINE__);

    result = (Calculate("5^8*[(3+2)]", &err) == 1953125);
    PrintResult("1953125", result, __LINE__);

    result = (Calculate("5^8*{{[(3+2)]}}", &err) == 1953125);
    PrintResult("1953125", result, __LINE__);

    Calculate("5 / 0", &err);
    result = (err == -4);
    PrintResult("math error", result, __LINE__);

    Calculate("[5 / 1)", &err);
    result = (err == -2);
    PrintResult("math error", result, __LINE__);

    result = PrintResult(NULL, 1, 1);
    TestSuccess(result);

    return 0;
}
