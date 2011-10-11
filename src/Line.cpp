#include "Line.h"
#include <assert.h>

void* Line::Constructor()
{
  return new Line();
}

Line::Line()
{
  
}

Line::Line(const Vector3& start, const Vector3& end)
{
  m_Start = start;
  m_End = end;
}

Line::Line(const Line& other)
{
  copy(other);
}
Line& Line::operator=(const Line& other)
{
  copy(other);
  return *this;
}

void Line::copy(const Line& other)
{
  m_Start = other.m_Start;
  m_End = other.m_End;
}

Line::~Line()
{
	
}

Line Line::Transform(const Matrix4x4& transform, const Line& line)
{
  
  Vector3 start = HomogenusPosition(line.GetStart()) * transform;
  Vector3 end = HomogenusPosition(line.GetEnd()) * transform;

  return Line(start, end);
}

double Line::GetXSlope() const
{  
  return (GetDirection()).getX();
}


double Line::GetXIntercept() const
{
  return m_Start.getX();
}

double Line::GetYSlope() const
{
  return (GetDirection()).getY();
}

double Line::GetYIntercept() const
{
  return m_Start.getY();
}

double Line::GetZSlope() const
{
  return (GetDirection()).getZ();
}

double Line::GetZIntercept() const
{
  return m_Start.getZ();
}

Vector3 Line::GetDirection() const
{
  return m_End - m_Start;
}

Vector3 Line::GetStart() const
{
  return m_Start;
}

Vector3 Line::GetEnd() const
{
  return m_End;
}

Vector3 Line::evaluate(double t) const
{
  Vector3 direction = GetDirection();
  Vector3 scaled = direction * t;
  return scaled + m_Start;
}

double Line::getLength()
{
  return GetDirection().mag();
}

double Line::solveForT(const Vector3& posOnLine) const
{
  //
  //just need x
  double x = posOnLine.getX();
  double t = (x - GetXIntercept()) / GetXSlope();
  return t;
}

bool Line::CramersRule(double a, double b, double c, double d, double e,
		       double f, double& x, double& y)
{
  double determinate = a*d - b*c;
	
  if(determinate == 0)
    {
      return false;
    }
	
  x = (e*d - b*f) / determinate;
  y = (a*f - e*c) / determinate;
  return true;
}

bool Line::intersect(const Line& other, Vector3& outputVec, double& leftT, 
		     double& rightT) const
{
  return Intersect(*this, other, outputVec, leftT, rightT);
}
 
bool Line::Intersect(const Line& left, const Line& right, Vector3& outputVec,
		     double& leftT, double& rightT)
{
	
  double a = left.GetXSlope();
  double b	= -1.0 * right.GetXSlope();
  double c = left.GetYSlope();
  double d = -1.0 * right.GetYSlope();
  double e = right.GetXIntercept() - left.GetXIntercept();
  double f = right.GetYIntercept() - left.GetYIntercept();
	
  bool intersected = CramersRule(a, b, c, d, e, f, leftT, rightT);
	
  if(!intersected)
    {
      return false;
    }
	
  Vector3 leftEval = left.evaluate(leftT);
  Vector3 rightEval = right.evaluate(rightT);
	
  //assert(leftEval.almostEqual(rightEval));
	
  outputVec = leftEval;
	
  return true;
	
	
}

Vector3 Line::evaluateInX(double x) const
{
  //solve in terms of x
  float t = (x - GetXIntercept()) / GetXSlope();
	
  return evaluate(t);
}

void Line::center()
{
  //find the centroid
  Vector3 centroid = (m_End + m_Start) * 0.5;
  //subtract it from the start and end
  m_Start -= centroid;
  m_End -= centroid;
}
