#ifndef __SINGESTD_H__
#define __SINGESTD_H__

// WinAPI.
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <wincodec.h>

// DXGI.
#include <dxgi.h>
#include <dxgidebug.h>

// Direct3D.
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

// Direct2D.
#include <d2d1_1.h>

// DirectWrite.
#include <dwrite_1.h>

// Storage.
#include <map>
#include <vector>
#include <array>
#include <list>

// Streams.
#include <ostream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

// Memory.
#include <atlbase.h>
#include <memory>

using std::tr1::shared_ptr;
using std::tr1::weak_ptr;
using std::tr1::static_pointer_cast;
using std::tr1::dynamic_pointer_cast;

#define NEW new
#define ASSERT assert

// Other.
#include <cmath>
#include <string>
#include <time.h>

/*

// Förhandsdeklarationer.
namespace Singe
{
	// Application.
	class Application;

	namespace Geometry
	{
		class Frustum;

		class Vec2;
		class Vec3;
		class Vec4;
	}

	namespace Graphics
	{
		// Mesh.
		class Mesh;
		struct MeshMaterial;
		struct MeshSubset;
		struct MeshVertex;

		// Texture.
		class Texture;

		// TextureRenderTarget.
		class TextureRenderTarget;

		// Shader.
		class Shader;

		// Font.
		class Font;

		// Renderer.
		class Renderer;
	}

	namespace Input
	{
		class IJoystickHandler;
		class IKeyboardHandler;
		class IPointerHandler;
	}
}

*/

#endif // __SINGESTD_H__