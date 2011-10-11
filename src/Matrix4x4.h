#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "globalDefines.h"
#include "Vector4.h"
#include "HomogenusPosition.h"
#include "Vector3.h"
#include <iostream>
using namespace std;

class Matrix4x4
{
 public:
  static void* Constructor();
	
  Matrix4x4();
  Matrix4x4(Float m00, Float m01, Float m02, Float m03, 
	    Float m10, Float m11, Float m12, Float m13,
	    Float m20, Float m21, Float m22, Float m23,
	    Float m30, Float m31, Float m32, Float m33);
  Matrix4x4(const Matrix4x4& other);
  Matrix4x4& operator=(const Matrix4x4& other);
  void copy(const Matrix4x4& other);


  static Matrix4x4 Multiply(const Matrix4x4& left, const Matrix4x4& right);
  Matrix4x4 operator*(const Matrix4x4& right);
	
  void multiply(const Matrix4x4& left, const Matrix4x4& right);
  void multiplyL(const Matrix4x4& left);
  void multiplyR(const Matrix4x4& right);

  Vector4 VecMultiplyR(const Vector4& right) const;
  friend Vector4 operator* (const Matrix4x4& left, 
			    const Vector4& right);
	
  Vector4 VecMultiplyL(const Vector4& left) const;
  friend Vector4 operator* (const Vector4& left, 
			    const Matrix4x4& right);
	
  HomogenusPosition VecMultiplyR(const HomogenusPosition& right) const;
  friend HomogenusPosition operator* (const Matrix4x4& left, 
				      const HomogenusPosition& right);
	
  HomogenusPosition VecMultiplyL(const HomogenusPosition& left) const;
  friend HomogenusPosition operator* (const HomogenusPosition& left, 
				      const Matrix4x4& right);
	
  static Matrix4x4 Transpose(const Matrix4x4& mat);
  void transpose();

  //row get set operations
  //use operator overloading
	
  Float getElement(int rowIndex, int columnIndex) const;
  void setElement(int rowIndex, int columnIndex, Float value); 


  static Matrix4x4 Add(const Matrix4x4& left, const Matrix4x4& right);
  Matrix4x4 operator+(const Matrix4x4& right);
  Matrix4x4 operator-(const Matrix4x4& right);
  void AddL(const Matrix4x4& left);
  void AddR(const Matrix4x4& right);

  static Matrix4x4 Inverse(const Matrix4x4 & mat);
  Matrix4x4 operator!();
  Matrix4x4& invert();

  Float Determinate(const Matrix4x4 & mat);
  Float determinate();

  static Matrix4x4 Scale(Float scale, const Matrix4x4& mat);
  Matrix4x4 operator*(Float scale) const;
  void scale(Float scale);

  static Matrix4x4 SetAll(Float value);
  void setAll(Float value);

  static Matrix4x4 Identity();
  void identity();

  static void GetArrayColumnOrder(Matrix4x4 mat, Float* m);
  void getArrayColumnOrder(Float* m);

  static Matrix4x4 SetArrayColumnOrder(Float* m);
  void setArrayColumnOrder(Float* m);

  void getColumnMajorArray(Float* array) const;
	
  bool isValid() const;

  Float m_Elements[4][4];

  friend ostream& operator<<(ostream& cout, Matrix4x4& obj);
 private:
	
};

#endif // MATRIX4X4_H
