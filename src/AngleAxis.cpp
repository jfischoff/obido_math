#include "AngleAxis.h"

void* AngleAxis::Constructor()
{
  return new AngleAxis();
}

AngleAxis::AngleAxis(Float x, Float y, Float z, Float angle)
{
  m_X = x; 
  m_Y = y; 
  m_Z = z; 
  m_Angle = angle;
}

AngleAxis::AngleAxis(const Vector3& vec, Float angle)
{ 
  m_X = vec.getX();
  m_Y = vec.getY(); 
  m_Z = vec.getZ(); 
  m_Angle = angle;
}

AngleAxis::AngleAxis() : m_Angle(0), m_X(0), m_Y(0), m_Z(0) {}

AngleAxis::AngleAxis(const AngleAxis& other)
{
  copy(other);
}

AngleAxis& AngleAxis::operator=(const AngleAxis& other)
{
  copy(other);
  return *this;
}

void AngleAxis::copy(const AngleAxis& other)
{
  m_Angle = other.m_Angle;
  m_X = other.m_X;
  m_Y = other.m_Y;
  m_Z = other.m_Z;
}

Float AngleAxis::getAngle() const 
{
  return m_Angle;
}

Float AngleAxis::getX() const 
{
  return m_X;
}

Float AngleAxis::getY() const 
{
  return m_Y;
}

Float AngleAxis::getZ() const 
{
  return m_Z;
}

void AngleAxis::normalize()
{
  Float mag = sqrt(m_X*m_X + m_Y*m_Y + m_Z*m_Z);
  m_X /= mag;
  m_Y /= mag;
  m_Z /= mag;
}

bool AngleAxis::AlmostEqual(const AngleAxis& other)
{
  float epsilon = 0.0001;
  if(fabs(m_X - other.m_X) < epsilon &&
     fabs(m_Y - other.m_Y) < epsilon &&
     fabs(m_Z - other.m_Z) < epsilon &&
     fabs(m_Angle - other.m_Angle) < epsilon)
    {
      return true;
    }
  else if(fabs(m_X - (-1.0 * other.m_X)) < epsilon &&
	  fabs(m_Y - (-1.0 * other.m_Y)) < epsilon &&
	  fabs(m_Z - (-1.0 * other.m_Z)) < epsilon &&
	  fabs(m_Angle - ((2 * M_PI) - other.m_Angle)) < epsilon)
    {
      return true;
    }
    else
    {
      return false;
    }
}

