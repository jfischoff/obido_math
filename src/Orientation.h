#ifndef ORIENTATION_H
#define ORIENTATION_H

#include "RotationUtils.h"
#include "RotationMatrix.h"
#include "Quaternion.h"
#include "AngleAxis.h"

//this is basically  a wrapper around rotations
//It abstracts the storage of a the rotation
//and provides methods for conversion
//it also provides normalization

class Orientation 
{
 public:
  //Constructors
  static void* Constructor();
  Orientation();
  Orientation(const Quaternion& quat);
  Orientation(const AngleAxis& angleAxis);
  Orientation(const RotationMatrix& rotationMatrix);
  Orientation(const Orientation& other);
  Orientation& operator=(const Orientation& other);


  void copy(const Orientation& other);
	
  //conversions
  RotationMatrix toRotationMatrix() const;
  void fromRotation(const RotationMatrix& rotationMatrix);
	
  Quaternion toQuaternion() const;
  void fromQuaternion(const Quaternion& quat);
	
  AngleAxis toAngleAxis() const;
  void fromAngleAxis(const AngleAxis& angleAxis);
	
  //forwarding methods for everything
  //add as needed
  void setRotation(const AngleAxis& angleAxis);
  void setRotation(const RotationMatrix& rotationMatrix);
  void appendRotation(const AngleAxis& angleAxis);
  Orientation& appendOrientation(const Orientation& orientation);
  Orientation& operator*=(const Orientation& orientation);

  void identity();
	
  //compose operator ...next over all types
  Orientation operator*(const Orientation& orientation) const;
	
  //invert
  Orientation operator!() const;
	
  //I should be able to interpolate
  static Orientation interpolate(const Orientation& left,
				 const Orientation& right, double t);
	
  //forwarded methods
  Vector3 getOutVector() const;
	
	
	
  bool almostEqual(const Orientation& right) const;
	
  static Orientation Arbitrary();
	
  bool operator==(const Orientation& other) const;
	
  //maybe I should multiply the vectors
  //wait until I see how I use it
	
 private:
  //store as a quaternion for now
  Quaternion m_Quaternion;
};

#endif //ORIENTATION_H
