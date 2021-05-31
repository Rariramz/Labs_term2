#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Задача 6.2.16
   Рейтинг студентов.
   Программа рассчитывает рейтинг студентов
   специальности «Информатика».Рейтинг учитывает все оценки,
   полученные студентами во время сессий – как положительные, так
   и отрицательные.Можно просмотреть рейтинг по курсам, по
   группам.Отображается текущий средний балл, рост
   (положительный или отрицательный) относительно последней
   сессии, изменение места в рейтинге. */

typedef struct student
{
	char* surname;
	char* name;
	char* patronym;
	int course;
	int group;
	int* marks1, * marks2; /*оценки за первую и вторую сессии*/
	double average1, average2; /*средний балл за первую и вторую сессии*/

	int ratingPlace1, ratingPlace2; /*место в рейтинге первой и второй сесии*/
	double averageDelta; /*рост (положительный или отрицательный) относительно последней сессии*/
	int ratingDelta; /*изменение места в рейтинге*/
} Student;

typedef struct node
{
	int number;
	Student* student;
	struct node* next;
	struct node* prev;
} Node;

typedef struct list
{
	Node* first, * last;
	int counter;
} List;

List* list;
int updated = 0;

void showMenu(void);
int chooseOption(void);

void showStudent(Student* student, int sem);
void showList(int sem);
void showByGroup(int group);
void showByCourse(int course);
void QuickSortList(Node* left, Node* right);

double getAverage(int** marks);
double getAverageDelta(Student* student);
int getRatingDelta(Node* node);
void update(void);

char* readString(FILE* file);
int* readDigit(FILE* file);
Student* readStudent(FILE* file);
void pushBack(Student* student);
void writeStudent(Student* student, FILE* file);

void save();

int main()
{
	list = (List*)malloc(sizeof(List));
	list->first = NULL;
	list->last = NULL;
	list->counter = 0;

	FILE* students = fopen("students.txt", "r");
	if (students == NULL)
	{
		printf("\nSomething is wrong. File wasn't open :<");
		return 0;
	}

	while (!feof(students))
		pushBack(readStudent(students));
	
	while (1)
		showMenu();

	fclose(students);
	return 0;
}

void showMenu(void)
{
	printf("\n\n-----------------------------------------MENU:------------------------------------------");
	printf("\n1. Show first semester rating");
	printf("\n2. Update on the results of the second semester");
	printf("\n3. Show second semester rating");
	printf("\n4. Show all");
	printf("\n5. Show course..");
	printf("\n6. Show group..");
	printf("\n7. Exit from the program");
	printf("\n----------------------------------------------------------------------------------------");

	chooseOption();
}

int chooseOption(void)
{
	int ans = 0;

	printf("\nChoose option, please. Enter a number 1-7\nOption #");
	while (!scanf("%d", &ans) || ans <= 0 || ans > 7)
	{
		printf("Wrong input! Try again :)\n");
		while (getchar() != '\n');
		printf("\nChoose option, please. Enter a number 1-7\nOption #");
	}
	while (getchar() != '\n');

	switch (ans)
	{
	case 1:
		showList(1);
		break;
	case 2:
		QuickSortList(list->first, list->last);
		update();
		system("cls");
		printf("\n\nRating was updated!\n\n");
		break;
	case 3:
		showList(2);
		break;
	case 4:
		showList(0);
		break;
	case 5:
	{
		int course = 0;
		printf("\nEnter number of a course\nCourse #");
		while (!scanf("%d", &course) || course < 0)
		{
			printf("Wrong input! Try again :)\n");
			while (getchar() != '\n');
			printf("\nEnter number of a course\nCourse #");
		}
		while (getchar() != '\n');

		showByCourse(course);
		break;
	}
	case 6:
	{
		int group = 0;
		printf("\nEnter number of a group\Group #");
		while (!scanf("%d", &group) || group < 0)
		{
			printf("Wrong input! Try again :)\n");
			while (getchar() != '\n');
			printf("\nEnter number of a group\Group #");
		}
		while (getchar() != '\n');

		showByGroup(group);
		break;
	}
	case 7:
		save();
		printf("\n\nChanges have been saved.\nGood bye!~\n\n");
		exit(1);
	default:
		printf("\nSomething is wrong! /(>,<)/");
	}

	return ans;
}

void showStudent(Student* student, int sem)
{
	printf("\n%s ", student->surname);
	printf("%s ", student->name);
	printf("%s", student->patronym);

	printf("\nCourse: %d", student->course);
	printf("\nGroup: %d", student->group);

	int k = 0;
	if (sem == 1 || sem == 0)
	{
		printf("\nFirst semester marks: ");
		for (k = 0; k < 4; k++)
			printf("%d ", student->marks1[k]);

		printf("\nRating place in first semester: %d", student->ratingPlace1);

		printf("\nAverage point in first semester: %.2f", student->average1);
	}
	if (sem == 2 || sem == 0)
	{
		if (updated == 1)
		{
			printf("\nSecond semester marks: ");
			for (k = 0; k < 4; k++)
				printf("%d ", student->marks2[k]);

			printf("\nRating place in second semester: %d", student->ratingPlace2);

			printf("\nRating increase: ");
			if (student->ratingDelta > 0)
				printf("+");
			printf("%d", student->ratingDelta);

			printf("\nAverage in second semester: %.2f", student->average2);

			printf("\nAverage point increase: ");
			if (student->averageDelta > 0)
				printf("+");
			printf("%.2f", student->averageDelta);
		}
		else
			printf("\nTo see more information firstly update rating :)");
	}

	printf("\n\n");
}

void showList(int sem)
{
	system("cls");

	Node* current = list->first;

	if (list->first == NULL)
		printf("The list is empty :/");
	else
	{
		while (current != NULL)
		{
			showStudent(current->student, sem);
			current = current->next;
		}
	}
}

void showByCourse(int course)
{
	system("cls");

	Node* current = list->first;

	int done = 0;

	if (list->first == NULL)
		printf("The list is empty :/");
	else
	{
		while (current != NULL)
		{
			if (current->student->course == course)
			{
				showStudent(current->student, 0);
				done = 1;
			}
			current = current->next;
		}
	}

	if (done == 0)
		printf("\n\nNo matches found :(\n\n");
}

void showByGroup(int group)
{
	system("cls");

	Node* current = list->first;

	int done = 0;

	if (list->first == NULL)
		printf("The list is empty :/");
	else
	{
		while (current != NULL)
		{
			if (current->student->group == group)
			{
				showStudent(current->student, 0);
				done = 1;
			}
			current = current->next;
		}
	}

	if (done == 0)
		printf("\n\nNo matches found :(\n\n");
}

void QuickSortList(Node* left, Node* right)
{
	if (list->first == NULL)
		return;

	Node* start;
	Node* current;
	Student* placeholder;

	if (left == right)
		return;

	start = left;
	current = start->next;

	while (1)
	{
		if (start->student->average2 > current->student->average2)
		{
			placeholder = current->student;
			current->student = start->student;
			start->student = placeholder;
		}

		if (current == right)
			break;

		current = current->next;
	}

	placeholder = left->student;
	left->student = current->student;
	current->student = placeholder;

	Node* oldCurrent = current;

	current = current->prev;

	if (current != NULL)
		if ((left->prev != current) && (current->next != left))
			QuickSortList(left, current);

	current = oldCurrent;
	current = current->next;

	if (current != NULL)
		if ((current->prev != right) && (right->next != current))
			QuickSortList(current, right);
}

double getAverage(int** marks)
{
	double sum = 0;
	int amount = 0;
	int i = 0;

	for (i = 0; (*marks)[i] != NULL; i++)
		amount += 1;
	for (i = 0; i < amount; i++)
		sum += (*marks)[i];

	return sum / amount;
}

double getAverageDelta(Student* student)
{
	return student->average2 - student->average1;
}

int getRatingDelta(Node* node)
{
	return node->student->ratingPlace1 - node->student->ratingPlace2;
}

void update(void)
{
	updated = 1;
	Node* current = list->first;

	while (current != NULL)
	{
		current->student->ratingPlace2 = current->number + 1;
		current->student->ratingDelta = getRatingDelta(current);
		current->student->averageDelta = getAverageDelta(current->student);
		current = current->next;
	}
}

Student* readStudent(FILE* file)
{
	Student* newStudent = (Student*)malloc(sizeof(Student));

	newStudent->surname = readString(file);
	newStudent->name = readString(file);
	newStudent->patronym = readString(file);
	newStudent->course = *(readDigit(file));
	newStudent->group = *(readDigit(file));
	newStudent->marks1 = readDigit(file);
	newStudent->marks2 = readDigit(file);
	                                         
	newStudent->average1 = getAverage(&(newStudent->marks1));
	newStudent->average2 = getAverage(&(newStudent->marks2));
	newStudent->averageDelta = 0;
	newStudent->ratingPlace1 = 0;
	newStudent->ratingPlace2 = 0;
	newStudent->ratingDelta = 0;

	return newStudent;
}

void pushBack(Student* student)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->student = student;
	newNode->number = list->counter;
	newNode->student->ratingPlace1 = newNode->number + 1;

	if (list->first == NULL)
	{
		list->first = newNode;
		list->last = newNode;
	}
	else
	{
		list->last->next = newNode;
		newNode->prev = list->last;
		list->last = newNode;
	}

	list->counter += 1;
}

char* readString(FILE* file)
{
	char s[100];
	fscanf(file, "%s", s);
	int len = strlen(s);

	char* output = calloc(len + 1, sizeof(char));
	if (output == NULL)
	{
		printf("\nNot enough memory :<");
		exit(1);
	}

	strcpy(output, s);

	return output;
}

int* readDigit(FILE* file) /*считывание строки с оценками*/
{
	int* vals = (int*)calloc(100, sizeof(int)); /*массив значений*/

	char s[30] = "";
	fscanf(file, "%s", s);

	int col = 0;
	int i = 0;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == ',')
			continue;

		if (s[i] == '-' || (s[i] >= '0' && s[i] <= '9'))
		{
			char* box = (char*)calloc(5, sizeof(char));
			int len = 0;
			while (s[i] == '-' || (s[i] >= '0' && s[i] <= '9'))
			{
				box[len++] = s[i];
				i++;
			}
			vals[col++] = atoi(box);
		}
	}
	return vals;
}

void save()
{
	FILE* file;
	file = fopen("studentsOutput.txt", "w");

	Node* current = list->first;

	while (current != NULL)
	{
		writeStudent(current->student, file);
		current = current->next;
	}
	fclose(file);
}

void writeStudent(Student* student, FILE* file)
{
	fprintf(file, "\n%s ", student->surname);
	fprintf(file, "%s ", student->name);
	fprintf(file, "%s", student->patronym);

	fprintf(file, "\nCourse: %d", student->course);
	fprintf(file, "\nGroup: %d", student->group);

	fprintf(file, "\nFirst semester marks: ");
	int k = 0;
	for (k = 0; k < 4; k++)
		fprintf(file, "%d ", student->marks1[k]);

	fprintf(file, "\nRating place in first semester: %d", student->ratingPlace1);

	fprintf(file, "\nAverage point in first semester: %.2f", student->average1);

	if (updated == 1)
	{
		fprintf(file, "\nSecond semester marks: ");
		for (k = 0; k < 4; k++)
			fprintf(file, "%d ", student->marks2[k]);

		fprintf(file, "\nRating place in second semester: %d", student->ratingPlace2);

		fprintf(file, "\nRating increase: ");
		if (student->ratingDelta > 0)
			fprintf(file, "+");
		fprintf(file, "%d", student->ratingDelta);

		fprintf(file, "\nAverage in second semester: %.2f", student->average2);

		fprintf(file, "\nAverage point increase: ");
		if (student->averageDelta > 0)
			fprintf(file, "+");
		fprintf(file, "%.2f", student->averageDelta);
	}

	fprintf(file, "\n\n");
}