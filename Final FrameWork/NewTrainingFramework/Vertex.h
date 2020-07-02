#pragma once
#include "Math.h"

struct Vertex 
{
	Vector3 pos;
	Vector4 col;
	Vector2 textcoord;
	Vector3 normal, bitangent, tangent;
};