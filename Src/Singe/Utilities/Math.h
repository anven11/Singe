#ifndef __MATH_H__
#define __MATH_H__

namespace Singe
{
	class Math
	{
	public:
		// Billig sinus.
		inline static const float Sin(const float theta)
		{
			/*float angle = NormalizeAngle(theta);
			unsigned int iangle = (unsigned int)angle;

			if (iangle == 0)
				return 0.0f;
			else if (iangle < 90) // Första tårtbiten.
				return m_sinTable[iangle];
			else if (iangle == 90)
				return 1.0f;
			else if (iangle > 90 && iangle < 180) // Andra tårtbiten.
				return m_sinTable[90 - (iangle - 90)];
			else if (iangle == 180)
				return 0.0f;
			else if (iangle > 180 && iangle < 270) // Tredje tårtbiten.
				return -m_sinTable[iangle - 180];
			else if (iangle == 270)
				return 1.0f;
			else if (iangle > 270) // Fjärde tårtbiten.
				return -m_sinTable[90 - (iangle - 270)];
			else
				return 0.0f;*/

			return sinf(DegToRad(theta));
		}

		// Billig cosinus.
		inline static const float Cos(const float theta)
		{
			return Math::Sin(theta + 90.0f);
		}
	
		// Billig tangens.
		inline static const float Tan(const float theta)
		{
			return tanf(theta);
		}

		// Billig sekans.
		inline static const float Sec(float theta)
		{
			return 1.0f / Math::Cos(theta);
		}

		// Billig cosekans.
		inline static const float Csc(float theta)
		{
			return 1.0f / Math::Sin(theta);
		}

		// Billig cotangens.
		inline static const float Cot(float theta)
		{
			return 1.0f / Math::Tan(theta);
		}

		inline static const float RadToDeg(const float theta)
		{
			return theta * (180.0f / 3.141592f);
		}

		inline static const float DegToRad(const float theta)
		{
			return theta * (3.141592f / 180.0f);
		}

		// Normalisera en vinkel (0 - 359 grader).
		inline static const float NormalizeAngle(const float theta)
		{
			float ret = theta;
			if (ret > 360.0f)
			{
				do
				{
					ret -= 360.0f;
				} while (360.0f <= ret);
			}
			else if (ret < 0.0f)
			{
				do
				{
					ret += 360.0f;
				} while (ret < 0.0f);
			}

			return ret;
		}

		inline static const int RoundUp(const int number, const int multiple)
		{
			if (multiple == 0)
				return number;

			int remainder = abs(number) % multiple;
			if (remainder == 0)
				return number;
			if (number < 0)
				return -(abs(number) - remainder);

			return number + multiple - remainder;
		}

	private:
		~Math(void) { }

		static const float m_sinTable[90];
	};
}

#endif // __MATH_H__