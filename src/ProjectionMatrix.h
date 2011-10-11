#ifndef PROJECTIONMATRIX_H
#define PROJECTIONMATRIX_H

#include "Matrix4x4.h"
#include "Vector3.h"
#include <iostream>
using namespace std;

class ProjectionMatrix
{
 public:
  static void* Constructor();
  ProjectionMatrix();
  ProjectionMatrix(const Vector3& near, const Vector3& far);
  ProjectionMatrix(const ProjectionMatrix& other);
  ProjectionMatrix& operator=(const ProjectionMatrix& other);
  void copy(const ProjectionMatrix& other);		
	
  void setFrustrum(const Vector3& near, const Vector3& far);
  void setFrustrum(Float nearX, Float nearY, Float nearZ, 
		   Float farX, Float farY, Float farZ);

  Matrix4x4 getMatrix() const;
	
  Float getNearZ() const;

  Vector3 getNear();
  Vector3 getFar();
	
 private:
  Vector3 m_Near;
  Vector3 m_Far;
};

#endif //PROJECTIONMATRIX_H
