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
#ifndef OTIUM_WINDOW_H
#define OTIUM_WINDOW_H

namespace Otium
{
class Window : public Widget
{
OTIUM_DECL_INTERNAL_ID(Window);

private:
	Position _hx;
	Position _hy;
	bool _hook;

	SrcPosition _sx;
	SrcPosition _sy;
	SrcSize     _sw;
	SrcSize     _sh;

	Text _text;

	Position _border;

public:
	Window(const char* name)
		: Widget(name), _border(0), _hook(false)
	{
		_text.SetAlignment(ALIGN_CENTER_X);
	}

	virtual ~Window()
	{
	}
	/* override */
	void OnMouseMoveEvent(Position x, Position y)
	{
		if (_hook)
		{
			Position ox = 0, oy = 0;

			CalcAlignment(&ox, &oy);

			if (GetParent())
			{
				SetX(x - _hx - GetParent()->GetX() - ox);
				SetY(y - _hy - GetParent()->GetY() - oy);
			}
			else
			{
				SetX(x - _hx - ox);
				SetY(y - _hy - oy);
			}
		}
	}

	/* override */ 
	void OnMouseButtonEvent(Position x, Position y, MouseButton button, bool down)
	{
		if (_border > static_cast<Position>(0.25) && down && button == MouseButton::MOUSE_BUTTON_LEFT && In(x, y))
		{
			if (y < GetAbsY() + _border)
			{
				_hook = true;

				_hx = x - GetAbsX();
				_hy = y - GetAbsY();
			}
		}
		else if (!down && button == MouseButton::MOUSE_BUTTON_LEFT)
			_hook = false;
	}

	/* override */
	void OnKeyEvent(Key key, bool down)
	{

	}

	/* override */
	void OnRender()
	{
		IManager::Get()->Render(GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), GetSrcX(), GetSrcY(), GetSrcWidth(), GetSrcHeight());

		_text.Render(GetAbsX() + static_cast<Position>(GetWidth() / static_cast<Size>(2)), GetAbsY() + GetBorder() / static_cast<Position>(2));
	
#ifndef OTIUM_NO_SCISSOR_TEST
		IManager::Get()->PushClipRect(GetAbsX(), GetAbsY() + GetBorder(), GetWidth(), GetHeight() - static_cast<Size>(GetBorder()));
#endif
	}
	
#ifndef OTIUM_NO_SCISSOR_TEST
	/* override */
	void OnPostRender()
	{
		IManager::Get()->PopClipRect();
	}
#endif

	inline SrcPosition GetSrcX() const { return _sx; }

	inline SrcPosition GetSrcY() const { return _sy; }

	inline SrcSize GetSrcWidth() const { return _sw; }

	inline SrcSize GetSrcHeight() const { return _sh; }

	inline Text* GetText() { return &_text; }

	inline Position GetBorder() const { return _border; }

	inline void SetSrcX(SrcPosition sx) { _sx = sx; }

	inline void SetSrcY(SrcPosition sy) { _sy = sy; }

	inline void SetSrcWidth(SrcSize sw) { _sw = sw; }

	inline void SetSrcHeight(SrcSize sh)  { _sh = sh; }
	
	inline void SetSource(SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh) { _sx = sx; _sy = sy; _sw = sw; _sh = sh; }

	inline void SetBorder(Position border) { _border = border; _text.SetAlignment((border > static_cast<Position>(0.25)) ? (ALIGN_CENTER) : (ALIGN_CENTER_X)); }
};

}

#endif