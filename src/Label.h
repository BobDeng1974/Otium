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
#ifndef OTIUM_LABEL_H
#define OTIUM_LABEL_H

namespace Otium
{

class Label : public Widget
{
private:
	std::string _text;

	uint32 _font;

	void* _image;

	int32 _srcWidth;
	int32 _srcHeight;

	bool _needRedraw;

	uint32 _color;

public:
	Label()
		: _font(0), _needRedraw(false), _image(0), _color(OTIUM_COLOR_ENCODE_ALPHA(255, 255, 255, 255))
	{
	}

	virtual ~Label()
	{
	}

	void OnRender(Renderer* renderer)
	{
		if (_needRedraw)
		{
			if (_image)
				renderer->FreeImage(_image);

			_image = renderer->RenderFont(_font, _text.c_str(), 256, _color, &_srcWidth, &_srcHeight);
			_needRedraw = false;
		}

		if (_image)
			renderer->RenderImage(_image, GetAbsX(), GetAbsY(), _srcWidth, _srcHeight, 0, 0, _srcWidth, _srcHeight);
	}

	void OnRelease(Renderer* renderer)
	{
		if (_image)
		{
			renderer->FreeImage(_image);

			_image = 0;
		}
	}

	inline void SetText(const char* text) { if (strcmp(_text.c_str(), text) != 0) { _text = text; _needRedraw = true; } }
	inline void SetFont(const char* font) { OTIUM_HASH_CODE(_font, font); _needRedraw = true; }

	inline const char* GetText() const { return _text.c_str(); }
	inline uint32 GetFont() const { return _font; }

	inline void SetColor(uint32 color) { _color = color; }
	inline void SetColor(uint8 red, uint8 green, uint8 blue, uint8 alpha) { _color = OTIUM_COLOR_ENCODE_ALPHA(red, green, blue, alpha); }
};

}

#endif