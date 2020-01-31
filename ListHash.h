#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class ListHash
{
private:
	vector<list<int>> tab;
	int size;
	int capacity;

	int MAX_PER_LIST;

	string path = "wynik.csv";
	ofstream file;

public:
	ListHash(int _size, int mpl);
	~ListHash();

	int hash(int key);

	void insert(int key);
	int find(int key);
	void deleteKey(int key);

private:
	void rehash(int key);

	void increase();
	void decrease();

public:
	void print();
	int getSize();
	int getCapacity();
};

ListHash::ListHash(int _size, int mpl = 4)
{
	tab.resize(_size);
	capacity = _size;
	size = 0;
	MAX_PER_LIST = mpl;

	file.open(path, ios::trunc);
	if (file.is_open())
		file << "ilosc_porownan" << "," << "ilosc_elementow" << endl;
	file.close();
}

ListHash::~ListHash()
{
	tab.clear();
}

int ListHash::hash(int key)
{
	return key % capacity;
}

void ListHash::insert(int key)
{
	if (find(key) == -1)
	{
		tab[hash(key)].push_back(key);
		size++;

		if (size > capacity* MAX_PER_LIST)
			increase();
	}
}

void ListHash::rehash(int key)
{
	tab[hash(key)].push_back(key);
	size++;
}

int ListHash::find(int key)
{
	file.open(path, ios::app);

	list<int>::iterator it;

	int i = 0;
	int index = hash(key);

	it = tab[index].begin();

	while (it != tab[index].end() && key != *it)
		it++;

	i = distance(tab[index].begin(), it);

//	printf("i: %d\tsize: %d\n", i, size);
	if (file.is_open())
	{
		file << i << ", " << size << endl;
	}
	file.close();

	if (it != tab[index].end())
		return i;
	else
		return -1;
}

void ListHash::deleteKey(int key)
{
	int ctrl = find(key);
	if (ctrl == -1)
		return;

	list<int>::iterator it;
	int index = hash(key);

	it = tab[index].begin();

	for (int i = 0; i < ctrl; i++)
		it++;

	tab[index].erase(it);
	size--;

	if (size * 4 < capacity * MAX_PER_LIST)
		decrease();
}

void ListHash::increase()
{
	int* tmp = new int[size];
	list<int>::iterator it;

	int j = 0;

	for (int i = 0; i < capacity; i++)
	{
		it = tab[i].begin();

		while (it != tab[i].end())
		{
			tmp[j] = *it;
			++j;
			++it;
		}
	}

	tab.clear();

	capacity *= 2;
	tab.resize(capacity);

	int tmpSize = size;
	size = 0;

	for (int i = 0; i < tmpSize; i++)
		rehash(tmp[i]);

	delete[] tmp;
}

void ListHash::decrease()
{
	int* tmp = new int[size];
	list<int>::iterator it;

	int j = 0;

	for (int i = 0; i < capacity; i++)
	{
		it = tab[i].begin();

		while (it != tab[i].end())
		{
			tmp[j] = *it;
			++j;
			++it;
		}
	}

	tab.clear();

	capacity /= 2;
	if (capacity < 1)
		capacity = 1;

	tab.resize(capacity);
	
	int tmpSize = size;
	size = 0;

	for (int i = 0; i < tmpSize; i++)
		rehash(tmp[i]);

	delete[] tmp;
}

void ListHash::print()
{
	for (int i = 0; i < capacity; i++)
	{
		printf("%d: ", i);

		for (auto l : tab[i])
			printf("%d, ", l);

		printf("\n");
	}
}

int ListHash::getSize()
{
	return size;
}

int ListHash::getCapacity()
{
	return capacity;
}