#ifndef OTIUM_RENDERER_SDL_H
#define OTIUM_RENDERER_SDL_H

namespace Otium
{
class RendererSDL : public Renderer
{
private:
	SDL_Renderer* _renderer;

	SDL_Texture* _skin;

	SDL_Rect _dst;
	SDL_Rect _src;

public:
	RendererSDL(SDL_Renderer* renderer)
		: _skin(0), _renderer(renderer)
	{
	}

	virtual ~RendererSDL()
	{
	}

	void RenderImage(void* image, 
					 int32 x, int32 y, int32 width, int32 height,
					 int32 srcX, int32 srcY, int32 srcWidth, int32 srcHeight)
	{
		SDL_Texture* texture = static_cast<SDL_Texture*>(image);
		
		_dst.x = x;
		_dst.y = y;
		_dst.w = width;
		_dst.h = height;
		
		_src.x = srcX;
		_src.y = srcY;
		_src.w = srcWidth;
		_src.h = srcHeight;

		SDL_RenderCopy(_renderer, texture, &_src, &_dst);
	}

	void RenderCopy(int32 x, int32 y, int32 width, int32 height,
					int32 srcX, int32 srcY, int32 srcWidth, int32 srcHeight)
	{
		_dst.x = x;
		_dst.y = y;
		_dst.w = width;
		_dst.h = height;
		
		_src.x = srcX;
		_src.y = srcY;
		_src.w = srcWidth;
		_src.h = srcHeight;

		SDL_RenderCopy(_renderer, _skin, &_src, &_dst);
	}

	inline void SetSkin(SDL_Texture* skin) { _skin = skin; }
};
}

#endif