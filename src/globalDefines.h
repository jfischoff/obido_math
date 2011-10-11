#ifndef GLOBALDEFINES_H
#define GLOBALDEFINES_H

#include <assert.h>
#include <float.h>

typedef float Float;
typedef unsigned int uint;

#ifndef NULL
#define NULL 0
#endif

typedef unsigned char UByte;

struct Float32Pos4
{
	float x;
	float y;
	float z;
	float w;
};


struct Position
{
  Position(float px, float py, float pz){x = px; y=py; z = pz;}
  float x;
  float y;
  float z;
};

struct Normal
{
  Normal(float nx, float ny, float nz){x = nx; y = ny; z = nz;}
  float x;
  float y;
  float z;
};

struct S_UV
{
  S_UV(float su, float sv){u = su; v = sv;}
  float u;
  float v;
};



struct Color4
{
	UByte red;
	UByte green;
	UByte blue;
	UByte alpha;
};

#endif //GLOBALDEFINES_H
