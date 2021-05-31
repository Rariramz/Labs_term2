#include "ListFuncs.h"

struct node* AddElement(struct node* listRoot, int val) /*Добавление элемента в конец списка*/
{
	struct node* current = listRoot, * newNode;
	while (current->next != NULL)
	{
		current = current->next;
	}
	newNode = (struct node*)malloc(sizeof(struct node)); /*Создаем узел*/
	MemoryCheck(newNode);          /*Проверка выделения памяти*/
	newNode->element = val;
	newNode->next = NULL;
	current->next = newNode; /*Присваиваем нулевому указателю адрес, где хранится новый узел*/
	return newNode;
}

struct node* Sort(struct node* listRoot) /*Сортировка по возрастанию*/
{
	struct node* current = listRoot, * tmp = NULL, * prev = NULL;
	int flag = 0;
	do
	{
		flag = 0;
		current = listRoot;
		while (current->next != NULL)
		{
			if (current->element > current->next->element)
			{
				if (current == listRoot)
				{
					tmp = current;
					current = tmp->next;
					tmp->next = current->next;
					current->next = tmp;
					listRoot = current;
					flag = 1;
				}
				else
				{
					tmp = current;
					current = tmp->next;
					tmp->next = current->next;
					current->next = tmp;
					prev->next = current;
					flag = 1;
				}
			}
			prev = current;
			current = current->next;
		}
	} while (flag == 1);
	return listRoot;
}

void DeleteDuplicateElements(struct node* listRoot) /*Удаление дублей в списке*/
{
	struct node* current = listRoot, * placeholder;
	while (current != NULL && current->next != NULL)
	{
		if (current->element == current->next->element)
		{
			placeholder = current->next->next;
			free(current->next);
			current->next = placeholder;
		}
		current = current->next;
	}
}

struct node* PlusList(struct node* listPlusRoot, struct node* generalListRoot) /*Добавление списка в general список*/
{
	struct node* listPlus = listPlusRoot, * generalList = generalListRoot;
	while (listPlus != NULL)
	{
		if (generalListRoot == NULL)
		{
			generalListRoot = (struct node*)malloc(sizeof(struct node));
			MemoryCheck(generalListRoot);
			generalListRoot->element = listPlus->element;
			generalListRoot->next = generalList;
		}
		else
			generalList = AddElement(generalListRoot, listPlus->element);
		listPlus = listPlus->next;
	}
	return generalListRoot;
}
void ShowList(struct node* listRoot)  /*Вывод в консоль*/
{
	struct node* current;
	current = listRoot;
	while (current != NULL)
	{
		printf(" %d ", current->element);
		current = current->next;
	}
}

void MemoryCheck(struct node* pointer)
{
	if (pointer == NULL)        /*Проверка выделения памяти*/
	{
		printf("\nNot enough memory :<");
		exit(1);
	}
}
