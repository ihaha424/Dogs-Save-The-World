#include "Transform.h"

namespace gameMath
{
	Transform::Transform(void) : _position(0, 0, 0), _offsetPosition(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1) {}
	Transform::Transform(const Transform& src)
	{
		*this = src;
	}

	Transform::~Transform(void) {}
	Transform& Transform::operator=(const Transform& rhs)
	{
		if (this != &rhs)
		{
			this->_position = rhs._position;
			this->_rotation = rhs._rotation;
			this->_offsetPosition = rhs._offsetPosition;
			this->_scale = rhs._scale;
		}
		return *this;
	}

	void Transform::SetPosition(const float x, const float y, const float z)
	{
		_position = Vector3(x, y, z);
	}

	void Transform::SetPosition(const Vector3 &v)
	{
		_position = v;
	}

	Vector3 Transform::GetPosition()
	{
		return _position;
	}

	void Transform::SetOffsetPosition(const float x, const float y, const float z)
	{
		_offsetPosition = Vector3(x, y, z);
	}

	void Transform::SetOffsetPosition(const Vector3& v)
	{
		_offsetPosition = v;
	}

	Vector3 Transform::GetOffsetPosition()
	{
		return _offsetPosition;
	}

	void Transform::SetRotation(const float x, const float y, const float z)
	{
		_rotation = Vector3(x, y, z);
	}

	void Transform::SetRotation(const Vector3& v)
	{
		_rotation = v;
	}

	Vector3 Transform::GetRotation()
	{
		return _rotation;
	}
	Vector3 Transform::GetRotationVector()
	{
		float  x = 1;
		float  y = 0;
		float  z = 0;
		//z축 연산
		float x1 = x * cos(_rotation._z * PI / 180) - y * sin(_rotation._z * PI / 180);
		float y1 = x * sin(_rotation._z * PI / 180) - y * sin(_rotation._z * PI / 180);
		//----------------------------------
		//x축 연산
		float y2 = y1 * cos(_rotation._x * PI / 180) - z * sin(_rotation._x * PI / 180);
		float z1 = y1 * sin(_rotation._x * PI / 180) + z * cos(_rotation._x * PI / 180);
		//----------------------------------
		//y축 연산
		float x2 = z1 * sin(_rotation._y * PI / 180) + x1 * cos(_rotation._y * PI / 180);
		float z2 = z1 * cos(_rotation._y * PI / 180) - x1 * sin(_rotation._y * PI / 180);

		return Vector3(x2, y2, z2);
	}

	Vector3 Transform::GetRotationVector(Vector3 v)
	{
		float  x = v._x;
		float  y = v._y;
		float  z = v._z;
		//z축 연산
		float x1 = x * cos(_rotation._z * PI / 180) - y * sin(_rotation._z * PI / 180);
		float y1 = x * sin(_rotation._z * PI / 180) - y * sin(_rotation._z * PI / 180);
		//----------------------------------
		//x축 연산
		float y2 = y1 * cos(_rotation._x * PI / 180) - z * sin(_rotation._x * PI / 180);
		float z1 = y1 * sin(_rotation._x * PI / 180) + z * cos(_rotation._x * PI / 180);
		//----------------------------------
		//y축 연산
		float x2 = z1 * sin(_rotation._y * PI / 180) + x1 * cos(_rotation._y * PI / 180);
		float z2 = z1 * cos(_rotation._y * PI / 180) - x1 * sin(_rotation._y * PI / 180);

		return Vector3(x2, y2, z2);
	}


	void Transform::SetScale(const float x, const float y, const float z)
	{
		_scale = Vector3(x, y, z);
	}
	void Transform::SetScale(const Vector3& v)
	{
		_scale = v;
	}
	Vector3 Transform::GetScale()
	{
		return _scale;
	}
}