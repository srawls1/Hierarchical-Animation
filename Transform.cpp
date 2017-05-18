#include "Transform.h"
#include "Model.h"
#include "GL/glut.h"

void Transform::glTransform()
{
	glTranslatef(position.x, position.y, position.z);
	glRotatef(eulerAngles.y, 0, 1, 0);
	glRotatef(eulerAngles.x, 1, 0, 0);
	glRotatef(eulerAngles.z, 0, 0, 1);
	glScalef(scale.x, scale.y, scale.y);
}

void Transform::render()
{
	glPushMatrix();
	glTransform();
	if (model != nullptr)
	{
		model->draw();
	}
	for (int i = 0; i < children.size(); ++i)
	{
		children[i]->render();
	}
	glPopMatrix();
}