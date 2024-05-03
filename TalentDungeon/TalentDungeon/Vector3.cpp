#include "Vector3.h"

namespace gameMath
{
	Vector3::Vector3(void) : _x(0), _y(0), _z(0) {}
	Vector3::Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) {}
	Vector3::Vector3(const Vector3& src)
	{
		*this = src;
	}

	Vector3::~Vector3(void) {}

	float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
	{
		return (float)((double)lhs._x * (double)rhs._x 
			+ (double)lhs._y * (double)rhs._y 
			+ (double)lhs._z * (double)rhs._z);
	}

	Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(
			  (float)((double)lhs._y * (double)rhs._z - (double)lhs._z * (double)rhs._y)
			, (float)((double)lhs._z * (double)rhs._x - (double)lhs._x * (double)rhs._z)
			, (float)((double)lhs._x * (double)rhs._y - (double)lhs._y * (double)rhs._x));
	}

	float Vector3::Angle2D(const Vector3& lhs, const Vector3& rhs)
	{
		float dot = Dot(lhs, rhs);
		float magnitude1 = lhs.Magnitude();
		float magnitude2 = rhs.Magnitude();

		if (magnitude1 == 0 || magnitude2 == 0) {
			return 0;
		}

		// 내적을 벡터 길이의 곱으로 나누어 내적의 코사인을 계산합니다.
		float cosine = dot / (magnitude1 * magnitude2);

		// 아크 코사인을 사용하여 라디안 각도를 계산하고, 이를 도 단위로 변환하여 반환합니다.
		return std::acos(cosine) * (180.0f / PI);
	}

	Vector3 Vector3::Nomalization()
	{
		float len = Magnitude();
		float x, y, z;
		if (len != 0)
		{
			x = _x / len;
			y = _y / len;
			z = _z / len;
			return Vector3(x, y, z);
		}
		return Vector3();
	}

	float Vector3::Magnitude() const
	{
		return sqrt(_x * _x + _y * _y + _z * _z);
	}

	Vector3& Vector3::operator=(const Vector3& rhs)
	{
		if (this != &rhs)
		{
			_x = rhs._x;
			_y = rhs._y;
			_z = rhs._z;
		}
		return *this;
	}

	Vector3 Vector3::operator+=(const Vector3& rhs)
	{
		_x += rhs._x;
		_y += rhs._y;
		_z += rhs._z;
		return *this;
	}
	Vector3 Vector3::operator-=(const Vector3& rhs)
	{
		_x -= rhs._x;
		_y -= rhs._y;
		_z -= rhs._z;
		return *this;
	}
	Vector3 Vector3::operator*=(const Vector3& rhs)
	{
		_x *= rhs._x;
		_y *= rhs._y;
		_z *= rhs._z;
		return *this;
	}
	Vector3 Vector3::operator/=(const Vector3& rhs)
	{
		assert(!(rhs._x == 0 || rhs._y == 0 || rhs._z == 0));
		_x /= rhs._x;
		_y /= rhs._y;
		_z /= rhs._z;
		return *this;
	}
	Vector3 Vector3::operator*=(const int rhs)
	{
		_x *= rhs;
		_y *= rhs;
		_z *= rhs;
		return *this;
	}
	Vector3 Vector3::operator/=(const int rhs)
	{
		assert(rhs != 0);
		_x /= rhs;
		_y /= rhs;
		_z /= rhs;
		return *this;
	}
	Vector3 Vector3::operator*=(const float rhs)
	{
		_x *= rhs;
		_y *= rhs;
		_z *= rhs;
		return *this;
	}
	Vector3 Vector3::operator/=(const float rhs)
	{
		assert(rhs != 0);
		_x /= rhs;
		_y /= rhs;
		_z /= rhs;
		return *this;
	}


	Vector3 Vector3::operator+(const Vector3& rhs) const
	{
		return Vector3(_x + rhs._x, _y + rhs._y, _z + rhs._z);
	}
	Vector3 Vector3::operator-(const Vector3& rhs) const
	{
		return Vector3(_x - rhs._x, _y - rhs._y, _z - rhs._z);
	}
	Vector3 Vector3::operator*(const Vector3& rhs) const
	{
		return Vector3(_x * rhs._x, _y * rhs._y, _z * rhs._z);
	}
	Vector3 Vector3::operator/(const Vector3& rhs) const
	{
		assert(!(rhs._x == 0 || rhs._y == 0 || rhs._z == 0));
		return Vector3(_x / rhs._x, _y / rhs._y, _z / rhs._z);
	}
	Vector3 Vector3::operator*(const int rhs) const
	{
		return Vector3(_x * rhs, _y * rhs, _z * rhs);
	}
	Vector3 Vector3::operator/(const int rhs) const
	{
		assert(rhs != 0);
		return Vector3(_x * rhs, _y * rhs, _z * rhs);
	}
	Vector3 Vector3::operator*(const float rhs) const
	{
		return Vector3(_x * rhs, _y * rhs, _z * rhs);
	}
	Vector3 Vector3::operator/(const float rhs) const
	{
		assert(rhs != 0);
		return  Vector3(_x * rhs, _y * rhs, _z * rhs);
	}
	bool Vector3::operator==(const Vector3& rhs) const
	{
		if (_x == rhs._x && _y == rhs._y && _z == rhs._z)
			return true;
		return false;
	}
	bool Vector3::operator!=(const Vector3& rhs) const
	{
		if (_x == rhs._x && _y == rhs._y && _z == rhs._z)
			return false;
		return true;
	}
}