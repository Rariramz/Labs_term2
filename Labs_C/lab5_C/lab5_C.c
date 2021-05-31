#include "ListFuncs.h"

/*Задача 5.1.20
 Даны два упорядоченных списка, в которых могут быть одинаковые
 элементы.Разработать функцию создания одного общего
 упорядоченного списка, исключив повторяющиеся элементы. */

void EnterAndCheckInput(int*); /*Проверка пользовательского ввода*/

int main(int argc, char* argv[])
{
	struct node* list1Root = NULL, * list2Root = NULL;
	struct node* list1 = NULL, * list2 = NULL;

	int i = 0;
	int n1 = 0;
	printf("Size of first list = ");       	   /*Ввод первого списка*/
	EnterAndCheckInput(&n1);   /*Проверка ввода*/
	printf("Enter elements of first list:\n");
	for (i = 0; i < n1; i++)
	{
		int x = 0;
		scanf("%d", &x);
		if (list1Root == NULL)
		{
			list1Root = (struct node*)malloc(sizeof(struct node));
			MemoryCheck(list1Root);          /*Проверка выделения памяти*/
			list1Root->element = x;
			list1Root->next = list1;
		}
		else
			list1 = AddElement(list1Root, x);
	}
	while (getchar() != '\n');

	int n2 = 0;
	printf("\nSize of second list = ");        /*Ввод второго списка*/
	EnterAndCheckInput(&n2);   /*Проверка ввода*/
	printf("Enter elements of second list:\n");
	for (i = 0; i < n2; i++)
	{
		int x = 0;
		scanf("%d", &x);
		if (list2Root == NULL)
		{
			list2Root = (struct node*)malloc(sizeof(struct node));
			MemoryCheck(list2Root);          /*Проверка выделения памяти*/
			list2Root->element = x;
			list2Root->next = list2;
		}
		else
			list2 = AddElement(list2Root, x);
	}
	while (getchar() != '\n');

	system("cls");
	printf("\nFirst list after sort:\n");   /*Сортировка и вывод первого списка*/
	list1Root = Sort(list1Root);
	ShowList(list1Root);
	printf("\nSecond list after sort:\n");  /*Сортировка и вывод второго списка*/
	list2Root = Sort(list2Root);
	ShowList(list2Root);
	DeleteDuplicateElements(list1Root);  /*Удаление повторяющихся элементов из списков*/
	DeleteDuplicateElements(list2Root);
	struct node* generalListRoot = NULL, * generalList = NULL;
	generalListRoot = PlusList(list1Root, generalListRoot);  /*Присоединение к общему списку списка №1*/
	generalListRoot = PlusList(list2Root, generalListRoot);  /*Присоединение к общему списку списка №2*/
	generalListRoot = Sort(generalListRoot);       	/*Сортировка общего списка*/
	DeleteDuplicateElements(generalListRoot);       /*Удаление дублей*/
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~ ~ General list: ~ ~~~~~~~~~~~~~~~~~~~~~~~~~\n"); /*Вывод общего списка*/
	ShowList(generalListRoot);
	printf("\n");

	free(list1Root);
	free(list2Root);
	return 0;
}

void EnterAndCheckInput(int* a)
{
	while (!scanf("%d", &(*a)))
	{
		printf("Wrong input! Try again :)\n");
		while (getchar() != '\n');
		printf("..new input: ");
	}
	while (getchar() != '\n');
}
