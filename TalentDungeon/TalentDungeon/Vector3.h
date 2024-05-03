#pragma once

#include <cmath>
#include <cassert>

namespace gameMath
{
#define PI 3.1415926535f
	class Vector3
	{
	public:
		float _x;
		float _y;
		float _z;

	public:
		Vector3(void);
		Vector3(float x, float y = 0, float z = 0);
		Vector3(const Vector3& src);

		~Vector3(void);

		static float Dot(const Vector3 &lhs, const Vector3 &rhs);
		static Vector3 Cross(const Vector3 &lhs, const Vector3 &rhs);
		static float Angle2D(const Vector3 &lhs, const Vector3 &rhs);

		Vector3 Nomalization();
		float Magnitude() const;

		bool operator == (const Vector3& rhs) const;
		bool operator != (const Vector3& rhs) const;

		Vector3& operator=(const Vector3& rhs);
		Vector3 operator += (const Vector3& rhs);
		Vector3 operator -= (const Vector3& rhs);
		Vector3 operator *= (const Vector3& rhs);
		Vector3 operator /= (const Vector3& rhs);
		Vector3 operator *= (const int rhs);
		Vector3 operator /= (const int rhs);
		Vector3 operator *= (const float rhs);
		Vector3 operator /= (const float rhs);

		Vector3 operator + (const Vector3& rhs) const;
		Vector3 operator - (const Vector3& rhs) const;
		Vector3 operator * (const Vector3& rhs) const;
		Vector3 operator / (const Vector3& rhs) const;
		Vector3 operator * (const int rhs) const;
		Vector3 operator / (const int rhs) const;
		Vector3 operator * (const float rhs) const;
		Vector3 operator / (const float rhs) const;
	};
}