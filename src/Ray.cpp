#include "Ray.h"
#include "assert.h"

Ray::Ray()
{
	
}

Ray::Ray(const Ray& ray)
{
  Line::copy(ray);
}

Ray::Ray(const Line& line)
{
  Line::copy(line);
}

Ray& Ray::operator=(const Ray&ray)
{
  Line::copy(ray);
  return *this;
}

Ray::Ray(const Vector3& start, const Vector3& end) : Line(start, end)
{
	
}

bool Ray::intersect(const Ray& other, Vector3& intersectionPoint, double& thisT, 
		    double& otherT) const
{	
  bool result = Line::Intersect(*this, other, intersectionPoint,
				thisT, otherT);
	
  if (result == false) {
    return false;
  }
  else if(thisT < 0 || otherT < 0){
    return false;
  }
	
  return true;
}


Ray Ray::transform(const Matrix4x4& trans) const
{

  return Ray(Line::Transform(trans, *this));
}






