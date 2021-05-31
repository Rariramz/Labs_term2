#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct node
{
	int element;
	struct node* next;
};
struct node* AddElement(struct node*, int);
struct node* Sort(struct node*);
void DeleteDuplicateElements(struct node*);
struct node* PlusList(struct node*, struct node*);
void ShowList(struct node*);
void MemoryCheck(struct node*);