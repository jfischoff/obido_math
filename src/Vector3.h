#ifndef VECTOR3_H
#define VECTOR3_H

#include "globalDefines.h"
#include <math.h>
#include <iostream>
#include "Vector2.h"
using namespace std;

class Vector3
{
 public:
  static void* Constructor();
  Vector3();
  Vector3(Float x, Float y, Float z);
  Vector3(const Vector3& other);
  Vector3& operator=(const Vector3& other);
  Vector3(const Vector2& vec2);
  void copy(const Vector3& other);
	
  bool operator==(const Vector3& other) const;
	
  static Vector3 Zero();
	
  Float getX() const;
  Float getY() const;
  Float getZ() const;
	
  void setX(Float x);
  void setY(Float y);
  void setZ(Float z);
	
  Float getIndex(int index) const;
	
  void setIndex(int index, Float value);	
	

	
  static Vector3 Cross(const Vector3& left, 
		       const Vector3& right);
	
  Float mag() const;
	
  Vector3 normalize() const;
	
  Vector3 invert() const;
	
  Float dot(const Vector3& right) const;
  float operator*(const Vector3& right) const;		
	
  Float angle(const Vector3& right) const;
	
  Vector3 add(const Vector3& right) const;
  Vector3 operator+(const Vector3& right) const;
	
  Vector3 subtract(const Vector3& right) const;
	
  Vector3 operator-(const Vector3& right) const;	
  Vector3& operator-=(const Vector3& right);
  	
  Float distance(const Vector3& right) const;
	
  Vector3 scale(double scale) const;
  Vector3 operator*(double scale) const;
  Vector3 operator/(double scale) const;
	
  bool almostEqual(const Vector3& right) const;
	
  void arbitrary();
	
  bool isValid();
	
 private:
  Float m_X;
  Float m_Y;
  Float m_Z;
};

#endif 
