#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int value;
	struct node* right;
	struct node* left;
}Node;

void addNode(Node** root, int val);
void printTree(Node* current);
int getLongestBranchLenAndSum(Node* current, int length, int* sum);
