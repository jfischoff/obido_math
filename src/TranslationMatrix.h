#ifndef TRANSLATIONMATRIX_H
#define TRANSLATIONMATRIX_H

#include "Matrix4x4.h"
#include "TranslationVector.h"

class TranslationMatrix : public Matrix4x4
{
 public:
  TranslationMatrix();
  TranslationMatrix(const TranslationMatrix& other);
  TranslationMatrix(const Vector3& other);
  TranslationMatrix& operator=(const TranslationMatrix& other);
  TranslationMatrix& operator=(const TranslationVector& vec);
  TranslationMatrix(const Matrix4x4& mat);
  void copy(const TranslationMatrix& other);
  void copy(const Matrix4x4& other);
  //etc	
	
  TranslationMatrix add(const TranslationMatrix& right) const;
  TranslationMatrix operator+(const TranslationMatrix& right) const;
	

  TranslationMatrix add(const Vector3& right) const;
  TranslationMatrix operator+(const Vector3& right) const;

  void addAccum(const Vector3& right);
  void operator+=(const Vector3& right);
	
	
  //conversions from/to vector form
  void fromTranslationVector(const Vector3& vec);
  Vector3 toTranslationVector() const;
  operator Vector3 () const;

  void fromMatrix4x4(const Matrix4x4& matrix);
	
  void zero();
  //get individual elements
  Float getX() const;		
  Float getY() const;
  Float getZ() const;
		
  void setX(Float x);
  void setY(Float y);	
  void setZ(Float z);
	
	
  //helper stuff
  void setIndex(uint index, Float x);
  Float getIndex(uint index);

};

#endif //TRANSLATIONMATRIX_H
