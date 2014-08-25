/*

Copyright(C) 2014 Andreas Vennström

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

#include <SingeStd.h>

#include "Vec4.h"

#include "Vec3.h"

//
// Konstanter.
//
const Vec4 Vec4::Up = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
const Vec4 Vec4::Right = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
const Vec4 Vec4::Forward = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
const Vec4 Vec4::Ana = Vec4(0.0f, 0.0f, 0.0f, 1.0f);

const DXGI_FORMAT Vec4::VertexFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

// { 0, 0, 0, 0 }
Vec4::Vec4(void)
{
	Vec4(0.0f);
}

// { x, y, z, w }
Vec4::Vec4(const float x, const float y, const float z, const float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

// { n, n, n, n }
Vec4::Vec4(const float n)
{
	this->x =
		this->y =
		this->z =
		this->w = n;
}

// { v3.x, v3.y, v3.z, w }
Vec4::Vec4(const Vec3& v3, const float w)
{
	this->x = v3.x;
	this->y = v3.y;
	this->z = v3.z;
	this->w = w;
}

// { v3.x, v3.y, v3.z, 0 }
Vec4::Vec4(const Vec3& v3)
{
	(*this) = Vec4(v3, 0);
}

//
// Operatorer.
//

const Vec4 Vec4::operator = (const Vec4& v4)
{
	this->x = v4.x;
	this->y = v4.y;
	this->z = v4.z;
	this->w = v4.w;
	return (*this);
}

const bool Vec4::operator == (const Vec4& v4) const
{
	return (this->x == v4.x &&
			this->y == v4.y &&
			this->z == v4.z &&
			this->w == v4.w);
}

const bool Vec4::operator > (const Vec4& v4) const
{
	return (this->Magnitude() > v4.Magnitude());
}

const bool Vec4::operator < (const Vec4& v4) const
{
	return (this->Magnitude() < v4.Magnitude());
}

const Vec4 Vec4::operator + (const float a) const
{
	return Vec4(this->x + a, this->y + a, this->z + a, this->w + a);
}

const Vec4 Vec4::operator += (const float a)
{
	(*this) = (*this) + a;
	return (*this);
}

const Vec4 Vec4::operator - (const float a) const
{
	return Vec4(this->x - a, this->y - a, this->z - a, this->w - a);
}

const Vec4 Vec4::operator -= (const float a)
{
	(*this) = (*this) - a;
	return (*this);
}

const Vec4 Vec4::operator * (const float a) const
{
	return Vec4(this->x * a, this->y * a, this->z * a, this->w * a);
}

const Vec4 Vec4::operator *= (const float a) 
{
	(*this) = (*this) * a;
	return (*this);
}

const Vec4 Vec4::operator / (const float a) const
{
	return Vec4(this->x / a, this->y / a, this->z / a, this->w / a);
}

const Vec4 Vec4::operator /= (const float a) 
{
	(*this) = (*this) / a;
	return (*this);
}

const Vec4 Vec4::operator + (const Vec4& v4) const
{
	return Vec4(this->x + v4.x, this->y + v4.y, this->z / v4.z, this->w / v4.w);
}

const Vec4 Vec4::operator += (const Vec4& v4)
{
	(*this) = (*this) + v4;
	return (*this);
}

const Vec4 Vec4::operator - (const Vec4& v4) const
{
	return Vec4(this->x - v4.x, this->y - v4.y, this->z / v4.z, this->w / v4.w);
}

const Vec4 Vec4::operator -= (const Vec4& v4)
{
	(*this) = (*this) - v4;
	return (*this);
}

const Vec4 Vec4::operator * (const Vec4& v4) const
{
	return Vec4(this->x * v4.x, this->y * v4.y, this->z / v4.z, this->w / v4.w);
}

const Vec4 Vec4::operator *= (const Vec4& v4)
{
	(*this) = (*this) * v4;
	return (*this);
}

const Vec4 Vec4::operator / (const Vec4& v4) const
{
	return Vec4(this->x / v4.x, this->y / v4.y, this->z / v4.z, this->w / v4.w);
}

const Vec4 Vec4::operator /= (const Vec4& v4)
{
	(*this) = (*this) / v4;
	return (*this);
}

//
// Metoder.
//

// Vektorns storlek.
const float Vec4::Magnitude(void) const
{
	return sqrtf(powf(x, 2.0f) + powf(y, 2.0f) + powf(z, 2.0f) + powf(w, 2.0f));
}

const float Vec4::Magnitude(const Vec4& v4)
{
	return sqrtf(powf(v4.x, 2.0f) + powf(v4.y, 2.0f) + powf(v4.z, 2.0f) + powf(v4.w, 2.0f));
}

// Normalisera en vektor.
const Vec4 Vec4::Normalize(const Vec4& v4)
{
	const float magnitude = v4.Magnitude();
	return v4 / magnitude;
}

// Ta reda på vektorernas skalärprodukt.
const float Vec4::Dot(const Vec4& u, const Vec4& v)
{
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z) + (u.w * v.w);
}

// Ta reda på tre vektorers kryssprodukt.
// Tagen från http://steve.hollasch.net/thesis/chapter2.html.
const Vec4 Vec4::Cross(const Vec4& u, const Vec4& v, const Vec4& w)
{
	Vec4 cross;
	float a, b, c, d, e, f;

	// Calculate intermediate values.
	a = (v.x * w.y) - (v.y * w.x);
	b = (v.x * w.z) - (v.z * w.x);
	c = (v.x * w.w) - (v.w * w.x);
	d = (v.y * w.z) - (v.z * w.y);
	e = (v.y * w.w) - (v.w * w.y);
	f = (v.z * w.w) - (v.w * w.z);

	// Calculate the result-vector components.
	cross.x = (u.y * f) - (u.z * e) + (u.w * d);
	cross.y = -(u.x * f) + (u.z * c) - (u.w * b);
	cross.z = (u.x * e) - (u.y * c) + (u.w * a);
	cross.w = -(u.x * d) + (u.y * b) - (u.z * a);

	return cross;
}

// Ta reda på medelvektorn.
const Vec4 Vec4::Mean(const std::vector<Vec4>& v4s)
{
	Vec4 mean;
	for (auto it = v4s.begin(); it != v4s.end(); it++)
		mean += (*it);
	return mean / (float)v4s.size();
}

// Ta reda på medianvektorn.
const Vec4 Vec4::Median(const std::vector<Vec4>& v4s)
{
	return v4s[v4s.size() / 2];
}