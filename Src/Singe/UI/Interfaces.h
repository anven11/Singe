#ifndef __UI_INTERFACES_H__
#define __UI_INTERFACES_H__

namespace Singe
{
	namespace UI
	{
		class IScreenElement;

		typedef std::list<shared_ptr<IScreenElement>> ScreenElementList;

		//
		// Ett IScreenElement är ett objekt som är en del av användargränssnittet.
		// T.ex. knappar, textboxes eller progress bars.
		//
		class IScreenElement
		{
		public:
			virtual const HRESULT VOnRestore(void) = 0;
			virtual const HRESULT VOnLostDevice(void) = 0;

			virtual void VOnUpdate(int deltaMilliseconds) = 0;
			virtual const HRESULT VOnRender(double fTime, float fElapsedTime) = 0;

			virtual const int VGetZOrder(void) const = 0;
			virtual void VSetZOrder(int const zOrder) = 0;

			virtual const bool VIsVisible(void) const = 0;
			virtual void VSetVisible(bool visible) = 0;

			//virtual LRESULT CALLBACK VOnMsgProc(const ApplicationMessage& msg) = 0;

			virtual ~IScreenElement()
			{
			}

			virtual bool const operator < (const IScreenElement& other)
			{
				return VGetZOrder() < other.VGetZOrder();
			}
		};
	}
}

#endif // __UI_INTERFACES_H__