#pragma once

#include <string>

class Point2D {
public:
	float x;
	float y;
	Point2D(float x, float y) : x(x), y(y) {}
	Point2D() {}
	std::string string();
};