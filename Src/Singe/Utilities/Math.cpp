#include <SingeStd.h>

#include "Math.h"

namespace Singe
{
	// En sinustabell.
	// Tagen fr�n http://www.grc.nasa.gov/WWW/k-12/airplane/tablsin.html.
	const float Math::m_sinTable[90] = 
	{
		0.0000f, 0.0174f, 0.0349f, 0.0523f, 0.0698f, 0.0872f, 0.1045f, 0.1219f, 0.1392f, 0.1564f, 
		0.1736f, 0.1908f, 0.2079f, 0.2249f, 0.2419f, 0.2588f, 0.2756f, 0.2924f, 0.3090f, 0.3256f, 
		0.3420f, 0.3584f, 0.3746f, 0.3907f, 0.4067f, 0.4226f, 0.4384f, 0.4540f, 0.4695f, 0.4848f, 
		0.5000f, 0.5150f, 0.5299f, 0.5446f, 0.5592f, 0.5736f, 0.5878f, 0.6018f, 0.6157f, 0.6293f, 
		0.6428f, 0.6561f, 0.6691f, 0.6820f, 0.6947f, 0.7071f, 0.7193f, 0.7314f, 0.7431f, 0.7547f, 
		0.7660f, 0.7772f, 0.7880f, 0.7986f, 0.8090f, 0.8191f, 0.8290f, 0.8387f, 0.8480f, 0.8571f, 
		0.8660f, 0.8746f, 0.8829f, 0.8910f, 0.8988f, 0.9063f, 0.9135f, 0.9205f, 0.9272f, 0.9336f, 
		0.9379f, 0.9455f, 0.9511f, 0.9563f, 0.9613f, 0.9659f, 0.9703f, 0.9744f, 0.9781f, 0.9816f, 
		0.9848f, 0.9877f, 0.9903f, 0.9926f, 0.9945f, 0.9962f, 0.9976f, 0.9986f, 0.9994f, 0.9998f
	};
}