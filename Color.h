#pragma once

struct Color
{
	float r, g, b;
	Color(float rr, float gg, float bb)
		: r(rr), g(gg), b(bb) {}
};

extern Color white;
extern Color red;
extern Color blue;
extern Color green;
extern Color cyan;
extern Color magenta;
extern Color yellow;
extern Color black;