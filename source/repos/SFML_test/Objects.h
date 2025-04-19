#pragma once

#include <vector>
#include <memory>

class Ocean;
struct Point;
class Action;

#define RANDOM_SPREAD 5

#define STONE_MIN_LIFE_DURATION 8
#define REEF_MIN_LIFE_DURATION 10

#define PREY_MIN_LIFE_DURATION 6
#define PREY_ADULT_AGES 5

#define PREDATOR_MIN_LIFE_DURATION 8
#define PREDATOR_ADULT_AGES 4
#define PREDATOR_HUNGER_MAX 4
#define PREDATOR_WEL_FED_DAYS 4

#define APEX_PREDATOR_MIN_LIFE_DURATION 12
#define APEX_PREDATOR_ADULT_AGES 8
#define APEX_PREDATOR_HUNGER_MAX 5
#define APEX_PREDATOR_WEL_FED_DAYS 3

using namespace std;

struct Object
{
	virtual ~Object() = default;
	virtual unique_ptr<Action> action(const vector<vector<int>>& neighbourds, Ocean& ocean) = 0;
	virtual int key() const = 0;
	virtual bool get_adult() = 0;
	virtual bool get_hunger() = 0;
	virtual void set_radius(int rad) = 0;
	virtual int get_radius() = 0;

	virtual void print_neibourds(const vector<vector<int>>& neighbourds) const = 0;
};

struct Stone : public Object, public enable_shared_from_this<Stone>
{
	Stone();

	unique_ptr<Action> action(const vector<vector<int>>& neighbourds, Ocean& ocean) override;

	int key() const override { return 1; }

	bool get_adult() override { return false; }
	bool get_hunger() override { return false; }
	void set_radius(int rad) override {}
	int get_radius() override { return 0; }

	void print_neibourds(const vector<vector<int>>& neighbourds) const override;

private:
	int age;
	int life_duration;
};

struct Reef : public Object, public enable_shared_from_this<Reef>
{
	Reef();

	unique_ptr<Action> action(const vector<vector<int>>& neighbourds, Ocean& ocean) override;

	int key() const override { return 2; }

	bool get_adult() override { return false; }
	bool get_hunger() override { return false; }
	void set_radius(int rad) override {}
	int get_radius() override { return 0; }

	void print_neibourds(const vector<vector<int>>& neighbourds) const override;

private:
	int age;
	int life_duration;
};

struct Prey : public Object, public enable_shared_from_this<Prey>
{
private:
	int life_duration;
	int age;
	bool adult;
	int radius;

public:

	Prey();

	unique_ptr<Action> action(const vector<vector<int>>& neighbourds, Ocean& ocean) override;

	bool get_adult() override { return adult; }
	bool get_hunger() override { return false; }
	int get_radius() override { return 1; }
	void set_radius(int rad) override {}

	int key() const override { return 3; }

	void print_neibourds(const vector<vector<int>>& neighbourds) const override;
};

struct Predator : public Object, public enable_shared_from_this<Predator>
{
private:
	int life_duration;
	int age;
	bool adult;
	int radius;
	bool hunger;
	int hunger_level;
	int well_fed_days;

public:

	Predator();

	unique_ptr<Action> action(const vector<vector<int>>& neighbourds, Ocean& ocean) override;

	void set_radius(int rad) override { radius = rad; }
	int get_radius() override { return radius; }

	bool get_adult() override { return adult; }
	bool get_hunger() override { return hunger; }

	int key() const override { return 4; }

	void print_neibourds(const vector<vector<int>>& neighbourds) const override;
};

struct ApexPredator : public Object, public enable_shared_from_this<ApexPredator>
{
private:
	int life_duration;
	int age;
	bool adult;
	int radius;
	bool hunger;
	int hunger_level;
	int well_fed_days;

public:

	ApexPredator();

	unique_ptr<Action> action(const vector<vector<int>>& neighbourds, Ocean& ocean) override;

	void set_radius(int rad) override { radius = rad; }
	int get_radius() override { return radius; }

	bool get_adult() override { return adult; }
	bool get_hunger() override { return hunger; }

	int key() const override { return 5; }

	void print_neibourds(const vector<vector<int>>& neighbourds) const override;
};