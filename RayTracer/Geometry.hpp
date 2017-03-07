#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <cmath>

struct Point
{
	float x, y, z;
};
struct Vector
{
	float x, y, z;
};

static double length(Vector v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

static Vector normalize(Vector v){
    float a = length(v);
    return {v.x/a, v.y/a, v.z/a};
}

struct Ray
{
	Point o;
	Vector d;
};

template <typename T,typename U>
float dot(T a,U b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

template <typename T>
T operator / (T a, float b)
{
	return T{a.x / b, a.y / b, a.z / b};
}
template <typename T>
T operator * (T a, float b)
{
	return T{ a.x * b, a.y * b, a.z * b };
}

template <typename T,typename U>
T cross(T a, U b)
{
    return T{(a.y * b.z) - (a.z * b.y), -((a.x * b.z) - (a.z * b.x)), (a.x * b.y) - (a.y * b.x)};
}

template <typename T,typename U>
T operator+(T a, U b)
{
	return T{ a.x + b.x, a.y + b.y, a.z + b.z };
}

template <typename T>
T operator-=(T a, T b)
{
	return T{ a.x - b.x, a.y - b.y, a.z - b.z };
}

template <typename T>
T operator-(T a)
{
	return T{ -a.x ,- a.y , -a.z  };
}

inline Vector operator-(Point a, Point b)
{
	return{ a.x - b.x, a.y - b.y, a.z - b.z };
}

inline Vector operator-(Vector a, Vector b)
{
	return{ a.x - b.x, a.y - b.y, a.z - b.z };
}

inline Point operator-(Point a, Vector b)
{
	return{ a.x - b.x, a.y - b.y, a.z - b.z };
}


#endif
