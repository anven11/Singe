#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

namespace Singe
{
	namespace Utilities
	{
		class FileSystem
		{
		public:

			/// <summary>Kolla om en fil existerar.</summary>
			/// <param name="filename">Filen i fråga.</param>
			static bool FileExists(const std::wstring& filename);

			/// <summary>Ta reda på en fils unika kontrollsumma.</summary>
			/// <param name="filename">Filen i fråga.</param>
			static unsigned long long FileChecksum(const std::wstring& filename);

			/// <summary>Ta reda på en fils eller en katalogs förälderkatalog.</summary>
			/// <param name="filename">Katalogen/filen i fråga.</param>
			static const std::wstring ParentDirectory(const std::wstring& path);

		private:
			~FileSystem() { }
		};
	}
}

#endif // __FILESYSTEM_H__