#include "Orientation.h"

void* Orientation::Constructor()
{
  return new Orientation();
}

Orientation::Orientation()
{
	
}

Orientation::Orientation(const Quaternion& quat)
{
  m_Quaternion = quat;
}

Orientation::Orientation(const AngleAxis& angleAxis)
{
  fromAngleAxis(angleAxis);									
}

Orientation::Orientation(const RotationMatrix& rotationMatrix)
{
  fromRotation(rotationMatrix);
}

Orientation::Orientation(const Orientation& other)
{
  copy(other);
}

Orientation& Orientation::operator=(const Orientation& other)
{
  copy(other);
  return *this;
}

void Orientation::copy(const Orientation& other)
{
  m_Quaternion = other.m_Quaternion;
}

void Orientation::identity()
{
  m_Quaternion.identity();
}

//conversions
RotationMatrix Orientation::toRotationMatrix() const
{
  RotationMatrix rotationMatrix;
  RotationUtils::quaterionToRotationMatrix(m_Quaternion, rotationMatrix);	
  return rotationMatrix;
}

void Orientation::fromRotation(const RotationMatrix& rotationMatrix)
{
  RotationUtils::rotationMatrixToQuaternion(rotationMatrix, 
					    m_Quaternion);
}

Quaternion Orientation::toQuaternion() const
{
  return m_Quaternion;
}

void Orientation::fromQuaternion(const Quaternion& quat)
{
  m_Quaternion = quat;
}

AngleAxis Orientation::toAngleAxis() const
{
  AngleAxis angleAxis;
  RotationUtils::quaterionToAngleAxis(m_Quaternion, 
				      angleAxis);
  return angleAxis;
}

void Orientation::fromAngleAxis(const AngleAxis& angleAxis)
{
  RotationUtils::angleAxisToQuaternion(angleAxis, m_Quaternion);
}

Orientation Orientation::operator*(const Orientation& orientation) const
{
  return m_Quaternion * orientation.m_Quaternion;
}

Orientation Orientation::operator!() const
{
  return !m_Quaternion;
}

Orientation Orientation::interpolate(const Orientation& left,
				     const Orientation& right, double t)
{
  return Quaternion::Slerp(left.m_Quaternion, right.m_Quaternion , t);
}

Vector3 Orientation::getOutVector() const
{
  return toRotationMatrix().getRow(2);
}

bool Orientation::almostEqual(const Orientation& right) const
{
  return m_Quaternion.almostEqual(right.m_Quaternion);
}

Orientation Orientation::Arbitrary()
{
  return Orientation(Quaternion::Arbitrary());
}

bool Orientation::operator==(const Orientation& other) const
{
  return m_Quaternion == other.m_Quaternion;
}

void Orientation::setRotation(const AngleAxis& angleAxis)
{
  RotationUtils::angleAxisToQuaternion(angleAxis, m_Quaternion);
}

void Orientation::setRotation(const RotationMatrix& rotationMatrix)
{
  RotationUtils::rotationMatrixToQuaternion(rotationMatrix, m_Quaternion);
}


void Orientation::appendRotation(const AngleAxis& angleAxis)
{
  Quaternion offsetQuat;
  RotationUtils::angleAxisToQuaternion(angleAxis, offsetQuat);
	
  m_Quaternion *= offsetQuat;
}

Orientation& Orientation::appendOrientation(const Orientation& orientation)
{
  m_Quaternion *= orientation.m_Quaternion;
  return *this;
}

Orientation& Orientation::operator*=(const Orientation& orientation)
{
  return appendOrientation(orientation);
}


