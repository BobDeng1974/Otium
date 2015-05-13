#ifndef OTIUM_FOR_SDL_H
#define OTIUM_FOR_SDL_H

#define OTIUM_DEFINED_TYPES
typedef uint32       ID;
typedef int32        Position;    /* should be signed */
typedef int32        Size;
typedef int32        SrcPosition; /* should be signed */
typedef int32        SrcSize;
typedef TTF_Font*    Font;        /* nullable */
typedef uint8        FontSize;
typedef SDL_Texture* Image;       /* nullable */
typedef uint32       Color;       /* can't change it to SDL_Color */
typedef float32      Time;        /* must be floating point */

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

public:
	Manager(SDL_Renderer* renderer)
		: _renderer(renderer)
	{
	}

	virtual ~Manager()
	{
		for (uint32 i = 0; i < _fonts.size(); i++)
			if (_fonts[i].font)
				TTF_CloseFont(_fonts[i].font);
	}
	
	/* override */
	Font GetFont(const char* name, FontSize size)
	{
		ID hash;
		OTIUM_STRING_HASH_CODE(name, hash);

		for (uint32 i = 0; i < _fonts.size(); i++)
			if (_fonts[i].hash == hash && _fonts[i].size == size)
				return _fonts[i].font;
	
		Font font;
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
		SDL_Color c;
		OTIUM_DECODE_COLOR(color, c.r, c.g, c.b, c.a);
		SDL_Surface* surface = TTF_RenderUTF8_Blended(static_cast<TTF_Font*>(font), string, c);
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
		uint8 r, g, b, a;
		OTIUM_DECODE_COLOR(color, r, g, b, a);
		SDL_SetRenderDrawColor(_renderer, r, g, b, a);
		SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
	}

	inline void SetSkin(SDL_Texture* skin) { _skin = skin; }
};

}

#endif