#ifndef ANGLEAXIS_H
#define ANGLEAXIS_H

#include "globalDefines.h"
#include "Vector3.h"
#include <math.h>
#include <iostream>

using namespace std;

class AngleAxis
{
public:
  static void* Constructor();
  AngleAxis(Float x, Float y, Float z, Float angle);  
  AngleAxis(const Vector3& vec, Float angle);       
  AngleAxis();
  AngleAxis(const AngleAxis& other);
  AngleAxis& operator=(const AngleAxis& other);
  void copy(const AngleAxis& other);


  Float getAngle() const;
  Float getX() const;
  Float getY() const;
  Float getZ() const;

  void normalize();

  bool AlmostEqual(const AngleAxis& other);

private:

  Float m_Angle;
  
  Float m_X;
  Float m_Y;
  Float m_Z;
};

#endif //ANGLEAXIS_H
