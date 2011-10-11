#ifndef MATRIX4X3_H
#define MATRIX4X3_H

#include "globalDefines.h"
#include "Vector4.h"
#include "HomogenusPosition.h"
#include "Vector3.h"

class Matrix4x3
{
 public:
 static void* Constructor();
	
  Matrix4x3();
  Matrix4x3(Float m00, Float m01, Float m02, 
	    Float m10, Float m11, Float m12,
	    Float m20, Float m21, Float m22,
	    Float m30, Float m31, Float m32);
  Matrix4x3(const Matrix4x3& other);
  Matrix4x3& operator=(const Matrix4x3& other);
  void copy(const Matrix4x3& other);

	
  Vector4 VecMultiplyL(const Vector4& left) const;
  friend Vector4 operator* (const Vector4& left, 
			    const Matrix4x3& right);
	  	
  HomogenusPosition VecMultiplyL(const HomogenusPosition& left) const;
  friend HomogenusPosition operator* (const HomogenusPosition& left, 
				      const Matrix4x3& right);
	
  //row get set operations
  //use operator overloading
	
  Float getElement(int rowIndex, int columnIndex) const;
  void setElement(int rowIndex, int columnIndex, Float value); 


  static Matrix4x3 Add(const Matrix4x3& left, const Matrix4x3& right);
  Matrix4x3 operator+(const Matrix4x3& right);
  Matrix4x3 operator-(const Matrix4x3& right);
  void AddL(const Matrix4x3& left);
  void AddR(const Matrix4x3& right);

  static Matrix4x3 Scale(Float scale, const Matrix4x3& mat);
  Matrix4x3 operator*(Float scale) const;
  void scale(Float scale);

  static Matrix4x3 SetAll(Float value);
  void setAll(Float value);

  static void GetArrayColumnOrder(Matrix4x3 mat, Float* m);
  void getArrayColumnOrder(Float* m);

  static Matrix4x3 SetArrayColumnOrder(Float* m);
  void setArrayColumnOrder(Float* m);

  void getColumnMajorArray(Float* array) const;
	
  bool isValid() const;

  Float m_Elements[4][3];

  friend ostream& operator<<(ostream& cout, Matrix4x3& obj);

  static const uint ROW_COUNT;
  static const uint COLUMN_COUNT;

 private:
};

#endif //MATRIX4X3_H
