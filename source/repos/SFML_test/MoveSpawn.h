#pragma once

#include <vector>
#include <memory>

struct Object;
class Ocean;

void move_random(std::shared_ptr<Object> obj, Ocean& ocean, int radius);
void spawn(std::shared_ptr<Object> obj, Ocean& ocean);