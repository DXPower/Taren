#pragma once
#include <string>

class Vector2 {
	public:	
	static Vector2 zero;

	float x;
	float y;

	Vector2(float, float);
	~Vector2();

	Vector2* Normalized();
	Vector2* Copy();
	float Magnitude();
	float Magnitude2();/// <summary>Returns the magnitude squared. Faster but not accurate distance. Good for comparing</summary>
	std::string ToString();
	void Normalize();

	Vector2 operator*(const int& rhs);
	bool operator==(const Vector2& rhs);
	bool operator!=(const Vector2& rhs);
};

