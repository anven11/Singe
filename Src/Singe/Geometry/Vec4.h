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

#ifndef __VEC4_H__
#define __VEC4_H__

// Förhandsdeklarationer.
struct Vec3;

struct Vec4
{
	//
	// Variabler.
	//

	float x; // Höger, Vänster
	float y; // Upp, Ner
	float z; // Fram, Bak
	float w; // Ana, Kata

	//
	// Konstruktorer.
	//

	// { 0, 0, 0, 0 }
	Vec4(void);

	// { x, y, z, w }
	Vec4(const float x, const float y, const float z, const float w);

	// { n, n, n, n }
	Vec4(const float n);

	// { v3.x, v3.y, v3.z, w }
	Vec4(const Vec3& v3, const float w);

	// { v3.x, v3.y, v3.z, 1 }
	Vec4(const Vec3& v3);

	//
	// Operatorer.
	//

	const Vec4 operator = (const Vec4& v4);
	const bool operator == (const Vec4& v4) const;
	const bool operator > (const Vec4& v4) const;
	const bool operator < (const Vec4& v4) const;
	const Vec4 operator + (const float a) const;
	const Vec4 operator += (const float a);
	const Vec4 operator - (const float a) const;
	const Vec4 operator -= (const float a);
	const Vec4 operator * (const float a) const;
	const Vec4 operator *= (const float a);
	const Vec4 operator / (const float a) const;
	const Vec4 operator /= (const float a);
	const Vec4 operator + (const Vec4& v4) const;
	const Vec4 operator += (const Vec4& v4);
	const Vec4 operator - (const Vec4& v4) const;
	const Vec4 operator -= (const Vec4& v4);
	const Vec4 operator * (const Vec4& v4) const;
	const Vec4 operator *= (const Vec4& v4);
	const Vec4 operator / (const Vec4& v4) const;
	const Vec4 operator /= (const Vec4& v4);

	//
	// Metoder.
	//

	// Vektorns storlek.
	const float Magnitude(void) const;

	// Ta reda på en vektors magnitud.
	static const float Magnitude(const Vec4& v4);

	// Normalisera en vektor.
	static const Vec4 Normalize(const Vec4& v4);

	// Ta reda på vektorernas skalärprodukt.
	static const float Dot(const Vec4& u, const Vec4& v);

	// Ta reda på vektorns kryssprodukt.
	// Tagen från http://steve.hollasch.net/thesis/chapter2.html.
	static const Vec4 Cross(const Vec4& u, const Vec4& v, const Vec4& w);

	// Ta reda på medelvektorn.
	static const Vec4 Mean(const std::vector<Vec4>& v4s);

	// Ta reda på medianvektorn.
	static const Vec4 Median(const std::vector<Vec4>& v4s);

	//
	// Konstanter.
	//

	static const Vec4 Up;
	static const Vec4 Right;
	static const Vec4 Forward;
	static const Vec4 Ana;

	static const DXGI_FORMAT VertexFormat;
};

#endif // __VEC4_H__