#include "TranslationMatrix.h"

TranslationMatrix::TranslationMatrix()
{
  identity();
}

TranslationMatrix::TranslationMatrix(const TranslationMatrix& other)
{
  copy(other);
}

TranslationMatrix& TranslationMatrix::operator=(const TranslationMatrix& other)
{
  copy(other);
  return *this;
}

TranslationMatrix::TranslationMatrix(const Matrix4x4& other)
{
  Matrix4x4::copy(other);
}

TranslationMatrix::TranslationMatrix(const Vector3& other)
{
  fromTranslationVector(other);
}

TranslationMatrix& TranslationMatrix::operator=(const TranslationVector& vec)
{

  fromTranslationVector(vec);
  return *this;
}

void TranslationMatrix::copy(const TranslationMatrix& other)
{
  Matrix4x4::copy(other);
}

void TranslationMatrix::copy(const Matrix4x4& other)
{
  setX(other.getElement(3, 0));
  setY(other.getElement(3, 1));
  setZ(other.getElement(3, 2));
}

void TranslationMatrix::fromTranslationVector(const Vector3& vec)
{
  identity();
  setX(vec.getX());
  setY(vec.getY());
  setZ(vec.getZ());
}

Vector3 TranslationMatrix::toTranslationVector() const
{
  return Vector3(getX(), getY(), getZ());
}

TranslationMatrix::operator Vector3 () const
{
  return toTranslationVector();
}

TranslationMatrix TranslationMatrix::add(const TranslationMatrix& right) const
{
  return TranslationMatrix(Matrix4x4::Add(*this, right)); 
}

TranslationMatrix TranslationMatrix::operator+(const TranslationMatrix& right) const
{
  return add(right);
}


TranslationMatrix TranslationMatrix::add(const Vector3& right) const
{
  return TranslationMatrix(toTranslationVector() + right);
}

TranslationMatrix TranslationMatrix::operator+(const Vector3& right) const
{
  return add(right);
}

void TranslationMatrix::addAccum(const Vector3& right)
{
  *this = add(right);
}

void TranslationMatrix::operator+=(const Vector3& right)
{
  addAccum(right);
}

Float TranslationMatrix::getX() const
{
  return getElement(3, 0);
}

Float TranslationMatrix::getY() const
{
  return getElement(3, 1);
}

Float TranslationMatrix::getZ() const
{
  return getElement(3, 2);
}

void TranslationMatrix::setX(Float x)
{
  setElement(3, 0, x);
}

void TranslationMatrix::setY(Float y)
{
  setElement(3, 1, y);
}

void TranslationMatrix::setZ(Float z)
{
  setElement(3, 2, z);
}

void TranslationMatrix::setIndex(uint index, Float x)
{
  setElement(3, index, x);
}

Float TranslationMatrix::getIndex(uint index)
{
  return getElement(3, index);
}


void TranslationMatrix::fromMatrix4x4(const Matrix4x4& matrix)
{
  Float x = matrix.getElement(3, 0);
  Float y = matrix.getElement(3, 1);
  Float z = matrix.getElement(3, 2);

  setElement(3, 0, x);
  setElement(3, 1, y);
  setElement(3, 2, z);
}

void TranslationMatrix::zero()
{
  setElement(3, 0, 0.0);
  setElement(3, 1, 0.0);
  setElement(3, 2, 0.0);
}
