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
#ifndef OTIUM_TEXTBOX_H
#define OTIUM_TEXTBOX_H

namespace Otium
{
class Textbox : public Widget
{
private:
	SrcPosition _sx;
	SrcPosition _sy;
	SrcSize     _sw;
	SrcSize     _sh;

	Text _text;

	Time _caretTime;

public:
	Textbox()
	{
		_text.SetAlignment(Widget::ALIGN_CENTER_Y);
	}

	virtual ~Textbox()
	{
	}

	/* override */
	void OnUpdate(Time deltaTime)
	{
		_caretTime += deltaTime;
		while (_caretTime > 1.0f)
			_caretTime -= 1.0f;
	}

	/* override */
	void OnTextInputEvent(const char* text)
	{
		if (Widget::GetFocus() == this)
			_text.Add(text);
	}
	
	/* override */
	void OnKeyEvent(Key key, bool down)
	{
		if (Widget::GetFocus() == this && down)
		{
			switch (key)
			{
			case KEY_BACKSPACE:
				_text.Pop();
				break;
			}
		}
	}

	/* override */
	void OnRender()
	{
		IManager::Get()->Render(GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), GetSrcX(), GetSrcY(), GetSrcWidth(), GetSrcHeight());

		_text.Render(GetAbsX() + 3, GetAbsY() + static_cast<Position>(GetHeight() / static_cast<Size>(2)));

		if (Widget::GetFocus() == this && _caretTime < 0.5f)
		{
			Font font = _text.GetFont();
			if (font)
			{
				SrcSize w;
				IManager::Get()->ReadImageSize(_text.GetImage(), &w, 0);
				Position size = static_cast<Position>(IManager::Get()->GetFontSize(font));
				Color color = OTIUM_ENCODE_COLOR(255, 255, 255, 255);
				IManager::Get()->RenderLine(GetAbsX() + 3 + static_cast<Position>(w), 
											GetAbsY() + GetHeight() / static_cast<Position>(2) - size / static_cast<Position>(2),
											GetAbsX() + 3 + static_cast<Position>(w),
											GetAbsY() + GetHeight() / static_cast<Position>(2) + size / static_cast<Position>(2),
											color);
			}
		}
	}

	inline SrcPosition GetSrcX() const { return _sx; }

	inline SrcPosition GetSrcY() const { return _sy; }

	inline SrcSize GetSrcWidth() const { return _sw; }

	inline SrcSize GetSrcHeight() const { return _sh; }

	inline Text* GetText() { return &_text; }

	inline void SetSrcX(SrcPosition sx) { _sx = sx; }

	inline void SetSrcY(SrcPosition sy) { _sy = sy; }

	inline void SetSrcWidth(SrcSize sw) { _sw = sw; }

	inline void SetSrcHeight(SrcSize sh)  { _sh = sh; }
	
	inline void SetSource(SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh) { _sx = sx; _sy = sy; _sw = sw; _sh = sh; }
};

}

#endif