#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>

//Определить k-ю цифру последовательности
//1 8 27 64 125 216 343 512 729 1000 1331
//в которой выписаны подряд кубы натуральных чисел.

void DetermineDigitOfSequence(void)
{
	int k = 0, i = 1, s = 0;

	printf("Enter a number of digit you want to find: ");

	while (!scanf("%d", &k) || k <= 0)
	{
		printf("Wrong input! Try again :)");
		while (getchar() != '\n');
		printf("\nEnter a number of digit you want to find: ");
	}
	while (getchar() != '\n');

	for (; s < k; i++)
	{
		int x = i * i * i, t = 0;

		while (x > 0)
		{
			t++;
			x /= 10;
		}
		s += t;
	}
	i--; 
	i = i * i * i;
	for (int j = 1; j <= s - k; j++, i /= 10);
	printf("Desired digit is %d", i % 10);
}

int main(int argc, char* argv[])
{
	printf("Enter any key to start or \"-\" to exit.\n");
	char start = _getch();

	while (start != '-')
	{
		DetermineDigitOfSequence();

		printf("\nEnter any symbol to continue or \"-\" to exit ...");
		start = _getch();
		if (start == '-')
		{
			return 0;
		}
		else
			printf("\n\n");
	}
}
