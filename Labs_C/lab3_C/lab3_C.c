#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <math.h>

//Массив a(n, m) состоит из нулей и единиц.Требуется удалить из него
//совпадающие строки, а оставшиеся упорядочить по возрастанию
//двоичных чисел, формируемых из данных соответствующей строки.

int** a;
int n, m;

void FillArrayWithZerosAndOnes(void);
void DeleteDuplicateRows(void);
void ChangeElementsOrder(void);
void ShowArray(void);
void EnterAndCheckInput(int* a);

int main(void)
{
	printf("Enter a number of array rows: ");
	EnterAndCheckInput(&n);
	printf("Enter a number of array colomns: ");
	EnterAndCheckInput(&m);

	a = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
		a[i] = (int*)malloc(m * sizeof(int));

	printf("Fill the array with elements - numbers 0 or 1:\n");
	FillArrayWithZerosAndOnes();

	printf("\nInitial array:\n");
	ShowArray();

	DeleteDuplicateRows();
	printf("\nThe array after deleting duplicate rows:\n");
	ShowArray();
	if (n == 0)
		printf("[Nothing to print, sorry, man]\n");

	ChangeElementsOrder();
	printf("\nThe array after ascending sort:\n");
	ShowArray();
	if (n == 0)
		printf("[Still nothing to print, man]\n");

	for (int i = 0; i < n; i++)
		free(a[i]);
	free(a);

	return 0;
}

void EnterAndCheckInput(int* a)
{
	while (!scanf("%d", &(*a)) || *a <= 0)
	{
		printf("Wrong input! Try again :)\n");
		while (getchar() != '\n');
		printf("Enter a number of array rows: ");
	}
	while (getchar() != '\n');
}

void FillArrayWithZerosAndOnes(void)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			printf("Enter an element: ");
			while (!scanf("%d", &a[i][j]) || !(a[i][j] == 1 || a[i][j] == 0))
			{
				printf("Array elements can only be 1 or 0. Try again :)\n");
				while (getchar() != '\n');
				printf("Enter an element: ");
			}
			while (getchar() != '\n');
		}
}

void DeleteDuplicateRows(void)
{
	int duplicate = 1, duplicateMain = 0;
	int numberOfDuplicateRows = 0;

	for (int i = 0; i < n - 1; i++)
	{
		duplicateMain = 0;
		for (int I = i + 1; I < n; I++)
		{
			duplicate = 1;
			for (int j = 0; j < m; j++)
			{
				if (a[i][j] != a[I][j])
				{
					duplicate = 0;
				}
			}
			if (duplicate == 1)
			{
				a[I][0] = 3;     //если строки совпали, заменяю первый элемент одной из этих строк на 3
				duplicateMain = 1;
			}
		}
		if (duplicateMain == 1)  //Main - строка, с которой сравниваются последующие. Ее тоже удаляем
		{
			numberOfDuplicateRows++;
			a[i][0] = 3;
		}
	}

	for (int k = 0; k <= numberOfDuplicateRows; k++)
	{
		for (int i = 0; i < n; i++)  //переписываем массив
		{
			if (a[i][0] == 3)
			{
				n--;
				for (int j = i; j < n; j++)
					a[j] = a[j + 1];
				a[n] = NULL;
			}
		}
	}
}

void ChangeElementsOrder(void)
{
	int** temp = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
		temp[i] = (int*)malloc(1 * sizeof(int));

	for (int i = 0; i < n; i++)
		temp[i][0] = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0, k = m - 1; j < m; j++, k--)
			temp[i][0] += a[i][j] * (int)pow(10, k);

	for (int i = 0; i < n - 1; i++)
	{
		for (int k = i + 1; k < n; k++)
		{
			if (temp[i][0] > temp[k][0])
			{
				int buf = temp[i][0];
				temp[i][0] = temp[k][0];
				temp[k][0] = buf;
			}
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0, k = m - 1; j < m; j++, k--)
		{
			int step = (int)pow(10, k);
			a[i][j] = temp[i][0] / step;
			temp[i][0] %= step;
		}

	for (int i = 0; i < n; i++)
		free(temp[i]);
	free(temp);
}

void ShowArray(void)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%d\t", a[i][j]);
		printf("\n");
	}
}
