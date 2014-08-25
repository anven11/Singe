#include <SingeStd.h>

#include "Camera.h"

namespace Singe
{
	namespace Graphics
	{
		Camera::Camera(void)
		{
			DirectX::XMStoreFloat4x4(&m_transform, DirectX::XMMatrixIdentity());

			if (!m_pActiveCamera)
				m_pActiveCamera = shared_from_this();
		}
	}
}