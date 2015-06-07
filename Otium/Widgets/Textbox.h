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

#define OTIUM_TEXTBOX_OFFSET_LEFT  static_cast<Position>(3)
#define OTIUM_TEXTBOX_OFFSET_RIGHT static_cast<Position>(3)
#define OTIUM_TEXTBOX_OFFSET       (OTIUM_TEXTBOX_OFFSET_LEFT + OTIUM_TEXTBOX_OFFSET_RIGHT)

namespace Otium
{
class Textbox : public Widget
{
OTIUM_DECL_INTERNAL_ID(Textbox);
private:
	SrcPosition _sx;
	SrcPosition _sy;
	SrcSize     _sw;
	SrcSize     _sh;

	Text* _text;

	Time _caretTime;

	uint32 _caretStartIndex;
	uint32 _caretEndIndex;

	uint32 _caretIndex;
	Position _caretX;

	bool _mouseDown;

public:
	Textbox(const char* name)
		: Widget(name), _mouseDown(false), _caretIndex(0), _caretStartIndex(0), _caretEndIndex(0)
	{
		_text = new Text();
		_text->SetAlignment(ALIGN_CENTER_Y);
	}

	virtual ~Textbox()
	{
		delete _text;
	}

	void GetSelectionBounds(uint32& start, uint32& end)
	{
		start = _caretStartIndex;
		end = _caretEndIndex;

		if (start > end)
			Swap(start, end);
	}

	void UpdateCaretIndex()
	{
		IManager* manager = IManager::Get();

		const Codepoint* string = _text->GetString();

		Codepoint lastChar = 0;
		_caretX = 0;
		for (uint32 i = 0; i < _caretIndex; i++)
		{
			Size kerning, advance;
			manager->GetGlyphKerning(_text->GetFont(), lastChar, string[i], &kerning);
			lastChar = 0;

			_caretX += kerning;

			manager->GetGlyphAdvance(_text->GetFont(), string[i], &advance);

			_caretX += advance;
		}
	}

	void UpdateCaretIndex(Position x, Position y)
	{
		if (x < GetAbsX() + OTIUM_TEXTBOX_OFFSET_LEFT)
		{
			_caretIndex = 0;
			_caretX = 0;
			return;
		}

		IManager* manager = IManager::Get();

		Size sizeX = 0;
		Codepoint lastChar = 0;
		const Codepoint* it;
		Codepoint passchar = _text->GetPasswordChar();
		Size lastAdvance = 0;
		for (it = _text->GetString(); *it; it++)
		{
			Codepoint codepoint;
			if (passchar != 0)
				codepoint = passchar;
			else
				codepoint = *it;

			Size kerning;
			manager->GetGlyphKerning(_text->GetFont(), lastChar, codepoint, &kerning);
			lastChar = codepoint;

			sizeX += kerning;

			Size advance;
			manager->GetGlyphAdvance(_text->GetFont(), lastChar, &advance);

			if (x >= OTIUM_TEXTBOX_OFFSET_LEFT + GetAbsX() + sizeX - lastAdvance / 2 &&
				x < OTIUM_TEXTBOX_OFFSET_LEFT + GetAbsX() + sizeX + advance / 2)
			{
				_caretIndex = it - _text->GetString();
				_caretX = sizeX;
				return;
			}

			sizeX += advance;
			lastAdvance = advance;
		}
		_caretIndex = it - _text->GetString();
		_caretX = sizeX;
	}

	/* override */
	void OnUpdate(Time deltaTime)
	{
		_caretTime += deltaTime;
		while (_caretTime > 1.0f)
			_caretTime -= 1.0f;
	}
	
	/* override */
	void OnMouseMoveEvent(Position x, Position y)
	{
		if (_mouseDown && In(x, y))
		{
			_caretTime = 0.0f;

			UpdateCaretIndex(x, y);
		}
	}

	/* override */ 
	void OnMouseButtonEvent(Position x, Position y, MouseButton button, bool down)
	{
		if (down && button == MouseButton::MOUSE_BUTTON_LEFT && In(x, y))
		{
			_caretTime = 0.0f;

			UpdateCaretIndex(x, y);

			_caretStartIndex = _caretIndex;

			_mouseDown = true;
		}
		else
		{
			if (_mouseDown)
				_caretEndIndex = _caretIndex;

			_mouseDown = false;
		}
	}

	/* override */
	void OnTextInputEvent(Codepoint codepoint)
	{
		if (Widget::IsFocus(this))
		{
			_text->Insert(codepoint, _caretIndex);

			_caretIndex++;

			UpdateCaretIndex();

			_caretTime = 0.0f;
		}
	}
	
	/* override */
	void OnKeyEvent(Key key, bool down)
	{
		if (Widget::IsFocus(this) && down)
		{
			switch (key)
			{
			case KEY_BACKSPACE:
				if (_caretIndex > 0)
				{
					_text->Remove(--_caretIndex);
					UpdateCaretIndex();
				}
				_caretTime = 0.0f;
				break;
			}
		}
	}

	/* override */
	void OnGetFocusEvent()
	{
		_caretTime = 0.0f;
	}

	/* override */
	void OnRender()
	{
		IManager* manager = IManager::Get();

		manager->Render(GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), GetSrcX(), GetSrcY(), GetSrcWidth(), GetSrcHeight());
		
		SrcSize w = _caretX;
#ifdef OTIUM_NO_SCISSOR_TEST
		_text.Render(GetAbsX() + OTIUM_TEXTBOX_OFFSET_LEFT, GetAbsY() + static_cast<Position>(GetHeight() / static_cast<Size>(2)));
#else
		manager->PushClipRect(GetAbsX(), GetAbsY(), GetWidth(), GetHeight());

		if (w > static_cast<SrcSize>(GetWidth() - static_cast<Size>(OTIUM_TEXTBOX_OFFSET_RIGHT)))
			_text->Render(GetAbsX() + static_cast<Position>(GetWidth()) - w - OTIUM_TEXTBOX_OFFSET_RIGHT, GetAbsY() + static_cast<Position>(GetHeight() / static_cast<Size>(2)));
		else
			_text->Render(GetAbsX() + OTIUM_TEXTBOX_OFFSET_LEFT, GetAbsY() + static_cast<Position>(GetHeight() / static_cast<Size>(2)));
		
		manager->PopClipRect();
#endif

		// Caret rendering
		if (Widget::IsFocus(this) && _caretTime < 0.5f)
		{
			Font font = _text->GetFont();
			if (font)
			{
				Position size = static_cast<Position>(IManager::Get()->GetFontSize(font));
				Color color = manager->EncodeColor(255, 255, 255, 255);

#ifndef OTIUM_NO_SCISSOR_TEST
				if (w > static_cast<SrcSize>(GetWidth() - OTIUM_TEXTBOX_OFFSET_RIGHT)) 
					w = static_cast<SrcSize>(GetWidth() - OTIUM_TEXTBOX_OFFSET);
#endif

				manager->RenderLine(GetAbsX() + OTIUM_TEXTBOX_OFFSET_LEFT + w, 
									GetAbsY() + GetHeight() / static_cast<Position>(2) - size / static_cast<Position>(2),
									GetAbsX() + OTIUM_TEXTBOX_OFFSET_LEFT + w,
									GetAbsY() + GetHeight() / static_cast<Position>(2) + size / static_cast<Position>(2),
									color);
			}
		}
	}

	inline SrcPosition GetSrcX() const { return _sx; }

	inline SrcPosition GetSrcY() const { return _sy; }

	inline SrcSize GetSrcWidth() const { return _sw; }

	inline SrcSize GetSrcHeight() const { return _sh; }

	inline Text* GetText() const { return _text; }

	inline void SetSrcX(SrcPosition sx) { _sx = sx; }

	inline void SetSrcY(SrcPosition sy) { _sy = sy; }

	inline void SetSrcWidth(SrcSize sw) { _sw = sw; }

	inline void SetSrcHeight(SrcSize sh)  { _sh = sh; }
	
	inline void SetSource(SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh) { _sx = sx; _sy = sy; _sw = sw; _sh = sh; }
};

}

#undef OTIUM_TEXTBOX_OFFSET_LEFT  
#undef OTIUM_TEXTBOX_OFFSET_RIGHT 
#undef OTIUM_TEXTBOX_OFFSET     

#endif