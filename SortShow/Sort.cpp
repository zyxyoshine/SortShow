#include "stdafx.h"
#include "Sort.h"
#include <algorithm>
#include <stack>

Sort::Sort()
{
	myCashList = new CList<int>();
}
Sort::~Sort()
{

}
CList<int>* Sort::myCashList;
void Sort::getData(int data[], int size)
{
	sortData = new Node[size];
	for (int i = 0; i < size; i++)
	{
		sortData[i].value = data[i];
		sortData[i].index = i;
	}
}
void Sort::swap(int i, int j)
{
	std::stack<Node>stack;
	stack.push(sortData[i]);
	stack.push(sortData[j]);
	sortData[i] = stack.top();
	stack.pop();
	sortData[j] = stack.top();
}
void Sort::copyList(CList<int>*outCash)
{
	POSITION pos = myCashList->GetHeadPosition();
	while (pos != NULL)
	{
		int d = myCashList->GetNext(pos);
		outCash->AddTail(d);
	}
	myCashList->RemoveAll();
}

void Sort::Bubble(int data[],int size, CList<int>* cash)
{
	getData(data, size);
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = size - 1; j >i; j--)
		{
			if (sortData[j - 1].value> sortData[j].value)
			{
				swap(j - 1, j);
			}
		}
	}
	copyList(cash);
}


void Sort::Select(int data[], int size, CList<int>*cash)
{
	getData(data, size);
	int temp;
	int pos;
	for (int i = 0; i < size; i++)
	{
		temp = sortData[i].value;
		pos = i;
		for (int j = i + 1; j < size; j++)
		{
			if (sortData[j].value < temp)
			{
				temp = sortData[j].value;
				pos = j;
			}
		}
		swap(i, pos);
	}
	copyList(cash);
}

void Sort::Insert(int data[], int size, CList<int>*cash)
{
	getData(data, size);
	int temp;
	int pos;
	for (int i = 1; i < size; i++)
	{
		temp = sortData[i].value;
		pos = i - 1;
		while (pos >= 0 && temp < sortData[pos].value)
		{
			sortData[pos + 1] = sortData[pos];
			//id[pos + 1] = id[pos];
			pos--;
		}
		Node node;
		node.index = sortData[i].index;
		node.value = temp;
		sortData[pos + 1] = node;
	}
	copyList(cash);
}

void Sort::Insert2(int data[], int size, CList<int>*cash)
{
	getData(data, size);
	int temp;
	for (int i = 1; i < size; i++)
	{
		temp = sortData[i].value;
		int l = 0;
		int r = i - 1;
		while (l <= r)
		{
			int mid = (l + r) / 2;
			if (sortData[mid].value <= temp)
			{
				l = mid + 1;
			}
			else
				r = mid - 1;
		}
		Node node;
		node.index = sortData[i].index;
		node.value = temp;
		for (int j = i - 1;j >= r + 1;j--)
			sortData[j + 1] = sortData[j];
		sortData[r + 1] = node;
	}
	copyList(cash);
}

void Sort::Shell(int data[], int size, CList<int>*cash)
{
	getData(data, size);
	int temp, pos;
	int d = size;
	do
	{
		d = d / 3 + 1;
		for (int i = d; i<size; i++)
		{
			temp = sortData[i].value;
			pos = i - d;
			while (pos >= 0 && temp<sortData[pos].value)
			{
				sortData[pos + d] = sortData[pos];
				pos -= d;
			}
			Node node;
			node.index = sortData[i].index;
			node.value = temp;
			sortData[pos + d] = node;
		}
	} while (d>1);
	copyList(cash);
}

void Sort::qsort(Node*data, int l, int r)
{
	int i, j;
	int mid;
	i = l;
	j = r;
	mid = data[(l + r) / 2].value;
	do
	{
		while (data[i].value < mid && i < r)
		{
			i++;
		}
		while (data[j].value > mid && j > l)
		{
			j--;
		}
		if (i <= j)
		{
			swap(i, j);
			i++;
			j--;
		}
	} while (i <= j);
	if (l < j)
	{
		qsort(data, l, j);
	}
	if (r>i)
	{
		qsort(data, i, r);
	}
}

void Sort::Quick(int data[], int size, CList<int>*cash)
{
	getData(data, size);
	qsort(sortData, 0, size - 1);
	copyList(cash);
}

void Sort::MaxInHeap(Node*data, int size)
{
	for (int j = size - 1; j > 0; j--)
	{
		int parent = j / 2;
		int child = j;
		if (j < size - 1 && data[j].value < data[j + 1].value)
		{
			child++;
		}
		if (data[child].value > data[parent].value)
		{
			swap(child, parent);
		}
	}
}

void Sort::Heap(int data[], int size, CList<int>*cash)
{
	getData(data, size);
	for (int j = size; j > 0; j--)
	{
		MaxInHeap(sortData, j);
		swap(0, j - 1);
	}
	copyList(cash);
}

void Sort::MergeSort(Node*data, int l, int r)
{
	int mid;
	if (l < r)
	{
		mid = (l + r) / 2;
		MergeSort(data, l, mid);
		MergeSort(data, mid + 1, r);
		MergeAarry(data, l, mid, r);
	}
}

void Sort::MergeAarry(Node*data, int p, int q, int r)
{
	int n1, n2, i, j, k;
	Node *left = NULL, *right = NULL;
	n1 = q - p + 1;
	n2 = r - q;
	left = (Node*)malloc(sizeof(Node)*n1);
	right = (Node*)malloc(sizeof(Node)*n2);
	for (int i = 0; i < n1; i++)
	{
		left[i].value = data[p + i].value;
		left[i].index = data[p + i].index;
	}
	for (int j = 0; j < n2; j++)
	{
		right[j].value = data[q + 1 + j].value;
		right[j].index = data[q + 1 + j].index;
	}
	i = 0;
	j = 0;
	k = p;
	while (i < n1 && j < n2)
	{
		if (left[i].value <= right[j].value)
		{
			data[k++] = left[i++];
		}
		else
		{
			data[k++] = right[j++];
		}
	}
	for (; i < n1; i++)
	{
		data[k++] = left[i];
	}
	for (; j < n2; j++)
	{
		data[k++] = right[j];
	}
	delete[]left;
	delete[]right;
}

void Sort::Merge(int data[], int size, CList<int>*cash)
{
	getData(data, size);
	MergeSort(sortData, 0, size - 1);
	copyList(cash);
}
