#pragma once
#include <iostream>
using namespace std;

template<typename TemplateClass>
class Vector2D
{
private:

	TemplateClass x, y;
public:

	Vector2D() {};
	Vector2D(const TemplateClass& x, const TemplateClass& y) : x(x), y(y) {}

	TemplateClass const& get_x() const { return x; }
	TemplateClass const& get_y() const { return y; }

	void set_x(const TemplateClass& n_x) { x = n_x; }
	void set_y(const TemplateClass& n_y) { y = n_y; }

	operator Vector2D<float>()
	{
		return Vector2D<float>(this->x, this->y);
	}

	bool operator ==(const Vector2D& v2)
	{
		if (x == v2.x && y == v2.y)
			return true;
		return false;
	}

	bool operator !=(const Vector2D& v2)
	{
		if (x != v2.x && y != v2.y)
			return true;
		return false;
	}

	Vector2D operator + (const Vector2D& v2) const
	{
		Vector2D temp = *this;
		temp += v2;
		return temp;
	}

	Vector2D& operator +=(const Vector2D& v2)
	{
		x += v2.x;
		y += v2.y;
		return *this;
	}

	Vector2D operator - (const Vector2D& v2) const
	{
		Vector2D temp = *this;
		temp -= v2;
		return temp;
	}

	Vector2D& operator -=(const Vector2D& v2)
	{
		x -= v2.x;
		y -= v2.y;
		return *this;
	}

	Vector2D operator *(const int& num) const
	{
		Vector2D temp = *this;
		temp *= num;
		return temp;
	}

	Vector2D operator *=(const int& num)
	{
		x *= num;
		y *= num;
		return *this;
	}
};