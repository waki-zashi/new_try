#include "MoveSpawn.h"
#include "Ocean.h"
#include "Objects.h"
#include "Actions.h"

#include <memory>
#include <vector>

void move_random(std::shared_ptr<Object> obj, Ocean& ocean, int radius)
{
	for (size_t i = 0; i < ocean.rows; ++i)
	{
		for (size_t j = 0; j < ocean.cols; ++j)
		{
			if (ocean.field[i * ocean.cols + j] == obj)
			{
				for (int dx = ((-1) * radius); dx <= radius; dx++)
				{
					for (int dy = ((-1) * radius); dy <= radius; dy++)
					{
						if (dx == 0 && dy == 0) continue;

						int nx = (i + dx + ocean.rows) % ocean.rows;
						int ny = (j + dy + ocean.cols) % ocean.cols;

						if (ocean.field[nx * ocean.cols + ny] == nullptr)
						{
							ocean.field[nx * ocean.cols + ny] = obj;
							ocean.field[i * ocean.cols + j] = nullptr;

							return;
						}
					}
				}
			}
		}
	}
}

void spawn(std::shared_ptr<Object> obj, Ocean& ocean)
{
	for (size_t i = 0; i < ocean.rows; ++i)
	{
		for (size_t j = 0; j < ocean.cols; ++j)
		{
			if (ocean.field[i * ocean.cols + j] == obj)
			{
				for (int dx = -1; dx <= 1; dx++)
				{
					for (int dy = -1; dy <= 1; dy++)
					{
						if (dx == 0 && dy == 0) continue;

						size_t ni = (i + dx + ocean.rows) % ocean.rows;
						size_t nj = (j + dy + ocean.cols) % ocean.cols;
						size_t new_index = ni * ocean.cols + nj;

						if (new_index < ocean.field.size() && !ocean.field[new_index]) {
							switch (obj->key()) {
							case 3:
								ocean.field[new_index] = std::make_shared<Prey>();
								ocean.prey_count++;
								break;
							case 4:
								ocean.field[new_index] = std::make_shared<Predator>();
								ocean.count_predator++;
								break;
							case 5:
								ocean.field[new_index] = std::make_shared<ApexPredator>();
								ocean.count_apexpredator++;
								break;
							default:
								break;
							}
							return;
						}
					}
				}
			}
		}
	}
}