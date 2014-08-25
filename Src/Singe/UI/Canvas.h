#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "Interfaces.h"

namespace Singe
{
	namespace UI
	{
		class Canvas : public IScreenElement
		{
		public:
			void AddScreenElement(shared_ptr<IScreenElement> pScreenElement)
			{
				m_screenElements.push_back(pScreenElement);
			}

			bool RemoveScreenElement(shared_ptr<IScreenElement> pScreenElement)
			{
				auto find = std::find(m_screenElements.begin(), m_screenElements.end(), pScreenElement);

				if (find == m_screenElements.end())
					return false;

				m_screenElements.erase(find);

				return true;
			}

		private:
			ScreenElementList m_screenElements;
		};
	}
}

#endif // __CANVAS_H__