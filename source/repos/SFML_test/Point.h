#pragma once

struct Point
{
	int x;
	int y;

	Point() = default;

	Point(int kx, int ky) : x{ kx }, y{ ky } {}

	Point operator-(const Point& other) const
	{
		return { x - other.x, y - other.y };
	}

	Point operator+(const Point& other) const
	{
		return { x + other.x, y + other.y };
	}

	Point operator*(int scalar) const
	{
		return { x * scalar, y * scalar };
	}

	bool operator=(const Point& other) const
	{
		return (x == other.x) && (y == other.y);
	}

	bool operator!=(const Point& other) const
	{
		return (x != other.x) || (y != other.y);
	}

	float magnitude() const
	{
		return sqrt(x * x + y * y);
	}

	Point normalized() const
	{
		float mag = magnitude();
		if (mag == 0) return { 0, 0 };
		return { static_cast<int>(x / mag), static_cast<int>(y / mag) };
	}
};