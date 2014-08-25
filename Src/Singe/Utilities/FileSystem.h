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
			/// <param name="filename">Filen i fr�ga.</param>
			static bool FileExists(const std::wstring& filename);

			/// <summary>Ta reda p� en fils unika kontrollsumma.</summary>
			/// <param name="filename">Filen i fr�ga.</param>
			static unsigned long long FileChecksum(const std::wstring& filename);

			/// <summary>Ta reda p� en fils eller en katalogs f�r�lderkatalog.</summary>
			/// <param name="filename">Katalogen/filen i fr�ga.</param>
			static const std::wstring ParentDirectory(const std::wstring& path);

		private:
			~FileSystem() { }
		};
	}
}

#endif // __FILESYSTEM_H__