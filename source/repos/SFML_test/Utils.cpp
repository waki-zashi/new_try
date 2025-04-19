#include "Utils.h"    
#include "Ocean.h"
#include "Objects.h"
#include "Actions.h"
#include "Point.h"

#include <memory>
#include <vector>


void clearConsole()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

std::vector<std::vector<int>> generate_neibourhood(std::shared_ptr<Object> obj, const Ocean& ocean, int radius)
{
	std::vector<std::vector<int>> neighbourds;
	int x, y = -1;

	for (size_t i = 0; i < ocean.rows; ++i)
	{
		for (size_t j = 0; j < ocean.cols; ++j)
		{
			if (ocean.field[i * ocean.cols + j] == obj)
			{
				x = i;
				y = j;
			}
		}
	}

	if (x != -1 || y != -1)
	{
		for (int dx = ((-1) * radius); dx <= radius; dx++)
		{
			for (int dy = ((-1) * radius); dy <= radius; dy++)
			{
				if (dx == 0 && dy == 0) continue;

				int nx = (x + dx + ocean.rows) % ocean.rows;
				int ny = (y + dy + ocean.cols) % ocean.cols;

				if (ocean.field[nx * ocean.cols + ny] != nullptr)
				{
					std::vector<int> item;

					item.push_back(nx);
					item.push_back(ny);
					item.push_back(ocean.field[nx * ocean.cols + ny]->key());

					neighbourds.push_back(item);
				}
			}
		}
	}

	return neighbourds;
}

//void move_random(std::shared_ptr<Object> obj, Ocean& ocean, int radius)
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
//
//						int nx = (i + dx + ocean.rows) % ocean.rows;
//						int ny = (j + dy + ocean.cols) % ocean.cols;
//
//						if (ocean.field[nx * ocean.cols + ny] == nullptr)
//						{
//							ocean.field[nx * ocean.cols + ny] = obj;
//							ocean.field[i * ocean.cols + j] = nullptr;
//
//							return;
//						}
//					}
//				}
//			}
//		}
//	}
//}
//
//void spawn(std::shared_ptr<Object> obj, Ocean& ocean)
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
//
//						size_t ni = (i + dx + ocean.rows) % ocean.rows;
//						size_t nj = (j + dy + ocean.cols) % ocean.cols;
//						size_t new_index = ni * ocean.cols + nj;
//
//						if (new_index < ocean.field.size() && !ocean.field[new_index]) {
//							switch (obj->key()) {
//							case 3:
//								ocean.field[new_index] = std::make_shared<Prey>();
//								ocean.prey_count++;
//								break;
//							case 4:
//								ocean.field[new_index] = std::make_shared<Predator>();
//								ocean.count_predator++;
//								break;
//							case 5:
//								ocean.field[new_index] = std::make_shared<ApexPredator>();
//								ocean.count_apexpredator++;
//								break;
//							default:
//								break;
//							}
//							return;
//						}
//					}
//				}
//			}
//		}
//	}
//}

Point find_escape_direction(const Point& currentPos, const std::vector<Point>& predatorPositions, int cols, int rows)
{

	Point threatVector = { 0, 0 };

	for (const auto& predatorPos : predatorPositions)
	{
		int dx = predatorPos.x - currentPos.x;
		int dy = predatorPos.y - currentPos.y;

		if (dx > cols / 2) dx -= cols;
		if (dx < -cols / 2) dx += cols;
		if (dy > rows / 2) dy -= rows;
		if (dy < -rows / 2) dy += rows;

		Point toPredator = { dx, dy };
		Point normalized = toPredator.normalized();

		threatVector = threatVector + normalized;
	}

	if (threatVector.x == 0 && threatVector.y == 0) {
		return { 0, 0 };
	}

	Point escapeDirection = threatVector * -1;

	escapeDirection = escapeDirection.normalized();

	int finalX = 0;
	int finalY = 0;

	if (escapeDirection.x > 0.5)
		finalX = 1;
	else if (escapeDirection.x < -0.5)
		finalX = -1;

	if (escapeDirection.y > 0.5)
		finalY = 1;
	else if (escapeDirection.y < -0.5)
		finalY = -1;

	return { finalX, finalY };
}