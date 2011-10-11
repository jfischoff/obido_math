#ifndef VECTOR2_H
#define VECTOR2_H

#include "globalDefines.h"
#include <iostream>
using namespace std;

class Vector2
{


 public:
  static void* Constructor();
  Vector2();
	
  Vector2(Float x, Float y);
  Float getX() const;
  void setX(Float x);
  Float getY() const;
  void setY(Float y);
	
  static Float Dot(const Vector2& left, const Vector2& right);
	
  static Float Distance(const Vector2& left, const Vector2& right);
	
  static Vector2 Add(const Vector2& left, const Vector2& right);
	
  static Vector2 Subtract(const Vector2& left, const Vector2& right);

  static Float Angle(const Vector2& left, const Vector2& right);
	
  static Vector2 Scale(float scale, const Vector2& vec);
	
  friend Vector2 operator+(const Vector2& left, const Vector2& right);
  friend Vector2 operator-(const Vector2& left, const Vector2& right);
  friend float operator*(const Vector2& left, const Vector2& right);
  friend Vector2 operator*(float scale, const Vector2& right);
  friend Vector2 operator*(const Vector2& right, float scale);
  friend Vector2 operator/(float scale, const Vector2& right);
  friend Vector2 operator/(const Vector2& right, float scale);
	
  friend bool operator==(const Vector2& a, const Vector2& b);
 private:
  Float m_X;
  Float m_Y;
};

#endif //VECTOR2_H
