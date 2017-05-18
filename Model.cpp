#include "Model.h"

/* Model
///////////////////*/
Model::Model(Color c)
: color(c)
{
	quadric = gluNewQuadric();
}

Model::~Model()
{
	gluDeleteQuadric(quadric);
}

/* Sphere
//////////////////*/
Sphere::Sphere(Color c, float r)
: Model(c), radius(r)
{}

void Sphere::draw()
{
	glColor3f(color.r, color.g, color.b);
	gluSphere(quadric, radius, 20, 10);
}

/* Cylinder
//////////////////*/
Cylinder::Cylinder(Color c, float h, float r)
: Model(c), height(h), radius(r)
{}

void Cylinder::draw()
{
	glColor3f(color.r, color.g, color.b);
	gluCylinder(quadric, radius, radius, height, 20, 2);
}