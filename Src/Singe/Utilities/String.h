#ifndef __STRING_H__
#define __STRING_H__

namespace Singe
{
	namespace Utilities
	{
		class StringHelper
		{
		public:
			static const std::vector<std::string> TokenizeString(const std::string& string, const char* delimiters = nullptr);
			static const std::vector<std::string> SplitString(const std::string& string, char delimiter);

			static const std::string ToLower(const std::string& string);
			static const std::wstring ToLower(const std::wstring& wstring);

			static const std::string ToUpper(const std::string& string);
			static const std::wstring ToUpper(const std::wstring& wstring);

			static const bool WildcardMatch(const std::string& pattern, const std::string& string);

			static const std::string WideStringToString(const std::wstring& wstring);
			static const std::wstring StringToWideString(const std::string& string);

			static const void* HashName(const std::string& string);
		};
	}
}

#endif // __STRING_H__