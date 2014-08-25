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

#ifndef __VEC3_H__
#define __VEC3_H__

// Förhandsdeklarationer.
struct Vec2;
struct Mat4x4;

struct Vec3
{
	//
	// Variabler.
	//

	float x; // Höger, Vänster
	float y; // Upp, Ner
	float z; // Fram, Bak

	//
	// Konstruktorer.
	//

	Vec3(void);

	Vec3(const Vec3& v3);

	Vec3(float x, float y, float z);

	Vec3(float n);

	Vec3(const Vec2& v2, const float z);

	Vec3(const Vec2& v2);

	//
	// Operatorer.
	//

	const Vec3 operator = (const float a);
	const Vec3 operator = (const Vec3& v3);
	const bool operator == (const Vec3& v3) const;
	const bool operator > (const Vec3& v3) const;
	const bool operator < (const Vec3& v3) const;
	const Vec3 operator + (const float a) const;
	const Vec3 operator += (const float a);
	const Vec3 operator - (const float a) const;
	const Vec3 operator -= (const float a);
	const Vec3 operator * (const float a) const;
	const Vec3 operator *= (const float a);
	const Vec3 operator / (const float a) const;
	const Vec3 operator /= (const float a);
	const Vec3 operator + (const Vec3& v3) const;
	const Vec3 operator += (const Vec3& v3);
	const Vec3 operator - (const Vec3& v3) const;
	const Vec3 operator -= (const Vec3& v3);
	const Vec3 operator * (const Vec3& v3) const;
	const Vec3 operator *= (const Vec3& v3);
	const Vec3 operator / (const Vec3& v3) const;
	const Vec3 operator /= (const Vec3& v3);
	friend std::ostream& operator << (std::ostream& out, const Vec3& v3);

	//
	// Metoder.
	//

	// Vektorns storlek.
	const float Magnitude(void) const;

	// Normalisera vektorn.
	static const Vec3 Normalize(const Vec3& v3);

	// Hämta vektorn som normaliserad.
	const Vec3& Normalized(void) const;

	// Ta reda på vektorernas skalärprodukt.
	static const float Dot(const Vec3& u, const Vec3& v);

	// Ta reda på vektorns kryssprodukt.
	static const Vec3 Cross(const Vec3& u, const Vec3& v);

	// Ta reda på medelvektorn.
	static const Vec3 Mean(const std::vector<Vec3>& v3s);

	// Ta reda på medianvektorn.
	static const Vec3 Median(const std::vector<Vec3>& v3s);

	// Transformera vektorn.
	void Transform(const Mat4x4& m4x4);

	// Transformara en vektor.
	static const Vec3 Transform(const Vec3& v3, const Mat4x4& m4x4);

	const DirectX::FXMVECTOR AsFXMVECTOR(void) const;

	//
	// Konstanter.
	//

	static const Vec3 Up;
	static const Vec3 Right;
	static const Vec3 Forward;

	static const DXGI_FORMAT VertexFormat;
};

#endif // __VEC3_H__