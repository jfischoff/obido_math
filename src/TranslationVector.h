#ifndef TRANSLATIONVECTOR_H
#define TRANSLATIONVECTOR_H

#include "Vector3.h"
#include "Matrix4x4.h"

class TranslationVector : public Vector3 {
 public:
  //constructor stuff
  TranslationVector();
  TranslationVector(const Vector3& vec);
  TranslationVector(const Matrix4x4& mat);

 private:
};

#endif //TRANSLATIONVECTOR_H
