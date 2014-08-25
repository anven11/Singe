#ifndef __TARGETCAMERA_H__
#define __TARGETCAMERA_H__

#include "Camera.h"

#include "..\..\Geometry\Vec3.h"
#include "..\..\Geometry\Frustum.h"

namespace Singe
{
	namespace Graphics
	{
		// Den här kameran är det mest simpla av kameror.
		class TargetCamera : public Camera
		{
		public:
			TargetCamera(Frustum frustum, float zNear, float zFar);

			//
			// Åtkomstmetoder.
			//

			const void SetPosition(const Vec3& position)
			{
				m_position = position;
				this->_UpdateTransform();
			}

			const Vec3 GetPosition(void) const
			{
				return m_position;
			}

			const void SetTarget(const Vec3& target)
			{
				m_target = target;
				this->_UpdateTransform();
			}

			const Vec3 GetTarget(void) const
			{
				return m_target;
			}

		private:
			const void _UpdateTransform(void)
			{
				DirectX::XMStoreFloat4x4(&m_transform, DirectX::XMMatrixLookAtLH(m_position.AsFXMVECTOR(), m_target.AsFXMVECTOR(), Vec3::Up.AsFXMVECTOR()));
			}

			Vec3 m_position, m_target;
		};
	}
}

#endif // __TARGETCAMERA_H__