#include "Actions.h"
#include "Ocean.h"
#include "Utils.h"
#include "MoveSpawn.h"

using namespace std;

Action::Action(shared_ptr<Object> obj) : obj{ obj } {}

NoAction::NoAction(shared_ptr<Object> obj) : Action{ obj } {}

bool NoAction::apply(Ocean& ocean) const
{
	return true;
}

TransformToReef::TransformToReef(shared_ptr<Object> obj) : Action{ obj } {}


bool TransformToReef::apply(Ocean& ocean) const 
{
	for (size_t i = 0; i < ocean.rows; ++i)
	{
		for (size_t j = 0; j < ocean.cols; ++j)
		{
			if (ocean.field[i * ocean.cols + j] == obj)
			{
				ocean.field[i * ocean.cols + j] = static_pointer_cast<Object>(make_shared<Reef>());
				/*delete ocean.field[i * ocean.cols + j];
				ocean.field[i * ocean.cols + j] = new Reef();*/

				return true;
			}
		}
	}
	return false;
}

TransformToStone::TransformToStone(shared_ptr<Object> obj) : Action{ obj } {}


bool TransformToStone::apply(Ocean& ocean) const 
{
	for (size_t i = 0; i < ocean.rows; ++i)
	{
		for (size_t j = 0; j < ocean.cols; ++j)
		{
			if (ocean.field[i * ocean.cols + j] == obj)
			{
				ocean.field[i * ocean.cols + j] = static_pointer_cast<Object>(make_shared<Stone>());
				/*delete ocean.field[i * ocean.cols + j];
				ocean.field[i * ocean.cols + j] = new Stone();*/

				return true;
			}
		}
	}
	return false;
}

Die::Die(shared_ptr<Object> obj) : Action{ obj } {}

bool Die::apply(Ocean & ocean) const 
{
	for (size_t i = 0; i < ocean.rows; ++i)
	{
		for (size_t j = 0; j < ocean.cols; ++j)
		{
			if (ocean.field[i * ocean.cols + j] == obj)
			{
				ocean.field[i * ocean.cols + j].reset();

				return true;
			}
		}
	}
	return false;
}

Move::Move(shared_ptr<Object> obj, Point to, int rad) : Action{ obj }, go_to{ to }, radius{ rad } {}


bool Move::apply(Ocean& ocean) const
{
	for (size_t i = 0; i < ocean.rows; ++i)
	{
		for (size_t j = 0; j < ocean.cols; ++j)
		{
			if (ocean.field[i * ocean.cols + j] == obj)
			{
				if (ocean.field[go_to.x * ocean.cols + go_to.y] == nullptr)
				{
					ocean.field[go_to.x * ocean.cols + go_to.y] = obj;
					ocean.field[i * ocean.cols + j].reset();
				}
				else
				{
					move_random(obj, ocean, radius);
				}
				return true;
			}
		}
	}
	return false;
}

MoveRand::MoveRand(shared_ptr<Object> obj, int rad) : Action{ obj }, radius{ rad } {}


bool MoveRand::apply(Ocean& ocean) const 
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
							ocean.field[i * ocean.cols + j].reset();

							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool Hunt::apply(Ocean& ocean) const 
{
	for (size_t i = 0; i < ocean.rows; ++i)
	{
		for (size_t j = 0; j < ocean.cols; ++j)
		{
			if (ocean.field[i * ocean.cols + j] == obj)
			{
				ocean.field[prey.x * ocean.cols + prey.y].reset();
				ocean.field[prey.x * ocean.cols + prey.y] = obj;
				ocean.field[i * ocean.cols + j].reset();
					
				return true;
			}
		}
	}
	return false;
}