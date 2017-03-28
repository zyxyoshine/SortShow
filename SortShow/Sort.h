#pragma once
class Sort
{
private:
	class Node
	{
	public:
		int value = -1;
		int index = -1;
		Node& operator=(Node n)
		{
			value = n.value;
			if (index != -1 && n.index != -1)
			{
				myCashList->AddTail(index);
				myCashList->AddTail(n.value);
			}
			return *this;
		}
	};
	static CList<int>* myCashList;
	Node *sortData;
	void getData(int[], int);
	void swap(int, int);
	void copyList(CList<int>*);

	void MergeSort(Node*, int, int);
	void MergeAarry(Node*, int, int, int);

	void MaxInHeap(Node*, int);

	void qsort(Node*, int, int);

public:
	Sort();
	~Sort();
	void Bubble(int[], int, CList<int>*);
	void Select(int[], int, CList<int>*);
	void Insert(int[], int, CList<int>*);
	void Insert2(int[], int, CList<int>*);
	void Shell(int[], int, CList<int>*);
	void Quick(int[], int, CList<int>*);
	void Heap(int[], int, CList<int>*);
	void Merge(int[], int, CList<int>*);

};