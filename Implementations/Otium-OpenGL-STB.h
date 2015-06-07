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
#ifndef OTIUM_FOR_OPENGL_WITH_STB_H
#define OTIUM_FOR_OPENGL_WITH_STB_H

/*
	Define STB_IMAGE_IMPLEMENTATION and STB_TRUETYPE_IMPLEMENTATION on source file where you want STB implemenations,
	before 'Otium-OpenGL-STB' header or included STB files.
*/
#include "STB/stb_image.h"
#include "STB/stb_truetype.h"

namespace Otium 
{

struct STB_Font
{
	stbtt_fontinfo font;
	unsigned char* buffer;
};

struct OGL_Image
{
	GLuint id;
	float width;
	float height;
};

typedef unsigned int  ID;
typedef float         Position;    /* should be signed */
typedef float         Size;
typedef float         SrcPosition; /* should be signed */
typedef float         SrcSize;
typedef STB_Font*     Font;        /* nullable */
typedef unsigned char FontSize;
typedef OGL_Image*    Image;       /* nullable */
typedef unsigned int  Color;       
typedef float         Time;        /* must be floating point */
typedef unsigned int  Codepoint;
}

/* we have already defined types */
#define OTIUM_DEFINED_TYPES
#include "Otium.h"


namespace Otium
{

class ManagerOGLxSTB : public IManager
{
private:
	struct FontDesc
	{
		ID hash;
		FontSize size;

		STB_Font* font;
	};

	OGL_Image* _skin;

	std::vector<FontDesc> _fonts;

public:
	ManagerOGLxSTB()
		: _skin(0)
	{
	}

	virtual ~ManagerOGLxSTB()
	{
		for (uint32 i = 0; i < _fonts.size(); i++)
			if (_fonts[i].font)
				delete _fonts[i].font;

		if (_skin)
			FreeImage(_skin);
	}

#ifdef _glfw3_h_
	MouseButton TransformButton(int32 button)
	{
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_LEFT: return MOUSE_BUTTON_LEFT;
			case GLFW_MOUSE_BUTTON_MIDDLE: return MOUSE_BUTTON_MIDDLE;
			case GLFW_MOUSE_BUTTON_RIGHT: return MOUSE_BUTTON_RIGHT;
		}
		return MOUSE_BUTTON_UNKNOWN;
	}
	
	Key TransformScancode(int32 scancode)
	{
		switch (scancode)
		{
			case GLFW_KEY_ENTER: return KEY_RETURN;
			case GLFW_KEY_ESCAPE: return KEY_ESCAPE;
			case GLFW_KEY_BACKSPACE: return KEY_BACKSPACE;
			case GLFW_KEY_TAB: return KEY_TAB;
			case GLFW_KEY_SPACE: return KEY_SPACE;
			case GLFW_KEY_INSERT: return KEY_INSERT;
			case GLFW_KEY_HOME: return KEY_HOME;
			case GLFW_KEY_PAGE_UP: return KEY_PAGEUP;
			case GLFW_KEY_DELETE: return KEY_DELETE;
			case GLFW_KEY_END: return KEY_END;
			case GLFW_KEY_PAGE_DOWN: return KEY_PAGEDOWN;
			case GLFW_KEY_RIGHT: return KEY_RIGHT;
			case GLFW_KEY_LEFT: return KEY_LEFT;
			case GLFW_KEY_DOWN: return KEY_DOWN;
			case GLFW_KEY_UP: return KEY_UP;
		}
		return KEY_UNKNOWN;
	}
#endif
	
	STB_Font* LoadFont(const char* name)
	{
		return 0;
	}

	/* override */
	Font GetFont(const char* name, FontSize size)
	{
		ID hash = GetStringHashCode(name);

		for (uint32 i = 0; i < _fonts.size(); i++)
			if (_fonts[i].hash == hash && _fonts[i].size == size)
				return _fonts[i].font;
	
		FontDesc font;
		FILE* file = fopen(name, "rb");
		if (!file)
			return 0;
		font.font = new STB_Font();

		fseek(file, 0, SEEK_END);
		uint32 fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		font.font->buffer = new unsigned char[fileSize];
		fread(font.font->buffer, 1, fileSize, file);
		fclose(file);

		if (!stbtt_InitFont(&font.font->font, font.font->buffer, stbtt_GetFontOffsetForIndex(font.font->buffer, 0)))
		{
			delete[] font.font->buffer;
			delete font.font;
			return 0;
		}

		font.hash = hash;
		font.size = size;
		_fonts.push_back(font);

		return font.font;
	}

	FontSize GetFontSize(Font font)
	{
		return 0; //TTF_FontHeight(font);
	}
	
	/* override */
	void ReadImageSize(Image image, SrcSize* width, SrcSize* height)
	{
		if (width) *width = image->width;
		if (height) *height = image->height;
	}

	/* override */
	void FreeImage(Image image) 
	{
		if (image->id > 0)
			glDeleteTextures(1, &image->id);

		delete image;
	}

	/* override */
	Image Write(Font font, const char* string, Color color)
	{
		return 0;
	}

	/* override */
	void Render(Position x, Position y, Size w, Size h, SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh)
	{
		glEnable(GL_TEXTURE_2D);

		w += x;
		h += y;

		sx /= _skin->width;
		sy /= _skin->height;

		sw /= _skin->width;
		sh /= _skin->height;

		sw += sx;
		sh += sy;

		glBindTexture(GL_TEXTURE_2D, _skin->id);

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
	void RenderImage(Image image, Position x, Position y, Size w, Size h, SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh)
	{
		glEnable(GL_TEXTURE_2D);

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

		glColor4ub(color & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF, (color >> 24) & 0xFF);
	
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);

		glEnd();
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