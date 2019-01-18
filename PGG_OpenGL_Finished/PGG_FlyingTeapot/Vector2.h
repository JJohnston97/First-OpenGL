#ifndef _VECTOR2_H
#define _VECTOR2_H


class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);

	Vector2 operator-(Vector2 param);
	Vector2 operator+(Vector2 param);

};

#endif
