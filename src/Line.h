#ifndef LINE_H
#define LINE_H

#include "Vector3.h"
#include "Matrix4x4.h"
#include <iostream>
using namespace std;

class Line
{
 public:
  static void* Constructor();
  Line();
  Line(const Vector3& start, const Vector3& end);
  Line(const Line& other);
  Line& operator=(const Line& other);
  virtual void copy(const Line& other);
  virtual ~Line();
   
  static Line Transform(const Matrix4x4& transform, const Line& line);
  
  double GetXSlope() const;
  double GetXIntercept() const;

  double GetYSlope() const;
  double GetYIntercept() const;

  double GetZSlope() const;
  double GetZIntercept() const;

  Vector3 GetDirection() const;

  Vector3 GetStart() const;
  Vector3 GetEnd() const;

  Vector3 evaluate(double t) const;

  double getLength();
	
  double solveForT(const Vector3& posOnLine) const;
	
  virtual bool intersect(const Line& other, Vector3& outputVec, double& leftT, 
			 double& rightT) const;
	
  static bool Intersect(const Line& left, const Line& right, Vector3& outputVec,
			double& leftT, double& rightT);
	
  static bool CramersRule(double a, double b, double c, double d, double e,
			  double f, double& x, double& y);
	
  Vector3 evaluateInX(double x) const;
	
  void center();
			
 private:
  Vector3 m_Start;
  Vector3 m_End;

};

#endif //LINE_H
