#ifndef RAY_H
#define RAY_H

#include "Vector3.h"
#include "Line.h"

class Ray : public Line
{
public:
	Ray();
	Ray(const Ray& ray);
	Ray(const Line& line);
	Ray& operator=(const Ray&ray);       
	Ray(const Vector3& start, const Vector3& end);
		
	void copy(const Ray& ray);
		
	void eval(float t, Vector3& point) const;
	
	bool intersect(const Ray& other, Vector3& intersectionPoint, double& thisT, 
				   double& otherT) const;
	
	Ray transform(const Matrix4x4& trans) const;
	
};


#endif //RAY_H
