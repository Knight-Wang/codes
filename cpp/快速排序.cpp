// 快速排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
using namespace std;

void swap(int a[], int i, int j)
{
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}

int partition(int a[], int p, int r)
{
	int i = p;
	int j = r + 1;
	int x = a[p];
	while (1)
	{
		while (i < r && a[++i] < x);
		while (a[--j] > x);
		if (i >= j) break;
		swap(a, i, j);
	}
	swap(a, j, p);
	return j;
}

void quicksort(int a[], int p, int r)
{
	if (p < r)
	{
		int q = partition(a, p, r);
		quicksort(a, p, q - 1);
		quicksort(a, q + 1, r);
	}
}

int main()
{
	int a[] = { 5, 13, 6, 24, 2, 8, 19, 27, 6, 12, 1, 17 };
	int N = 12;
	quicksort(a, 0, N - 1);
	for (int i = 0; i < N; i++) 
		printf("%d ", a[i]);
	printf("\n");
	system("pause");
	return 0;
}


