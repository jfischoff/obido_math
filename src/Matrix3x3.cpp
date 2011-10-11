#include "Matrix3x3.h"

void* Matrix3x3::Constructor()
{
  return new Matrix3x3();
}

Matrix3x3::Matrix3x3()
{
  for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
	{
	  m_Elements[i][j] = 0.0f;
	}
    }
  assert(isValid());
}

Vector3 Matrix3x3::vecMultiplyR(const Vector3& vec) const
{
  Vector3 output;
	
  for(int rowIndex = 0; rowIndex < 3; rowIndex++)
    {
      for(int columnIndex = 0; columnIndex < 1; columnIndex++)
	{	
	  float element = 0;
			
	  for(int index = 0; index < 3; index++)
	    {
	      element += getElement(rowIndex, index) * 
		vec.getIndex(index);
	    }
			
	  output.setIndex(rowIndex, element);
	}
    }
	
  return output;
}

Vector3 operator*(const Matrix3x3& mat, const Vector3& vec)
{
  return mat.vecMultiplyR(vec);
}

Vector3 Matrix3x3::vecMultiplyL(const Vector3& vec) const
{
  Vector3 output;
	
  for(int rowIndex = 0; rowIndex < 3; rowIndex++)
    {
      for(int columnIndex = 0; columnIndex < 1; columnIndex++)
	{	
	  float element = 0;
			
	  for(int index = 0; index < 3; index++)
	    {
	      element += vec.getIndex(index) * 
		getElement(index, rowIndex);
	    }
			
	  output.setIndex(rowIndex, element);
	}
    }
	
  return output;
}

Vector3 operator*(const Vector3& vec, const Matrix3x3& mat)
{
  return mat.vecMultiplyL(vec);
}

Matrix3x3 Matrix3x3::multiply(const Matrix3x3& right) const
{
  Matrix3x3 returnValue;
  const Matrix3x3& left = *this;
	
  for(int rowIndex = 0; rowIndex < 3; rowIndex++)
    {
      for(int columnIndex = 0; columnIndex < 3; columnIndex++)
	{	
	  float element = 0;
			
	  for(int index = 0; index < 3; index++)
	    {
	      element += left.getElement(rowIndex, index) * right.getElement(index, columnIndex);
	    }
			
	  returnValue.setElement(rowIndex, columnIndex, element);
	}
    }
	
  return returnValue;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& right) const
{
  return multiply(right);
}

Matrix3x3 Matrix3x3::transpose() const
{
  Matrix3x3 returnValue(*this);
	
  for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
	{
	  returnValue.setElement(i, j, getElement(j, i));
	}
    }
	
  return returnValue;
}

Float Matrix3x3::getElement(int rowIndex, int columnIndex) const
{
  return m_Elements[rowIndex][columnIndex];
}

void Matrix3x3::setElement(int rowIndex, int columnIndex, Float value)
{
  assert(isnan(value) == false);
  m_Elements[rowIndex][columnIndex] = value;

}

Matrix3x3 Matrix3x3::add(const Matrix3x3& right) const
{
  Matrix3x3 returnValue;
  const Matrix3x3& left = *this;
	
  for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
	{
	  Float elementLeft = left.getElement(i, j);
	  Float elementRight = right.getElement(i, j);
	  Float added = elementLeft + elementRight;
			
	  returnValue.setElement(i, j, added);
	}
    }
	
  return returnValue;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& right) const
{	
  return add(right);
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& right) const
{
  return add(right * -1.0);
}

Matrix3x3 Matrix3x3::invert() const
{
  Float determinant = determinate();
	
  Matrix3x3 returnValue;
	
  Float invdet = 1/determinant;
  returnValue.setElement(0,0, (getElement(1,1)*getElement(2,2)- getElement(2,1)*getElement(1,2))*invdet);
  returnValue.setElement(1,0, -1.0 * (getElement(0,1)*getElement(2,2) - getElement(0,2)*getElement(2,1))*invdet);
  returnValue.setElement(2,0, (getElement(0,1)*getElement(1,2)- getElement(0,2)*getElement(1,1))*invdet);
  returnValue.setElement(0,1, -1.0 * (getElement(1,0)*getElement(2,2)-getElement(1,2)*getElement(2,0))*invdet);
  returnValue.setElement(1,1, (getElement(0,0)*getElement(2,2)-getElement(0,2)*getElement(2,0))*invdet);
  returnValue.setElement(2,1, -1.0 * (getElement(0,0)*getElement(1,2)-getElement(1,0)*getElement(0,2))*invdet);
  returnValue.setElement(0,2,   (getElement(1,0)*getElement(2,1)-getElement(2,0)*getElement(1,1))*invdet);
  returnValue.setElement(1,2, -1.0 * (getElement(0,0)*getElement(2,1)-getElement(2,0)*getElement(0,1))*invdet);
  returnValue.setElement(2,2, (getElement(0,0)*getElement(1,1)-getElement(1,0)*getElement(0,1))*invdet);
	
  return returnValue;
}

Matrix3x3 Matrix3x3::operator!() const
{
  return invert();
}



Float Matrix3x3::determinate() const
{
  Float determinant = getElement(0,0)*(getElement(1,1)*getElement(2,2)-getElement(2,1)*getElement(1,2))
    -getElement(0,1)*(getElement(1,0)*getElement(2,2)-getElement(1,2)*getElement(2,0))
    +getElement(0,2)*(getElement(1,0)*getElement(2,1)-getElement(1,1)*getElement(2,0));
	
  return determinant;
}



Matrix3x3 Matrix3x3::scale(Float scale) const
{
  Matrix3x3 returnValue;
	
  for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
	{
	  Float element = getElement(i, j);			
	  Float scaled = element * scale;
			
	  returnValue.setElement(i, j, scaled);
	}
    }
	
  return returnValue;
}

Matrix3x3 Matrix3x3::operator*(Float scale) const
{
  return Matrix3x3::scale(scale);
}


Matrix3x3 Matrix3x3::SetAll(Float value)
{
  Matrix3x3 mat;
  mat.setAll(value);
  return mat;
}
void Matrix3x3::setAll(Float value)
{
  for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
	{			
	  setElement(i, j, value);
	}
    }
  assert(isValid());
}

Matrix3x3 Matrix3x3::Identity()
{
  Matrix3x3 returnValue;
  returnValue.setAll(0);
	
  returnValue.setElement(0, 0, 1.0f);
  returnValue.setElement(1, 1, 1.0f);
  returnValue.setElement(2, 2, 1.0f);
	
  return returnValue;
}
void Matrix3x3::identity()
{
  copy(Identity());
  assert(isValid());
	
}

void Matrix3x3::getArrayColumnOrder(Float* m) const
{
  GetArrayColumnOrder(*this, m);
}
void Matrix3x3::setArrayColumnOrder(Float* m)
{
  copy(SetArrayColumnOrder(m));
  assert(isValid());
	
}

void Matrix3x3::GetArrayColumnOrder(Matrix3x3 mat, Float* m)
{
  for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
	{
	  m[3*j + i] = mat.getElement(i, j);
	}
    }
}

Matrix3x3 Matrix3x3::SetArrayColumnOrder(Float* m)
{
  Matrix3x3 returnValue;
	
  for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
	{
	  returnValue.setElement(i, j, m[3*j + i]);
	}
    }
	
  return returnValue;
}

void Matrix3x3::copy(const Matrix3x3& mat)
{
  for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
	{
	  setElement(i, j, mat.getElement(i, j));
	}
    }
  assert(isValid());
	
}

Vector3 Matrix3x3::getRow(int index) const 
{
  Float x = getElement(index, 0);
  Float y = getElement(index, 1);
  Float z = getElement(index, 2);
	
  return Vector3(x, y, z);
}

Vector3 Matrix3x3::operator[](int index) const
{
  return getRow(index);
}

void Matrix3x3::setRow(int rowIndex, const Vector3& row)
{
  setElement(rowIndex, 0, row.getX());
  setElement(rowIndex, 1, row.getY());
  setElement(rowIndex, 2, row.getZ());
	
  assert(isValid());
}

bool Matrix3x3::isValid() const
{
  bool isNan = false;
  for (int rowIndex = 0; rowIndex < 3; rowIndex++) {
    for (int columnIndex = 0 ; columnIndex < 3; columnIndex++) {
      isNan |= isnan(getElement(rowIndex, columnIndex));
    }
  }
  return !isNan;						
}
