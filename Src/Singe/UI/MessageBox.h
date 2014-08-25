#ifndef __MESSAGEBOX_H__
#define __MESSAGEBOX_H__

#include "Interfaces.h"

namespace Singe
{
	namespace UI
	{
		class MessageBox : public IScreenElement
		{
		public:
			enum Type
			{
				Neutral, 
				Information, 
				Error, 
			};

			MessageBox(const std::string& caption, const std::string& title, Type type = Type::Neutral);

		private:

		};
	}
}

#endif // __MESSAGEBOX_H__