#include "Objects.h"
#include "Ocean.h"
#include "Actions.h"
#include "Utils.h"
#include "Point.h"
#include "MoveSpawn.h"

#include <iostream>
#include <vector>

using namespace std;

Stone::Stone() : life_duration(STONE_MIN_LIFE_DURATION + (rand() % RANDOM_SPREAD)), age(0) {}

unique_ptr<Action> Stone::action(const vector<vector<int>>& neighbourds, Ocean& ocean) 
{
	++age;

	if (age > life_duration)
	{
		//if (ocean.stone_count > 0)
		--ocean.stone_count;

		return make_unique<TransformToReef>(shared_from_this());
	}

	return make_unique<NoAction>(shared_from_this());
}

void Stone::print_neibourds(const vector<vector<int>>& neighbourds) const 
{
	cout << "Type: " << key() << endl;
	for (int i = 0; i < neighbourds.size(); ++i)
	{
		cout << "Place: " << neighbourds[i][0] << " " << neighbourds[i][1] << " Type: " << neighbourds[i][2] << endl;
	}

	cout << endl;
}


Reef::Reef() : life_duration(STONE_MIN_LIFE_DURATION + (rand() % RANDOM_SPREAD)), age(0) {}

unique_ptr<Action> Reef::action(const vector<vector<int>>& neighbourds, Ocean& ocean) 
{
	++age;

	if (age > life_duration)
	{
		//if (ocean.reef_count > 0)
		--ocean.reef_count;

		return make_unique<TransformToStone>(shared_from_this());
	}

	return make_unique<NoAction>(shared_from_this());
}

void Reef::print_neibourds(const vector<vector<int>>& neighbourds) const 
{
	cout << "Type: " << key() << endl;
	for (int i = 0; i < neighbourds.size(); ++i)
	{
		cout << "Place: " << neighbourds[i][0] << " " << neighbourds[i][1] << " Type: " << neighbourds[i][2] << endl;
	}

	cout << endl;
}


Prey::Prey() : life_duration(PREY_MIN_LIFE_DURATION + (rand() % RANDOM_SPREAD)), age(0), adult(false), radius{ 1 } {}

unique_ptr<Action> Prey::action(const vector<vector<int>>& neighbourds, Ocean& ocean) 
{
	++age;

	if (age > life_duration)
	{
		//if (ocean.prey_count > 0)
		--ocean.prey_count;

		return make_unique<Die>(shared_from_this());
	}

	if (adult == false && age > PREY_ADULT_AGES)
		adult = true;

	for (size_t i = 0; i < ocean.rows; ++i)
	{
		for (size_t j = 0; j < ocean.cols; ++j)
		{
			if (ocean.field[i * ocean.cols + j] == shared_from_this())
			{
				if (neighbourds.size() == sqrt(radius * 2 + 1) - 1)
				{
					return make_unique<NoAction>(shared_from_this());
				}
				else if (neighbourds.size() > 0)
				{
					vector<Point> enemies;

					for (int n = 0; n < neighbourds.size(); ++n)
					{
						if (neighbourds[n][2] == 4 || neighbourds[n][2] == 5)
						{
							Point enemy(neighbourds[n][0], neighbourds[n][1]);
							enemies.push_back(enemy);
						}
					}

					if (!enemies.empty())
					{
						Point p(i, j);

						Point run = find_escape_direction(p, enemies, ocean.cols, ocean.rows);

						if (p != run)
						{
							return make_unique<Move>(shared_from_this(), run, radius);
						}
					}
					else
					{
						if (this->get_adult())
						{
							for (int pr = 0; pr < neighbourds.size(); ++pr)
							{
								if (neighbourds[pr][2] == 3)
								{
									shared_ptr<Object> second_prey = ocean.field[neighbourds[pr][0] * ocean.cols + neighbourds[pr][1]];

									if (second_prey->get_adult())
									{
										spawn(shared_from_this(), ocean);
										adult = false;
										++ocean.prey_count;
									}
								}
							}
						}
						return make_unique<MoveRand>(shared_from_this(), radius);
					}
				}
			}
		}
	}

	return make_unique<NoAction>(shared_from_this());
}

void Prey::print_neibourds(const vector<vector<int>>& neighbourds) const 
{
	cout << "Type: " << key() << endl;
	for (int i = 0; i < neighbourds.size(); ++i)
	{
		cout << "Place: " << neighbourds[i][0] << " " << neighbourds[i][1] << " Type: " << neighbourds[i][2] << endl;
	}

	cout << endl;
}


Predator::Predator() : life_duration(PREDATOR_MIN_LIFE_DURATION + (rand() % RANDOM_SPREAD)), age(0), adult(false),
hunger_level{ 0 }, hunger{ false }, well_fed_days{ PREDATOR_WEL_FED_DAYS }, radius{ 1 } {}

unique_ptr<Action> Predator::action(const vector<vector<int>>& neighbourds, Ocean& ocean) 
{
	++age;
	--well_fed_days;

	if (age > life_duration)
	{
		//if (ocean.count_predator > 0)
		--ocean.count_predator;

		return make_unique<Die>(shared_from_this());
	}

	if (adult == false && age > PREDATOR_ADULT_AGES)
		adult = true;

	if (!hunger && well_fed_days < 0)
	{
		hunger = true;
		hunger_level = 0;
	}

	if (hunger)
	{
		if (hunger_level >= PREDATOR_HUNGER_MAX)
		{
			//if (ocean.count_predator > 0)
			--ocean.count_predator;

			return make_unique<Die>(shared_from_this());
		}
		++hunger_level;
	}

	for (size_t i = 0; i < ocean.rows; ++i)
	{
		for (size_t j = 0; j < ocean.cols; ++j)
		{
			if (ocean.field[i * ocean.cols + j] == shared_from_this())
			{
				if (neighbourds.size() == sqrt(radius * 2 + 1) - 1)
				{
					return make_unique<NoAction>(shared_from_this());
				}
				else if (neighbourds.size() > 0)
				{
					vector<Point> enemies;

					for (int n = 0; n < neighbourds.size(); ++n)
					{
						if (neighbourds[n][2] == 5)
						{
							Point enemy(neighbourds[n][0], neighbourds[n][1]);
							enemies.push_back(enemy);
						}
					}

					if (!enemies.empty())
					{
						Point p(i, j);

						Point run = find_escape_direction(p, enemies, ocean.cols, ocean.rows);

						if (p != run)
						{
							return make_unique<Move>(shared_from_this(), run, radius);
						}
					}
					else
					{
						for (int prey = 0; prey < neighbourds.size(); ++prey)
						{
							if (neighbourds[prey][2] == 3)
							{
								hunger = false;
								hunger_level = PREDATOR_WEL_FED_DAYS;

								//if (ocean.prey_count > 0)
								--ocean.prey_count;

								return make_unique<Hunt>(shared_from_this(), Point(neighbourds[prey][0], neighbourds[prey][1]));
							}
						}

						if (this->get_adult())
						{
							for (int pr = 0; pr < neighbourds.size(); ++pr)
							{
								if (neighbourds[pr][2] == 4)
								{
									shared_ptr<Object> second_predator = ocean.field[neighbourds[pr][0] * ocean.cols + neighbourds[pr][1]];

									if (second_predator->get_adult())
									{
										spawn(shared_from_this(), ocean);
										adult = false;
										++ocean.count_predator;
									}
								}
							}
						}
						return make_unique<MoveRand>(shared_from_this(), radius);
					}
				}
			}
		}
	}

	return make_unique<NoAction>(shared_from_this());
}

void Predator::print_neibourds(const vector<vector<int>>& neighbourds) const 
{
	cout << "Type: " << key() << endl;
	for (int i = 0; i < neighbourds.size(); ++i)
	{
		cout << "Place: " << neighbourds[i][0] << " " << neighbourds[i][1] << " Type: " << neighbourds[i][2] << endl;
	}

	cout << endl;
}


ApexPredator::ApexPredator() : life_duration(APEX_PREDATOR_MIN_LIFE_DURATION + (rand() % RANDOM_SPREAD)), age(0), adult(false),
hunger_level{ 0 }, hunger{ false }, well_fed_days{ APEX_PREDATOR_WEL_FED_DAYS }, radius{ 1 } {}

unique_ptr<Action> ApexPredator::action(const vector<vector<int>>& neighbourds, Ocean& ocean) 
{
	++age;
	--well_fed_days;

	if (age > life_duration)
	{
		//if (ocean.count_apexpredator > 0)
		--ocean.count_apexpredator;

		return make_unique<Die>(shared_from_this());
	}

	if (adult == false && age > APEX_PREDATOR_ADULT_AGES)
		adult = true;

	if (!hunger && well_fed_days < 0)
	{
		hunger = true;
		hunger_level = 0;
	}

	if (hunger)
	{
		if (hunger_level >= APEX_PREDATOR_HUNGER_MAX)
		{
			//if (ocean.count_apexpredator > 0)
			--ocean.count_apexpredator;

			return make_unique<Die>(shared_from_this());
		}
		++hunger_level;
	}

	for (size_t i = 0; i < ocean.rows; ++i)
	{
		for (size_t j = 0; j < ocean.cols; ++j)
		{
			if (ocean.field[i * ocean.cols + j] == shared_from_this())
			{
				if (neighbourds.size() == sqrt(radius * 2 + 1) - 1)
				{
					return make_unique<NoAction>(shared_from_this());
				}
				else if (neighbourds.size() > 0)
				{
					vector<Point> enemies;

					for (int n = 0; n < neighbourds.size(); ++n)
					{
						if (neighbourds[n][2] == 5)
						{
							Point enemy(neighbourds[n][0], neighbourds[n][1]);
							enemies.push_back(enemy);
						}
					}

					if (!enemies.empty())
					{
						Point p(i, j);

						Point run = find_escape_direction(p, enemies, ocean.cols, ocean.rows);

						if (p != run)
						{
							return make_unique<Move>(shared_from_this(), run, radius);
						}
					}
					else
					{
						for (int prey = 0; prey < neighbourds.size(); ++prey)
						{
							if (neighbourds[prey][2] == 3 || (neighbourds[prey][2] == 4 && hunger))
							{
								hunger = false;
								hunger_level = PREDATOR_WEL_FED_DAYS;

								if (neighbourds[prey][2] == 3)
								{
									//if (ocean.prey_count > 0)
									--ocean.prey_count;
								}
								else
								{
									//if (ocean.count_predator > 0)
									--ocean.count_predator;
								}

								return make_unique<Hunt>(shared_from_this(), Point(neighbourds[prey][0], neighbourds[prey][1]));
							}
						}

						if (this->get_adult())
						{
							for (int pr = 0; pr < neighbourds.size(); ++pr)
							{
								if (neighbourds[pr][2] == 4)
								{
									shared_ptr<Object> second_predator = ocean.field[neighbourds[pr][0] * ocean.cols + neighbourds[pr][1]];

									if (second_predator->get_adult())
									{
										spawn(shared_from_this(), ocean);
										adult = false;
										++ocean.count_apexpredator;
									}
								}
							}
						}

						return make_unique<MoveRand>(shared_from_this(), radius);
					}
				}
			}
		}
	}

	return make_unique<NoAction>(shared_from_this());
}

void ApexPredator::print_neibourds(const vector<vector<int>>& neighbourds) const 
{
	cout << "Type: " << key() << endl;
	for (int i = 0; i < neighbourds.size(); ++i)
	{
		cout << "Place: " << neighbourds[i][0] << " " << neighbourds[i][1] << " Type: " << neighbourds[i][2] << endl;
	}

	cout << endl;
}