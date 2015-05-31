#include "Cone.h"

Cone::Cone(Vector base, float height, float baseRadius, Colour colour)
{
	this->color = colour;
	this->center = base;
	this->height = height;
	this->radius = baseRadius;
}

float Cone::intersect(Vector pos, Vector dir)
{
	auto a = powf(radius / height, 2);
	auto b = pos.x - center.x;
	auto c = height - pos.y + center.y;
	auto d = pos.z - center.z;

	auto A = powf(dir.z, 2) + powf(dir.x, 2) - a * powf(dir.y, 2);
	auto B = 2 * b*dir.x + 2 * d*dir.z + 2 * a*c*dir.y;
	auto C = powf(b, 2) + powf(d, 2) - a*powf(c, 2);

	auto root = powf(B, 2) - 4 * A * C;
	if (root <= 0.001) return -1;

	A *= 2;
	B *= -1;
	root = sqrtf(root);

	float t[2];
	t[0] = (B + root) / A;
	t[1] = (B - root) / A;
	
	t[0] = min(t[0], t[1]);

	auto v = pos.y + t[0] * dir.y;

	return center.y + height > v && center.y < v ? t[0] : -1;
}

Vector Cone::normal(Vector pos)
{
	auto a = pos.x - center.x;
	auto b = pos.z - center.z;
	auto r = sqrt(powf(a, 2) + powf(b, 2));
	auto normal = Vector(a, r * (radius / height), b);
	normal.normalise();
	return normal;
}