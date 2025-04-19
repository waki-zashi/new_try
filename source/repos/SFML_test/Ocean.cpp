#include "Ocean.h"
#include "Actions.h"
#include "Objects.h"  
#include "Utils.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Ocean::Ocean(size_t n, size_t m) : rows(n), cols(m)
{
	field.resize(n * m);

	cout << "Enter number of stones: ";
	cin >> stone_count;

	int count = 0;

	while (count < stone_count)
	{
		int r = rand() % (n * m);
		if (field[r] == nullptr)
		{
			field[r] = static_pointer_cast<Object>(make_shared<Stone>());
			++count;
		}
	}

	cout << "Enter number of reefs: ";
	cin >> reef_count;

	count = 0;

	while (count < reef_count)
	{
		int r = rand() % (n * m);
		if (field[r] == nullptr)
		{
			field[r] = static_pointer_cast<Object>(make_shared<Reef>());
			++count;
		}
	}

	cout << "Enter number of preys: ";
	cin >> prey_count;

	count = 0;

	while (count < prey_count)
	{
		int r = rand() % (n * m);
		if (field[r] == nullptr)
		{
			field[r] = static_pointer_cast<Object>(make_shared<Prey>());
			++count;
		}
	}

	cout << "Enter number of predators: ";
	cin >> count_predator;

	count = 0;

	while (count < count_predator)
	{
		int r = rand() % (n * m);
		if (field[r] == nullptr)
		{
			field[r] = static_pointer_cast<Object>(make_shared<Predator>());
			++count;
		}
	}

	cout << "Enter number of apex predators: ";
	cin >> count_apexpredator;

	count = 0;

	while (count < count_apexpredator)
	{
		int r = rand() % (n * m);
		if (field[r] == nullptr)
		{
			field[r] = static_pointer_cast<Object>(make_shared<ApexPredator>());
			++count;
		}
	}
}

int Ocean::stopper()
{
	if (prey_count <= 0 && count_predator <= 0 && count_apexpredator <= 0)
		return 1;
	else if (prey_count <= 0 && count_predator <= 0)
		return 2;
	else if (count_apexpredator <= 0 && count_predator <= 0)
		return 3;
	else if (prey_count <= 0 && count_apexpredator <= 0)
		return 4;
	else
		return 0;
}

void Ocean::tick()
{
	int c_stones = 0;
	int c_reefs = 0;
	int c_preys = 0;
	int c_predators = 0;
	int c_apredators = 0;

	stone_count = 0;
	reef_count = 0;
	prey_count = 0;
	count_predator = 0;
	count_apexpredator = 0;

	++iterations;

	vector<shared_ptr<Action>> actions;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (i < 0 || i >= rows || j < 0 || j >= cols) continue;

			int index = i * cols + j;

			if (index < field.size() && field[index] != nullptr)
			{
				shared_ptr<Object> obj = field[index];

				if (obj->key() == 1)
				{
					++c_stones;

					vector<vector<int>> neibourds = generate_neibourhood(obj, *this, obj->get_radius());
					//obj->print_neibourds(neibourds);

					auto action  = obj->action(neibourds, *this);
					if (action) 
						actions.push_back(move(action));
				}
				else if (obj->key() == 2)
				{
					++c_reefs;

					vector<vector<int>> neibourds = generate_neibourhood(obj, *this, obj->get_radius());
					//obj->print_neibourds(neibourds);

					auto action = obj->action(neibourds, *this);
					if (action)
						actions.push_back(move(action));
				}
				else if (obj->key() == 3)
				{
					++c_preys;

					vector<vector<int>> neibourds = generate_neibourhood(obj, *this, obj->get_radius());
					//obj->print_neibourds(neibourds);

					auto action = obj->action(neibourds, *this);
					if (action) 
						actions.push_back(move(action));
				}
				else if (obj->key() == 4)
				{
					++c_predators;

					if (obj->get_hunger())
						obj->set_radius(2);
					else
						obj->set_radius(1);

					vector<vector<int>> neibourds = generate_neibourhood(obj, *this, obj->get_radius());
					//obj->print_neibourds(neibourds);

					auto action = obj->action(neibourds, *this);
					if (action) 
						actions.push_back(move(action));
				}
				else if (obj->key() == 5)
				{
					++c_apredators;

					if (obj->get_hunger())
						obj->set_radius(3);
					else
						obj->set_radius(1);

					vector<vector<int>> neibourds = generate_neibourhood(obj, *this, obj->get_radius());
					//obj->print_neibourds(neibourds);

					auto action = obj->action(neibourds, *this);
					if (action) 
						actions.push_back(move(action));
				}
			}
		}
	}

	for (auto& action : actions) 
	{
		if (action)
			(*action)(*this);
	}

	stone_count += c_stones;
	reef_count += c_reefs;
	prey_count += c_preys;
	count_predator += c_predators;
	count_apexpredator += c_apredators;

	print();

	this_thread::sleep_for(chrono::milliseconds(500));
}

void Ocean::print() const
{
	//clearConsole();
	cout << endl;

	std::cout << "Stones: " << stone_count
		<< " | Reefs: " << reef_count
		<< " | Prey: " << prey_count
		<< " | Predators: " << count_predator
		<< " | Apex Predators: " << count_apexpredator << "\n\n";

	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			if (field[i * cols + j]) {
				std::cout << field[i * cols + j]->key() << " ";
			}
			else {
				std::cout << ". ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	cout << "Iterations: " << iterations << endl;
}