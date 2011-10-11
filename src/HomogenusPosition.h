#ifndef HOMOGENUSPOSITION_H
#define HOMOGENUSPOSITION_H

#include "Vector4.h"

class HomogenusPosition : public Vector4
{
 public:
  HomogenusPosition(Float x, Float y, Float z, Float w);

  HomogenusPosition(const Vector3& vec);
  HomogenusPosition(const Vector4& vec);
	    
  HomogenusPosition();
	
  static HomogenusPosition Zero();

  Vector3 normalizeToVector3() const;
	
  operator Vector3 () const;
};

#endif //HOMOGENUSPOSITION_H
