#include <stdio.h>

#define AMOUNT 5


void CreateParkingSlots(int *parking)
{
	int i = 0;

	parking[0] = 1;

	for (i = 1; i < AMOUNT; ++i)
	{
		parking[i] = i+1;
	}

	parking[AMOUNT] = -1;
}

void PrintArr(int *parking)
{
	int i = 0;

	for (i = 0; i < AMOUNT + 1; ++i)
	{
		printf("%d: %d\n", i, parking[i]);
	}

}

int Park(int *parking)
{
	int next_parking = 0;
	int current_parking = parking[0];

	if (current_parking < 0)
	{
		printf("minus\n");
		return current_parking;
	}

	next_parking = parking[current_parking];
	parking[current_parking] = 0;
	parking[0] = next_parking;

	return current_parking;
}

int FreeParking(int *parking, int spot)
{
		int temp = 0;

		if (parking[spot] != 0)
		{
			printf("parking is free!");
			return -1;
		}

		temp = parking[0];
		parking[0] = spot;
		parking[spot] = temp;

		return 0;
}

int main()
{
	int parking[AMOUNT + 1];
	int i = 0;
	CreateParkingSlots(parking);

	for (i = 0; i < AMOUNT+3; ++i)
	{
		printf("%d parking: %d\n",i, Park(parking));
	}

	PrintArr(parking);
	FreeParking(parking, 3);
	FreeParking(parking, 1);
	FreeParking(parking, 1);
FreeParking(parking, 2);
FreeParking(parking, 5);
FreeParking(parking, 4);
	for (i = 0; i < AMOUNT+1; ++i)
	{
		printf("%d parking: %d\n",i, Park(parking));
	}
	FreeParking(parking, 3);
	FreeParking(parking, 1);
	FreeParking(parking, 2);
	FreeParking(parking, 5);
	FreeParking(parking, 4);

	for (i = 0; i < AMOUNT; ++i)
	{
		printf("%d parking: %d\n",i, Park(parking));
	}




	return 0;

}
