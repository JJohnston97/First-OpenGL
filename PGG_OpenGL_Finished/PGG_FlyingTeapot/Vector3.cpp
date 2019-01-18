#include "Vector3.h"
#include "Vector2.h"

#include <cmath>


Vector3::Vector3()
{
  x = 0;
  y = 0;
  z = 0;
}

Vector3::Vector3(float x, float y)
{
  this->x = x;
  this->y = y;
  this->z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3 Vector3::operator*(Vector3 param)
{
  return Vector3(x * param.x, y * param.y, z * param.z);
}

Vector3 Vector3::operator+(Vector3 param)
{
  return Vector3(x + param.x, y + param.y, z + param.z);
}

Vector3 Vector3::operator-(Vector3 param)
{
  return Vector3(x - param.x, y - param.y, z - param.z);
}

Vector3 Vector3::operator-(Vector2 param)
{
  return Vector3(x - param.x, y - param.y, z);
}

Vector3 Vector3::operator*(float param)
{
  return Vector3(x * param, y * param, z * param);
}

Vector3 Vector3::operator+(float param)
{
  return Vector3(x + param, y + param, z + param);
}

Vector3 Vector3::operator/(float param)
{
  return Vector3(x / param, y / param, z / param);
}

Vector3 Vector3::getNormalized()
{
  Vector3 rtn;
  float length = sqrt(x*x+y*y+z*z);

  rtn.x = x/length;
  rtn.y = y/length;
  rtn.z = z/length;

  return rtn;
}

float Vector3::getMagnitude()
{
  return sqrt(x*x+y*y+z*z);
}

float Vector3::getDistance(Vector3 a, Vector3 b)
{
  return (a - b).getMagnitude();
}
