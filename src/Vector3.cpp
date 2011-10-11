#include "Vector3.h"
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <float.h>
#include <limits.h>
using namespace std;

void* Vector3::Constructor()
{
  return new Vector3();
}

Vector3::Vector3(Float x, Float y, Float z)
{
  m_X = x; m_Y = y; m_Z = z; 
  assert(isValid());
}

Vector3::Vector3(const Vector2& vec2)
{
  m_X = vec2.getX();
  m_Y = vec2.getY();
  m_Z = 0;
  assert(isValid());
}

Vector3::Vector3()
{
  m_X = 0.0; m_Y = 0.0; m_Z = 0.0;
  assert(isValid());
}

Vector3::Vector3(const Vector3& other)
{
  copy(other);
  assert(isValid());
}

Vector3& Vector3::operator=(const Vector3& other)
{
  copy(other);
  assert(isValid());
  return *this;
}

void Vector3::copy(const Vector3& other)
{
  m_X = other.m_X;
  m_Y = other.m_Y;
  m_Z = other.m_Z;
  assert(isValid());
}

Vector3 Vector3::Zero()
{
  return Vector3();
}

bool Vector3::operator==(const Vector3& other) const
{
  if(m_X == other.m_X && m_Y == other.m_Y && m_Z == other.m_Z)
    {
      return true;
    }
  else
    {
      return false;
    }
}

Float Vector3::getX() const 
{
  return m_X;
}

Float Vector3::getY() const 
{
  return m_Y;
}

Float Vector3::getZ() const 
{
  return m_Z;
}

void Vector3::setX(Float x)
{
  m_X = x;
  assert(isValid());
}

void Vector3::setY(Float y)
{
  m_Y = y;
  assert(isValid());
}

void Vector3::setZ(Float z)
{
  m_Z = z;
  assert(isValid());
}

Float Vector3::getIndex(int index) const
{
  switch(index)
    {
    case 0:
      return m_X;
    case 1:
      return m_Y;
    case 2:
      return m_Z;
    }
  
  assert(0);
  return -1;
}

void Vector3::setIndex(int index, Float value)
{
  switch(index)
    {
    case 0:
      m_X = value;
      return;
    case 1:
      m_Y = value;
      return;
    case 2:
      m_Z = value;
      return;
    }
	
  assert(isValid());
}

Float Vector3::mag() const
{
  return sqrt(m_X*m_X + m_Y*m_Y + m_Z*m_Z);
}

Vector3 Vector3::normalize() const
{
  float m = mag();
  Vector3 result(*this);
	
  if(m == 0)
    return result;
  
  result.m_X /= m;
  result.m_Y /= m;
  result.m_Z /= m;
  return result;
}

Vector3 Vector3 ::Cross(const Vector3& left, 
			const Vector3& right)
{
  Vector3 output;

  output.setX(left.getY()*right.getZ() - left.getZ()*right.getY());
  output.setY(left.getZ()*right.getX() - left.getX()*right.getZ());
  output.setZ(left.getX()*right.getY() - left.getY()*right.getX());
	
  return output;
}

Float Vector3::angle(const Vector3& right) const
{
  Float dotP = dot(right);
  Float angle = 0.0;

  if(dotP >= 1.0)
    {
      angle = 0;
    }
  else
    {
      angle = acos(dotP);	    
    }

  return angle;

}

Float Vector3::dot(const Vector3& right) const
{
  return getX()*right.getX() + 
    getY()*right.getY() + 
    getZ()*right.getZ();
}

float Vector3::operator*(const Vector3& right) const
{
  return dot(right);
}

Vector3 Vector3::subtract(const Vector3& right) const
{
  return Vector3(getX() - right.getX(), 
		 getY() - right.getY(), 
		 getZ() - right.getZ());
}

Vector3 Vector3::operator+(const Vector3& right) const
{
  return add(right);
}

Vector3 Vector3::add(const Vector3& right) const
{
  return Vector3(getX() + right.getX(), 
		 getY() + right.getY(), 
		 getZ() + right.getZ());
}

Vector3 Vector3::operator-(const Vector3& right) const
{
  return subtract(right);
}

Vector3& Vector3::operator-=(const Vector3& right)
{
  *this = subtract(right);	
  return *this;
}


Float Vector3::distance(const Vector3& right) const
{
  return (subtract(right)).mag();
}

Vector3 Vector3::scale(double scale) const
{
  return Vector3(getX() * scale, getY() * scale,
		 getZ() * scale);
}

Vector3 Vector3::operator*(double scale) const
{
  return Vector3::scale(scale);
}

Vector3 Vector3::operator/(double scale) const
{
  return Vector3::scale(1.0 / scale);
}

bool Vector3::almostEqual(const Vector3& right) const
{
  const Vector3& left = *this;
  const double epsilon = 0.000001;
  if(fabs(left.getX() - right.getX()) < epsilon && 
     fabs(left.getY() - right.getY()) < epsilon && 
     fabs(left.getZ() - right.getZ()) < epsilon)
    {
      return true;
    }
  else
    {
      return false;
    }
}




Vector3 Vector3::invert() const
{
  Vector3 result;
  result.m_X *= -1;
  result.m_Y *= -1;
  result.m_Z *= -1;
  return result;
}

void Vector3::arbitrary()
{
  *this = Vector3(((float)rand() / (float)INT_MAX) * 10.0, ((float)rand() / (float)INT_MAX) * 10.0, 
		  ((float)rand() / (float)INT_MAX) * 10.0);
	
  assert(isValid());
}

bool Vector3::isValid()
{
  if(isnan(m_X) == false && isnan(m_Y) == false && isnan(m_Z) == false)
    {
      return true;
    }
  else 
    {
      return false;
    }
}

