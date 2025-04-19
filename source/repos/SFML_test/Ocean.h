#pragma once

#include <vector>
#include <memory>

class Object;
struct Point;

using namespace std;

class Ocean final
{
private:
	int iterations = 0;

public:
	int stone_count = 0;
	int reef_count = 0;
	int prey_count = 0;
	int count_predator = 0;
	int count_apexpredator = 0;

	size_t rows = 0;
	size_t cols = 0;

	vector<shared_ptr<Object>> field;

	Ocean(size_t n, size_t m);
	int stopper();
	void tick();
	void print() const;
};