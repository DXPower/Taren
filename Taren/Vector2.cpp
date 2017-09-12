#include <math.h>
#include <string>
#include <sstream>
#include "Vector2.h"

Vector2 Vector2::zero = Vector2(0, 0);

Vector2::Vector2(float x, float y) : x(x), y(y) {

}

Vector2::~Vector2() {}

void Vector2::Normalize() {
	float m = Magnitude();
	x = x / m;
	y = y / m;
}

Vector2* Vector2::Normalized() {
	float m = Magnitude();
	return &Vector2(x / m, y / m);
}

float Vector2::Magnitude() {
	return sqrtf((x * x) + (y * y));
}

float Vector2::Magnitude2() {
	return (x * x) + (y * y);
}

Vector2* Vector2::Copy() {
	return &Vector2(x, y);
}

Vector2 Vector2::operator*(const int& rhs) {
	return Vector2(x * rhs, y * rhs);
}

bool Vector2::operator==(const Vector2& rhs) {
	return x == rhs.x && y == rhs.y;
}

bool Vector2::operator!=(const Vector2& rhs) {
	return x != rhs.x || y != rhs.y;
}

std::string Vector2::ToString() {
	std::ostringstream s;
	s << "(" << x << ", " << y << ")";
	return s.str();
}



