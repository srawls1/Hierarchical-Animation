#include "Vector3.h"

Vector3 operator+(Vector3 v1, Vector3 v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 operator*(Vector3 v1, float a)
{
	return Vector3(v1.x * a, v1.y * a, v1.z * a);
}