#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Задача 4.1.27
// Поздравления.По заданному в массиве списку фамилий напечатать
// каждому упомянутому в списке поздравление к определенному
// празднику.Чтобы избежать шаблона, перечень желаемых благ
// выбирать как случайное подмножество из заготовленного списка
// (например, здоровья, счастья, продвижения по службе, долголетия и
// т.д.).Для универсальности программы сделать переменным и
// название праздника.

int main()
{
	const char* names[] = { "Ann", "Mary", "Kate", "Emily", "Alexander", "Ivan", "Eugene" };
	const char* wishes[] = { "happiness", "great health", "well-being", "longevity", "career growth", "more joy",
		"vivid impressions", "love", "good luck" };
	char* holidays[] = { "birthday", "New Year", "Xmas", "Easter", "wedding", "laboratory-check day" };

	int namesCount = sizeof(names) / sizeof(char*);
	int wishesCount = sizeof(wishes) / sizeof(char*);
	int holidaysCount = sizeof(holidays) / sizeof(char*);

	srand(time(NULL));

	for (int i = 0; i < namesCount; i++)
	{
		int indexOfRandomWish = rand() % wishesCount;
		int indexOfRandomHoliday = rand() % holidaysCount;

		printf("\n~Dear ");
		for (int j = 0; names[i][j] != '\0'; j++)
			printf("%c", names[i][j]);

		printf("! On this happy day - ");
		for (int j = 0; holidays[indexOfRandomHoliday][j] != '\0'; j++)
			printf("%c", holidays[indexOfRandomHoliday][j]);

		printf(" I wish you ");
		for (int j = 0; j < wishes[indexOfRandomWish][j] != '\0'; j++)
			printf("%c", wishes[indexOfRandomWish][j]);

		printf(". Be happy!~");
	}
	printf("\n");

	return 0;
}
