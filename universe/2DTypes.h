#pragma once

#include <cmath>

template<typename T>
struct Point2D
{
	// Constructors
	template<typename T>
	Point2D(T ix, T iy) : x(ix), y(iy) {}
	template<typename T>
	Point2D(T ia) : x(ia), y(ia) {}
	template<typename T>
	Point2D() : x(0), y(0) {}

	// transforms
	void normalize()
	{
		if (x != 0 || y != 0)
		{
			T lenght = sqrt(pow(x, 2) + pow(y, 2));
			x /= lenght;
			y /= lenght;
		}
	}

	Point2D<T> normalized()
	{
		if (x != 0 || y != 0)
		{
			T lenght = sqrt(pow(x, 2) + pow(y, 2));
			return Point2D<T>(x / lenght, y / lenght);
		}
		else
		{
			return Point2D<T>(0, 0);
		}
	}

	void rotate(T rot)
	{
		T x_1 = x;
		x = (x * cos(rot)) - (y * sin(rot));
		y = (x_1 * sin(rot)) + (y * cos(rot));
	}

	Point2D<T> rotated(T rot)
	{
		return Point2D<T>(
			(x * cos(rot)) - (y * sin(rot)),
			(x * sin(rot)) + (y * cos(rot))
		);
	}

	T absolute() const
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	T dotProduct(const Point2D<T>& other) const
	{
		return x * other.x + y * other.y;
	}

	// Operators
	template<typename T>
	Point2D<T> operator+(const Point2D<T>& right) const 
	{
		Point2D<T> temp(*this);
		temp += right;
		return temp;
	}

	template<typename T>
	Point2D<T> operator-(const Point2D<T>& right) const 
	{
		Point2D<T> temp(*this);
		temp -= right;
		return temp;
	}

	template<typename T>
	Point2D<T> operator*(const Point2D<T>& right) const 
	{
		Point2D<T> temp(*this);
		temp *= right;
		return temp;
	}

	template<typename T>
	Point2D<T> operator/(const Point2D<T>& right) const
	{
		Point2D<T> temp(*this);
		temp /= right;
		return temp;
	}
	
	template<typename T>
	Point2D<T>& operator+=(const Point2D<T>& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}
	
	template<typename T>
	Point2D<T>& operator-=(const Point2D<T>& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}
	
	template<typename T>
	Point2D<T>& operator*=(const Point2D<T>& right)
	{
		x *= right.x;
		y *= right.y;
		return *this;
	}

	template<typename T>
	Point2D<T>& operator/=(const Point2D<T>& right)
	{
		if (right.x != 0 && right.y != 0)
		{
			x /= right.x;
			y /= right.y;
		}
		return *this;
	}

	// Variables
	T x, y;
};

template<typename T>
struct Rect2D
{
	Rect2D() : pos(), width(0), height(0) {}
	Rect2D(T x, T y, T w, T h) : pos(x, y), width(w), height(h) {}

	Point2D<T> pos;

	bool IsPointWithin(T x, T y) const
	{
		T bx = pos.x + width;
		T by = pos.y + height;

		return ((x >= pos.x && y >= pos.y) && (x < bx && y < by));
	}

	T width;
	T height;
};

enum class Direction
{
	UP, DOWN, LEFT, RIGHT
};