#include <SingeStd.h>

#include "String.h"

namespace Singe
{
	namespace Utilities
	{
		// Standardtecken: .,:;(){}[]= och mellanslag.
		const std::vector<std::string> StringHelper::TokenizeString(const std::string& string, const char* delimiters)
		{
			if (delimiters == nullptr)
				delimiters = ".,:;(){}[]= ";

			std::vector<std::string> tmp;

			std::size_t prev = 0, pos;
			while ((pos = string.find_first_of(delimiters, prev)) != std::string::npos)
			{
				if (pos > prev)
					tmp.push_back(string.substr(prev, pos - prev));

				prev = pos + 1;
			}

			if (prev < string.length())
				tmp.push_back(string.substr(prev, std::string::npos));

			return tmp;
		}

		const std::vector<std::string> StringHelper::SplitString(const std::string& string, char delimiter)
		{
			std::vector<std::string> tmp;
			std::stringstream ss(string);
			std::string item;

			while (std::getline(ss, item, delimiter))
			{
				tmp.push_back(item);
			}

			return tmp;
		}

		const std::string StringHelper::ToLower(const std::string& string)
		{
			std::string ret = string;
			std::transform(ret.cbegin(), ret.cend(), ret.begin(), ::tolower);
			return ret;
		}

		const std::wstring StringHelper::ToLower(const std::wstring& wstring)
		{
			std::wstring ret = wstring;
			std::transform(ret.cbegin(), ret.cend(), ret.begin(), ::towlower);
			return ret;
		}

		const std::string StringHelper::ToUpper(const std::string& string)
		{
			std::string ret = string;
			std::transform(ret.cbegin(), ret.cend(), ret.begin(), ::toupper);
			return ret;
		}

		const std::wstring StringHelper::ToUpper(const std::wstring& wstring)
		{
			std::wstring ret = wstring;
			std::transform(ret.cbegin(), ret.cend(), ret.begin(), ::towupper);
			return ret;
		}

		const bool StringHelper::WildcardMatch(const std::string& pattern, const std::string& string)
		{
			int i, star;
			const char* pattern_c = pattern.c_str();
			const char* string_c = string.c_str();

		new_segment:

			star = 0;
			if (*pattern_c == '*')
			{
				star = 1;
				do
				{
					pattern_c++;
				} while (*pattern_c == '*'); /* enddo */
			} /* endif */

		test_match:

			for (i = 0; pattern_c[i] && (pattern_c[i] != '*'); i++)
			{
				//if (mapCaseTable[str[i]] != mapCaseTable[pat[i]]) {
				if (string_c[i] != pattern_c[i])
				{
					if (!string_c[i]) 
						return false;

					if ((pattern_c[i] == '?') && (string_c[i] != '.')) 
						continue;

					if (!star) 
						return false;

					string_c++;
					goto test_match;
				}
			}

			if (pattern_c[i] == '*')
			{
				string_c += i;
				pattern_c += i;
				goto new_segment;
			}

			if (!string_c[i]) 
				return true;

			if (i && pattern_c[i - 1] == '*') 
				return true;

			if (!star) 
				return false;

			string_c++;
			goto test_match;
		}

		const std::string StringHelper::WideStringToString(const std::wstring& wstring)
		{
			int slength = (int)wstring.length() + 1;
			int len = WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), slength, 0, 0, 0, 0) - 1;

			std::string ret(len, '\0');
			WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), slength, &ret[0], len, 0, 0);

			return ret;
		}

		const std::wstring StringHelper::StringToWideString(const std::string& string)
		{
			int slength = (int)string.length() + 1;
			int len = MultiByteToWideChar(CP_ACP, 0, string.c_str(), slength, 0, 0) - 1;

			std::wstring ret(len, '\0');
			MultiByteToWideChar(CP_ACP, 0, string.c_str(), slength, &ret[0], len);

			return ret;
		}

		const void* StringHelper::HashName(const std::string& string)
		{
			// Relatively simple hash of arbitrary text string into a
			// 32-bit identifier Output value is
			// input-valid-deterministic, but no guarantees are made
			// about the uniqueness of the output per-input
			//
			// Input value is treated as lower-case to cut down on false
			// separations cause by human mistypes. Sure, it could be
			// construed as a programming error to mix up your cases, and
			// it cuts down on permutations, but in Real World Usage
			// making this text case-sensitive will likely just lead to
			// Pain and Suffering.
			//
			// This code lossely based upon the adler32 checksum by Mark
			// Adler and published as part of the zlib compression
			// library sources.

			// largest prime smaller than 65536
			unsigned long BASE = 65521L;

			// NMAX is the largest n such that 255n(n+1)/2 +
			// (n+1)(BASE-1) <= 2^32-1
			unsigned long NMAX = 5552;

		#define DO1(buf,i)  {s1 += tolower(buf[i]); s2 += s1;}
		#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
		#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
		#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
		#define DO16(buf)   DO8(buf,0); DO8(buf,8);

			const char* string_c = string.c_str();

			if (string.length() == 0)
				return nullptr;

			unsigned long s1 = 0;
			unsigned long s2 = 0;

			for (size_t len = string.size(); len > 0;)
			{
				unsigned long k = len < NMAX ? len : NMAX;

				len -= k;

				while (k >= 16)
				{
					DO16(string_c);
					string_c += 16;
					k -= 16;
				}

				if (k != 0) do
				{
					s1 += tolower(*string_c++);
					s2 += s1;
				} while (--k);

				s1 %= BASE;
				s2 %= BASE;
			}

		#pragma warning(push)
		#pragma warning(disable : 4312)

			return reinterpret_cast<void*>((s2 << 16) | s1);

		#pragma warning(pop)
		#undef DO1
		#undef DO2
		#undef DO4
		#undef DO8
		#undef DO16
		}
	}
}