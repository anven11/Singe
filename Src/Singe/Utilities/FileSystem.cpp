#include <SingeStd.h>

#include "FileSystem.h"

#include "Macros.h"
#include "..\Graphics\Renderer.h"

namespace Singe
{
	namespace Utilities
	{
		bool FileSystem::FileExists(const std::wstring& filename)
		{
			DWORD attr = GetFileAttributes(filename.c_str());
			if (attr == INVALID_FILE_ATTRIBUTES)
			{
				return GetLastError() != ERROR_FILE_NOT_FOUND;
			}

			return true;
		}

		unsigned long long FileSystem::FileChecksum(const std::wstring& filename)
		{
			return 0; // lol jk
		}

		const std::wstring FileSystem::ParentDirectory(const std::wstring& path)
		{
			std::wstring ret = path;

			// Ta bort \ i slutet.
			if (*(ret.cend() - 1) == L'\\')
				ret.erase(ret.cend() - 1);

			return ret.substr(0, ret.rfind(L'\\'));
		}
	}
}