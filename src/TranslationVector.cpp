#include "TranslationVector.h"

TranslationVector::TranslationVector() : Vector3()
{
  
}

TranslationVector::TranslationVector(const Vector3& vec)
{
  Vector3::copy(vec);
}

TranslationVector::TranslationVector(const Matrix4x4& mat)
{
  setX(mat.getElement(3, 0));
  setY(mat.getElement(3, 1));
  setZ(mat.getElement(3, 2));
}
