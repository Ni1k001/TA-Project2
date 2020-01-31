#include <iostream>
#include <random>
#include <ctime>
#include <functional>

#include "ListHash.h"
#include "OpenHash.h"

using namespace std;

int main()
{
	auto random = bind(uniform_int_distribution<>(0, 1000000), mt19937(time(NULL)));
	int randValue;

/*
	ListHash listHash(1, 4);

	for (int i = 0; i < 1000000; i++)
	{
		randValue = random();
		listHash.insert(randValue);
	}

//	listHash.print();
	printf("\n\n%d\n%d\n", listHash.getSize(), listHash.getCapacity());
*/

	OpenHash openHash(1);

	for (int i = 0; i < 1000000; i++)
	{
		randValue = random();
		openHash.insert(randValue);
	}

	/*openHash.insert(50);
	openHash.insert(260);
	openHash.insert(190);
	openHash.insert(330);
	openHash.insert(120);
	openHash.insert(121);

	openHash.print();
	printf("\n\n%d\n%d\n", openHash.getSize(), openHash.getCapacity());

	printf("\n\n");
	openHash.deleteKey(121);
	openHash.print();
	printf("\n\n");
	openHash.deleteKey(50);
	openHash.print();*/

	printf("\n\n");
	system("pause");
	return 0;
}