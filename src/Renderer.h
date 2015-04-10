#ifndef OTIUM_RENDERER_H
#define OTIUM_RENDERER_H

namespace Otium
{

class Renderer
{
private:

public:
	Renderer()
	{
	}

	virtual ~Renderer()
	{
	}

	virtual void RenderImage(void* image, 
							 int32 x, int32 y, int32 width, int32 height,
							 int32 srcX, int32 srcY, int32 srcWidth, int32 srcHeight) = 0;

	virtual void RenderCopy(int32 x, int32 y, int32 width, int32 height,
							int32 srcX, int32 srcY, int32 srcWidth, int32 srcHeight) = 0;
};

}

#ifdef _SDL_H
#include "RendererSDL.h"
namespace Otium { typedef RendererSDL DefaultRenderer; }
#else
namespace Otium { typedef Renderer DefaultRenderer; }
#endif

#endif