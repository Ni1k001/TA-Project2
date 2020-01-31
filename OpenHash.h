#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>

using namespace std;

class OpenHash
{
private:
	vector<int> tab;
	int size;
	int capacity;

	string path = "wynik2.csv";
	ofstream file;

	int PRIME = 7;

public:
	OpenHash(int _size);
	~OpenHash();

	int hash(int key);
	int hash2(int key);

	void insert(int key);
	int scan(int key);
	int find(int key);
	void deleteKey(int key);

private:
	void increase();
	void decrease();

	void FileAppend(int i);

	bool empty(int index);
	bool deleted(int index);

public:
	void print();
	int getSize();
	int getCapacity();
};

OpenHash::OpenHash(int _size)
{
	tab.resize(_size);
	capacity = _size;
	size = 0;

	for (int i = 0; i < capacity; i++)
		tab[i] = -1;

	file.open(path, ios::trunc);
	if (file.is_open())
		file << "ilosc_porownan" << "," << "ilosc_elementow" << endl;
	file.close();
}

OpenHash::~OpenHash()
{
	tab.clear();
}

int OpenHash::hash(int key)
{
	return key % capacity;
}

int OpenHash::hash2(int key)
{
	int v = PRIME - (key % PRIME);
	
	if (v % 2 == 0)
		v = (v - 1) % capacity;

	if (v >= capacity / 2 && capacity > 2)
	{
		v = capacity / 2;

		if (v % 2 == 0)
			v = (v - 1) % capacity;
		else
			v -= 2;
	}

	if (v == 0)
		return 1;

	return v;
}

void OpenHash::insert(int key)
{
	int i = scan(key);

	if (empty(i) || deleted(i))
	{
		tab[i] = key;
		size++;

		if (size * 10 > capacity * 7)
			increase();
	}
	else
		tab[i] = key;
}

int OpenHash::scan(int key)
{
	int index = hash(key);
	int jump = hash2(key);
	int d = -1;
	int i = index;

	int ip = 0;

	while (!empty(i))
	{
		ip++;

		if (deleted(i))
		{
			if (d == -1)
				d = i;
		}
		else if (tab[i] == key)
		{
			FileAppend(ip);
			return i;
		}
		i = (i + jump) % capacity;

		if (i == index)
		{
			FileAppend(ip);
			return d;
		}
	}

	if (d != -1)
	{
		FileAppend(ip);
		return d;
	}

	FileAppend(ip);
	return i;
}

int OpenHash::find(int key)
{
	int i = scan(key);

	if (empty(i) || deleted(i))
		return -1;

	return tab[i];
}

void OpenHash::deleteKey(int key)
{
	/*int i = scan(key);

	if (!empty(i) && !deleted(i))
	{
		tab[i] = -2;
		size--;

		if (size > 1 && size * 4 * 10 < capacity * 7)
			decrease();
	}*/

	int f = hash(key);
	int jump = hash2(key);
	int i = scan(key);
	int index = i;
	int j = 0;
	int d = -1;

	while (!empty(i) && (i + jump) % capacity != index)
	{
		if (hash(tab[(i + jump) % capacity]) == f)
		{
			tab[(i - j * jump) % capacity] = tab[(i + jump) % capacity];
			j = 0;
			d = (i + jump) % capacity;
		}
		else
			j++;

		i = (i + jump) % capacity;
	}

	if (d != -1)
		tab[d] = -1;

	if (tab[index] == key)
		tab[index] = -1;

	size--;

	if (size > 1 && size * 4 * 10 < capacity * 7)
		decrease();
}


void OpenHash::increase()
{
	int cap = capacity;

	capacity *= 2;

	int* tmp = new int[capacity];
	
	for (int i = 0; i < capacity; i++)
		tmp[i] = -1;

	for (int i = 0; i < cap; i++)
		if (!empty(i) && !deleted(i))
		{
			int key = tab[i];
			int index = hash(key);
			int jump = hash2(key);

			while (tmp[index] != -1)
			{
				index = (index + jump) % (capacity);
			}
			
			tmp[index] = tab[i];
		}

	tab.clear();

	tab.resize(capacity);

	for (int i = 0; i < capacity; i++)
		tab[i] = tmp[i];

	delete[] tmp;
}

void OpenHash::decrease()
{
	int cap = capacity;

	capacity /= 2;
	if (capacity < 1)
		capacity = 1;

	int* tmp = new int[capacity];

	for (int i = 0; i < capacity; i++)
		tmp[i] = -1;

	for (int i = 0; i < cap; i++)
		if (!empty(i) && !deleted(i))
		{
			int key = tab[i];
			int index = hash(key);
			int jump = hash2(key);

			while (tmp[index] != -1)
			{
				index = (index + jump) % (capacity);
				tmp[index] = tab[i];
			}
		}

	tab.clear();

	tab.resize(capacity);

	for (int i = 0; i < capacity; i++)
		tab[i] = tmp[i];

	delete[] tmp;
}

void OpenHash::print()
{
	for (int i = 0; i < capacity; i++)
		printf("%d ", tab[i]);
}

void OpenHash::FileAppend(int i)
{
	file.open(path, ios::app);

	if (file.is_open())
	{
		file << i << ", " << size << endl;
	}
	file.close();
}

bool OpenHash::empty(int index)
{
	if (tab[index] == -1)
		return true;
	return false;
}

bool OpenHash::deleted(int index)
{
	if (tab[index] == -2)
		return true;
	return false;
}

int OpenHash::getSize()
{
	return size;
}

int OpenHash::getCapacity()
{
	return capacity;
}