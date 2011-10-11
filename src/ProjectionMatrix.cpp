#include "ProjectionMatrix.h"

void* ProjectionMatrix::Constructor()
{
  return new ProjectionMatrix();
}

ProjectionMatrix::ProjectionMatrix()
{
	
}

ProjectionMatrix::ProjectionMatrix(const Vector3& near, const Vector3& far)
{
  m_Near = near;
  m_Far = far;
}

ProjectionMatrix::ProjectionMatrix(const ProjectionMatrix& other)
{
  copy(other);
}

ProjectionMatrix& ProjectionMatrix::operator=(const ProjectionMatrix& other)
{
  copy(other);
  return *this;
}

void ProjectionMatrix::copy(const ProjectionMatrix& other)
{
  m_Near = other.m_Near;
  m_Far = other.m_Far;

}

void ProjectionMatrix::setFrustrum(const Vector3& near, 
				   const Vector3& far)
{
  m_Near = near;
  m_Far = far;
}


void ProjectionMatrix::setFrustrum(Float nearX, Float nearY, Float nearZ, 
				   Float farX, Float farY, Float farZ)
{
  m_Near.setX(nearX);
  m_Near.setY(nearY);
  m_Near.setZ(nearZ);
	
  m_Far.setX(farX);
  m_Far.setY(farY);
  m_Far.setZ(farZ);	
}

Matrix4x4 ProjectionMatrix::getMatrix() const 
{
  //the idea is that the extents are setup so 

  //I need to make it so the farX and farY become as small as the nearX and nearY

  Matrix4x4 projection = Matrix4x4::Identity();

	
  double n = m_Near.getZ();
  double r = m_Near.getX();
  double t = m_Near.getY();
  double f = m_Far.getZ();
       
  double m00 = n / r;
  double m11 = n / t;
  double m22 = -(f + n) / (f - n);
  double m23 = -1.0;
  double m32 = (-2.0*f*n) / (f - n);
  double m33 = 0.0;
	

  projection.setElement(0, 0, m00);
  projection.setElement(1, 1, m11);
  projection.setElement(2, 2, m22);
  projection.setElement(2, 3, m23);
  projection.setElement(3, 2, m32);
  projection.setElement(3, 3, m33);


  return projection;
}

Float ProjectionMatrix::getNearZ() const
{
  return m_Near.getZ();
}

Vector3 ProjectionMatrix::getNear()
{
  return m_Near;
}

Vector3 ProjectionMatrix::getFar()
{
  return m_Far;  
}
