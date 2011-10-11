#include "Matrix4x3.h"
#include <string.h>

const uint Matrix4x3::ROW_COUNT = 4;
const uint Matrix4x3::COLUMN_COUNT = 3;

void* Matrix4x3::Constructor()
{
  return new Matrix4x3();
}

Matrix4x3::Matrix4x3()
{
  memset(m_Elements, 0, sizeof(Float) * (ROW_COUNT * COLUMN_COUNT));
}

Matrix4x3::Matrix4x3(Float m00, Float m01, Float m02,  
		  Float m10, Float m11, Float m12, 
		  Float m20, Float m21, Float m22, 
		  Float m30, Float m31, Float m32)
{
	setElement(0, 0, m00);
	setElement(0, 1, m01);
	setElement(0, 2, m02);
	
	setElement(1, 0, m10);
	setElement(1, 1, m11);
	setElement(1, 2, m12);
	
	setElement(2, 0, m20);
	setElement(2, 1, m21);
	setElement(2, 2, m22);
	
	setElement(3, 0, m30);
	setElement(3, 1, m31);
	setElement(3, 2, m32);
	assert(isValid());
}

Matrix4x3::Matrix4x3(const Matrix4x3& other)
{
	copy(other);
	assert(isValid());
}

Matrix4x3& Matrix4x3::operator=(const Matrix4x3& other)
{
	copy(other);
	assert(isValid());
	return *this;
}

HomogenusPosition Matrix4x3::VecMultiplyL(const HomogenusPosition& left) const
{
	return HomogenusPosition(VecMultiplyL((const Vector4&)left));
}

HomogenusPosition operator* (const HomogenusPosition& left, 	
			     const Matrix4x3& right)
{
	return right.VecMultiplyL(left);
}

Vector4 Matrix4x3::VecMultiplyL(const Vector4& left) const
{
	Vector4 output;

	for(uint leftRowIndex = 0; leftRowIndex < 1; leftRowIndex++)
	{
		for(uint rightColumnIndex = 0; rightColumnIndex < ROW_COUNT; 
		    rightColumnIndex++)
		{	
			float outputElement = 0;

			for(uint leftColumnIndex = 0; leftColumnIndex < COLUMN_COUNT; 
			    leftColumnIndex++)
			{
				
				float currentLeftElement = left.getIndex(leftColumnIndex);
				float currentRightElement = getElement(leftColumnIndex, 
								       rightColumnIndex);
				float currentMultiplication = currentLeftElement * 				  currentRightElement;								
				
				outputElement +=  currentMultiplication;
			}

			output.setIndex(rightColumnIndex, outputElement);
		}
	}

	return output;
}

Vector4 operator* (const Vector4& left, 
		   const Matrix4x3& right)
{
	return right.VecMultiplyL(left);
}

Float Matrix4x3::getElement(int rowIndex, int columnIndex) const
{
	return m_Elements[rowIndex][columnIndex];
}

void Matrix4x3::setElement(int rowIndex, int columnIndex, Float value)
{
	assert(isnan(value) == false);
	m_Elements[rowIndex][columnIndex] = value;
}

Matrix4x3 Matrix4x3::Add(const Matrix4x3& left, const Matrix4x3& right)
{
	Matrix4x3 returnValue;
	
	for(uint i = 0; i < ROW_COUNT; i++)
	{
		for(uint j = 0; j < COLUMN_COUNT; j++)
		{
			Float elementLeft = left.getElement(i, j);
			Float elementRight = right.getElement(i, j);
			Float added = elementLeft + elementRight;

			returnValue.setElement(i, j, added);
		}
	}

	return returnValue;
}

Matrix4x3 Matrix4x3::operator+(const Matrix4x3& right)
{
	return Add(*this, right);
}

Matrix4x3 Matrix4x3::operator-(const Matrix4x3& right)
{
	return Add(*this, right * 1.0f);	
}

void Matrix4x3::AddL(const Matrix4x3& left)
{
	copy(Add(left, *this));
	assert(isValid());
}

void Matrix4x3::AddR(const Matrix4x3& right)
{
	copy(Add(*this, right));
	assert(isValid());
}



Matrix4x3 Matrix4x3::Scale(Float scale, const Matrix4x3& mat)
{
	Matrix4x3 returnValue;
	
	for(uint i = 0; i < ROW_COUNT; i++)
	{
		for(uint j = 0; j < COLUMN_COUNT; j++)
		{
			Float element = mat.getElement(i, j);			
			Float scaled = element * scale;

			returnValue.setElement(i, j, scaled);
		}
	}

	return returnValue;
}

Matrix4x3 Matrix4x3::operator*(Float scale) const
{
	return Matrix4x3::Scale(scale, *this);
}

void Matrix4x3::scale(Float scale)
{
	copy(Scale(scale, *this));
	assert(isValid());
}

Matrix4x3 Matrix4x3::SetAll(Float value)
{
	Matrix4x3 mat;
	mat.setAll(value);
	return mat;
}
void Matrix4x3::setAll(Float value)
{
	for(uint i = 0; i < ROW_COUNT; i++)
	{
		for(uint j = 0; j < COLUMN_COUNT; j++)
		{			
			setElement(i, j, value);
		}
	}
	assert(isValid());
}

void Matrix4x3::getArrayColumnOrder(Float* m)
{
	GetArrayColumnOrder(*this, m);
}
void Matrix4x3::setArrayColumnOrder(Float* m)
{
	copy(SetArrayColumnOrder(m));
		assert(isValid());
}

void Matrix4x3::GetArrayColumnOrder(Matrix4x3 mat, Float* m)
{
	for(uint i = 0; i < ROW_COUNT; i++)
	{
		for(uint j = 0; j < COLUMN_COUNT; j++)
		{
			m[4*j + i] = mat.getElement(i, j);
		}
	}
}

Matrix4x3 Matrix4x3::SetArrayColumnOrder(Float* m)
{
	Matrix4x3 returnValue;

	for(uint i = 0; i < ROW_COUNT; i++)
	{
		for(uint j = 0; j < COLUMN_COUNT; j++)
		{
			returnValue.setElement(i, j, m[ROW_COUNT*j + i]);
		}
	}

	return returnValue;
}

void Matrix4x3::copy(const Matrix4x3& mat)
{
	for(uint i = 0; i < ROW_COUNT; i++)
	{
		for(uint j = 0; j < COLUMN_COUNT; j++)
		{
			setElement(i, j, mat.getElement(i, j));
		}
	}
	
		assert(isValid());
}

void Matrix4x3::getColumnMajorArray(Float* array) const
{
  for(uint rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++)
    {
      for(uint columnIndex = 0; columnIndex < COLUMN_COUNT; columnIndex++)
	{
	  array[(COLUMN_COUNT * rowIndex) + columnIndex] = 
	    getElement(rowIndex, columnIndex);
	}
    }
}

ostream& operator<<(ostream& cout, Matrix4x3& obj)
{
   for(uint rowIndex = 0; rowIndex < Matrix4x3::ROW_COUNT; rowIndex++)
    {
      cout << "[";
      for(uint columnIndex = 0; columnIndex < Matrix4x3::COLUMN_COUNT; columnIndex++)
	{
	  cout << " " << obj.getElement(rowIndex, columnIndex) ;
	}
      cout << "]";
    }

   return cout;
}

bool Matrix4x3::isValid() const
{
	bool isNan = false;
	for (uint rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++) {
		for (uint columnIndex = 0 ; columnIndex < COLUMN_COUNT; columnIndex++) {
			isNan |= isnan(getElement(rowIndex, columnIndex));
		}
	}
	return !isNan;						
}

