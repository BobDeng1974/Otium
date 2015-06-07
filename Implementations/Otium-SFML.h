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
#ifndef OTIUM_FOR_SFML_H
#define OTIUM_FOR_SFML_H

namespace Otium 
{

typedef unsigned int     ID;
typedef float            Position;    /* should be signed */
typedef float            Size;
typedef int              SrcPosition; /* should be signed */
typedef int              SrcSize;
typedef unsigned char    FontSize;
typedef struct FontDesc
{
	ID hash;
	FontSize size;

	sf::Font font;
}                       *Font;        /* nullable */
typedef sf::Texture*     Image;       /* nullable */
typedef sf::Color        Color;       
typedef float            Time;        /* must be floating point */
typedef unsigned int     Codepoint;
}

/* we have already defined types */
#define OTIUM_DEFINED_TYPES

#define OTIUM_NO_STATIC_TEXT
#include "Otium.h"

namespace Otium
{

class ManagerSFML : public IManager
{
private:
	sf::RenderWindow* _renderer;
	sf::Texture* _skin;
	
	sf::Sprite _sprite;
	sf::Text _text;

	std::vector<FontDesc*> _fonts;

public:
	ManagerSFML(sf::RenderWindow* renderer)
		: _renderer(renderer)
	{
	}

	virtual ~ManagerSFML()
	{
		for (uint32 i = 0; i < _fonts.size(); i++)
			if (_fonts[i])
				delete _fonts[i];
	}
	
	MouseButton TransformButton(sf::Mouse::Button button)
	{
		switch (button)
		{
			case sf::Mouse::Left: return MOUSE_BUTTON_LEFT;
			case sf::Mouse::Middle: return MOUSE_BUTTON_MIDDLE;
			case sf::Mouse::Right: return MOUSE_BUTTON_RIGHT;
		}
		return MOUSE_BUTTON_UNKNOWN;
	}
	
	Key TransformScancode(sf::Keyboard::Key scancode)
	{
		switch (scancode)
		{
			case sf::Keyboard::Return: return KEY_RETURN;
			case sf::Keyboard::Escape: return KEY_ESCAPE;
			case sf::Keyboard::BackSpace: return KEY_BACKSPACE;
			case sf::Keyboard::Tab: return KEY_TAB;
			case sf::Keyboard::Space: return KEY_SPACE;
			case sf::Keyboard::Insert: return KEY_INSERT;
			case sf::Keyboard::Home: return KEY_HOME;
			case sf::Keyboard::PageUp: return KEY_PAGEUP;
			case sf::Keyboard::Delete: return KEY_DELETE;
			case sf::Keyboard::End: return KEY_END;
			case sf::Keyboard::PageDown: return KEY_PAGEDOWN;
			case sf::Keyboard::Right: return KEY_RIGHT;
			case sf::Keyboard::Left: return KEY_LEFT;
			case sf::Keyboard::Down: return KEY_DOWN;
			case sf::Keyboard::Up: return KEY_UP;
		}
		return KEY_UNKNOWN;
	}

	/* override */
	Font GetFont(const char* name, FontSize size)
	{
		ID hash = GetStringHashCode(name);

		for (uint32 i = 0; i < _fonts.size(); i++)
			if (_fonts[i]->hash == hash && _fonts[i]->size == size)
				return _fonts[i];
	
		FontDesc* font = new FontDesc();
		if (!font->font.loadFromFile(name))
		{
			delete font;
			return 0;
		}

		font->hash = hash;
		font->size = size;
		_fonts.push_back(font);

		return font;
	}

	FontSize GetFontSize(Font font)
	{
		return static_cast<FontSize>(font->font.getLineSpacing(font->size));
	}
	
	/* override */
	void MeasureText(Font font, const Codepoint* string, SrcSize* width, SrcSize* height) 
	{
		if (width || height)
		{
			SrcSize w = 0;
			if (height) *height = GetFontSize(font);
			if (width) *width = 0;
			uint32 lastChar = 0;
			for (uint32 i = 0; string[i]; i++)
			{
				w += (SrcSize)font->font.getKerning(lastChar, string[i], font->size);
				lastChar = string[i];

				sf::Glyph glyph = font->font.getGlyph(string[i], font->size, false);
				
				if (height && lastChar == '\n')
					*height += GetFontSize(font);
			
				w += (SrcSize)glyph.advance;

				if (lastChar == '\n')
					w = 0;

				if (width && w > *width)
					*width = w;
			}
		}
	}
	
	/* override */
	void GetGlyphAdvance(Font font, Codepoint codepoint, Size* advance)
	{
		*advance = font->font.getGlyph(codepoint, font->size, false).advance;
	}
	
	/* override */
	void GetGlyphKerning(Font font, Codepoint first, Codepoint second, Size* kerning)
	{
		*kerning = font->font.getKerning(first, second, font->size);
	}

	/* override */
	void ReadImageSize(Image image, SrcSize* width, SrcSize* height)
	{
		sf::Vector2u size = image->getSize();

		if (width) *width = static_cast<SrcSize>(size.x);
		if (height) *height = static_cast<SrcSize>(size.y);
	}

	/* override */
	void FreeImage(Image image) 
	{
		delete image;
	}

	sf::String fromUtf8(const std::string &in)
	{
		std::basic_string<sf::Uint32> tmp;
		sf::Utf8::toUtf32(in.begin(), in.end(), back_inserter(tmp));
		return sf::String(tmp);
	}

	/* override */
	void RenderText(Font font, const Codepoint* string, Position x, Position y, Color color)
	{
		_text.setFont(font->font);
		_text.setString(string);
		_text.setColor(color);
		_text.setCharacterSize((unsigned int)font->size);
		_text.setPosition(std::floor(x), std::floor(y));
		
		_renderer->draw(_text);
	}

	/* override */
	void Render(Position x, Position y, Size w, Size h, SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh)
	{
		_sprite.setPosition(std::floor(x), std::floor(y));
		_sprite.setTexture(*_skin);
		_sprite.setTextureRect(sf::IntRect(sx, sy, sw, sh));
		_sprite.setScale(w / static_cast<Size>(sw), h / static_cast<Size>(sh));
		
		_renderer->draw(_sprite);
	}

	/* override */
	void RenderImage(Image image, Position x, Position y, Size w, Size h, SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh)
	{
		_sprite.setPosition(std::floor(x), std::floor(y));
		_sprite.setTexture(*image);
		_sprite.setTextureRect(sf::IntRect(sx, sy, sw, sh));
		_sprite.setScale(w / static_cast<Size>(sw), h / static_cast<Size>(sh));
		
		_renderer->draw(_sprite);
	}
	
	/* override */
	void RenderLine(Position x1, Position y1, Position x2, Position y2, Color color)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(x1, y1)),
			sf::Vertex(sf::Vector2f(x2, y2))
		};

		_renderer->draw(line, 2, sf::Lines);
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

	inline void SetSkin(sf::Texture* skin) { _skin = skin; }
};

}

#endif
