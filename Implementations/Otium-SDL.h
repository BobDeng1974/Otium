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
#ifndef OTIUM_FOR_SDL_H
#define OTIUM_FOR_SDL_H

namespace Otium 
{
	
/*
	Options for SDL implementation:
	#define OTIUM_SDL_SOLID_TEXT 
*/

typedef unsigned int   ID;
typedef int            Position;    /* should be signed */
typedef int            Size;
typedef int            SrcPosition; /* should be signed */
typedef int            SrcSize;
typedef TTF_Font*      Font;        /* nullable */
typedef unsigned char  FontSize;
typedef SDL_Texture*   Image;       /* nullable */
typedef SDL_Color      Color;       
typedef float          Time;        /* must be floating point */
typedef unsigned short Codepoint;
}

/* we have already defined types */
#define OTIUM_DEFINED_TYPES
#include "Otium.h"

namespace Otium
{

class ManagerSDL : public IManager
{
private:
	struct FontDesc
	{
		ID hash;
		FontSize size;

		TTF_Font* font;
	};

	SDL_Renderer* _renderer;
	SDL_Texture* _skin;
	
	SDL_Rect _dst;
	SDL_Rect _src;
	SDL_Rect _color;

	std::vector<FontDesc> _fonts;

	std::vector<SDL_Rect> _clips;

public:
	ManagerSDL(SDL_Renderer* renderer)
		: _renderer(renderer)
	{
	}

	virtual ~ManagerSDL()
	{
		for (uint32 i = 0; i < _fonts.size(); i++)
			if (_fonts[i].font)
				TTF_CloseFont(_fonts[i].font);
	}
	
	MouseButton TransformButton(uint8 button)
	{
		switch (button)
		{
			case SDL_BUTTON_LEFT: return MOUSE_BUTTON_LEFT;
			case SDL_BUTTON_MIDDLE: return MOUSE_BUTTON_MIDDLE;
			case SDL_BUTTON_RIGHT: return MOUSE_BUTTON_RIGHT;
		}
		return MOUSE_BUTTON_UNKNOWN;
	}
	
	Key TransformScancode(SDL_Scancode scancode)
	{
		switch (scancode)
		{
			case SDL_SCANCODE_RETURN: return KEY_RETURN;
			case SDL_SCANCODE_ESCAPE: return KEY_ESCAPE;
			case SDL_SCANCODE_BACKSPACE: return KEY_BACKSPACE;
			case SDL_SCANCODE_TAB: return KEY_TAB;
			case SDL_SCANCODE_SPACE: return KEY_SPACE;
			case SDL_SCANCODE_INSERT: return KEY_INSERT;
			case SDL_SCANCODE_HOME: return KEY_HOME;
			case SDL_SCANCODE_PAGEUP: return KEY_PAGEUP;
			case SDL_SCANCODE_DELETE: return KEY_DELETE;
			case SDL_SCANCODE_END: return KEY_END;
			case SDL_SCANCODE_PAGEDOWN: return KEY_PAGEDOWN;
			case SDL_SCANCODE_RIGHT: return KEY_RIGHT;
			case SDL_SCANCODE_LEFT: return KEY_LEFT;
			case SDL_SCANCODE_DOWN: return KEY_DOWN;
			case SDL_SCANCODE_UP: return KEY_UP;
		}
		return KEY_UNKNOWN;
	}
	
	/* override */
	Font GetFont(const char* name, FontSize size)
	{
		ID hash = GetStringHashCode(name);

		for (uint32 i = 0; i < _fonts.size(); i++)
			if (_fonts[i].hash == hash && _fonts[i].size == size)
				return _fonts[i].font;
	
		FontDesc font;
		font.font = TTF_OpenFont(name, static_cast<int>(size));
		if (font.font == 0)
			return 0;

		font.hash = hash;
		font.size = size;
		_fonts.push_back(font);

		return font.font;
	}

	FontSize GetFontSize(Font font)
	{
		return TTF_FontHeight(font);
	}
	
	/* override */
	void ReadImageSize(Image image, SrcSize* width, SrcSize* height)
	{
		SDL_QueryTexture(image, 0, 0, width, height);
	}

	/* override */
	void FreeImage(Image image) 
	{
		SDL_DestroyTexture(image);
	}

	/* override */
	Image Write(Font font, const char* string, Color color)
	{
#ifdef OTIUM_SDL_SOLID_TEXT 
		SDL_Surface* surface = TTF_RenderUTF8_Solid(font, string, color);
#else
		SDL_Surface* surface = TTF_RenderUTF8_Blended(font, string, color);
#endif
		if (surface)
		{
			Image image = SDL_CreateTextureFromSurface(_renderer, surface);
			SDL_FreeSurface(surface);
			return image;
		}
		return 0;
	}

	/* override */
	void Render(Position x, Position y, Size w, Size h, SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh)
	{
		_dst.x = x;
		_dst.y = y;
		_dst.w = w;
		_dst.h = h;
		
		_src.x = sx;
		_src.y = sy;
		_src.w = sw;
		_src.h = sh;
		
		SDL_RenderCopy(_renderer, _skin, &_src, &_dst);
	}

	/* override */
	void RenderImage(Image image, Position x, Position y, Size w, Size h, SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh)
	{
		_dst.x = x;
		_dst.y = y;
		_dst.w = w;
		_dst.h = h;
		
		_src.x = sx;
		_src.y = sy;
		_src.w = sw;
		_src.h = sh;
		
		SDL_RenderCopy(_renderer, image, &_src, &_dst);
	}
	
	/* override */
	void RenderLine(Position x1, Position y1, Position x2, Position y2, Color color)
	{
		SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
	}

	void PushClipRect(Position x, Position y, Size w, Size h)
	{
		SDL_Rect clip;
		SDL_RenderGetClipRect(_renderer, &clip);
		_clips.push_back(clip);

		clip = { x, y, w ,h };

		SDL_RenderSetClipRect(_renderer, &clip);
	}

	void PopClipRect()
	{
		if (_clips.size() > 0)
		{
			SDL_Rect clip = _clips.back();

			if (clip.w > 0 && clip.h > 0)
				SDL_RenderSetClipRect(_renderer, &clip);
			else
				SDL_RenderSetClipRect(_renderer, 0);

			_clips.pop_back();
		}
	}
	
	/* override */
	Color EncodeColor(uint8 r, uint8 g, uint8 b, uint8 a)
	{
		Color color;
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
		return color;
	}

	inline void SetSkin(SDL_Texture* skin) { _skin = skin; }
};

}

#endif
