int NumExistInArray(int *arr, size_t size, int random_num);

void CreateRandomArray(int *arr, size_t arr_size, int modulus);

void WrapperCompareInt(char *func_name, int exiting_value, int expected_value);

void WrapperCompareSizet(char *func_name, size_t exiting_value, size_t expected_value);

void WrapperComparetoNULL(char *func_name, void *data);

void WrapperCompareStringsWithStrLen(char *func_name, char *str1, char *str2);
