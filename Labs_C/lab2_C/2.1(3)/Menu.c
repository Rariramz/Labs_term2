#include "Menu.h"

float A = -1, B = -1, C = -1;  //lengthes of segments of a triangle
float* pa = &A, * pb = &B, * pc = &C;
int IsTriangle = -1;

void ShowMenu(void)
{
	printf("\n\n-----------------------------------------MENU:------------------------------------------");
	printf("\n1. Set coordinates of the beginning and end of three segments in two-dimensional space");
	printf("\n2. Determine whether a triangle can be drawn on theses segments");
	printf("\n3. Determine the type of triangle");
	printf("\n4. Calculate the perimeter of a formed triangle");
	printf("\n5. Calculate the area of triangle");
	printf("\n6. Information about the version and author of the program");
	printf("\n7. Exit from the program");
	printf("\n----------------------------------------------------------------------------------------");

	ChooseOption();
}
int ChooseOption(void)
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
		SetCoordinatesOfSegments();
		break;
	case 2:
	{
		if (A != -1 && B != -1 && C != -1)
			IsTrianglePossible(A, B, C);
		else
			printf("You can't use this option yet");
		break;
	}
	case 3:
	{
		if (IsTriangle == 1)
			TypeOfTriangle(A, B, C);
		else
		{
			if (IsTriangle == -1)
				printf("You have to access function #2 firstly");
			else
				printf("You can't use this option, it is available only for triangles.");
		}
		ShowMenu();
		break;
	}
	case 4:
	{
		if (IsTriangle == 1)
			CalculatePerimeterOfTriangle(A, B, C);
		else
		{
			if (IsTriangle == -1)
				printf("You have to access function #2 firstly");
			else
				printf("You can't use this option, it is available only for triangles.");
		}
		ShowMenu();
		break;
	}
	case 5:
	{
		if (IsTriangle == 1)
			CalculateAreaOfTriangle(A, B, C);
		else
		{
			if (IsTriangle == -1)
				printf("You have to access function #2 firstly");
			else
				printf("You can't use this option, it is available only for triangles.");
		}
		ShowMenu();
		break;
	}
	case 6:
		InformationAboutAuthorAndVersion();
		break;
	case 7:
		Exit();
		break;
	default:
		printf("\nSomething is wrong! /(>,<)/");
	}

	return ans;
}
void SetCoordinatesOfSegments(void)
{
	float a = 0, b = 0, c = 0;
	float coordinates[12];
	float dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0, dx3 = 0, dy3 = 0;

	printf("Enter coordinates of the beginning and end of three segments in two-dimensional space ");
	printf("\n1 - X1\t2 - x1\t3 - Y1\t4 - y1\t5 - X2\t6 - x2\t7 - Y2\t8 - y2\t9 - X3\t10 - x3\t11 - Y3\t12 - y3\n\n");
	for (int i = 0; i < 12; i++)
	{
		printf("%d - ", i + 1);
		while (!scanf("%f", &coordinates[i]))
		{
			printf("Wrong input! Try again :)\n");
			printf("%d - ", i + 1);
			while (getchar() != '\n');
		}
		while (getchar() != '\n');
	}
	dx1 = coordinates[1] - coordinates[0];
	dy1 = coordinates[3] - coordinates[2];
	dx2 = coordinates[5] - coordinates[4];
	dy2 = coordinates[7] - coordinates[6];
	dx3 = coordinates[9] - coordinates[8];
	dy3 = coordinates[11] - coordinates[10];
	a = sqrt(pow(dx1, 2) + pow(dy1, 2));
	b = sqrt(pow(dx2, 2) + pow(dy2, 2));
	c = sqrt(pow(dx3, 2) + pow(dy3, 2));
	*pa = a;
	*pb = b;
	*pc = c;
	printf("A = %f\tB = %f\tC = %f", A, B, C);
	ShowMenu();
}
void IsTrianglePossible(float a, float b, float c)
{
	if (a < b + c && b < a + c && c < a + b)
	{
		printf("A triangle can be composed of segments with entered coordinates");
		IsTriangle = 1;
	}
	else
	{
		printf("A triangle can NOT be composed of segments with entered coordinates :<");
		IsTriangle = 0;
	}
	ShowMenu();
}

#define eps 1e-9

void TypeOfTriangle(float a, float b, float c)
{
	if (fabs(a * a - b * b + c * c) < eps || fabs(b * b - a * a + c * c) < eps || fabs(c * c - a * a + b * b) < eps)
		printf("This triangle is rectangular");
	else
	{
		if (a * a > b* b + c * c || b * b > a* a + c * c || c * c > a* a + b * b)
			printf("This is an obtuse triangle");
		else //if (a * a < b * b + c * c || b * b < a * a + c * c || c * c < a * a + b * b)
			printf("This triangle is acute - angled");
	}

	if (a == b && b == c && a == c)
		printf(" equilateral");
	else
	{
		if (a == b && b == c && a != c || b == c && a == c && b != c || a == c && a == b && a != b)
			printf(" isosceles");
		else
			if (!(a * a == b * b + c * c || b * b == a * a + c * c || c * c == a * a + b * b))
				printf(" arbitrary");
	}

	ShowMenu();
}
void CalculatePerimeterOfTriangle(float a, float b, float c)
{
	float perimeter = a + b + c;
	printf("The perimeter of the triangle is %f", perimeter);
	ShowMenu();
}
void CalculateAreaOfTriangle(float a, float b, float c)
{
	float area = 0;
	float halfperimeter = (a + b + c) / 2;

	area = sqrt((double)(halfperimeter * (halfperimeter - a) * (halfperimeter - b) * (halfperimeter - c)));
	printf("The area of the triangle is %f", area);
	ShowMenu();
}
void InformationAboutAuthorAndVersion(void)
{
	printf("Lab.work No. 2\tTask No.2.1(3)\tBystrova Maria");
	ShowMenu();
}
void Exit(void)
{
	exit(1);
}