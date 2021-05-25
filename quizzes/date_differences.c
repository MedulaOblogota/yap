#include <stdio.h>

void CalculateDifference(char *first_date, char *second_date)
{
    static int days_per_month[12] = {31, 28, 31, 30, 31, 30, 31, 30, 30, 31, 30, 31};
    int year_diff = 0;
    int month_diff = 0;
    int day_diff = 0;

    
}

int main()
{
    char first_date[11];
    char second_date[11];

    printf("input first data format DD/MM/YYYY in numbers: ");
    scanf("%s", first_date);

    printf("\n");

    printf("input second data format DD/MM/YYYY in numbers: ");
    scanf("%s", second_date);

    CalculateDifference(first_date, second_date);

}
