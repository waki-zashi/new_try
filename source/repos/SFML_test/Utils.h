#pragma once

#include <vector>
#include <memory>

class Object;
class Ocean;
struct Point;

void clearConsole();
std::vector<std::vector<int>> generate_neibourhood(std::shared_ptr<Object> obj, const Ocean& ocean, int radius);
//void move_random(std::shared_ptr<Object> obj, Ocean& ocean, int radius);
//void spawn(std::shared_ptr<Object> obj, Ocean& ocean);
Point find_escape_direction(const Point& currentPos, const std::vector<Point>& predatorPositions, int cols, int rows);