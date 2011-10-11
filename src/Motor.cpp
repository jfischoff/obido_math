#include "Motor.h"
#include "HomogenusPosition.h"
using namespace std;

void* Motor::Constructor()
{
  return new Motor();
}

Motor::Motor()
{
  m_Inverted = false;
}

Motor::Motor(const Vector3& offset, 
		     const Orientation& orientation,
		     const Vector3& pivot, bool inverted)
{
  m_Offset = TranslationVector(offset);
  m_Pivot = TranslationVector(pivot);
  m_Orientation = orientation;
  m_Inverted = inverted;
}

Motor::Motor(const Vector3& offset, 
		     const Orientation& orientation, const Vector3& pivot)
{
  *this = Motor(offset, orientation, pivot, false);
}

Motor Motor::OffsetOrientation(const Vector3& offset, 
				       const Orientation& orientation)
{
  return Motor(offset, orientation, Vector3::Zero(), false);
}

Motor Motor::PivotOrientation(const Vector3& pivot, 
				      const Orientation& orientation)
{
  return Motor(Vector3::Zero(), orientation, pivot, false);
}

Motor::Motor(const Motor& other, bool inverted)
{
  copy(other);
  m_Inverted = inverted;
}

Motor::Motor(const Motor& other)
{
  copy(other);
}

Motor& Motor::operator=(const Motor& other)
{
  copy(other);
  return *this;
}

void Motor::copy(const Motor& other)
{
  m_Offset = other.m_Offset;
  m_Orientation = other.m_Orientation;
  m_Pivot = other.m_Pivot;
  m_Inverted = other.m_Inverted;
}

void Motor::identity()
{
  m_Offset.zero();
  m_Orientation.identity();
  m_Pivot.zero();
  m_Inverted = false;
}

Motor Motor::compose(const Motor& right) const
{
  //I have to keep the 
  Matrix4x4 thisAsMatrix = toMatrix4x4();
  Matrix4x4 rightAsMatrix = right.toMatrix4x4();

  Matrix4x4 combMatrix = thisAsMatrix * rightAsMatrix;
  Vector3 pivot = combMatrix * HomogenusPosition(m_Pivot);
  //I am unsure of this
  Orientation orientation = m_Orientation * right.m_Orientation;
	
  TranslationMatrix translation;
	
  return Motor(translation, orientation, pivot);
}

Motor Motor::operator*(const Motor& transform) const
{
  return compose(transform);
}

Motor Motor::invert() const
{
  return Motor(*this, !getInverted());
}

Motor Motor::operator!() const
{
  return invert();
}

Vector3 Motor::vecMultiplyR(const Vector3& right) const
{
  return toMatrix4x4() * HomogenusPosition(right);
}

Vector3 operator*(const Motor& left, const Vector3& right)
{
  return left.vecMultiplyR(right);
}

Vector3 Motor::vecMultiplyL(const Vector3& left) const
{
  return HomogenusPosition(left) * toMatrix4x4();
}

Vector3 operator*(const Vector3& left, const Motor& right)
{
  return right.vecMultiplyL(left);
}   

void Motor::setRotation(const AngleAxis& angleAxis)
{	
  m_Orientation.setRotation(angleAxis);
}

void Motor::setRotation(const Quaternion& quaternion)
{
  m_Orientation.fromQuaternion(quaternion);  
}

void Motor::appendRotation(const AngleAxis& angleAxis)
{
  m_Orientation.appendRotation(angleAxis);
}

void Motor::setOffset(Float x, Float y, Float z)
{
  m_Offset.setX(x);
  m_Offset.setY(y);
  m_Offset.setZ(z);
}

void Motor::setOffset(const Vector3& vec)
{
  m_Offset.fromTranslationVector(vec);
}

Vector3 Motor::getOffset() const
{
  return m_Offset.toTranslationVector();
}

Motor& Motor::appendOffset(Float x, Float y, Float z)
{
  return appendOffset(Vector3(x, y, z));
}

Motor& Motor::appendOffset(const Vector3& trans)
{
  m_Offset += trans;
  return *this;
}

Motor& Motor::appendPivot(const Vector3& trans)
{
  m_Pivot += trans;
  return *this;
}

Motor& Motor::appendOrientation(const Orientation& orientation)
{
  m_Orientation *= orientation;
  return *this;
}

Motor& Motor::operator+=(const Orientation& orientation)
{
  return appendOrientation(orientation);
}

Vector3 Motor::getPivot() const
{
  return m_Pivot.toTranslationVector();
}

void Motor::setPivot(const Vector3& pivot) 
{
  m_Pivot.fromTranslationVector(pivot);
}

RotationMatrix Motor::getRotationMatrix() const
{
  return m_Orientation.toRotationMatrix();
}
Matrix4x4 Motor::getRotationMatrix4x4() const
{
  return getRotationMatrix().toMatrix4x4();
}

Vector3 Motor::getOutVector() const
{
  return m_Orientation.getOutVector();
}

Matrix4x4 Motor::getOffsetMatrix4x4() const
{
  return m_Offset;
}

Matrix4x4 Motor::getPivotMatrix4x4() const
{
  return m_Pivot;
}

Matrix4x4 Motor::toMatrix4x4() const
{
  //o * r * p
  Matrix4x4 rotationMatrix = getRotationMatrix4x4();
  Matrix4x4 offset = getOffsetMatrix4x4();
  Matrix4x4 pivot = getPivotMatrix4x4();
	
  Matrix4x4 comb;
  if(!m_Inverted)
    {
      comb = offset * rotationMatrix * pivot;	
    }
  else 
    {
      comb = pivot.invert() * rotationMatrix.invert() * offset.invert();	 
    }
	
  return comb;
}

void Motor::fromMatrix4x4(const Matrix4x4& matrix)
{
  //assert that the last thing is one
  assert(fabs(matrix.getElement(3, 3) - 1.0) < 000.1);
  //assert that the last parts are zero
  assert(fabs(matrix.getElement(0, 3)) < 000.1);
  assert(fabs(matrix.getElement(1, 3)) < 000.1);
  assert(fabs(matrix.getElement(2, 3)) < 000.1);

  m_Offset.zero();
  //take the translation out
  m_Pivot.fromMatrix4x4(matrix);

  //make the top part a rotation matrix and convert
  RotationMatrix rotationMatrix;
  rotationMatrix.fromMatrix4x4(matrix);
  m_Orientation.fromRotation(rotationMatrix);
}

Matrix4x4 Motor::toInverseMatrix4x4() const
{
  Matrix4x4 rotationMatrix = getRotationMatrix4x4();
  Matrix4x4 offset = getOffsetMatrix4x4();
  Matrix4x4 pivot = getPivotMatrix4x4();
	
  Matrix4x4 comb;
  if(m_Inverted)
    {
      comb = offset * rotationMatrix * pivot;	
    }
  else 
    {
      comb = pivot.invert() * rotationMatrix.invert() * offset.invert();	 
    }
	
  return comb;
}

void Motor::setRotationMatrix(const RotationMatrix& rotationMatrix)
{
  m_Orientation.setRotation(rotationMatrix);
}

bool Motor::getInverted() const
{
  return m_Inverted;
}

Vector3 Motor::getTransformedPosition() const
{
  Matrix4x4 finalMatrix = toMatrix4x4();
  HomogenusPosition origin = HomogenusPosition::Zero();
  Vector3 result = origin * finalMatrix;
	
  Vector3 otherResult = finalMatrix * origin;
	
  return result;
}


Orientation Motor::getOrientation() const
{
  return m_Orientation;
}

TranslationMatrix Motor::getOffsetTranslationMatrix() const
{
  return m_Offset;
}

TranslationMatrix Motor::getPivotTranslationMatrix() const
{
  return m_Pivot;
}





