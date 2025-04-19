	//#include <iostream>
	//#include <algorithm>
	//#include <vector>
	//#include <thread>
	//#include <chrono>
	//#include <memory>

	//using namespace std;

	//#define RANDOM_SPREAD 5

	//#define STONE_MIN_LIFE_DURATION 8
	//#define REEF_MIN_LIFE_DURATION 10

	//#define PREY_MIN_LIFE_DURATION 6
	//#define PREY_ADULT_AGES 2

	//#define PREDATOR_MIN_LIFE_DURATION 8
	//#define PREDATOR_ADULT_AGES 4
	//#define PREDATOR_HUNGER_MAX 4
	//#define PREDATOR_WEL_FED_DAYS 4

	//#define APEX_PREDATOR_MIN_LIFE_DURATION 12
	//#define APEX_PREDATOR_ADULT_AGES 8
	//#define APEX_PREDATOR_HUNGER_MAX 5
	//#define APEX_PREDATOR_WEL_FED_DAYS 3


	//struct Object;
	//class Ocean; 
	//struct Point;
	//struct Action;

	//struct TransformToReef;

	//struct Stone;
	//struct Reef;
	//struct Prey;
	//struct Predator;
	//struct ApexPredator;

	//struct NoAction;
	//struct TransformToStone;
	//struct Die;
	//struct Move;
	//struct Hunt;

	//vector<vector<int>> generate_neibourhood(shared_ptr<Object> obj, const Ocean& ocean, int radius);
	//void move_random(shared_ptr<Object> obj, Ocean& ocean, int radius);
	//void spawn(shared_ptr<Object> obj, Ocean& ocean);
	//Point find_escape_direction(const Point& currentPos, const vector<Point>& predatorPositions, int cols, int rows);

	//void clearConsole() 
	//{
	//#ifdef _WIN32
	//	system("cls");
	//#else
	//	system("clear");
	//#endif
	//}

	//struct Object
	//{
	//	virtual ~Object() = default;
	//	virtual unique_ptr<Action> action(const vector<vector<int>>& neighbourds, Ocean& ocean) = 0;
	//	virtual int key() const = 0;
	//	virtual bool get_adult() = 0;
	//	virtual bool get_hunger() = 0;
	//	virtual void set_radius(int rad) = 0;
	//	virtual int get_radius() = 0;
	//};

	//class Ocean final
	//{
	//private:
	//	int iterations = 0;

	//public:
	//	int stone_count = 0;
	//	int reef_count = 0;
	//	int prey_count = 0;
	//	int count_predator = 0;
	//	int count_apexpredator = 0;

	//	size_t rows = 0;
	//	size_t cols = 0;

	//	vector<shared_ptr<Object>> field;


	//	Ocean(size_t n, size_t m) : rows(n), cols(m)
	//	{
	//		field.resize(n * m);

	//		cout << "Enter number of stones: ";
	//		cin >> stone_count;

	//		int count = 0;

	//		while (count < stone_count)
	//		{
	//			int r = rand() % (n * m);
	//			if (field[r] == nullptr)
	//			{
	//				field[r] = static_pointer_cast<Object>(make_shared<Stone>());
	//				++count;
	//			}
	//		}

	//		cout << "Enter number of reefs: ";
	//		cin >> reef_count;

	//		count = 0;

	//		while (count < reef_count)
	//		{
	//			int r = rand() % (n * m);
	//			if (field[r] == nullptr)
	//			{
	//				field[r] = static_pointer_cast<Object>(make_shared<Reef>());
	//				++count;
	//			}
	//		}

	//		cout << "Enter number of preys: ";
	//		cin >> prey_count;

	//		count = 0;

	//		while (count < prey_count)
	//		{
	//			int r = rand() % (n * m);
	//			if (field[r] == nullptr)
	//			{
	//				field[r] = static_pointer_cast<Object>(make_shared<Prey>());
	//				++count;
	//			}
	//		}

	//		cout << "Enter number of predators: ";
	//		cin >> count_predator;

	//		count = 0;

	//		while (count < count_predator)
	//		{
	//			int r = rand() % (n * m);
	//			if (field[r] == nullptr)
	//			{
	//				field[r] = static_pointer_cast<Object>(make_shared<Predator>());
	//				++count;
	//			}
	//		}

	//		cout << "Enter number of apex predators: ";
	//		cin >> count_apexpredator;

	//		count = 0;

	//		while (count < count_apexpredator)
	//		{
	//			int r = rand() % (n * m);
	//			if (field[r] == nullptr)
	//			{
	//				field[r] = static_pointer_cast<Object>(make_shared<ApexPredator>());
	//				++count;
	//			}
	//		}
	//	}

	//	int stopper() // rewrite later
	//	{
	//		if (prey_count == 0 && count_predator == 0 && count_apexpredator == 0)
	//			return 1;
	//		else if (prey_count == 0 && count_predator == 0)
	//			return 2;
	//		else if (count_apexpredator == 0 && count_predator == 0)
	//			return 3;
	//		else if (prey_count == 0 && count_apexpredator == 0)
	//			return 4;
	//		else
	//			return 0;
	//	}

	//	void tick()
	//	{
	//		++iterations;

	//		for (int i = 0; i < rows; ++i)
	//		{
	//			for (int j = 0; j < cols; ++j)
	//			{
	//				int index = i * cols + j;

	//				if (index < field.size() && field[index] != nullptr)
	//				{
	//					shared_ptr<Object> obj = field[index];

	//					if (obj->key() == 1 || obj->key() == 2)
	//					{
	//						obj->action(generate_neibourhood(obj, *this, 1), *this);
	//					}
	//					else if (obj->key() == 3)
	//					{
	//						obj->action(generate_neibourhood(obj, *this, 1), *this);
	//					}
	//					else if (obj->key() == 4)
	//					{
	//						if (obj->get_hunger())
	//							obj->set_radius(2);
	//						else
	//							obj->set_radius(1);

	//						obj->action(generate_neibourhood(obj, *this, obj->get_radius()), *this);
	//					}
	//					else if (obj->key() == 5)
	//					{
	//						if (obj->get_hunger())
	//							obj->set_radius(3);
	//						else
	//							obj->set_radius(1);

	//						obj->action(generate_neibourhood(obj, *this, obj->get_radius()), *this);
	//					}
	//				}
	//			}
	//		}

	//		print();

	//		this_thread::sleep_for(chrono::milliseconds(3000));
	//	}

	//	void print() const 
	//	{
	//		clearConsole();

	//		std::cout << "Stones: " << stone_count
	//			<< " | Reefs: " << reef_count
	//			<< " | Prey: " << prey_count
	//			<< " | Predators: " << count_predator
	//			<< " | Apex Predators: " << count_apexpredator << "\n\n";

	//		for (size_t i = 0; i < rows; ++i) {
	//			for (size_t j = 0; j < cols; ++j) {
	//				if (field[i * cols + j]) {
	//					std::cout << field[i * cols + j]->key() << " ";
	//				}
	//				else {
	//					std::cout << ". ";
	//				}
	//			}
	//			std::cout << "\n";
	//		}
	//		std::cout << "\n";

	//		cout << "Iterations: " << iterations;
	//	}
	//};

	//struct Point
	//{
	//	int x;
	//	int y;

	//	Point() = default;

	//	Point(int kx, int ky) : x{ kx }, y{ ky } {}

	//	Point operator-(const Point& other) const
	//	{
	//		return { x - other.x, y - other.y };
	//	}

	//	Point operator+(const Point& other) const
	//	{
	//		return { x + other.x, y + other.y };
	//	}

	//	Point operator*(int scalar) const
	//	{
	//		return { x * scalar, y * scalar };
	//	}

	//	bool operator=(const Point& other) const
	//	{
	//		return (x == other.x) && (y == other.y);
	//	}

	//	bool operator!=(const Point& other) const
	//	{
	//		return (x != other.x) || (y != other.y);
	//	}

	//	float magnitude() const
	//	{
	//		return sqrt(x * x + y * y);
	//	}

	//	Point normalized() const
	//	{
	//		float mag = magnitude();
	//		if (mag == 0) return { 0, 0 };
	//		return { static_cast<int>(x / mag), static_cast<int>(y / mag) };
	//	}
	//};

	//struct Action
	//{
	//	Action(shared_ptr<Object> obj) : obj{ obj } {}
	//	virtual ~Action() = default;
	//	bool operator()(class Ocean& f) { return apply(f); }

	//protected:
	//	shared_ptr<Object> obj;

	//private:
	//	virtual bool apply(Ocean&) const = 0;
	//};

	//vector<vector<int>> generate_neibourhood(shared_ptr<Object> obj, const Ocean& ocean, int radius)
	//{
	//	vector<vector<int>> neighbourds;
	//	int x, y = -1;

	//	for (size_t i = 0; i < ocean.rows; ++i)
	//	{
	//		for (size_t j = 0; j < ocean.cols; ++j)
	//		{
	//			if (ocean.field[i * ocean.cols + j] == obj)
	//			{
	//				x = i;
	//				y = j;
	//			}
	//		}
	//	}

	//	if (x != -1 || y != -1)
	//	{
	//		for (int dx = ((-1) * radius); dx <= radius; dx++)
	//		{
	//			for (int dy = ((-1) * radius); dy <= radius; dy++)
	//			{
	//				if (dx == 0 && dy == 0) continue;

	//				int nx = (x + dx + ocean.rows) % ocean.rows;
	//				int ny = (y + dy + ocean.cols) % ocean.cols;

	//				if (ocean.field[nx * ocean.cols + ny] != nullptr)
	//				{
	//					vector<int> item;

	//					item.push_back(nx);
	//					item.push_back(ny);
	//					item.push_back(ocean.field[nx * ocean.cols + ny]->key());

	//					neighbourds.push_back(item);
	//				}
	//			}
	//		}
	//	}

	//	return neighbourds;
	//}

	//struct NoAction : public Action
	//{
	//	NoAction(shared_ptr<Object> obj) : Action{ obj } {}

	//	bool apply(Ocean& ocean) const override
	//	{
	//		return true;
	//	}
	//};

	//struct TransformToReef : public Action
	//{
	//	TransformToReef(shared_ptr<Object> obj) : Action{ obj } {}

	//	bool apply(Ocean& ocean) const override
	//	{
	//		for (size_t i = 0; i < ocean.rows; ++i)
	//		{
	//			for (size_t j = 0; j < ocean.cols; ++j)
	//			{
	//				if (ocean.field[i * ocean.cols + j] == obj)
	//				{
	//					ocean.field[i * ocean.cols + j] = static_pointer_cast<Object>(make_shared<Reef>());

	//					return true;
	//				}
	//			}
	//		}
	//		return false;
	//	}
	//};

	//struct TransformToStone : public Action
	//{
	//	TransformToStone(shared_ptr<Object> obj) : Action{ obj } {}

	//	bool apply(Ocean& ocean) const override
	//	{
	//		for (size_t i = 0; i < ocean.rows; ++i)
	//		{
	//			for (size_t j = 0; j < ocean.cols; ++j)
	//			{
	//				if (ocean.field[i * ocean.cols + j] == obj)
	//				{
	//					ocean.field[i * ocean.cols + j] = static_pointer_cast<Object>(make_shared<Stone>());

	//					return true;
	//				}
	//			}
	//		}
	//		return false;
	//	}
	//};

	//struct Die : public Action
	//{
	//	Die(shared_ptr<Object> obj) : Action{ obj } {}

	//	bool apply(Ocean& ocean) const override
	//	{
	//		for (size_t i = 0; i < ocean.rows; ++i)
	//		{
	//			for (size_t j = 0; j < ocean.cols; ++j)
	//			{
	//				if (ocean.field[i * ocean.cols + j] == obj)
	//				{
	//					ocean.field[i * ocean.cols + j].reset();

	//					return true;
	//				}
	//			}
	//		}
	//		return false;
	//	}
	//};

	//struct Move : public Action
	//{
	//	Move(shared_ptr<Object> obj, Point to, int rad) : Action{ obj }, go_to{ to }, radius{ rad } {}

	//	bool apply(Ocean& ocean) const override
	//	{
	//		for (size_t i = 0; i < ocean.rows; ++i)
	//		{
	//			for (size_t j = 0; j < ocean.cols; ++j)
	//			{
	//				if (ocean.field[i * ocean.cols + j] == obj)
	//				{
	//					if (ocean.field[go_to.x * ocean.cols + go_to.y] == nullptr)
	//					{
	//						ocean.field[go_to.x * ocean.cols + go_to.y] = obj;
	//						ocean.field[i * ocean.cols + j].reset();
	//					}
	//					else
	//					{
	//						move_random(obj, ocean, radius);
	//					}
	//					return true;
	//				}
	//			}
	//		}
	//		return false;
	//	}

	//private:
	//	Point go_to;
	//	int radius;
	//};

	//struct MoveRand : public Action
	//{
	//	MoveRand(shared_ptr<Object> obj, int rad) : Action{ obj }, radius{ rad } {}

	//	bool apply(Ocean& ocean) const override
	//	{
	//		for (size_t i = 0; i < ocean.rows; ++i)
	//		{
	//			for (size_t j = 0; j < ocean.cols; ++j)
	//			{
	//				if (ocean.field[i * ocean.cols + j] == obj)
	//				{
	//					for (int dx = ((-1) * radius); dx <= radius; dx++)
	//					{
	//						for (int dy = ((-1) * radius); dy <= radius; dy++)
	//						{
	//							if (dx == 0 && dy == 0) continue;

	//							int nx = (i + dx + ocean.rows) % ocean.rows;
	//							int ny = (j + dy + ocean.cols) % ocean.cols;

	//							if (ocean.field[nx * ocean.cols + ny] == nullptr)
	//							{
	//								ocean.field[nx * ocean.cols + ny] = obj;
	//								ocean.field[i * ocean.cols + j].reset();

	//								return true;
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//		return false;
	//	}

	//private:
	//	int radius;
	//};


	//struct Hunt : public Action
	//{
	//	Hunt(shared_ptr<Object> obj, Point to) : Action{ obj }, prey{ to } {}

	//	bool apply(Ocean& ocean) const override
	//	{
	//		for (size_t i = 0; i < ocean.rows; ++i)
	//		{
	//			for (size_t j = 0; j < ocean.cols; ++j)
	//			{
	//				if (ocean.field[i * ocean.cols + j] == obj)
	//				{
	//					ocean.field[prey.x * ocean.cols + prey.y].reset();
	//					ocean.field[prey.x * ocean.cols + prey.y] = obj;
	//					ocean.field[i * ocean.cols + j].reset();

	//					return true;
	//				}
	//			}
	//		}
	//		return false;
	//	}

	//private:
	//	Point prey;
	//};

	//struct Stone : public Object, public enable_shared_from_this<Stone>
	//{
	//	Stone() : life_duration(STONE_MIN_LIFE_DURATION + (rand() % RANDOM_SPREAD)), age(0) {}

	//	unique_ptr<Action> action(const vector<vector<int>>& neighbourds, Ocean& ocean) override
	//	{
	//		++age;

	//		if (age > life_duration) 
	//		{
	//			--ocean.stone_count;
	//			return make_unique<TransformToReef>(shared_from_this());
	//		}

	//		return make_unique<NoAction>(shared_from_this());
	//	}

	//	int key() const override { return 1; }

	//	bool get_adult() override { return false; }
	//	bool get_hunger() override { return false; }  
	//	void set_radius(int rad) override {}
	//	int get_radius() override { return 0; }

	//private:
	//	int age;
	//	int life_duration;
	//};

	//struct Reef : public Object, public enable_shared_from_this<Reef>
	//{
	//	Reef() : life_duration(STONE_MIN_LIFE_DURATION + (rand() % RANDOM_SPREAD)), age(0) {}

	//	unique_ptr<Action> action(const vector<vector<int>>& neighbourds, Ocean& ocean) override
	//	{
	//		++age;

	//		if (age > life_duration)
	//		{
	//			--ocean.reef_count;
	//			return make_unique<TransformToStone>(shared_from_this());
	//		}

	//		return make_unique<NoAction>(shared_from_this());
	//	}

	//	int key() const override { return 2; }

	//	bool get_adult() override { return false; }
	//	bool get_hunger() override { return false; }
	//	void set_radius(int rad) override {}
	//	int get_radius() override { return 0; }

	//private:
	//	int age;
	//	int life_duration;
	//};

	//struct Prey : public Object, public enable_shared_from_this<Prey>
	//{
	//private:
	//	int life_duration;
	//	int age;
	//	bool adult;
	//	int radius;

	//public:

	//	Prey() : life_duration(PREY_MIN_LIFE_DURATION + (rand() % RANDOM_SPREAD)), age(0), adult(false), radius{ 1 } {}

	//	unique_ptr<Action> action(const vector<vector<int>>& neighbourds, Ocean& ocean) override
	//	{
	//		++age;

	//		if (age > life_duration)
	//		{
	//			--ocean.prey_count;
	//			return make_unique<Die>(shared_from_this());
	//		}

	//		if (adult == false && age > PREY_ADULT_AGES)
	//			adult = true;

	//		for (size_t i = 0; i < ocean.rows; ++i)
	//		{
	//			for (size_t j = 0; j < ocean.cols; ++j)
	//			{
	//				if (ocean.field[i * ocean.cols + j] == shared_from_this())
	//				{
	//					if (neighbourds.size() == sqrt(radius * 2 + 1) - 1)
	//					{
	//						return make_unique<NoAction>(shared_from_this());
	//					}
	//					else if (neighbourds.size() > 0)
	//					{
	//						vector<Point> enemies;

	//						for (int n = 0; n < neighbourds.size(); ++n)
	//						{
	//							if (neighbourds[n][2] == 4 || neighbourds[n][2] == 5)
	//							{
	//								Point enemy(neighbourds[n][0], neighbourds[n][1]);
	//								enemies.push_back(enemy);
	//							}
	//						}

	//						if (!enemies.empty())
	//						{
	//							Point p(i, j);

	//							Point run = find_escape_direction(p, enemies, ocean.cols, ocean.rows);

	//							if (p != run)
	//							{
	//								return make_unique<Move>(shared_from_this(), run, radius);
	//							}
	//						}
	//						else
	//						{
	//							if (this->get_adult())
	//							{
	//								for (int pr = 0; pr < neighbourds.size(); ++pr)
	//								{
	//									if (neighbourds[pr][2] == 3)
	//									{
	//										shared_ptr<Object> second_prey = ocean.field[neighbourds[pr][0] * ocean.cols + neighbourds[pr][1]];

	//										if (second_prey->get_adult())
	//										{
	//											spawn(shared_from_this(), ocean);
	//											++ocean.prey_count;
	//										}
	//									}
	//								}
	//							}
	//							return make_unique<MoveRand>(shared_from_this(), radius);
	//						}
	//					}
	//				}
	//			}
	//		}

	//		return make_unique<NoAction>(shared_from_this());
	//	}

	//	bool get_adult() override { return adult; }
	//	bool get_hunger() override { return false; }
	//	int get_radius() override { return 1; }
	//	void set_radius(int rad) override {}

	//	int key() const override { return 3; }
	//};

	//struct Predator : public Object, public enable_shared_from_this<Predator>
	//{
	//private:
	//	int life_duration;
	//	int age;
	//	bool adult;
	//	int radius;
	//	bool hunger;
	//	int hunger_level;
	//	int well_fed_days;

	//public:

	//	Predator() : life_duration(PREDATOR_MIN_LIFE_DURATION + (rand() % RANDOM_SPREAD)), age(0), adult(false), 
	//		hunger_level{ 0 }, hunger{ false }, well_fed_days{ PREDATOR_WEL_FED_DAYS }, radius{ 1 } {}

	//	unique_ptr<Action> action(const vector<vector<int>>& neighbourds, Ocean& ocean) override
	//	{
	//		++age;
	//		--well_fed_days;

	//		if (age > life_duration)
	//		{
	//			--ocean.count_predator;
	//			return make_unique<Die>(shared_from_this());
	//		}

	//		if (adult == false && age > PREDATOR_ADULT_AGES)
	//			adult = true;

	//		if (!hunger && well_fed_days < 0)
	//		{
	//			hunger = true;
	//			hunger_level = 0;
	//		}

	//		if (hunger)
	//		{
	//			if (hunger_level >= PREDATOR_HUNGER_MAX)
	//			{
	//				--ocean.count_predator;
	//				return make_unique<Die>(shared_from_this());
	//			}
	//			++hunger_level;
	//		}

	//		for (size_t i = 0; i < ocean.rows; ++i)
	//		{
	//			for (size_t j = 0; j < ocean.cols; ++j)
	//			{
	//				if (ocean.field[i * ocean.cols + j] == shared_from_this())
	//				{
	//					if (neighbourds.size() == sqrt(radius * 2 + 1) - 1)
	//					{
	//						return make_unique<NoAction>(shared_from_this());
	//					}
	//					else if (neighbourds.size() > 0)
	//					{
	//						vector<Point> enemies;

	//						for (int n = 0; n < neighbourds.size(); ++n)
	//						{
	//							if (neighbourds[n][2] == 5)
	//							{
	//								Point enemy(neighbourds[n][0], neighbourds[n][1]);
	//								enemies.push_back(enemy);
	//							}
	//						}

	//						if (!enemies.empty())
	//						{
	//							Point p(i, j);

	//							Point run = find_escape_direction(p, enemies, ocean.cols, ocean.rows);

	//							if (p != run)
	//							{
	//								return make_unique<Move>(shared_from_this(), run, radius);
	//							}
	//						}
	//						else
	//						{
	//							for (int prey = 0; prey < neighbourds.size(); ++prey)
	//							{
	//								if (neighbourds[prey][2] == 3)
	//								{
	//									hunger = false;
	//									hunger_level = PREDATOR_WEL_FED_DAYS;

	//									--ocean.prey_count;

	//									return make_unique<Hunt>(shared_from_this(), Point(neighbourds[prey][0], neighbourds[prey][1]));
	//								}
	//							}

	//							if (this->get_adult())
	//							{
	//								for (int pr = 0; pr < neighbourds.size(); ++pr)
	//								{
	//									if (neighbourds[pr][2] == 4)
	//									{
	//										shared_ptr<Object> second_predator = ocean.field[neighbourds[pr][0] * ocean.cols + neighbourds[pr][1]];

	//										if (second_predator->get_adult())
	//										{
	//											++ocean.count_predator;
	//											spawn(shared_from_this(), ocean);
	//										}
	//									}
	//								}
	//							}
	//							return make_unique<MoveRand>(shared_from_this(), radius);
	//						}
	//					}
	//				}
	//			}
	//		}

	//		return make_unique<NoAction>(shared_from_this());
	//	}

	//	void set_radius(int rad) override { radius = rad; }
	//	int get_radius() override { return radius; }

	//	bool get_adult() override { return adult; }
	//	bool get_hunger() override { return hunger;  }

	//	int key() const override { return 4; }
	//};

	//struct ApexPredator : public Object, public enable_shared_from_this<ApexPredator>
	//{
	//private:
	//	int life_duration;
	//	int age;
	//	bool adult;
	//	int radius;
	//	bool hunger;
	//	int hunger_level;
	//	int well_fed_days;

	//public:

	//	ApexPredator() : life_duration(APEX_PREDATOR_MIN_LIFE_DURATION + (rand() % RANDOM_SPREAD)), age(0), adult(false),
	//		hunger_level{ 0 }, hunger{ false }, well_fed_days{ APEX_PREDATOR_WEL_FED_DAYS }, radius{ 1 } {}

	//	unique_ptr<Action> action(const vector<vector<int>>& neighbourds, Ocean& ocean) override
	//	{
	//		++age;
	//		--well_fed_days;

	//		if (age > life_duration)
	//		{
	//			--ocean.count_apexpredator;
	//			return make_unique<Die>(shared_from_this());
	//		}

	//		if (adult == false && age > APEX_PREDATOR_ADULT_AGES)
	//			adult = true;

	//		if (!hunger && well_fed_days < 0)
	//		{
	//			hunger = true;
	//			hunger_level = 0;
	//		}

	//		if (hunger)
	//		{
	//			if (hunger_level >= APEX_PREDATOR_HUNGER_MAX)
	//			{
	//				--ocean.count_apexpredator;
	//				return make_unique<Die>(shared_from_this());
	//			}
	//			++hunger_level;
	//		}

	//		for (size_t i = 0; i < ocean.rows; ++i)
	//		{
	//			for (size_t j = 0; j < ocean.cols; ++j)
	//			{
	//				if (ocean.field[i * ocean.cols + j] == shared_from_this())
	//				{
	//					if (neighbourds.size() == sqrt(radius * 2 + 1) - 1)
	//					{
	//						return make_unique<NoAction>(shared_from_this());
	//					}
	//					else if (neighbourds.size() > 0)
	//					{
	//						vector<Point> enemies;

	//						for (int n = 0; n < neighbourds.size(); ++n)
	//						{
	//							if (neighbourds[n][2] == 5)
	//							{
	//								Point enemy(neighbourds[n][0], neighbourds[n][1]);
	//								enemies.push_back(enemy);
	//							}
	//						}

	//						if (!enemies.empty())
	//						{
	//							Point p(i, j);

	//							Point run = find_escape_direction(p, enemies, ocean.cols, ocean.rows);

	//							if (p != run)
	//							{
	//								return make_unique<Move>(shared_from_this(), run, radius);
	//							}
	//						}
	//						else
	//						{
	//							for (int prey = 0; prey < neighbourds.size(); ++prey)
	//							{
	//								if (neighbourds[prey][2] == 3 || (neighbourds[prey][2] == 4 && hunger))
	//								{
	//									hunger = false;
	//									hunger_level = PREDATOR_WEL_FED_DAYS;

	//									if (neighbourds[prey][2] == 3)
	//										--ocean.prey_count;
	//									else
	//										--ocean.count_predator;

	//									return make_unique<Hunt>(shared_from_this(), Point(neighbourds[prey][0], neighbourds[prey][1]));
	//								}
	//							}

	//							if (this->get_adult())
	//							{
	//								for (int pr = 0; pr < neighbourds.size(); ++pr)
	//								{
	//									if (neighbourds[pr][2] == 4)
	//									{
	//										shared_ptr<Object> second_predator = ocean.field[neighbourds[pr][0] * ocean.cols + neighbourds[pr][1]];

	//										if (second_predator->get_adult())
	//										{
	//											++ocean.count_apexpredator;
	//											spawn(shared_from_this(), ocean);
	//										}
	//									}
	//								}
	//							}

	//							return make_unique<MoveRand>(shared_from_this(), radius);
	//						}
	//					}
	//				}
	//			}
	//		}

	//		return make_unique<NoAction>(shared_from_this());
	//	}

	//	void set_radius(int rad) override { radius = rad; }
	//	int get_radius() override { return radius; }

	//	bool get_adult() override { return adult; }
	//	bool get_hunger() override { return hunger; }

	//	int key() const override { return 5; }
	//};

	//void move_random(shared_ptr<Object> obj, Ocean& ocean, int radius)
	//{
	//	for (size_t i = 0; i < ocean.rows; ++i)
	//	{
	//		for (size_t j = 0; j < ocean.cols; ++j)
	//		{
	//			if (ocean.field[i * ocean.cols + j] == obj)
	//			{
	//				for (int dx = ((-1) * radius); dx <= radius; dx++)
	//				{
	//					for (int dy = ((-1) * radius); dy <= radius; dy++)
	//					{
	//						if (dx == 0 && dy == 0) continue;

	//						int nx = (i + dx + ocean.rows) % ocean.rows;
	//						int ny = (j + dy + ocean.cols) % ocean.cols;

	//						if (ocean.field[nx * ocean.cols + ny] == nullptr)
	//						{
	//							ocean.field[nx * ocean.cols + ny] = obj;
	//							ocean.field[i * ocean.cols + j].reset();
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	//void spawn(shared_ptr<Object> obj, Ocean& ocean)
	//{
	//	for (size_t i = 0; i < ocean.rows; ++i)
	//	{
	//		for (size_t j = 0; j < ocean.cols; ++j)
	//		{
	//			if (ocean.field[i * ocean.cols + j] == obj)
	//			{
	//				for (int dx = -1; dx <= 1; dx++)
	//				{
	//					for (int dy = -1; dy <= 1; dy++)
	//					{
	//						if (dx == 0 && dy == 0) continue;

	//						int nx = (i + dx + ocean.rows) % ocean.rows;
	//						int ny = (j + dy + ocean.cols) % ocean.cols;

	//						if (ocean.field[nx * ocean.cols + ny] == nullptr)
	//						{
	//							if (obj->key() == 3)
	//								ocean.field[nx * ocean.cols + ny] = make_shared<Prey>();
	//							else if (obj->key() == 4)
	//								ocean.field[nx * ocean.cols + ny] = make_shared<Predator>();
	//							else if (obj->key() == 5)
	//								ocean.field[nx * ocean.cols + ny] = make_shared<ApexPredator>();
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	//Point find_escape_direction(const Point& currentPos, const vector<Point>& predatorPositions, int cols, int rows) 
	//{

	//	Point threatVector = { 0, 0 };

	//	for (const auto& predatorPos : predatorPositions) 
	//	{
	//		int dx = predatorPos.x - currentPos.x;
	//		int dy = predatorPos.y - currentPos.y;

	//		if (dx > cols / 2) dx -= cols;
	//		if (dx < -cols / 2) dx += cols;
	//		if (dy > rows / 2) dy -= rows;
	//		if (dy < -rows / 2) dy += rows;

	//		Point toPredator = { dx, dy };
	//		Point normalized = toPredator.normalized();

	//		threatVector = threatVector + normalized;
	//	}

	//	if (threatVector.x == 0 && threatVector.y == 0) {
	//		return { 0, 0 };
	//	}

	//	Point escapeDirection = threatVector * -1;

	//	escapeDirection = escapeDirection.normalized();

	//	int finalX = 0;
	//	int finalY = 0;

	//	if (escapeDirection.x > 0.5) 
	//		finalX = 1;
	//	else if (escapeDirection.x < -0.5) 
	//		finalX = -1;

	//	if (escapeDirection.y > 0.5) 
	//		finalY = 1;
	//	else if (escapeDirection.y < -0.5) 
	//		finalY = -1;

	//	return { finalX, finalY };
	//}

	//int main()
	//{
	//	srand(time(nullptr));

	//	size_t rows, cols;

	//	cout << "Enter field size (&n &m): ";
	//	cin >> rows >> cols;

	//	Ocean ocean(rows, cols);

	//	int stop = ocean.stopper();

	//	ocean.print();

	//	clearConsole();

	//	while (stop == 0)
	//	{
	//		ocean.tick();
	//	
	//		stop = ocean.stopper();
	//	}
	//
	//	cout << endl << endl;

	//	if (stop == 1)
	//		cout << "No more alive animals" << endl;
	//	else if (stop == 2)
	//		cout << "Apex Predators win" << endl;
	//	else if (stop == 4)
	//		cout << "Predators win" << endl;
	//	else
	//		cout << "Preys win" << endl;
	//}