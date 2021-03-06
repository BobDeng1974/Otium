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
#ifndef OTIUM_BUTTON_H
#define OTIUM_BUTTON_H

namespace Otium
{

class Button : public Input
{
OTIUM_DECL_INTERNAL_ID(Button);

public:
	enum State
	{
		STATE_DEFAULT = 0,
		STATE_HOVER,
		STATE_ACTIVE,
		STATE_DISABLED,

		STATE_COUNT
	};

private:
	State _state;

	SrcPosition _sx[STATE_COUNT];
	SrcPosition _sy[STATE_COUNT];
	SrcSize     _sw;
	SrcSize     _sh;

public:
	Button(const char* name)
		: Input(name),  _state(STATE_DEFAULT)
	{
		GetText()->SetAlignment(ALIGN_CENTER);
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
	
		GetText()->Render(GetAbsX() + static_cast<Position>(GetWidth() / static_cast<Size>(2)), GetAbsY() + static_cast<Position>(GetHeight() / static_cast<Size>(2)) + stateOffsets[_state]);
	}

	inline SrcPosition GetSrcX(State state) const { return _sx[state]; }

	inline SrcPosition GetSrcY(State state) const { return _sy[state]; }

	inline SrcSize GetSrcWidth() const { return _sw; }

	inline SrcSize GetSrcHeight() const { return _sh; }

	inline State GetState() const { return _state; }

	inline void SetSrcX(State state, SrcPosition sx) { _sx[state] = sx; }

	inline void SetSrcY(State state, SrcPosition sy) { _sy[state] = sy; }

	inline void SetSrcWidth(SrcSize sw) { _sw = sw; }

	inline void SetSrcHeight(SrcSize sh)  { _sh = sh; }
	
	inline void SetSrcPosition(State state, SrcPosition sx, SrcPosition sy) { _sx[state] = sx; _sy[state] = sy; }

	inline void SetSrcSize(SrcSize sw, SrcSize sh) { _sw = sw; _sh = sh; }
};

}

#endif