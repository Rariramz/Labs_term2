#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

// Задача 4.2.27
// Вычислить значения арифметических выражений, записанных в
// файл.Имя переменной – одна буква.Значения переменных в виде
// a=3.1415, b=-37.2 и т.д.записаны во второй файл. Вывести на
// печать сами выражения и их вычисленные значения.

double stod(const char* s)
{
	int point = 0;
	double result = 0, fact = 1;
	if (*s == '-')
	{
		fact = -1;
		s++;
	}

	for (point; *s; s++)
	{
		if (*s == '.')
		{
			point = 1;
			continue;
		}

		int digit = *s - '0';
		if (digit >= 0 && digit <= 9)
		{
			if (point)
				fact /= 10;

			result = result * 10 + (double)digit;
		}
	}
	return result * fact;
}

int main()
{
	FILE* arithmeticExpressions = fopen("arithmeticExpressions.txt", "r");
	FILE* variableValues = fopen("variableValues.txt", "r");
	if (arithmeticExpressions == NULL || variableValues == NULL)
	{
		printf("\nFile is not found :<\n");
		return 0;
	}

	double** vals = (double**)calloc(100, sizeof(double*));    //Массив значений
	if (vals == NULL)
	{
		printf("\nNot enough memory :<");
		return 0;
	}
	for (int i = 0; i < 100; i++)
	{
		vals[i] = (double*)calloc(100, sizeof(double));
		if (vals[i] == NULL)
		{
			printf("\nNot enough memory :<");
			return 0;
		}
	}

	int row = 0;
	while (!feof(variableValues))
	{
		char s[100];
		int col = 0;
		fgets(s, 30, variableValues);
		for (int i = 0; s[i] != '\n'; i++)
		{
			if (s[i] == ' ' || s[i] == '\t' || s[i] == ',') continue;
			if (s[i] == '.' || s[i] == '-' || (s[i] >= '0' && s[i] <= '9'))
			{
				char* box = (char*)calloc(100, sizeof(char));
				int len = 0;
				while (s[i] == '.' || s[i] == '-' || (s[i] >= '0' && s[i] <= '9'))
				{
					box[len++] = s[i];
					i++;
				}
				vals[row][++col] = stod(box);
			}
			if (s[i] == '\n')
				i--;
		}
		vals[row][0] = col;               //vals[row][0] хранит количество чисел в строке
		row++;
	}
	int rows = row - 1;

	/*for (int i = 0; i < rows; i++)
	{
		for (int j = 1; j <= (int)vals[i][0]; j++)
		{
			printf("%f ", vals[i][j]);
		}
		printf("\n");
	}*/

	row = 0;
	while (!feof(arithmeticExpressions) && row < rows)
	{
		char s[100];
		int col = 0;
		double result = 0;
		result = vals[row][++col];
		printf("\n");
		printf("%.2f ", vals[row][col]);
		fgets(s, 30, arithmeticExpressions);
		for (int i = 0; s[i] != '\n'; i++)
		{
			if (s[i] == ' ' || s[i] == '\t' || s[i] == ',') continue;
			if (s[i] >= 'a' && s[i] <= 'z')
			{
				i++;
				if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%')
				{
					printf("%c ", s[i]);
					switch (s[i])
					{
					case '+':
						result += vals[row][++col];
						printf("%.2f ", vals[row][col]);
						break;
					case '-':
						result -= vals[row][++col];
						printf("%.2f ", vals[row][col]);
						break;
					case '*':
						result *= vals[row][++col];
						printf("%.2f ", vals[row][col]);
						break;
					case '/':
						result /= vals[row][++col];
						printf("%.2f ", vals[row][col]);
						break;
					case '%':
						result = fmod(result, vals[row][++col]);
						printf("%.2f ", vals[row][col]);
						break;
					}
				}
				else
				{
					if (s[i] == '\n')
					{
						printf("= %.2f", result);
						row++;
						i--;
					}
				}
			}
		}
	}
	printf("\n");

	for (int i = 0; i < rows; i++)
		free(vals[i]);
	free(vals);

	fclose(arithmeticExpressions);
	fclose(variableValues);
	return 0;
}
