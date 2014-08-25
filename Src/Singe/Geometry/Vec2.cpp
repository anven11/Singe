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

#include "Vec2.h"

//
// Konstanter.
//

const Vec2 Vec2::Up = Vec2(0.0f, 1.0f);
const Vec2 Vec2::Right = Vec2(1.0f, 0.0f);

const DXGI_FORMAT Vec2::VertexFormat = DXGI_FORMAT_R32G32_FLOAT;

//
// Konstruktorer.
//

Vec2::Vec2(void)
{
	(*this) = Vec2(0.0f);
}

Vec2::Vec2(const float x, const float y)
{
	this->x = x;
	this->y = y;
}

Vec2::Vec2(const float n)
{
	this->x =
	this->y = n;
}

//
// Operatorer.
//

const Vec2 Vec2::operator = (const float a)
{
	(*this) = Vec2(a);
	return (*this);
}

const Vec2 Vec2::operator = (const Vec2& v2)
{
	this->x = v2.x;
	this->y = v2.y;
	return (*this);
}

const bool Vec2::operator == (const float a) const
{
	return (this->Magnitude() == a);
}

const bool Vec2::operator == (const Vec2& v2) const
{
	return (this->x == v2.x &&
			this->y == v2.y);
}

const bool Vec2::operator > (const float a) const
{
	return (this->Magnitude() > a);
}

const bool Vec2::operator > (const Vec2& v2) const
{
	return (this->Magnitude() > v2.Magnitude());
}

const bool Vec2::operator < (const float a) const
{
	return (this->Magnitude() < a);
}

const bool Vec2::operator < (const Vec2& v2) const
{
	return (this->Magnitude() < v2.Magnitude());
}

const Vec2 Vec2::operator + (const float a) const
{
	return Vec2(this->x + a, this->y + a);
}

const Vec2 Vec2::operator += (const float a)
{
	(*this) = (*this) + a;
	return (*this);
}

const Vec2 Vec2::operator - (const float a) const
{
	return Vec2(this->x - a, this->y - a);
}

const Vec2 Vec2::operator -= (const float a)
{
	(*this) = (*this) - a;
	return (*this);
}

const Vec2 Vec2::operator * (const float a) const
{
	return Vec2(this->x * a, this->y * a);
}

const Vec2 Vec2::operator *= (const float a)
{
	(*this) = (*this) * a;
	return (*this);
}

const Vec2 Vec2::operator / (const float a) const
{
	return Vec2(this->x / a, this->y / a);
}

const Vec2 Vec2::operator /= (const float a)
{
	(*this) = (*this) / a;
	return (*this);
}

const Vec2 Vec2::operator + (const Vec2& v2) const
{
	return Vec2(this->x + v2.x, this->y + v2.y);
}

const Vec2 Vec2::operator += (const Vec2& v2)
{
	(*this) = (*this) + v2;
	return (*this);
}

const Vec2 Vec2::operator - (const Vec2& v2) const
{
	return Vec2(this->x - v2.x, this->y - v2.y);
}

const Vec2 Vec2::operator -= (const Vec2& v2)
{
	(*this) = (*this) - v2;
	return (*this);
}

const Vec2 Vec2::operator * (const Vec2& v2) const
{
	return Vec2(this->x * v2.x, this->y * v2.y);
}

const Vec2 Vec2::operator *= (const Vec2& v2)
{
	(*this) = (*this) * v2;
	return (*this);
}

const Vec2 Vec2::operator / (const Vec2& v2) const
{
	return Vec2(this->x / v2.x, this->y / v2.y);
}

const Vec2 Vec2::operator /= (const Vec2& v2)
{
	(*this) = (*this) / v2;
	return (*this);
}

//
// Metoder.
//

// Vektorns storlek.
const float Vec2::Magnitude(void) const
{
	return sqrtf(powf(x, 2.0f) + powf(y, 2.0f));
}

// Normalisera vektorn.
void Vec2::Normalize(void)
{
	const float magnitude = this->Magnitude();
	(*this) /= magnitude;
}

// Hämta vektorn som normaliserad.
const Vec2 Vec2::Normalized(void) const
{
	const float magnitude = this->Magnitude();
	return Vec2(x, y) / magnitude;
}

// Ta reda på vektorernas skalärprodukt.
const float Vec2::Dot(const Vec2& u, const Vec2& v)
{
	return (u.x * v.x) + (u.y * v.y);
}

// Ta reda på vektorns kryssprodukt.
const Vec2 Vec2::Cross(const Vec2& u)
{
	return Vec2(-u.y, u.x);
}

// Ta reda på medelvektorn.
const Vec2 Vec2::Mean(const std::vector<Vec2>& v2s)
{
	Vec2 mean;
	for (auto it = v2s.begin(); it != v2s.end(); it++)
		mean += (*it);
	return mean / (float)v2s.size();
}

// Ta reda på medianvektorn.
const Vec2 Vec2::Median(const std::vector<Vec2>& v2s)
{
	return v2s[v2s.size() / 2];
}