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
#ifndef OTIUM_TEXT_H
#define OTIUM_TEXT_H

namespace Otium
{

class Text
{
private:
	Font _font;

	std::string _string;

	Image _image;

	Color _color;

	bool _needUpdate;

	uint8 _align;

	Position _ox;
	Position _oy;

public:
	Text()
		: _needUpdate(false), _image(0), _font(0), _align(Widget::ALIGN_LEFT | Widget::ALIGN_TOP), _ox(static_cast<Position>(0)), _oy(static_cast<Position>(0))
	{

	}

	virtual ~Text()
	{

	}

	void Render(Position x, Position y)
	{
		if (_needUpdate)
		{
			if (_image)
			{
				IManager::Get()->FreeImage(_image);
				_image = 0;
			}

			if (_font)
			{
				_image = IManager::Get()->Write(_font, _string.c_str(), _color); 
			}
			
			if (_image)
			{
				SrcSize w, h;
				IManager::Get()->ReadImageSize(_image, &w, &h);
			
				_ox = _oy = 0;
				if ((_align & (Widget::ALIGN_RIGHT | Widget::ALIGN_LEFT)) == (Widget::ALIGN_RIGHT | Widget::ALIGN_LEFT))
					_ox -= static_cast<Position>(w / static_cast<Size>(2));
				else if ((_align & Widget::ALIGN_RIGHT) != 0)
					_ox -= static_cast<Position>(w);

				if ((_align & (Widget::ALIGN_BOTTOM | Widget::ALIGN_TOP)) == (Widget::ALIGN_BOTTOM | Widget::ALIGN_TOP))
					_oy -= static_cast<Position>(h / static_cast<Size>(2));
				else if ((_align & Widget::ALIGN_BOTTOM) != 0)
					_oy -= static_cast<Position>(h);
			}

			_needUpdate = false;
		}

		if (_image)
		{
			SrcSize w, h;
			IManager::Get()->ReadImageSize(_image, &w, &h);

			IManager::Get()->RenderImage(_image, x + _ox, y + _oy, static_cast<Size>(w), static_cast<Size>(h), static_cast<SrcPosition>(0), static_cast<SrcPosition>(0), w, h);
		}
	}

	void Pop()
	{
		if (!_string.empty())
		{	
			while ((_string.back() & 0xC0) == 0x80) 
				_string.pop_back();

			_string.pop_back();

			_needUpdate = true;
		}
	}

	inline const char* GetString() const { return _string.c_str(); }

	inline uint8 GetAlignment() const { return _align; }

	inline Font GetFont() const { return _font; }

	inline Image GetImage() const { return _image; }

	inline void SetColor(Color color) { _color = color; }

	inline void SetFont(const char* name, FontSize size) { _font = IManager::Get()->GetFont(name, size); }

	inline void SetString(const char* string) { _string = string; _needUpdate = true; }

	inline void SetAlignment(uint8 align) { _align = align; }

	inline void Add(const char* text) { _string += text; _needUpdate = true; }
};

}

#endif