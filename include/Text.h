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
	std::string _text;

	void* _font;

	void* _image;

	int32 _srcWidth;
	int32 _srcHeight;

	bool _needRedraw;

	uint32 _color;

public:
	Text();

	virtual ~Text();

	void Render(int32 x, int32 y);
	
	inline void SetText(const char* text) { if (strcmp(_text.c_str(), text) != 0) { _text = text; _needRedraw = true; } }
	inline void SetFont(void* font) { if (_font != font) { _font = font; _needRedraw = true; } }

	inline const char* GetText() const { return _text.c_str(); }
	inline void* GetFont() const { return _font; }
	inline int32 GetSrcWidth() const { return _srcWidth; }
	inline int32 GetSrcHeight() const { return _srcHeight; }
	inline void* GetImage() const { return _image; }

	inline void SetColor(uint32 color) { _color = color; }
	inline void SetColor(uint8 red, uint8 green, uint8 blue, uint8 alpha) { _color = OTIUM_COLOR_ENCODE_ALPHA(red, green, blue, alpha); }
};
}

#endif