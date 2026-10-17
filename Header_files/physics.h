#pragma once

#include <raylib.h>
#include <utility>
#include <vector>

using namespace std;

pair<float, Vector2> CheckCollision(const Rectangle& active, Vector2 velocity, float dt, const Rectangle& passive);