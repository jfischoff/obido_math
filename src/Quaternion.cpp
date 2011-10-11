#include "Quaternion.h"
#include <math.h>

#define max(a,b)	(((a) > (b)) ? (a) : (b))
#define min(a,b)	(((a) < (b)) ? (a) : (b))

Quaternion::Quaternion() : Vector4(0, 0, 0, 1)
{
  assert(isValid());
}

Quaternion::Quaternion(const Vector4& vector): Vector4(vector)
{
  assert(isValid());
}

Quaternion::Quaternion(Float x, Float y, Float z, Float w) : 
  Vector4(x, y, z, w)
{
  assert(isValid());
};

Quaternion::Quaternion(const Quaternion& other)
{
  copy(other);
  assert(isValid());
}

Quaternion& Quaternion::operator=(const Quaternion& other)
{
  copy(other);
  assert(isValid());
  return *this;
}

void Quaternion::identity()
{
  setX(0.0);
  setY(0.0);
  setZ(0.0);
  setW(1.0);
}

float Quaternion::Dot(const Quaternion &v0, const Quaternion &v1)
{	
  return Vector4::Dot(v0, v1);
}

Quaternion Quaternion::Subtraction(Quaternion const &v0, Quaternion const &v1)
{
  return Quaternion(Vector4::Subtraction(v0, v1));
}

Quaternion Quaternion::Add(Quaternion const &v0, Quaternion const &v1)
{
  return Quaternion(Vector4::Add(v0, v1));
}

Quaternion Quaternion::Scale(float t, Quaternion quat)
{
  return Quaternion(Vector4::Scale(t, quat));
}

double Quaternion::Clamp(float value, float low, float high)
{
  return max(min(high, value), low);
}

Quaternion Quaternion::Slerp(const Quaternion &v0, const Quaternion &v1, double t) 
{
  // Compute the cosine of the angle between the two vectors.
  double dot = Dot(v0, v1);
	
  const double DOT_THRESHOLD = 0.9995;
  if (dot > DOT_THRESHOLD) {
    // If the inputs are too close for comfort, linearly interpolate
    // and normalize the result.
		
    Vector4 diff = Vector4::Subtraction(v1, v0);
    Vector4 scaled = Vector4::Scale(t, diff);
    Vector4 result = Vector4::Add(v0, scaled);
    result.normalize();
    return Quaternion(result);
  }
	
  Clamp(dot, -1, 1);           // Robustness: Stay within domain of acos()
  double theta_0 = acos(dot);  // theta_0 = angle between input vectors
  double theta = theta_0*t;    // theta = angle between v0 and result 
	
  Vector4 scaled = Vector4::Scale(dot, v0);
  Vector4 v2 = Vector4::Subtraction(v1, scaled);
  v2.normalize();              // { v0, v2 } is now an orthonormal basis
	
  Vector4 cosScaled = Vector4::Scale(cos(theta), v0);
  Vector4 sinScaled = Vector4::Scale(sin(theta), v2);
  Vector4 result = Vector4::Add(cosScaled, sinScaled);

  return Quaternion(result);
}

bool Quaternion::isNormal(float tolerance) const
{
  float length = mag();
	
  if(fabs(length - 1.0f) < tolerance)
    {
      return true;
    }
  else
    {
      return false;
    }
}


bool Quaternion::almostEqual(const Quaternion& other) const
{
  Vector4 temp = Vector4::Invert(other);
	
  if(almostEqual(other))
    {
      return true;
    }
  else if(temp.almostEqual(other))
    {
      return true;
    }
  else
    {
      return false;
    }
}

Quaternion Quaternion::Arbitrary()
{
  return Vector4::Arbitrary();
}

Quaternion Quaternion::multiply(const Quaternion& right) const
{
  float b1 = getX();
  float c1 = getY();
  float d1 = getZ();
  float a1 = getW();
	
  float b2 = right.getX();
  float c2 = right.getY();
  float d2 = right.getZ();
  float a2 = right.getW();
	
  float a3 = a1*a2 - b1*b2 - c1*c2 - d1*d2;
  float b3 = a1*b2 + b1*a2 + c1*d2 - d1*c2;
  float c3 = a1*c2 - b1*d2 + c1*a2 + d1*b2;
  float d3 = a1*d2 + b1*c2 - c1*b2 + d1*a2;
	
  Quaternion result = Quaternion(b3, c3, d3, a3);
  result.normalize();
	
  return result;
}

Quaternion Quaternion::operator*(const Quaternion& right) const
{
  return multiply(right);
}

Quaternion& Quaternion::operator*=(const Quaternion& right)
{
  *this = multiply(right);
  assert(isValid());
  return *this;
}


Quaternion Quaternion::invert() const
{
  return Quaternion(-getX(), -getY(), -getZ(), getW());
}

Quaternion Quaternion::operator!() const
{
  return invert();
}

bool Quaternion::isValid() const
{
  if(Vector4::isValid() && isNormal(0.2f))
    {
      return true;
    }
  else 
    {
      return false;
    }
	
	
}

bool Quaternion::operator==(const Quaternion& other) const
{
  return Vector4::operator==(other);
}









