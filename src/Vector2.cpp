#include "Vector2.h"
#include <math.h>
#include <assert.h>
#include <float.h>


void* Vector2::Constructor()
{
  return new Vector2();
}

Vector2::Vector2()
{
  m_X = 0;
  m_Y = 0;
}

Vector2::Vector2(Float x, Float y)
{
  assert(isnan(x) == false);
  assert(isnan(y) == false);
	
  m_X = x;
  m_Y = y;
}

Float Vector2::getX() const 
{
  return m_X;
}

void Vector2::setX(Float x)
{
  assert(isnan(x) == false);

  m_X = x;
}

Float Vector2::getY() const 
{
  return m_Y;
}

void Vector2::setY(Float y)
{
  assert(isnan(y) == false);
  m_Y = y;
}

Float Vector2::Distance(const Vector2& left, const Vector2& right)
{
  Vector2 diff = Subtract(left, right);
  return sqrt(Dot(diff, diff));
}


Float Vector2::Dot(const Vector2& left, const Vector2& right)
{
  return left.getX()*right.getX() + 
    left.getY()*right.getY();
}

Vector2 Vector2::Subtract(const Vector2& left, const Vector2& right)
{
  return Vector2(left.getX() - right.getX(), left.getY() - right.getY());
}

Float Vector2::Angle(const Vector2& left, const Vector2& right)
{
  Float dotP = Dot(left, right);
	
  return acos(dotP);
}

bool operator==(const Vector2& a, const Vector2& b)
{
  if(a.getX() == b.getX() && a.getY() == b.getY())
    {
      return true;
    }
  else
    {
      return false;
    }
}

Vector2 Vector2::Scale(float scale, const Vector2& vec)
{
  return Vector2(scale * vec.getX(), scale * vec.getY());
}

Vector2 Vector2::Add(const Vector2& left, const Vector2& right)
{
  return Vector2(left.getX() + right.getX(), left.getY() + right.getY());
}

Vector2 operator+(const Vector2& left, const Vector2& right)
{
  return Vector2::Add(left, right);
}

Vector2 operator-(const Vector2& left, const Vector2& right)
{
  return Vector2::Subtract(left, right);	
}

float operator*(const Vector2& left, const Vector2& right)
{
  return Vector2::Dot(left, right);
}

Vector2 operator*(float scale, const Vector2& right)
{
  return Vector2::Scale(scale, right);
}

Vector2 operator*(const Vector2& right, float scale)
{
  return Vector2::Scale(scale, right);
}

Vector2 operator/(float scale, const Vector2& right)
{
  return Vector2::Scale(1.0 / scale, right);
}

Vector2 operator/(const Vector2& right, float scale)
{
  return Vector2::Scale(1.0 / scale, right);
}

