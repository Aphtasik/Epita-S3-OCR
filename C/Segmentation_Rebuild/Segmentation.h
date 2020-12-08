#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include<stdio.h>
#include"../Tools/Tools.h"

void HorizontalProjection(struct Matrix matrix, int* pList);
void VerticalProjection(struct Matrix matrix, int minIndex, int maxIndex, int* pList);
int MaxBlackPxl(int* pProj, int matrixLen);
int Size(int *pProj, int lenList);
int CountElt(int matrixLen, int Size, int* pProj);
void ijMatrix(int* pProj, struct Matrix lineOrCharMatrix, int matrixLen, int size);
void RecreateMatrix(struct Matrix picture, int *ptr, int iMin, int iMax, int jMin, int jMax);
void ReconstructText(struct Matrix picture);

#endif
