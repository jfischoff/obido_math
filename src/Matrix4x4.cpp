#include "Matrix4x4.h"
#include <string.h>

void* Matrix4x4::Constructor()
{
  return new Matrix4x4();
}

Matrix4x4::Matrix4x4()
{
  memset(m_Elements, 0, sizeof(Float) * 16);
}

Matrix4x4::Matrix4x4(Float m00, Float m01, Float m02, Float m03, 
		     Float m10, Float m11, Float m12, Float m13,
		     Float m20, Float m21, Float m22, Float m23,
		     Float m30, Float m31, Float m32, Float m33)
{
  setElement(0, 0, m00);
  setElement(0, 1, m01);
  setElement(0, 2, m02);
  setElement(0, 3, m03);
	
  setElement(1, 0, m10);
  setElement(1, 1, m11);
  setElement(1, 2, m12);
  setElement(1, 3, m13);
	
  setElement(2, 0, m20);
  setElement(2, 1, m21);
  setElement(2, 2, m22);
  setElement(2, 3, m23);
	
  setElement(3, 0, m30);
  setElement(3, 1, m31);
  setElement(3, 2, m32);
  setElement(3, 3, m33);
  assert(isValid());
}

Matrix4x4::Matrix4x4(const Matrix4x4& other)
{
  copy(other);
  assert(isValid());
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other)
{
  copy(other);
  assert(isValid());
  return *this;
}


Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& left, const Matrix4x4& right)
{
  Matrix4x4 returnValue;
	
  for(int rowIndex = 0; rowIndex < 4; rowIndex++)
    {
      for(int columnIndex = 0; columnIndex < 4; columnIndex++)
	{	
	  float element = 0;

	  for(int index = 0; index < 4; index++)
	    {
	      element += left.getElement(rowIndex, index) * 
		right.getElement(index, columnIndex);
	    }

	  returnValue.setElement(rowIndex, columnIndex, element);
	}
    }
	
  return returnValue;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& right)
{
  return Matrix4x4::Multiply(*this, right);
}

void Matrix4x4::multiply(const Matrix4x4& left, const Matrix4x4& right)
{
  return copy(Multiply(left, right));
}

void Matrix4x4::multiplyL(const Matrix4x4& left)
{
  copy(Multiply(left, *this));
}

void Matrix4x4::multiplyR(const Matrix4x4& right)
{
  copy(Multiply(*this, right));
}




Vector4 Matrix4x4::VecMultiplyR(const Vector4& right) const
{
  Vector4 output;

  for(int rowIndex = 0; rowIndex < 4; rowIndex++)
    {
      for(int columnIndex = 0; columnIndex < 1; columnIndex++)
	{	
	  float element = 0;

	  for(int index = 0; index < 4; index++)
	    {
	      element += getElement(rowIndex, index) * 
		right.getIndex(index);
	    }

	  output.setIndex(rowIndex, element);
	}
    }

  return output;
}

Vector4 operator*(const Matrix4x4& left, 
		  const Vector4& right)
{
  return left.VecMultiplyR(right);
}

HomogenusPosition Matrix4x4::VecMultiplyR(const HomogenusPosition& right) const
{
  return HomogenusPosition(VecMultiplyR((const Vector4&)right));
}

HomogenusPosition operator* (const Matrix4x4& left, 
			     const HomogenusPosition& right)
{
  return left.VecMultiplyR(right);
}

HomogenusPosition Matrix4x4::VecMultiplyL(const HomogenusPosition& left) const
{
  return HomogenusPosition(VecMultiplyL((const Vector4&)left));
}

HomogenusPosition operator* (const HomogenusPosition& left, 
			     const Matrix4x4& right)
{
  return right.VecMultiplyL(left);
}



Vector4 Matrix4x4::VecMultiplyL(const Vector4& left) const
{
  Vector4 output;

  for(int leftRowIndex = 0; leftRowIndex < 1; leftRowIndex++)
    {
      for(int rightColumnIndex = 0; rightColumnIndex < 4; rightColumnIndex++)
	{	
	  float outputElement = 0;

	  for(int leftColumnIndex = 0; leftColumnIndex < 4; leftColumnIndex++)
	    {
				
	      float currentLeftElement = left.getIndex(leftColumnIndex);
	      float currentRightElement = getElement(leftColumnIndex, rightColumnIndex);
	      float currentMultiplication = currentLeftElement * currentRightElement;								
				
	      outputElement +=  currentMultiplication;
	    }

	  output.setIndex(rightColumnIndex, outputElement);
	}
    }

  return output;
}

Vector4 operator* (const Vector4& left, 
		   const Matrix4x4& right)
{
  return right.VecMultiplyL(left);
}

Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& mat)
{
  Matrix4x4 returnValue;
	
  for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
	{
	  returnValue.setElement(i, j, mat.getElement(j, i));
	}
    }

  return returnValue;
}

void Matrix4x4::transpose()
{
  copy(Transpose(*this));
  assert(isValid());
}

Float Matrix4x4::getElement(int rowIndex, int columnIndex) const
{
  return m_Elements[rowIndex][columnIndex];
}

void Matrix4x4::setElement(int rowIndex, int columnIndex, Float value)
{
  assert(isnan(value) == false);
  m_Elements[rowIndex][columnIndex] = value;
}

Matrix4x4 Matrix4x4::Add(const Matrix4x4& left, const Matrix4x4& right)
{
  Matrix4x4 returnValue;
	
  for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
	{
	  Float elementLeft = left.getElement(i, j);
	  Float elementRight = right.getElement(i, j);
	  Float added = elementLeft + elementRight;

	  returnValue.setElement(i, j, added);
	}
    }

  return returnValue;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& right)
{
  return Add(*this, right);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& right)
{
  return Add(*this, right * 1.0f);	
}

void Matrix4x4::AddL(const Matrix4x4& left)
{
  copy(Add(left, *this));
  assert(isValid());
}

void Matrix4x4::AddR(const Matrix4x4& right)
{
  copy(Add(*this, right));
  assert(isValid());
}

Matrix4x4 Matrix4x4::Inverse(const Matrix4x4& mat)
{
	
  Float m[16];
  GetArrayColumnOrder(mat, m);

  Float inv[16], invOut[16], det;
  int i;

  inv[0] =   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15]
    + m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
  inv[4] =  -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15]
    - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
  inv[8] =   m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15]
    + m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
  inv[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14]
    - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
  inv[1] =  -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15]
    - m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
  inv[5] =   m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15]
    + m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
  inv[9] =  -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15]
    - m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
  inv[13] =  m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14]
    + m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
  inv[2] =   m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15]
    + m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
  inv[6] =  -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15]
    - m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
  inv[10] =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15]
    + m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
  inv[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14]
    - m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
  inv[3] =  -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11]
    - m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
  inv[7] =   m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11]
    + m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
  inv[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11]
    - m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
  inv[15] =  m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10]
    + m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];

  det = m[0]*inv[0] + m[1]*inv[4] + m[2]*inv[8] + m[3]*inv[12];

  det = 1.0 / det;

  for (i = 0; i < 16; i++)
    invOut[i] = inv[i] * det;

  return SetArrayColumnOrder(invOut);
}

Matrix4x4 Matrix4x4::operator!()
{
  return Inverse(*this);
}

Matrix4x4& Matrix4x4::invert()
{
  copy(Inverse(*this));
  assert(isValid());
  return *this;
}

Float Matrix4x4::Determinate(const Matrix4x4& mat)
{
  Float value;
  value =
    getElement(0, 3) * getElement(1, 2) * getElement(2, 1) * getElement(3, 0)-getElement(0, 2) * 
    getElement(1, 3) * getElement(2, 1) * getElement(3, 0)-getElement(0, 3) * getElement(1, 1) * 
    getElement(2, 2) * getElement(3, 0)+getElement(0, 1) * getElement(1, 3) * getElement(2, 2) * 
    getElement(3, 0) +
    getElement(0, 2) * getElement(1, 1) * getElement(2, 3) * getElement(3, 0)-getElement(0, 1) * 
    getElement(1, 2) * getElement(2, 3) * getElement(3, 0)-getElement(0, 3) * getElement(1, 2) * 
    getElement(2, 0) * getElement(3, 1)+getElement(0, 2) * getElement(1, 3) * getElement(2, 0) * 
    getElement(3, 1)+
    getElement(0, 3) * getElement(1, 0) * getElement(2, 2) * getElement(3, 1)-getElement(0, 0) * 
    getElement(1, 3) * getElement(2, 2) * getElement(3, 1)-getElement(0, 2) * getElement(1, 0) * 
    getElement(2, 3) * getElement(3, 1)+getElement(0, 0) * getElement(1, 2) * getElement(2, 3) * 
    getElement(3, 1)+
    getElement(0, 3) * getElement(1, 1) * getElement(2, 0) * getElement(3, 2)-getElement(0, 1) * 
    getElement(1, 3) * getElement(2, 0) * getElement(3, 2)-getElement(0, 3) * getElement(1, 0) * 
    getElement(2, 1) * getElement(3, 2)+getElement(0, 0) * getElement(1, 3) * getElement(2, 1) * 
    getElement(3, 2)+
    getElement(0, 1) * getElement(1, 0) * getElement(2, 3) * getElement(3, 2)-getElement(0, 0) * 
    getElement(1, 1) * getElement(2, 3) * getElement(3, 2)-getElement(0, 2) * getElement(1, 1) * 
    getElement(2, 0) * getElement(3, 3)+getElement(0, 1) * getElement(1, 2) * getElement(2, 0) * 
    getElement(3, 3)+
    getElement(0, 2) * getElement(1, 0) * getElement(2, 1) * getElement(3, 3)-getElement(0, 0) * 
    getElement(1, 2) * getElement(2, 1) * getElement(3, 3)-getElement(0, 1) * getElement(1, 0) * 
    getElement(2, 2) * getElement(3, 3)+getElement(0, 0) * getElement(1, 1) * 
    getElement(2, 2) * getElement(3, 3);
    
  return value;
}

Float Matrix4x4::determinate()
{
  return Determinate(*this);
}

Matrix4x4 Matrix4x4::Scale(Float scale, const Matrix4x4& mat)
{
  Matrix4x4 returnValue;
	
  for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
	{
	  Float element = mat.getElement(i, j);			
	  Float scaled = element * scale;

	  returnValue.setElement(i, j, scaled);
	}
    }

  return returnValue;
}

Matrix4x4 Matrix4x4::operator*(Float scale) const
{
  return Matrix4x4::Scale(scale, *this);
}

void Matrix4x4::scale(Float scale)
{
  copy(Scale(scale, *this));
  assert(isValid());
}

Matrix4x4 Matrix4x4::SetAll(Float value)
{
  Matrix4x4 mat;
  mat.setAll(value);
  return mat;
}
void Matrix4x4::setAll(Float value)
{
  for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
	{			
	  setElement(i, j, value);
	}
    }
  assert(isValid());
}

Matrix4x4 Matrix4x4::Identity()
{
  Matrix4x4 returnValue;
  returnValue.setAll(0);

  returnValue.setElement(0, 0, 1.0f);
  returnValue.setElement(1, 1, 1.0f);
  returnValue.setElement(2, 2, 1.0f);
  returnValue.setElement(3, 3, 1.0f);

  return returnValue;
}
void Matrix4x4::identity()
{
  copy(Identity());	
  assert(isValid());
}

void Matrix4x4::getArrayColumnOrder(Float* m)
{
  GetArrayColumnOrder(*this, m);
}
void Matrix4x4::setArrayColumnOrder(Float* m)
{
  copy(SetArrayColumnOrder(m));
  assert(isValid());
}

void Matrix4x4::GetArrayColumnOrder(Matrix4x4 mat, Float* m)
{
  for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
	{
	  m[4*j + i] = mat.getElement(i, j);
	}
    }
}

Matrix4x4 Matrix4x4::SetArrayColumnOrder(Float* m)
{
  Matrix4x4 returnValue;

  for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
	{
	  returnValue.setElement(i, j, m[4*j + i]);
	}
    }

  return returnValue;
}

void Matrix4x4::copy(const Matrix4x4& mat)
{
  for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
	{
	  setElement(i, j, mat.getElement(i, j));
	}
    }
	
  assert(isValid());
}

void Matrix4x4::getColumnMajorArray(Float* array) const
{
  for(int rowIndex = 0; rowIndex < 4; rowIndex++)
    {
      for(int columnIndex = 0; columnIndex < 4; columnIndex++)
	{
	  array[(4 * rowIndex) + columnIndex] = 
	    getElement(rowIndex, columnIndex);
	}
    }
}

ostream& operator<<(ostream& cout, Matrix4x4& obj)
{
  for(int rowIndex = 0; rowIndex < 4; rowIndex++)
    {
      cout << "[";
      for(int columnIndex = 0; columnIndex < 4; columnIndex++)
	{
	  cout << " " << obj.getElement(rowIndex, columnIndex) ;
	}
      cout << "]";
    }

  return cout;
}

bool Matrix4x4::isValid() const
{
  bool isNan = false;
  for (int rowIndex = 0; rowIndex < 4; rowIndex++) {
    for (int columnIndex = 0 ; columnIndex < 4; columnIndex++) {
      isNan |= isnan(getElement(rowIndex, columnIndex));
    }
  }
  return !isNan;						
}
