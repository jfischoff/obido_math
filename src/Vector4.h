#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector3.h"
#include "globalDefines.h"

class Vector4
{
 public:
  static void* Constructor();
  Vector4();
  Vector4(const Vector3& vec);
  Vector4(Float x, Float y, Float z, Float w);
  Vector4(const Vector4& other);
  Vector4& operator=(const Vector4& other);
  void copy(const Vector4& other);

  //group under addition
  static Vector4 Zero();
	
  static Vector4 Subtraction(Vector4 const &v0, Vector4 const &v1);
  static Vector4 Add(Vector4 const &v0, Vector4 const &v1);
  static Vector4 Invert(const Vector4& vec);
	
  //linear alg methods
  static Vector4 Scale(float t, const Vector4 v);
  static double Dot(const Vector4& left, const Vector4& right);

  Float getX() const;
  Float getY() const;
  Float getZ() const;
  Float getW() const;

  void setX(Float x);
  void setY(Float y);
  void setZ(Float z);
  void setW(Float w);

  Float getIndex(int index) const;

  void setIndex(int index, Float value);	

  Float mag() const;

  void normalize();

  bool almostEqual(const Vector4& other) const;
	
  static Vector4 Arbitrary();
	
  bool isValid() const;

  bool operator==(const Vector4& other) const;

 private:
  Float m_X;
  Float m_Y;
  Float m_Z;
  Float m_W;

};

#endif //VECTOR4_H
