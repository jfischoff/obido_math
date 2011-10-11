#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include "globalDefines.h"
#include "Vector3.h"

class Matrix3x3
{
public:
  static void* Constructor();
	Matrix3x3();
   void copy(const Matrix3x3& mat);

	Matrix3x3 multiply(const Matrix3x3& right) const;
	Matrix3x3 operator*(const Matrix3x3& right) const;
	
	Vector3 vecMultiplyR(const Vector3& vec) const;
	friend Vector3 operator*(const Matrix3x3& mat, const Vector3& vec);
	
	Vector3 vecMultiplyL(const Vector3& vec) const;
	friend Vector3 operator*(const Vector3& vec, const Matrix3x3& mat);

	Matrix3x3 transpose() const;

	Float getElement(int rowIndex, int columnIndex) const;
	void setElement(int rowIndex, int columnIndex, Float value); 

	
	Matrix3x3 add(const Matrix3x3& right) const;
	Matrix3x3 operator+(const Matrix3x3& right) const;
	Matrix3x3 operator-(const Matrix3x3& right) const;
	
	Matrix3x3 invert() const;
	Matrix3x3 operator!() const;

	Float determinate() const;

	Matrix3x3 scale(Float scale) const;
	Matrix3x3 operator*(Float scale) const;

	static Matrix3x3 SetAll(Float value);
	void setAll(Float value);

	static Matrix3x3 Identity();
	void identity();

	static void GetArrayColumnOrder(Matrix3x3 mat, Float* m);
	void getArrayColumnOrder(Float* m) const;

	static Matrix3x3 SetArrayColumnOrder(Float* m);
	void setArrayColumnOrder(Float* m);

	bool isValid() const;


	Vector3 getRow(int index) const;
	Vector3 getColumn(int index) const;
	Vector3 operator[](int index) const;

	void setRow(int rowIndex, const Vector3& row);

private:
	Float m_Elements[3][3];

};

#endif //MATRIX3X3_H
