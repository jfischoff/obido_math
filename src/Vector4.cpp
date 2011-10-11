#include "Vector4.h"
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>

void* Vector4::Constructor()
{
  return new Vector4();
}


Vector4::Vector4(const Vector4& other)
{
  copy(other);
}

Vector4& Vector4::operator=(const Vector4& other)
{
  copy(other);
  return *this;
}

void Vector4::copy(const Vector4& other)
{
  assert(isnan(other.m_X) == false);
  assert(isnan(other.m_Y) == false);
  assert(isnan(other.m_Z) == false);
  assert(isnan(other.m_W) == false);
 
  m_X = other.m_X;
  m_Y = other.m_Y;
  m_Z = other.m_Z;
  m_W = other.m_W;
}

Vector4::Vector4(Float x, Float y, Float z, Float w)
{
  assert(isnan(x) == false);
  assert(isnan(y) == false);
  assert(isnan(z) == false);
  assert(isnan(w) == false);
  m_X = x; m_Y = y; m_Z = z; m_W = w;
}

Vector4::Vector4()
{
  m_X = 0.0; m_Y = 0.0; m_Z = 0.0; m_W = 0.0;
}

Vector4::Vector4(const Vector3& vec)
{
  assert(isnan(vec.getX()) == false);
  assert(isnan(vec.getY()) == false);
  assert(isnan(vec.getZ()) == false);
  
  m_X = vec.getX(); 
  m_Y = vec.getY(); 
  m_Z = vec.getZ(); 
  m_W = 1.0;
}

Vector4 Vector4::Zero()
{
  return Vector4(0, 0, 0, 0);
}

Vector4 Vector4::Subtraction(Vector4 const &v0, Vector4 const &v1)
{
  return Vector4(v0.getX() -  v1.getX(), 
		 v0.getY() -  v1.getY(), 
		 v0.getZ() -  v1.getZ(), 
		 v0.getW() -  v1.getW());
}

Vector4 Vector4::Add(Vector4 const &v0, Vector4 const &v1)
{
  return Vector4(v0.getX() + v1.getX(), v0.getY() 
		 + v1.getY(), v0.getZ() + v1.getZ(), 
		 v0.getW() + v1.getW());
}

Vector4 Vector4::Scale(float t, const Vector4 v)
{
  return Vector4(t * v.getX(), t * v.getY(), t * v.getZ(), 
		 t * v.getW());
}

Vector4 Vector4::Invert(const Vector4& vec)
{
  return Vector4(-1 * vec.getX(), -1 * vec.getY(), 
		 -1 * vec.getZ(), -1 * vec.getZ());
}

Float Vector4::getX() const
{

  return m_X;
}

Float Vector4::getY() const
{
  return m_Y;
}

Float Vector4::getZ() const
{
  return m_Z;
}

Float Vector4::getW() const
{
  return m_W;
}

void Vector4::setX(Float x)
{
  assert(isnan(x) == false);
  m_X = x;
}

void Vector4::setY(Float y)
{
  assert(isnan(y) == false);
  m_Y = y;
}

void Vector4::setZ(Float z)
{
  assert(isnan(z) == false);
  m_Z = z;
}

void Vector4::setW(Float w)
{
  assert(isnan(w) == false);
  m_W = w;
}

Float Vector4::getIndex(int index) const
{
  switch(index)
    {
    case 0:
      return m_X;
    case 1:
      return m_Y;
    case 2:
      return m_Z;
    case 3:
      return m_W;
    }

  assert(0);
  return -1;
}

void Vector4::setIndex(int index, Float value)
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
    case 3:
      m_W = value;
      return;
    }
}	

Float Vector4::mag() const
{
  return sqrt(m_X*m_X + m_Y*m_Y + m_Z*m_Z + m_W*m_W);
}

void Vector4::normalize()
{
  float m = mag();
  m_X /= m;
  m_Y /= m;
  m_Z /= m;
  m_W /= m;
}

double Vector4::Dot(const Vector4& left, const Vector4& right)
{
  return left.getX()*right.getX() + left.getY()*right.getY() + 
    left.getZ()*right.getZ() + left.getW()*right.getW();
}

bool Vector4::almostEqual(const Vector4& other) const
{
  float epsilon = 0.0001;
  if(fabs(m_X - other.m_X) < epsilon &&
     fabs(m_Y - other.m_Y) < epsilon &&
     fabs(m_Z - other.m_Z) < epsilon &&
     fabs(m_W - other.m_W) < epsilon)
    {
      return true;
    }
  else
    {
      return false;
    }
}

bool Vector4::operator==(const Vector4& other) const
{
  if(m_X == other.m_X && 
     m_Y == other.m_Y && 
     m_Z == other.m_Z && 
     m_W == other.m_W)
    {
      return true;
    }
  else {
    return false;
  }

}

Vector4 Vector4::Arbitrary()
{
  return Vector4((Float)rand(), (Float)rand(), 
		 (Float)rand(), (Float)rand());
}

bool Vector4::isValid() const
{
  if(isnan(m_X) == false &&
     isnan(m_Y) == false &&
     isnan(m_Z) == false &&
     isnan(m_W) == false)
    {
      return true;
    }
  else 
    {
      return false;				
    }

}









