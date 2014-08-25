#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#include "..\Geometry\Vec3.h"

namespace Singe
{
	namespace Graphics
	{
		enum SceneNodeType
		{
			Null = 0, 
			Skybox, 
			Alpha, 
			Viewspace, 
		};

		//
		// En scene node representerar n�got som ska renderas i v�rlden. 
		//
		class SceneNode
		{
		public:
			///<summary>F�rbered rendering.</summary>
			virtual const bool VPreRender(void) = 0;

			///<summary>Slutf�r rendering.</summary>
			virtual const void VPostRender(void) = 0;

		protected:
			SceneNodeType m_type; // Nodens typ.

		private:
	
		};

		namespace SceneNodes
		{
			class CameraNode : public SceneNode
			{
			public:
				virtual const bool VPreRender(void);
				virtual const void VPostRender(void);

				///<summary>S�tt kamerans position.</summary>
				const void SetPosition(const Vec3& position)
				{
					m_position = position;
				}

				///<summary>H�mta kamerans position.</summary>
				const Vec3 GetPosition(void) const
				{
					return m_position;
				}

				///<summary>S�tt kamerans m�l.</summary>
				const void SetTarget(const Vec3& target)
				{
					m_target = target;
				}

				///<summary>H�mta kamerans m�l.</summary>
				const Vec3 GetTarget(void) const
				{
					return m_target;
				}

			private:
				Vec3 m_position, m_target;
				DirectX::XMFLOAT4X4 m_transform;
			};

			class AlphaNode : public SceneNode
			{
			public:
				virtual const bool VPreRender(void);
				virtual const void VPostRender(void);

			private:

			};
		}
	}
}

#endif // __SCENENODE_H__