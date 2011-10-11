#include "RotationUtils.h"
#include <assert.h>

void RotationUtils::rotationMatrixToAngleAxis(const RotationMatrix& rotationMatrix, 
					      AngleAxis& angleAxis)
{

  float m00 = rotationMatrix.getElement(0, 0);
  float m01 = rotationMatrix.getElement(0, 1);
  float m02 = rotationMatrix.getElement(0, 2);

  float m10 = rotationMatrix.getElement(1, 0);
  float m11 = rotationMatrix.getElement(1, 1);
  float m12 = rotationMatrix.getElement(1, 2);

  float m20 = rotationMatrix.getElement(2, 0);
  float m21 = rotationMatrix.getElement(2, 1);
  float m22 = rotationMatrix.getElement(2, 2);

  double angle,x,y,z; // variables for result
  double epsilon = 0.01; // margin to allow for rounding errors
  double epsilon2 = 0.1; // margin to distinguish between 0 and 180 degrees
  // optional check that input is pure rotation, 'isRotationMatrix' is defined at:
  // http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

 
  if ((fabs(m01-m10)< epsilon)
      && (fabs(m02-m20)< epsilon)
      && (fabs(m12-m21)< epsilon)) {
    // singularity found
    // first check for identity matrix which must have +1 for all terms
    //  in leading diagonaland zero in other terms
    if ((fabs(m01+m10) < epsilon2)
	&& (fabs(m02+m20) < epsilon2)
	&& (fabs(m12+m21) < epsilon2)
	&& (fabs(m00+m11+m22-3) < epsilon2)) {
      // this singularity is identity matrix so angle = 0
      angleAxis = AngleAxis(0,1,0,0); // zero angle, arbitrary axis
      return;
    }
    // otherwise this singularity is angle = 180
    angle = M_PI;
    double xx = (m00+1)/2;
    double yy = (m11+1)/2;
    double zz = (m22+1)/2;
    double xy = (m01+m10)/4;
    double xz = (m02+m20)/4;
    double yz = (m12+m21)/4;
    if ((xx > yy) && (xx > zz)) { // m00 is the largest diagonal term
      if (xx< epsilon) {
	x = 0;
	y = 0.7071;
	z = 0.7071;
      } else {
	x = sqrt(xx);
	y = xy/x;
	z = xz/x;
      }
    } else if (yy > zz) { // m11 is the largest diagonal term
      if (yy< epsilon) {
	x = 0.7071;
	y = 0;
	z = 0.7071;
      } else {
	y = sqrt(yy);
	x = xy/y;
	z = yz/y;
      }	
    } else { // m[2][2] is the largest diagonal term so base result on this
      if (zz< epsilon) {
	x = 0.7071;
	y = 0.7071;
	z = 0;
      } else {
	z = sqrt(zz);
	x = xz/z;
	y = yz/z;
      }
    }
    angleAxis = AngleAxis(x,y,z, angle); // return 180 deg rotation
    return;
  }
  // as we have reached here there are no singularities so we can handle normally
  double s = sqrt((m21 - m12)*(m21 - m12)
		  +(m02 - m20)*(m02 - m20)
		  +(m10 - m01)*(m10 - m01)); // used to normalise
  if (fabs(s) < 0.001) s=1; 
  // prevent divide by zero, should not happen if matrix is orthogonal and should be
  // caught by singularity test above, but I've left it in just in case
  angle = acos(( m00 + m11 + m22 - 1)/2);
  x = (m21 - m12)/s;
  y = (m02 - m20)/s;
  z = (m10 - m01)/s;
  angleAxis = AngleAxis(x,y,z,angle);
}



void RotationUtils::angleAxisToRotationMatrix(const AngleAxis& angleAxis, RotationMatrix& rotationMatrix)
{
  Float angle = angleAxis.getAngle();
  Float axisX = angleAxis.getX();
  Float axisY = angleAxis.getY();
  Float axisZ = angleAxis.getZ();

  Float mag = sqrt(axisX*axisX + axisY*axisY + axisZ*axisZ);

  Float c =cos(angle);
  Float s = sin(angle);
  Float t = 1 - c;
  Float x = axisX / mag;
  Float y = axisY / mag;
  Float z = axisZ / mag;
	
  Float r00 = t*x*x + c;
  Float r01 = t*x*y - z*s;
  Float r02 = t*x*z + y*s;
	
  Float r10 = t*x*y + z*s;
  Float r11 = t*y*y + c;
  Float r12 = t*y*z - x*s;
	
  Float r20 = t*x*z - y*s;
  Float r21 = t*y*z + x*s;
  Float r22 = t*z*z + c;

  rotationMatrix.setElement(0, 0, r00);
  rotationMatrix.setElement(0, 1, r01);
  rotationMatrix.setElement(0, 2, r02);

  rotationMatrix.setElement(1, 0, r10);
  rotationMatrix.setElement(1, 1, r11);
  rotationMatrix.setElement(1, 2, r12);

  rotationMatrix.setElement(2, 0, r20);
  rotationMatrix.setElement(2, 1, r21);
  rotationMatrix.setElement(2, 2, r22);	
}

void RotationUtils::quaterionToRotationMatrix(const Quaternion& quat, 
					      RotationMatrix& rotationMatrix)
{
  float x = quat.getX();
  float y = quat.getY();
  float z = quat.getZ();
  float w = quat.getW();
	
  float sqw = w*w;
  float sqx = x*x;
  float sqy = y*y;
  float sqz = z*z;

  // invs (inverse square length) is only required if quaternion is not already normalised
  //float invs = 1 / (sqx + sqy + sqz + sqw);
  rotationMatrix.setElement(0, 0, ( sqx - sqy - sqz + sqw)); // since sqw + sqx + sqy + sqz =1/invs*invs
  rotationMatrix.setElement(1, 1, (-sqx + sqy - sqz + sqw));
  rotationMatrix.setElement(2, 2, (-sqx - sqy + sqz + sqw));
	
  float tmp1 = x*y;
  float tmp2 = z*w;
  rotationMatrix.setElement(1, 0, 2.0 * (tmp1 + tmp2));
  rotationMatrix.setElement(0, 1, 2.0 * (tmp1 - tmp2));
	
  tmp1 = x*z;
  tmp2 = y*w;
  rotationMatrix.setElement(2, 0, 2.0 * (tmp1 - tmp2));//*invs ;
  rotationMatrix.setElement(0, 2, 2.0 * (tmp1 + tmp2));
  tmp1 = y*z;
  tmp2 = x*w;
  rotationMatrix.setElement(2, 1, 2.0 * (tmp1 + tmp2));
  rotationMatrix.setElement(1, 2, 2.0 * (tmp1 - tmp2));     
}
void RotationUtils::rotationMatrixToQuaternion(const RotationMatrix& rotationMatrix,	
					       Quaternion& quat)
{
  float m00 = rotationMatrix.getElement(0, 0);
  float m01 = rotationMatrix.getElement(0, 1);
  float m02 = rotationMatrix.getElement(0, 2);

  float m10 = rotationMatrix.getElement(1, 0);
  float m11 = rotationMatrix.getElement(1, 1);
  float m12 = rotationMatrix.getElement(1, 2);

  float m20 = rotationMatrix.getElement(2, 0);
  float m21 = rotationMatrix.getElement(2, 1);
  float m22 = rotationMatrix.getElement(2, 2);

  float trace = m00 + m11 + m22; 
  // I removed + 1.0f; see discussion with Ethan
  if( trace > 0 ) {// I changed M_EPSILON to 0
    float s = 0.5f / sqrt(trace+ 1.0f);
    quat.setW(0.25f / s);

    double x = (m21 - m12) * s;
    double y = (m02 - m20) * s;
    double z = (m10 - m01) * s;
		  
    quat.setX(x);
    quat.setY(y);
    quat.setZ(z);
  } 
  else {
    if ( m00 > m11 && m00 > m22 ) 
      {
	float s = 2.0f * sqrt( 1.0f + m00 - m11 - m22);
	quat.setW((m21 - m12 ) / s);
	quat.setX(0.25f * s);
	quat.setY((m01 + m10) / s);
	quat.setZ((m02 + m20) / s);
      } 
    else if (m11 > m22) {
      float s = 2.0f * sqrt( 1.0f + m11 - m00 - m22);
      quat.setW((m02 - m20 ) / s);
      quat.setX((m01 + m10 ) / s);
      quat.setY(0.25f * s);
      quat.setZ((m12 + m21) / s);
    } 
    else {
      float s = 2.0f * sqrt( 1.0f + m22 - m00 - m11 );
      quat.setW((m10 - m01 ) / s);
      quat.setX((m02 + m20) / s);
      quat.setY((m12 + m21 ) / s);
      quat.setZ(0.25f * s);
    }
  }

  //assert(quat.isNormal());
  quat.normalize();
}

void RotationUtils::quaterionToAngleAxis(const Quaternion& quat, AngleAxis& angleAxis)
{
  RotationMatrix rotationMatrix;
	
  quaterionToRotationMatrix(quat, rotationMatrix);	
  rotationMatrixToAngleAxis(rotationMatrix, angleAxis);
}

void RotationUtils::angleAxisToQuaternion(const AngleAxis& angleAxis, Quaternion& quat)
{
  RotationMatrix rotationMatrix;
	
  angleAxisToRotationMatrix(angleAxis, rotationMatrix);	
  rotationMatrixToQuaternion(rotationMatrix, quat);
}
