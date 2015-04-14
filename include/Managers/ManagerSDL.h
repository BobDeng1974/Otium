/*
Copyright 2015 Mariusz Dzikowski

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef OTIUM_MANAGER_SDL_H
#define OTIUM_MANAGER_SDL_H

namespace Otium
{
class ManagerSDL : public IManager
{
private:
	SDL_Renderer* _renderer;

	SDL_Texture* _skin;

	SDL_Rect _dst;
	SDL_Rect _src;

public:
	ManagerSDL(SDL_Renderer* renderer)
		: _skin(0), _renderer(renderer)
	{
	}

	virtual ~ManagerSDL()
	{
	}
	
	void* RenderFont(void* font, const char* text, uint32 wrapLength, uint32 color, int32* srcWidth, int32* srcHeight)
	{
		TTF_Font* f = static_cast<TTF_Font*>(font);

		SDL_Color c;
		OTIUM_COLOR_DECODE_ALPHA(color, c.r, c.g, c.b, c.a);
		SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(f, text, c, wrapLength);
		if (surface)
		{
			SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
			SDL_FreeSurface(surface);
			if (texture)
			{
				SDL_QueryTexture(texture, 0, 0, srcWidth, srcHeight);
				return texture;
			}
			return 0;
		}

		return 0;
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

	void RenderLine(int32 x1, int32 y1, int32 x2, int32 y2)
	{
		SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
	}

	virtual void FreeImage(void* image)
	{
		SDL_DestroyTexture(static_cast<SDL_Texture*>(image));
	}

	inline void SetSkin(SDL_Texture* skin) { _skin = skin; }
};
}


#endif