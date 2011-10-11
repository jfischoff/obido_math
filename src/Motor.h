#ifndef MOTOR_H
#define MOTOR_H

#include "RotationUtils.h"
#include "Matrix4x4.h"
#include "ScaleVector.h"
#include "TranslationVector.h"
#include "TranslationMatrix.h"
#include "Orientation.h"
#include <iostream>

using namespace std;

//rename this Motor
//make transform like the maya transform
//A whole shitload of matrices

class Motor
{
 public:
  static void* Constructor();
  Motor();
  //ignore scale for now
	
  Motor(const Vector3& offset, 
	    const Orientation& orientation, const Vector3& pivot, 
	    bool inverted);
  Motor(const Vector3& offset, 
	    const Orientation& orientation, const Vector3& pivot);	
  static Motor OffsetOrientation(const Vector3& offset, 
				     const Orientation& orientation);
  static Motor PivotOrientation(const Vector3& pivot, 
				    const Orientation& orientation);
  Motor(const Motor& other);
  Motor(const Motor& other, bool inverted);
  Motor& operator=(const Motor& other);
  void copy(const Motor& other);

  void identity();

  //Methods that make transforms a group
  Motor compose(const Motor& transform) const;
  Motor operator*(const Motor& transform) const;
  Motor invert() const;
  Motor operator!() const;
		
  Motor scale(float scale) const;
  Motor operator*(float scale) const;
  Motor operator/(float scale) const;
  //vector multiply
  //and bi directional vector multiply
  Vector3 vecMultiplyR(const Vector3& right) const;
  friend Vector3 operator*(const Motor& left, const Vector3& right);
	
  Vector3 vecMultiplyL(const Vector3& left) const;
  friend Vector3 operator*(const Vector3& left, const Motor& right);

  //convert to 4x4
  Matrix4x4 toMatrix4x4() const;
  void fromMatrix4x4(const Matrix4x4& matrix);
	
  Matrix4x4 toInverseMatrix4x4() const;
  Matrix4x4 fromInverseMatrix4x4() const;
	
  //forwards all of the RotationMatrix methods
  void setRotation(const AngleAxis& angleAxis);
  void setRotation(const Quaternion& quaternion);
  void appendRotation(const AngleAxis& angleAxis);
  void setRotationMatrix(const RotationMatrix& rotationMatrix);
  RotationMatrix getRotationMatrix() const;
	
  Vector3 getOutVector() const;
	
  //forwards the translation vector methods
  //add/subtract
  //remove
  Motor& appendOffset(Float x, Float y, Float z);
  Motor& appendOffset(const Vector3& trans);
	
  Motor addOffset(float x, float y, float z) const;
  Motor addOffset(const Vector3& trans) const;
  //Motor operator+(const Vector3& trans) const;
  //Motor operator-(const Vector3& trans) const;
  //Motor& operator+=(const Vector3& trans);
	
  Motor& appendPivot(const Vector3& trans);
  Motor addPivot(const Vector3& trans) const;
	
  Motor& appendOrientation(const Orientation& orientation);
  Motor& operator+=(const Orientation& orientation);

	
  //set/get
  void setOffset(Float x, Float y, Float z);
  void setOffset(const Vector3& offset);
  Vector3 getOffset() const;

  void setPivot(const Vector3& pivot);
  Vector3 getPivot() const;
	
	
  //get/set
  //add/subtract
  //multiply

  Matrix4x4 getRotationMatrix4x4() const;
  Matrix4x4 getOffsetMatrix4x4() const;
  Matrix4x4 getPivotMatrix4x4() const;
	
  Vector3 getTransformedPosition() const;

  //add equals
  //add almost equals
  //add inplace versions of all functions
  bool getInverted() const;
  Orientation getOrientation() const;
  TranslationMatrix getOffsetTranslationMatrix() const;
  TranslationMatrix getPivotTranslationMatrix() const;
	
 private:
  Orientation m_Orientation;
  TranslationMatrix m_Offset;
  TranslationMatrix m_Pivot;
	
  bool m_Inverted;
};

#endif //TRANSFORM_H
