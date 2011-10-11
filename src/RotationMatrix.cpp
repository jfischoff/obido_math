#include "RotationMatrix.h"
#include "AngleAxis.h"
#include "RotationUtils.h"

RotationMatrix::RotationMatrix()
{
  identity();
}

RotationMatrix::RotationMatrix(const Vector3& right, 
			       const Vector3& up, const Vector3& out)
{
  setRow(0, right);
  setRow(1, up);
  setRow(2, out);
}

RotationMatrix::RotationMatrix(const Matrix3x3& mat)
{
  Matrix3x3::copy(mat);
}

RotationMatrix& RotationMatrix::operator=(const Matrix3x3& mat)
{
  Matrix3x3::copy(mat);
  return *this;
}

RotationMatrix::RotationMatrix(const Matrix4x4& mat4x4)
{
  copy(mat4x4);
}

RotationMatrix& RotationMatrix::operator=(const Matrix4x4& mat4x4)
{
  copy(mat4x4);
  return *this;
}

void RotationMatrix::copy(const Matrix4x4& mat)
{
  for (int rowIndex = 0; rowIndex < 3; rowIndex++) 
    {
      for (int columnIndex = 0; columnIndex < 3; columnIndex++) 
	{
	  
	  Float element = mat.getElement(rowIndex, columnIndex);
	  setElement(rowIndex, columnIndex, element);
	}
    }
}

RotationMatrix::RotationMatrix(const RotationMatrix& rotationMatrix)
{
  copy(rotationMatrix);
}

RotationMatrix& RotationMatrix::operator=(const RotationMatrix& other)
{
  copy(other);
  return *this;
}

void RotationMatrix::copy(const RotationMatrix& mat)
{
  Matrix3x3::copy(mat);
}

RotationMatrix& RotationMatrix::fromMatrix3x3(const Matrix3x3& mat)
{
  copy(mat);  
  return *this;
}

Matrix3x3 RotationMatrix::toMatrix3x3() const
{
  return *this;
}

RotationMatrix& RotationMatrix::fromMatrix4x4(const Matrix4x4& mat)
{	
  copy(mat);  
  return *this;
}

Matrix4x4 RotationMatrix::toMatrix4x4() const
{
  Matrix4x4 mat;
	
  for(int rowIndex = 0; rowIndex < 3; rowIndex++)
    {
      for (int columnIndex = 0; columnIndex < 3; columnIndex++) {
	mat.setElement(rowIndex, columnIndex, 
		       getElement(rowIndex, columnIndex));
      }
    }
	
  mat.setElement(3, 3, 1.0);
	
  return mat;
}

RotationMatrix RotationMatrix::multiply(
					const RotationMatrix& right) const
{
  return RotationMatrix(Matrix3x3::multiply(right));
}

RotationMatrix RotationMatrix::operator*(
					 const RotationMatrix& right) const
{
  return multiply(right);
}

//vec multiply
RotationMatrix RotationMatrix::invert() const
{
  return transpose();
}

RotationMatrix RotationMatrix::operator!() const
{
  return invert();
}

RotationMatrix RotationMatrix::transpose() const
{
  return RotationMatrix(Matrix3x3::transpose());
}

bool RotationMatrix::isValid() const
{
  assert(!"not implemented");
  return true;
}

