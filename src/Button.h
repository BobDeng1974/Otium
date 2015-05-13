#ifndef OTIUM_BUTTON_H
#define OTIUM_BUTTON_H

namespace Otium
{


class Button : public Widget
{
public:
	enum ButtonState
	{
		STATE_DEFAULT = 0,
		STATE_HOVER,
		STATE_ACTIVE,
		STATE_DISABLED,

		STATE_COUNT
	};

private:
	ButtonState _state;

	SrcPosition _sx[STATE_COUNT];
	SrcPosition _sy[STATE_COUNT];
	SrcSize     _sw;
	SrcSize     _sh;

	Text _text;

public:
	Button()
		: _state(STATE_DEFAULT)
	{
		_text.SetAlignment(Widget::ALIGN_CENTER);
	}

	virtual ~Button()
	{
	}

	/* override */
	void OnMouseMoveEvent(Position x, Position y)
	{
		if (In(x, y))
		{
			if (_state == STATE_DEFAULT)
				_state = STATE_HOVER;
		}
		else
			if (_state == STATE_HOVER)
				_state = STATE_DEFAULT;
	}

	/* override */ 
	void OnMouseButtonEvent(Position x, Position y, MouseButton button, bool down)
	{
		if (down)
		{
			if (In(x, y))
				_state = STATE_ACTIVE;
		}
		else
		{
			if (In(x, y))
			{
				_state = STATE_HOVER;

				if (Click)
					Click(this, x, y);
			}
			else
				_state = STATE_DEFAULT;
		}
	}

	/* override */
	void OnRender()
	{
		static Position stateOffsets[STATE_COUNT] = { static_cast<Position>(0), static_cast<Position>(-1), static_cast<Position>(1), static_cast<Position>(0) };

		IManager::Get()->Render(GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), GetSrcX(_state), GetSrcY(_state), GetSrcWidth(), GetSrcHeight());
	
		_text.Render(GetAbsX() + static_cast<Position>(GetWidth() / static_cast<Size>(2)), GetAbsY() + static_cast<Position>(GetHeight() / static_cast<Size>(2)) + stateOffsets[_state]);
	}

	inline SrcPosition GetSrcX(ButtonState state) const { return _sx[state]; }

	inline SrcPosition GetSrcY(ButtonState state) const { return _sy[state]; }

	inline SrcSize GetSrcWidth() const { return _sw; }

	inline SrcSize GetSrcHeight() const { return _sh; }

	inline ButtonState GetState() const { return _state; }

	inline void SetSrcX(ButtonState state, SrcPosition sx) { _sx[state] = sx; }

	inline void SetSrcY(ButtonState state, SrcPosition sy) { _sy[state] = sy; }

	inline void SetSrcWidth(SrcSize sw) { _sw = sw; }

	inline void SetSrcHeight(SrcSize sh)  { _sh = sh; }
	
	inline void SetSrcPosition(ButtonState state, Position sx, Position sy) { _sx[state] = sx; _sy[state] = sy; }

	inline void SetSrcSize(Size sw, Size sh) { _sw = sw; _sh = sh; }

	inline Text* GetText() { return &_text; }
};

}

#endif