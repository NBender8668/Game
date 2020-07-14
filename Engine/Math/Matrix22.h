#pragma once
#include "Vector2.h"
namespace nc
{
	struct Matrix22
	{
		float m[2][2]; // column / row
		//m[0][0] m[1][0]
		//m[0][1] m[1][1]

		Matrix22() = default;
		Matrix22(const Vector2& column1, const Vector2& column2)
		{
			m[0][0] = column1[0];
			m[0][1] = column1[1];
			m[1][0] = column2[0];
			m[1][1] = column2[1];
		}
	};
}