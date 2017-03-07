#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

struct Point
{
	float x, y, z;
};
struct Vector
{
	float x, y, z;
};
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
	//TODO implement cross product
	return a;
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