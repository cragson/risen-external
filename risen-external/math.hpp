#pragma once

class vec2
{
public:
	float x, y;
};

class vec3
{
public:
	vec3& operator-( const vec3& vec )
	{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;

		return *this;
	}

	float x, y, z;
};

class vec4
{
public:
	void operator-( const vec4& vec )
	{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		this->w -= vec.w;
	}

	float x, y, z, w;
};

class matrix3x3
{
public:
	vec3 a, b, c;
};

class matrix4x4
{
public:
	void operator=( const matrix4x4 mat )
	{
		this->a = mat.a;
		this->b = mat.b;
		this->c = mat.c;
		this->d = mat.d;
	}

	void multiply( const matrix4x4& mat )
	{
		vec4 _a, _b, _c, _d;

		_a.x = a.x * mat.a.x + a.y * mat.b.x + a.z * mat.c.x + a.w * mat.d.x;
		_a.y = a.x * mat.a.y + a.y * mat.b.y + a.z * mat.c.y + a.w * mat.d.y;
		_a.z = a.x * mat.a.z + a.y * mat.b.z + a.z * mat.c.z + a.w * mat.d.z;
		_a.w = a.x * mat.a.w + a.y * mat.b.w + a.z * mat.c.w + a.w * mat.d.w;

		_b.x = b.x * mat.a.x + b.y * mat.b.x + b.z * mat.c.x + b.w * mat.d.x;
		_b.y = b.x * mat.a.y + b.y * mat.b.y + b.z * mat.c.y + b.w * mat.d.y;
		_b.z = b.x * mat.a.z + b.y * mat.b.z + b.z * mat.c.z + b.w * mat.d.z;
		_b.w = b.x * mat.a.w + b.y * mat.b.w + b.z * mat.c.w + b.w * mat.d.w;

		_c.x = c.x * mat.a.x + c.y * mat.b.x + c.z * mat.c.x + c.w * mat.d.x;
		_c.y = c.x * mat.a.y + c.y * mat.b.y + c.z * mat.c.y + c.w * mat.d.y;
		_c.z = c.x * mat.a.z + c.y * mat.b.z + c.z * mat.c.z + c.w * mat.d.z;
		_c.w = c.x * mat.a.w + c.y * mat.b.w + c.z * mat.c.w + c.w * mat.d.w;

		_d.x = d.x * mat.a.x + d.y * mat.b.x + d.z * mat.c.x + d.w * mat.d.x;
		_d.y = d.x * mat.a.y + d.y * mat.b.y + d.z * mat.c.y + d.w * mat.d.y;
		_d.z = d.x * mat.a.z + d.y * mat.b.z + d.z * mat.c.z + d.w * mat.d.z;
		_d.w = d.x * mat.a.w + d.y * mat.b.w + d.z * mat.c.w + d.w * mat.d.w;

		this->a = _a;
		this->b = _b;
		this->c = _c;
		this->d = _d;
	}

	vec4 a, b, c, d;
};
