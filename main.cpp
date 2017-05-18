#define _USE_MATH_DEFINES
#include "Model.h"
#include "Transform.h"
#include "GL/glut.h"
#include <unordered_map>

Transform origin;
Transform cameraRig;
Transform cameraPivot;
Transform camera;
Transform ujoint1;
Transform ljoint1;
Transform ujoint2;
Transform ljoint2;
Transform ujoint3;
Transform ljoint3;
Transform ujoint4;
Transform ljoint4;
Transform ujoint5;
Transform ljoint5;
Transform ujoint6;
Transform ljoint6;
Transform headJointX;
Transform headJointY;


void init(int* argc, char* argv[])
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glPolygonMode(GL_FRONT, GL_FILL);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Spencer Rawls - Assignment 4");

	glViewport(0, 0, 400, 300);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.33, 0.1, 20);
}

float zoomScale = 0.1f;

// buttons 3 and 4 are scroll up and down?
void onClick(int button, int state, int x, int y)
{
	/*if (button == 3)
	{
		printf("button 3");
		camera.position.z -= zoomScale * camera.position.z;
	}
	else if (button == 4)
	{
		printf("button 4");
		camera.position.z += zoomScale * camera.position.z;
	}*/
}

float rotScale = 1;
int prevX = -1;
int prevY = -1;

void onMouseMoved(int x, int y)
{
	if (prevX != -1 && prevY != -1)
	{
		cameraRig.eulerAngles.y += (x - prevX) * rotScale;
		cameraPivot.eulerAngles.x += (y - prevY) * rotScale;
	}
	prevX = x;
	prevY = y;
}

float dragScale = 0.05f;

void onMouseDragged(int x, int y)
{
	if (prevX != -1 && prevY != -1)
	{
		float theta = cameraRig.eulerAngles.y * M_PI / 180;
		float phi = (M_PI / 2 - cameraPivot.eulerAngles.x) * M_PI / 180;
		Vector3 right(sin(theta), 0, cos(theta));
		Vector3 up(cos(phi) * cos(theta), sin(phi), -cos(phi) * sin(theta));
		cameraRig.position = cameraRig.position
			+ right * (x - prevX) * -dragScale
			+ up * (y - prevY) * dragScale;
	}
	prevX = x;
	prevY = y;
}

enum turnDir {
	X,
	Y,
	Z,
	NONE
};
std::unordered_map<Transform*, turnDir> selected;

void select(Transform* trans, turnDir dir)
{
	selected[trans] = dir;
}

void onKeyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a': select(&ujoint1, Z); break;
	case 's': select(&ujoint2, Z); break;
	case 'd': select(&ujoint3, Z); break;
	case 'f': select(&ujoint4, Z); break;
	case 'g': select(&ujoint5, Z); break;
	case 'h': select(&ujoint6, Z); break;
	case 'z': select(&ljoint1, X); break;
	case 'x': select(&ljoint2, X); break;
	case 'c': select(&ljoint3, X); break;
	case 'v': select(&ljoint4, X); break;
	case 'b': select(&ljoint5, X); break;
	case 'n': select(&ljoint6, X); break;
	case 'j': 
		select(&headJointX, X);
		select(&headJointY, Y);
		break;
	case '+':
		camera.position.z -= zoomScale * camera.position.z;
		break;
	case '-':
		camera.position.z += zoomScale * camera.position.z;
		break;
	}
}

void deselect(Transform* trans)
{
	selected[trans] = NONE;
}

void onKeyReleased(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a': deselect(&ujoint1); break;
	case 's': deselect(&ujoint2); break;
	case 'd': deselect(&ujoint3); break;
	case 'f': deselect(&ujoint4); break;
	case 'g': deselect(&ujoint5); break;
	case 'h': deselect(&ujoint6); break;
	case 'z': deselect(&ljoint1); break;
	case 'x': deselect(&ljoint2); break;
	case 'c': deselect(&ljoint3); break;
	case 'v': deselect(&ljoint4); break;
	case 'b': deselect(&ljoint5); break;
	case 'n': deselect(&ljoint6); break;
	case 'j':
		deselect(&headJointX);
		deselect(&headJointY);
	}
}

bool movingUp = false;
bool movingDown = false;
bool movingRight = false;
bool movingLeft = false;

void onSpecialPressed(int keyCode, int x, int y)
{
	if (keyCode == GLUT_KEY_UP)
	{
		movingUp = true;
	}
	else if (keyCode == GLUT_KEY_DOWN)
	{
		movingDown = true;
	}
	else if (keyCode == GLUT_KEY_LEFT)
	{
		movingLeft = true;
	}
	else if (keyCode == GLUT_KEY_RIGHT)
	{
		movingRight = true;
	}
}

void onSpecialReleased(int keyCode, int x, int y)
{
	if (keyCode == GLUT_KEY_UP)
	{
		movingUp = false;
	}
	else if (keyCode == GLUT_KEY_DOWN)
	{
		movingDown = false;
	}
	else if (keyCode == GLUT_KEY_LEFT)
	{
		movingLeft = false;
	}
	else if (keyCode == GLUT_KEY_RIGHT)
	{
		movingRight = false;
	}
}

float rotateSpeed = 0.1f;

void update()
{
	int mult = (int)movingDown - (int)movingUp;
	int mult2 = (int)movingRight - (int)movingLeft;
	for (std::pair<Transform*, turnDir> trans : selected)
	{
		switch (trans.second)
		{
		case X:
			trans.first->eulerAngles.x += mult * rotateSpeed;
			break;
		case Y:
			trans.first->eulerAngles.y += mult2 * rotateSpeed;
			break;
		case Z:
			trans.first->eulerAngles.z += mult * rotateSpeed;
			break;
		case NONE:
			continue;
		}		
	}
	glutPostRedisplay();
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// begin(HACK)
	float theta = cameraRig.eulerAngles.y * M_PI / 180;
	float phi = (M_PI / 2 - cameraPivot.eulerAngles.x) * M_PI / 180;
	Vector3 forward(sin(phi) * cos(theta), -cos(phi), -sin(phi) * sin(theta));
	Vector3 s = cameraRig.position + forward * -camera.position.z;
	Vector3 t = cameraRig.position;
	Vector3 u(cos(phi) * cos(theta), sin(phi), -cos(phi) * sin(theta));
	// end(HACK)

	gluLookAt(s.x, s.y, s.z, t.x, t.y, t.z, u.x, u.y, u.z);
	glCullFace(GL_BACK);
	origin.render();

	glFlush();
}

int main(int argc, char* argv[])
{
	// camera
	cameraRig.eulerAngles = Vector3(0, 45, 0);
	origin.children.push_back(&cameraRig);
	cameraPivot.eulerAngles = Vector3(30, 0, 0);
	cameraRig.children.push_back(&cameraPivot);
	camera.position = Vector3(0, 0, 7);
	cameraPivot.children.push_back(&camera);

	// models
	Cylinder legMod(green, 2, 0.5f);
	Sphere jointMod(blue, 0.5f);
	Sphere bodyMod(white, 0.5f);
	Sphere headMod(red, 0.5f);

	// body
	Transform bodyTrans;
	bodyTrans.scale = Vector3(4, 4, 4);
	bodyTrans.model = (Model*)&bodyMod;
	origin.children.push_back(&bodyTrans);
	
	// leg 1
	ujoint1.position = Vector3(.292f, 0, -.132f);
	ujoint1.eulerAngles = Vector3(0, 30, 0);
	bodyTrans.children.push_back(&ujoint1);
	
	Transform uleg1;
	uleg1.eulerAngles = Vector3(0, 90, 180);
	uleg1.scale = Vector3(0.15f, 0.2f, 0.15f);
	uleg1.model = (Model*)&legMod;
	ujoint1.children.push_back(&uleg1);

	ljoint1.position = Vector3(0, 0, 2);
	ljoint1.eulerAngles = Vector3(30, 0, 0);
	ljoint1.scale = Vector3(1.33f, 1, 1.33f);
	ljoint1.model = (Model*)&jointMod;
	uleg1.children.push_back(&ljoint1);

	Transform lleg1;
	lleg1.position = Vector3(0, 0, 0);
	lleg1.scale = Vector3(0.62f, 0.77f, 0.57f);
	lleg1.model = (Model*)&legMod;
	ljoint1.children.push_back(&lleg1);

	// leg 2
	ujoint2.position = Vector3(.32f, 0, 0);
	ujoint2.eulerAngles = Vector3(0, 0, 0);
	bodyTrans.children.push_back(&ujoint2);

	Transform uleg2;
	uleg2.eulerAngles = Vector3(0, 90, 180);
	uleg2.scale = Vector3(0.15f, 0.2f, 0.15f);
	uleg2.model = (Model*)&legMod;
	ujoint2.children.push_back(&uleg2);

	ljoint2.position = Vector3(0, 0, 2);
	ljoint2.eulerAngles = Vector3(30, 0, 0);
	ljoint2.scale = Vector3(1.33f, 1, 1.33f);
	ljoint2.model = (Model*)&jointMod;
	uleg2.children.push_back(&ljoint2);

	Transform lleg2;
	lleg2.position = Vector3(0, 0, 0);
	lleg2.scale = Vector3(0.62f, 0.77f, 0.57f);
	lleg2.model = (Model*)&legMod;
	ljoint2.children.push_back(&lleg2);

	// leg 3
	ujoint3.position = Vector3(.292f, 0, .132f);
	ujoint3.eulerAngles = Vector3(0, -30, 0);
	bodyTrans.children.push_back(&ujoint3);

	Transform uleg3;
	uleg3.eulerAngles = Vector3(0, 90, 180);
	uleg3.scale = Vector3(0.15f, 0.2f, 0.15f);
	uleg3.model = (Model*)&legMod;
	ujoint3.children.push_back(&uleg3);

	ljoint3.position = Vector3(0, 0, 2);
	ljoint3.eulerAngles = Vector3(30, 0, 0);
	ljoint3.scale = Vector3(1.33f, 1, 1.33f);
	ljoint3.model = (Model*)&jointMod;
	uleg3.children.push_back(&ljoint3);

	Transform lleg3;
	lleg3.position = Vector3(0, 0, 0);
	lleg3.scale = Vector3(0.62f, 0.77f, 0.57f);
	lleg3.model = (Model*)&legMod;
	ljoint3.children.push_back(&lleg3);

	// leg 4
	ujoint4.position = Vector3(-.292f, 0, -.132f);
	ujoint4.eulerAngles = Vector3(0, 150, 0);
	bodyTrans.children.push_back(&ujoint4);

	Transform uleg4;
	uleg4.eulerAngles = Vector3(0, 90, 180);
	uleg4.scale = Vector3(0.15f, 0.2f, 0.15f);
	uleg4.model = (Model*)&legMod;
	ujoint4.children.push_back(&uleg4);

	ljoint4.position = Vector3(0, 0, 2);
	ljoint4.eulerAngles = Vector3(30, 0, 0);
	ljoint4.scale = Vector3(1.33f, 1, 1.33f);
	ljoint4.model = (Model*)&jointMod;
	uleg4.children.push_back(&ljoint4);

	Transform lleg4;
	lleg4.position = Vector3(0, 0, 0);
	lleg4.scale = Vector3(0.62f, 0.77f, 0.57f);
	lleg4.model = (Model*)&legMod;
	ljoint4.children.push_back(&lleg4);

	// leg 5
	ujoint5.position = Vector3(-.32f, 0, 0);
	ujoint5.eulerAngles = Vector3(0, 180, 0);
	bodyTrans.children.push_back(&ujoint5);

	Transform uleg5;
	uleg5.eulerAngles = Vector3(0, 90, 180);
	uleg5.scale = Vector3(0.15f, 0.2f, 0.15f);
	uleg5.model = (Model*)&legMod;
	ujoint5.children.push_back(&uleg5);

	ljoint5.position = Vector3(0, 0, 2);
	ljoint5.eulerAngles = Vector3(30, 0, 0);
	ljoint5.scale = Vector3(1.33f, 1, 1.33f);
	ljoint5.model = (Model*)&jointMod;
	uleg5.children.push_back(&ljoint5);

	Transform lleg5;
	lleg5.position = Vector3(0, 0, 0);
	lleg5.scale = Vector3(0.62f, 0.77f, 0.57f);
	lleg5.model = (Model*)&legMod;
	ljoint5.children.push_back(&lleg5);

	// leg 6
	ujoint6.position = Vector3(-.292f, 0, .132f);
	ujoint6.eulerAngles = Vector3(0, 210, 0);
	bodyTrans.children.push_back(&ujoint6);

	Transform uleg6;
	uleg6.eulerAngles = Vector3(0, 90, 180);
	uleg6.scale = Vector3(0.15f, 0.2f, 0.15f);
	uleg6.model = (Model*)&legMod;
	ujoint6.children.push_back(&uleg6);

	ljoint6.position = Vector3(0, 0, 2);
	ljoint6.eulerAngles = Vector3(30, 0, 0);
	ljoint6.scale = Vector3(1.33f, 1, 1.33f);
	ljoint6.model = (Model*)&jointMod;
	uleg6.children.push_back(&ljoint6);

	Transform lleg6;
	lleg6.position = Vector3(0, 0, 0);
	lleg6.scale = Vector3(0.62f, 0.77f, 0.57f);
	lleg6.model = (Model*)&legMod;
	ljoint6.children.push_back(&lleg6);

	// head
	headJointY.position = Vector3(0, 0, -.457f);
	bodyTrans.children.push_back(&headJointY);
	headJointY.children.push_back(&headJointX);
	Transform head;
	head.position = Vector3(0, 0, -.217f);
	head.scale = Vector3(0.5f, 0.5f, 0.5f);
	head.model = (Model*)&headMod;
	headJointX.children.push_back(&head);

	// run it
	init(&argc, argv);
	glutDisplayFunc(draw);
	glutKeyboardFunc(onKeyPressed);
	glutKeyboardUpFunc(onKeyReleased);
	glutSpecialFunc(onSpecialPressed);
	glutSpecialUpFunc(onSpecialReleased);
	glutMouseFunc(onClick);
	glutMotionFunc(onMouseDragged);
	glutPassiveMotionFunc(onMouseMoved);
	glutIdleFunc(update);

	glutMainLoop();
}