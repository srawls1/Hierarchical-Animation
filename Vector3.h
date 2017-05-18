#pragma once

struct Vector3
{
	float x, y, z;
	Vector3(float xx = 0, float yy = 0, float zz = 0)
		: x(xx), y(yy), z(zz) {}
};

Vector3 operator+(Vector3 v1, Vector3 v2);

Vector3 operator*(Vector3 v1, float a);