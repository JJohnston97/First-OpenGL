#ifndef _VECTOR3_H
#define _VECTOR3_H


class Vector2;
class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y);
	Vector3(float x, float y, float z);

	Vector3 operator-(Vector2 param);
	Vector3 operator-(Vector3 param);
	Vector3 operator+(Vector3 param);
	Vector3 operator*(Vector3 param);
	Vector3 operator/(float param);
	Vector3 operator*(float param);
	Vector3 operator+(float param);

	float getMagnitude();
	Vector3 getNormalized();
	static float getDistance(Vector3 a, Vector3 b);

};

#endif
