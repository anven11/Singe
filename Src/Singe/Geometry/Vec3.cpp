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

#include "Vec3.h"

#include "Vec2.h"

//
// Konstanter.
//
const Vec3 Vec3::Up = Vec3(0.0f, 1.0f, 0.0f);
const Vec3 Vec3::Right = Vec3(1.0f, 0.0f, 0.0f);
const Vec3 Vec3::Forward = Vec3(0.0f, 0.0f, 1.0f);

const DXGI_FORMAT Vec3::VertexFormat = DXGI_FORMAT_R32G32B32_FLOAT;

//
// Konstruktorer.
//

Vec3::Vec3(void)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vec3::Vec3(const Vec3& v3)
{
	this->x = v3.x;
	this->y = v3.y;
	this->z = v3.z;
}

Vec3::Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::Vec3(float n)
{
	this->x =
		this->y =
		this->z = n;
}

Vec3::Vec3(const Vec2& v2, const float z)
{
	this->x = v2.x;
	this->y = v2.y;
	this->z = z;
}

Vec3::Vec3(const Vec2& v2)
{
	this->x = v2.x;
	this->y = v2.y;
	this->z = 0.0f;
}

//
// Operatorer.
//

const Vec3 Vec3::operator = (const float a)
{
	this->x =
		this->y =
		this->z = a;
	return (*this);
}

const Vec3 Vec3::operator = (const Vec3& v3)
{
	this->x = v3.x;
	this->y = v3.y;
	this->z = v3.z;
	return (*this);
}

const bool Vec3::operator == (const Vec3& v3) const
{
	return (this->x == v3.x &&
			this->y == v3.y &&
			this->z == v3.z);
}

const bool Vec3::operator > (const Vec3& v3) const
{
	return (this->Magnitude() > v3.Magnitude());
}

const bool Vec3::operator < (const Vec3& v3) const
{
	return (this->Magnitude() < v3.Magnitude());
}

const Vec3 Vec3::operator + (const float a) const
{
	return Vec3(this->x + a, this->y + a, this->z + a);
}

const Vec3 Vec3::operator += (const float a)
{
	(*this) = (*this) + a;
	return (*this);
}

const Vec3 Vec3::operator - (const float a) const
{
	return Vec3(this->x - a, this->y - a, this->z - a);
}

const Vec3 Vec3::operator -= (const float a)
{
	(*this) = (*this) - a;
	return (*this);
}

const Vec3 Vec3::operator * (const float a) const
{
	return Vec3(this->x * a, this->y * a, this->z * a);
}

const Vec3 Vec3::operator *= (const float a)
{
	(*this) = (*this) * a;
	return (*this);
}

const Vec3 Vec3::operator / (const float a) const
{
	return Vec3(this->x / a, this->y / a, this->z / a);
}

const Vec3 Vec3::operator /= (const float a)
{
	(*this) = (*this) / a;
	return (*this);
}

const Vec3 Vec3::operator + (const Vec3& v3) const
{
	return Vec3(this->x + v3.x, this->y + v3.y, this->z / v3.z);
}

const Vec3 Vec3::operator += (const Vec3& v3)
{
	(*this) = (*this) + v3;
	return (*this);
}

const Vec3 Vec3::operator - (const Vec3& v3) const
{
	return Vec3(this->x - v3.x, this->y - v3.y, this->z / v3.z);
}

const Vec3 Vec3::operator -= (const Vec3& v3)
{
	(*this) = (*this) - v3;
	return (*this);
}

const Vec3 Vec3::operator * (const Vec3& v3) const
{
	return Vec3(this->x * v3.x, this->y * v3.y, this->z / v3.z);
}

const Vec3 Vec3::operator *= (const Vec3& v3)
{
	(*this) = (*this) * v3;
	return (*this);
}

const Vec3 Vec3::operator / (const Vec3& v3) const
{
	return Vec3(this->x / v3.x, this->y / v3.y, this->z / v3.z);
}

const Vec3 Vec3::operator /= (const Vec3& v3)
{
	(*this) = (*this) / v3;
	return (*this);
}

std::ostream& operator << (std::ostream& out, const Vec3& v3)
{
	out << std::dec << "{" << v3.x << ", " << v3.y << ", " << v3.z << "}";
	return out;
}

//
// Metoder.
//

// Vektorns storlek.
const float Vec3::Magnitude(void) const
{
	return sqrtf(powf(x, 2.0f) + powf(y, 2.0f) + powf(z, 2.0f));
}

// Normalisera vektorn.
const Vec3 Vec3::Normalize(const Vec3& v3)
{
	return v3 / v3.Magnitude();
}

// Ta reda på vektorernas skalärprodukt.
const float Vec3::Dot(const Vec3& u, const Vec3& v)
{
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

// Ta reda på vektorns kryssprodukt.
const Vec3 Vec3::Cross(const Vec3& u, const Vec3& v)
{
	return Vec3((u.y * v.z) - (u.z * v.y),
				(u.z * v.x) - (u.x * v.z),
				(u.x * v.y) - (u.y * v.x));
}

// Ta reda på medelvektorn.
const Vec3 Vec3::Mean(const std::vector<Vec3>& v3s)
{
	Vec3 mean;
	for (auto it = v3s.begin(); it != v3s.end(); it++)
		mean += (*it);
	return mean / (float)v3s.size();
}

// Ta reda på medianvektorn.
const Vec3 Vec3::Median(const std::vector<Vec3>& v3s)
{
	return v3s[v3s.size() / 2];
}

const DirectX::FXMVECTOR Vec3::AsFXMVECTOR(void) const
{
	return DirectX::XMVectorSet(this->x, this->y, this->z, 1.0f);
}