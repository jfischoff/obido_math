#ifndef ROTATIOTMATRIX_H
#define ROTATIOTMATRIX_H

#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "AngleAxis.h"
#include <iostream>

using namespace std;


class RotationMatrix : public Matrix3x3
{
 public:
  RotationMatrix();
  RotationMatrix(const Vector3& right, 
		 const Vector3& up, const Vector3& out);
	
  RotationMatrix(const Matrix3x3& mat);
  RotationMatrix& operator=(const Matrix3x3& mat);
	
	
  RotationMatrix(const Matrix4x4& mat4x4);
  RotationMatrix& operator=(const Matrix4x4& mat4x4);
  void copy(const Matrix4x4& mat);
	
  RotationMatrix(const RotationMatrix& rotationMatrix);
  RotationMatrix& operator=(const RotationMatrix& other);
  void copy(const RotationMatrix& mat);
	
  //add standard constructor stuff
  RotationMatrix& fromMatrix3x3(const Matrix3x3& mat);
  Matrix3x3 toMatrix3x3() const;
	
  RotationMatrix& fromMatrix4x4(const Matrix4x4& mat);
  Matrix4x4 toMatrix4x4() const;
	
	
  //Matrix3x3 methods
  //multiply
  RotationMatrix multiply(const RotationMatrix& right) const;
  RotationMatrix operator*(const RotationMatrix& right) const;
		
  //vec multiply
  RotationMatrix invert() const;
  RotationMatrix operator!() const;
  RotationMatrix transpose() const;
	
			
  bool isValid() const;
	
  void arbitrary();       	
  bool operator==(const RotationMatrix& rotationMatrix);
};

#endif //ROTATIOTMATRIX_H
