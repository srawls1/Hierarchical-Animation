#pragma once
#include "Transform.h"
#include "Color.h"
#include "GL/glut.h"

class Model
{
protected:
	GLUquadric* quadric;
	Color color;
	Model(Color c);
public:
	~Model();
	virtual void draw() = 0;
};

class Sphere : Model
{
	float radius;
public:
	Sphere(Color c, float r);
	void draw();
};

class Cylinder : Model
{
	float height;
	float radius;
public:
	Cylinder(Color c, float h, float r);
	void draw();
};