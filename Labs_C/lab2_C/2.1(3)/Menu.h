#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void ShowMenu(void);
int ChooseOption(void);
void SetCoordinatesOfSegments(void);
void IsTrianglePossible(float, float, float);
void TypeOfTriangle(float, float, float);
void CalculatePerimeterOfTriangle(float, float, float);
void CalculateAreaOfTriangle(float, float, float);
void InformationAboutAuthorAndVersion(void);
void Exit(void);