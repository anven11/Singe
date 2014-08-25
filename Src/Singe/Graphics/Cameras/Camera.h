#ifndef __CAMERA_H__
#define __CAMERA_H__

namespace Singe
{
	namespace Graphics
	{
		// Den här kameran är det mest simpla av kameror.
		class Camera : std::enable_shared_from_this<Camera>
		{
		public:
			static const shared_ptr<Camera> GetActiveCamera(void)
			{
				return m_pActiveCamera;
			}

			const DirectX::XMMATRIX GetTransform(void) const
			{
				return DirectX::XMLoadFloat4x4(&m_transform);
			}

		protected:
			Camera(void);
			Camera(const Camera& camera); // Implementera inte.

			DirectX::XMFLOAT4X4 m_transform;

		private:
			static shared_ptr<Camera> m_pActiveCamera;
		};
	}
}

#endif // __CAMERA_H__