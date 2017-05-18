#pragma once
#include "Vector3.h"
#include <vector>

class Model;

class Transform
{
public:
	Vector3 position;
	Vector3 eulerAngles;
	Vector3 scale;
	Model* model;
	std::vector<Transform*> children;
	void glTransform();
	void render();
	Transform()
		: scale(1, 1, 1) {}
};