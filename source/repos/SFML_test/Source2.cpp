#include "Ocean.h"
#include "Objects.h"
#include "Actions.h"
#include "Utils.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>
#include <cstdlib>

using namespace std;


int main()
{
	srand(time(nullptr));

	size_t rows, cols;

	cout << "Enter field size (&n &m): ";
	cin >> rows >> cols;

	Ocean ocean(rows, cols);

	int stop = ocean.stopper();

	ocean.print();

	clearConsole();

	while (stop == 0)
	{
		ocean.tick();

		stop = ocean.stopper();

		clearConsole();
	}

	cout << endl << endl;

	ocean.print();

	if (stop == 1)
		cout << "No more alive animals" << endl;
	else if (stop == 2)
		cout << "Apex Predators win" << endl;
	else if (stop == 3)
		cout << "Preys win" << endl;
	else
		cout << "Predators win" << endl;
}