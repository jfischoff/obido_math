#include "HomogenusPosition.h"

HomogenusPosition::HomogenusPosition(Float x, Float y, Float z, Float w) : 
Vector4(x, y, z, w) 
{

}

HomogenusPosition::HomogenusPosition(const Vector3& vec)
{
	setX(vec.getX());
	setY(vec.getY());
	setZ(vec.getZ());
	setW(1.0f);
};

HomogenusPosition::HomogenusPosition(const Vector4& vec)
{
	Vector4::copy(vec);
}

HomogenusPosition::HomogenusPosition()
{
}

HomogenusPosition HomogenusPosition::Zero()
{
	return HomogenusPosition(0, 0, 0, 1);
}

Vector3 HomogenusPosition::normalizeToVector3() const
{
	Vector3 result;
	
	result.setX(getX()/getW());
	result.setY(getY()/getW());
	result.setZ(getZ()/getW());
	
	return result;
}

HomogenusPosition::operator Vector3() const
{
	return normalizeToVector3();
}

