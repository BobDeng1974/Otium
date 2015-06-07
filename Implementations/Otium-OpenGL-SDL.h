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
#ifndef OTIUM_FOR_OPENGL_WITH_SDL_H
#define OTIUM_FOR_OPENGL_WITH_SDL_H

namespace Otium 
{
	
/*
	Options for OpenGL-SDL implementation:
	#define OTIUM_OPENGL_SDL_FLOOR       // Use it when you have glitches with Image rendering
	#define OTIUM_OPENGL_SDL_SMOOTH      // Use it to Linear texture filtering for PreRender-Text rendering
	#define OTIUM_OPENGL_SDL_SOLID_TEXT  
*/

struct OGL_Image
{
	GLuint id;
	float width;
	float height;
};

typedef unsigned int   ID;
typedef float          Position;    /* should be signed */
typedef float          Size;
typedef float          SrcPosition; /* should be signed */
typedef float          SrcSize;
typedef TTF_Font*      Font;        /* nullable */
typedef unsigned char  FontSize;
typedef OGL_Image*     Image;       /* nullable */
typedef SDL_Color      Color;       
typedef float          Time;        /* must be floating point */
typedef unsigned short Codepoint;
}

/* we have already defined types */
#define OTIUM_DEFINED_TYPES
#include "Otium.h"

namespace Otium
{

class ManagerOGLxSDL : public IManager
{
private:
	struct FontDesc
	{
		ID hash;
		FontSize size;

		TTF_Font* font;
	};

	OGL_Image* _skin;

	std::vector<FontDesc> _fonts;

public:
	ManagerOGLxSDL()
	{
	}

	virtual ~ManagerOGLxSDL()
	{
		for (uint32 i = 0; i < _fonts.size(); i++)
			if (_fonts[i].font)
				TTF_CloseFont(_fonts[i].font);

		if (_skin)
			delete _skin;
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

	/* override */
	FontSize GetFontSize(Font font)
	{
		return TTF_FontHeight(font);
	}
	
	/* override */
	void ReadImageSize(Image image, SrcSize* width, SrcSize* height)
	{
		if (width) *width = image->width;
		if (height) *height= image->height;
	}

	/* override */
	void FreeImage(Image image) 
	{
		if (image->id > 0)
			glDeleteTextures(1, &image->id);

		delete image;
	}

	/* override */
	Image Write(Font font, const Codepoint* string, Color color)
	{
#ifdef OTIUM_OPENGL_SDL_SOLID_TEXT 
		SDL_Surface* surface = TTF_RenderUNICODE_Solid(font, string, color);
#else
		SDL_Surface* surface = TTF_RenderUNICODE_Blended(font, string, color);
#endif
		if (surface)
		{
			if (surface->format->BytesPerPixel < 4)
			{
				SDL_Surface* temp = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
				SDL_FreeSurface(surface);
				surface = temp;
			}
			OGL_Image* image = new OGL_Image();

			image->width = static_cast<float32>(surface->w);
			image->height = static_cast<float32>(surface->h);

			glGenTextures(1, &image->id);
			glBindTexture(GL_TEXTURE_2D, image->id);

#if defined(OTIUM_OPENGL_SDL_SMOOTH) && !defined(OTIUM_OPENGL_SDL_FLOOR)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#else 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
#endif

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(surface->w), static_cast<GLsizei>(surface->h), 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

			glBindTexture(GL_TEXTURE_2D, 0);
			SDL_FreeSurface(surface);
			return image;
		}
		return 0;
	}
	
	/* override */
	void GetGlyphAdvance(Font font, Codepoint codepoint, Size* advance)
	{
		int a;
		TTF_GlyphMetrics(font, codepoint, 0, 0, 0, 0, &a);
		*advance = static_cast<Size>(a);
	}
	
	/* override */
	void GetGlyphKerning(Font font, Codepoint first, Codepoint second, Size* kerning)
	{
		*kerning = static_cast<Size>(TTF_GetFontKerningSize(font, first, second));
	}

	/* override */
	void Render(Position x, Position y, Size w, Size h, SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh)
	{
		RenderImage(_skin, x, y, w, h, sx, sy, sw, sh);
	}

	/* override */
	void RenderImage(Image image, Position x, Position y, Size w, Size h, SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh)
	{
		glEnable(GL_TEXTURE_2D);

#ifdef OTIUM_OPENGL_SDL_FLOOR
		x = std::floor(x);
		y = std::floor(y);
		w = std::floor(w);
		h = std::floor(h);
#endif

		w += x;
		h += y;

		sx /= image->width;
		sy /= image->height;

		sw /= image->width;
		sh /= image->height;

		sw += sx;
		sh += sy;

		glBindTexture(GL_TEXTURE_2D, image->id);

		glBegin(GL_QUADS);

		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(sx, sy); glVertex2f(x, y);
		glTexCoord2f(sx, sh); glVertex2f(x, h);
		glTexCoord2f(sw, sh); glVertex2f(w, h);
		glTexCoord2f(sw, sy); glVertex2f(w, y);

		glEnd();

		glDisable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	/* override */
	void RenderLine(Position x1, Position y1, Position x2, Position y2, Color color)
	{
		glBegin(GL_LINES);

		glColor4ub(color.r, color.g, color.b, color.a);
	
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);

		glEnd();
	}
	
	/* override */
	void PushClipRect(Position x, Position y, Size w, Size h)
	{
		glPushAttrib(GL_SCISSOR_BIT);
		GLint v[4];
		glGetIntegerv(GL_VIEWPORT, v);
		glEnable(GL_SCISSOR_TEST);
		glScissor(static_cast<GLint>(x), static_cast<GLint>(v[3]) - static_cast<GLint>(y) - static_cast<GLint>(h), static_cast<GLint>(w), static_cast<GLsizei>(h));
	}
	
	/* override */
	void PopClipRect()
	{
		glPopAttrib();
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

	inline void SetSkin(GLuint tex, float32 width, float32 height) 
	{ 
		if (_skin)
			FreeImage(_skin);

		_skin = new OGL_Image();
		_skin->id = tex;
		_skin->width = width;
		_skin->height = height;
	}
};

}

#endif
