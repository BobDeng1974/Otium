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

#define OTIUM_BUTTON_STATE_DEFAULT  0
#define OTIUM_BUTTON_STATE_HOVER    1
#define OTIUM_BUTTON_STATE_ACTIVE   2
#define OTIUM_BUTTON_STATE_DISABLED 3
#define OTIUM_BUTTON_STATE_COUNT    4

namespace Otium
{
class Button : public Widget
{
private:
	int32 _srcX[OTIUM_BUTTON_STATE_COUNT];
	int32 _srcY[OTIUM_BUTTON_STATE_COUNT];
	int32 _srcWidth;
	int32 _srcHeight;

	uint8 _state;
	
public:
	Button()
		: _srcWidth(0), _srcHeight(0), _state(OTIUM_BUTTON_STATE_DEFAULT)
	{
	}

	virtual ~Button()
	{
	}

	void OnMouseDown(int32 x, int32 y, int32 button)
	{
		if (button == OTIUM_MOUSE_BUTTON_LEFT)
			if (x >= GetAbsX() && x <= GetAbsX() + GetWidth() && y >= GetAbsY() && y <= GetAbsY() + GetHeight())
				_state = OTIUM_BUTTON_STATE_ACTIVE;
	}

	void OnMouseUp(int32 x, int32 y, int32 button)
	{
		if (button == OTIUM_MOUSE_BUTTON_LEFT)
		{
			if (x >= GetAbsX() && x <= GetAbsX() + GetWidth() && y >= GetAbsY() && y <= GetAbsY() + GetHeight())
			{
				_state = OTIUM_BUTTON_STATE_HOVER;
				
				if (OnClick)
					OnClick(this, x - GetAbsX(), y - GetAbsY());
			}
			else
			{
				_state = OTIUM_BUTTON_STATE_DEFAULT;
			}
		}
	}

	void OnMouseMove(int32 x, int32 y)
	{
		if (x >= GetAbsX() && x <= GetAbsX() + GetWidth() && y >= GetAbsY() && y <= GetAbsY() + GetHeight())
		{
			if (_state == OTIUM_BUTTON_STATE_DEFAULT)
				_state = OTIUM_BUTTON_STATE_HOVER;
		}
		else
		{
			if (_state == OTIUM_BUTTON_STATE_HOVER)
				_state = OTIUM_BUTTON_STATE_DEFAULT;
		}

	}

	void OnRender(Renderer* renderer)
	{
		renderer->RenderCopy(GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), GetSrcX(_state), GetSrcY(_state), GetSrcWidth(), GetSrcHeight());
	}

	inline void SetSrcX(uint8 state, int32 srcX) { _srcX[state] = srcX; }
	inline void SetSrcY(uint8 state, int32 srcY) { _srcY[state] = srcY; }
	inline void SetSrcWidth(int32 srcWidth) { _srcWidth = srcWidth; }
	inline void SetSrcHeight(int32 srcHeight) { _srcHeight = srcHeight; }

	inline int32 GetSrcX(uint8 state) const { return _srcX[state]; }
	inline int32 GetSrcY(uint8 state) const { return _srcY[state]; }
	inline int32 GetSrcWidth() const { return _srcWidth; }
	inline int32 GetSrcHeight() const { return _srcHeight; }
};
}

#endif