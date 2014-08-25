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

#ifndef __VEC2_H__
#define __VEC2_H__

struct Vec2
{
	//
	// Variabler.
	//

	float x; // Höger, Vänster
	float y; // Upp, Ner

	//
	// Konstruktorer.
	//

	Vec2(void);
	Vec2(const float x, const float y);
	Vec2(const float n);

	//
	// Operatorer.
	//

	const Vec2 operator = (const float a);
	const Vec2 operator = (const Vec2& v2);
	const bool operator == (const float a) const;
	const bool operator == (const Vec2& v2) const;
	const bool operator > (const float a) const;
	const bool operator > (const Vec2& v2) const;
	const bool operator < (const float a) const;
	const bool operator < (const Vec2& v2) const;
	const Vec2 operator + (const float a) const;
	const Vec2 operator += (const float a);
	const Vec2 operator - (const float a) const;
	const Vec2 operator -= (const float a);
	const Vec2 operator * (const float a) const;
	const Vec2 operator *= (const float a);
	const Vec2 operator / (const float a) const;
	const Vec2 operator /= (const float a);
	const Vec2 operator + (const Vec2& v2) const;
	const Vec2 operator += (const Vec2& v2);
	const Vec2 operator - (const Vec2& v2) const;
	const Vec2 operator -= (const Vec2& v2);
	const Vec2 operator * (const Vec2& v2) const;
	const Vec2 operator *= (const Vec2& v2);
	const Vec2 operator / (const Vec2& v2) const;
	const Vec2 operator /= (const Vec2& v2);

	//
	// Metoder.
	//

	// Vektorns storlek.
	const float Magnitude(void) const;

	// Normalisera vektorn.
	void Normalize(void);

	// Hämta vektorn som normaliserad.
	const Vec2 Normalized(void) const;

	// Ta reda på vektorernas skalärprodukt.
	static const float Dot(const Vec2& u, const Vec2& v);

	// Ta reda på vektorns kryssprodukt.
	static const Vec2 Cross(const Vec2& u);

	// Ta reda på medelvektorn.
	static const Vec2 Mean(const std::vector<Vec2>& v2s);

	// Ta reda på medianvektorn.
	static const Vec2 Median(const std::vector<Vec2>& v2s);

	//
	// Konstanter.
	//

	static const Vec2 Up;
	static const Vec2 Right;

	static const DXGI_FORMAT VertexFormat;
};

#endif // __VEC2_H__