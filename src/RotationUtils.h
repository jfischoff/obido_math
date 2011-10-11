#ifndef ROTATIONUTILS_H
#define ROTATIONUTILS_H

#include "AngleAxis.h"
#include "Quaternion.h"
#include "RotationMatrix.h"

class RotationUtils
{
 public:
  static void quaterionToAngleAxis(const Quaternion& quat, AngleAxis& angleAxis);
  static void angleAxisToQuaternion(const AngleAxis& angleAxis, Quaternion& quat);
	
  static void quaterionToRotationMatrix(const Quaternion& quat, RotationMatrix& rotationMatrix);
  static void rotationMatrixToQuaternion(const RotationMatrix& rotationMatrix, Quaternion& quat);
	
  static void rotationMatrixToAngleAxis(const RotationMatrix& rotationMatrix, 
					AngleAxis& angleAxis);
  static void angleAxisToRotationMatrix(const AngleAxis& angleAxis, RotationMatrix& rotationMatrix);

      
};

#endif //RotationUtils
