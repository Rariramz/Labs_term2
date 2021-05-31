#include "Tree.h"

void addNode(Node** root, int val)
{
	Node* current = *root, * prev = NULL;

	while (current != NULL)
	{
		if (val < current->value)
		{
			prev = current;
			current = current->left;
		}
		else if (val > current->value)
		{
			prev = current;
			current = current->right;
		}
		else return;
	}

	current = (Node*)malloc(sizeof(Node)); /*Создаем узел*/
	memoryCheck(current);          /*Проверка выделения памяти*/
	current->value = val;
	current->right = NULL;
	current->left = NULL;

	if (prev == NULL)
		*root = current;
	else
	{
		if (val < prev->value)
			prev->left = current;
		else
			prev->right = current;
	}
}

void printTree(Node* current)
{
	if (current != NULL)
	{
		if (current->left != NULL)
			printTree(current->left);

		printf("%d ", current->value);

		if (current->right != NULL)
			printTree(current->right);
	}
}

int getLongestBranchLenAndSum(Node* current, int length, int* sum)
{
	int left = 0, right = 0; /*Длина левой, правой ветки*/
	int sumLeft = 0, sumRight = 0;

	int curSum = *sum + current->value;
	*sum += current->value;

	if (current->left != NULL)
	{
		left = getLongestBranchLenAndSum(current->left, length + 1, sum);
		sumLeft = *sum;
		*sum = curSum;
	}
	if (current->right != NULL)
	{
		right = getLongestBranchLenAndSum(current->right, length + 1, sum);
		sumRight = *sum;
		*sum = curSum;
	}
	if (left == 0 && right == 0)
		return length;

	else if (left > right)
	{
		*sum = sumLeft;
		return left;
	}
	else
	{
		*sum = sumRight;
		return right;
	}
}