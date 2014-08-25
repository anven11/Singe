#include <SingeStd.h>

#include "SceneNode.h"

#include "Renderer.h"

namespace Singe
{
	namespace Graphics
	{
		namespace SceneNodes
		{
			// ---------------------------------------------
			//
			// CameraNode
			//
			// ---------------------------------------------
			const bool CameraNode::VPreRender(void)
			{
				const Renderer* pRenderer = Renderer::Get();

				

				return true;
			}

			const void CameraNode::VPostRender(void)
			{

			}

			// ---------------------------------------------
			//
			// AlphaNode
			//
			// ---------------------------------------------
			const bool AlphaNode::VPreRender(void)
			{


				return true;
			}

			const void AlphaNode::VPostRender(void)
			{

			}
		}
	}
}