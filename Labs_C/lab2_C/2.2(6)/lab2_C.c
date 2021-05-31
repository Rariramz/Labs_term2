#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define PI 3.1415926535

long long factorial(long long);
void sinByTaylorExpansion(double, double);
double sinByTaylorExpansionRec(double, int *, double, double);

long long factorial(long long a)
{
	if (a == 0)
		return 1;
	else
		return a * factorial(a - 1);
}

double myAbs(double a) {
	if (a < 0)
		return -a;
	return a;
}

double sinByTaylorExpansionRec(double x, int * nRec, double sum, double e)
{
	if (myAbs(sin(x) - sum) < e)
		return sum;

	sum += pow(x, 2 * *nRec - 1) / factorial(2 * *nRec - 1) * pow(-1, *nRec - 1);
	(*nRec)++;
	return sinByTaylorExpansionRec(x, nRec, sum, e);
}

void sinByTaylorExpansion(double x, double e)
{
	double sumCycle = 0, sumRec = 0;
	int nCycle = 1, nRec = 1;

	for (nCycle; myAbs(sin(x) - sumCycle) > e; nCycle++)
		sumCycle += pow(x, 2 * nCycle - 1) / factorial(2 * nCycle - 1) * pow(-1, nCycle - 1);

	sumRec = sinByTaylorExpansionRec(x, &nRec, 0, e);

	printf("The sin by the Taylor expansion formula is %lf\n", sumCycle);
	printf("The resulting calculation error is %lf\n", myAbs(sin(x) - sumCycle));
	printf("n = %d\n", nCycle);

	/*printf("The sin by the Taylor expansion formula is %lf\n", sumRec);
	printf("The resulting calculation error is %lf\n", myAbs(sin(x) - sumRec));
	printf("n = %d\n", nRec);*/
}

int main(int argc, char* argv[])
{
	printf("Enter any key to start or \"-\" to exit.\n");
	char start = _getch();

	while (start != '-')
	{
		double X = 0, x = 0, e = 0;

		printf("Enter x in degrees\nx = ");

		while (!scanf("%lf", &X))
		{
			printf("Wrong input! Try again :)\n");
			while (getchar() != '\n');
			printf("x = ");
		}
		while (getchar() != '\n');

		printf("Enter epsilon\ne = ");

		while (!scanf("%lf", &e) || !(e > 0 && e < 1))
		{
			printf("Wrong input! Try again :)\n");
			if (!(e > 0 && e < 1))
				printf("epsilon must be greater than 0 and less than 1\n");
			while (getchar() != '\n');
			printf("e = ");
		}
		while (getchar() != '\n');

		x = X * PI / 180;      //перевод в радианы
		x = fmod(x, 2 * PI);

		printf("sin(%lf) is %lf\n", X, sin(x));
		printf("Epsilon is %lf\n", e);
		sinByTaylorExpansion(x, e);
	
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
