#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector4.h"
#include <iostream>
using namespace std;

class Quaternion : public Vector4
{
public:
	Quaternion();
	Quaternion(const Vector4& vector);
	Quaternion(Float x, Float y, Float z, Float w);
	
	Quaternion(const Quaternion& other);
	Quaternion& operator=(const Quaternion& other);

	void identity();
	
	Quaternion invert() const;
	Quaternion operator!() const;
	
	static double Clamp(float value, float low, float high);
	
	static Quaternion Slerp(const Quaternion &v0, 
				const Quaternion &v1, double t);
	
	bool almostEqual(const Quaternion& other) const;
	
	bool isNormal(float tolerance = 0.00001) const;
	bool isValid() const;
	
	Quaternion multiply(const Quaternion& right) const;
	Quaternion operator*(const Quaternion& right) const;
	Quaternion& operator*=(const Quaternion& right);
	
	bool operator==(const Quaternion& other) const;

	static Quaternion Arbitrary();
		
	static float Dot(const Quaternion &v0, const Quaternion &v1);
	
	static Quaternion Subtraction(Quaternion const &v0, 
				      Quaternion const &v1);
	
	static Quaternion Add(Quaternion const &v0, Quaternion const &v1);
	
	static Quaternion Scale(float t, const Quaternion quat);

};

#endif //QUATERNION_H
