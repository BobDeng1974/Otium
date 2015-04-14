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
#include <Otium.h>

namespace Otium
{
	
Button::Button()
	: _srcWidth(0), _srcHeight(0), _state(OTIUM_BUTTON_STATE_DEFAULT)
{
	OTIUM_WIDGET_INIT("Button");
}

Button::~Button()
{
}

void Button::OnMouseDown(int32 x, int32 y, int32 button)
{
	if (button == OTIUM_MOUSE_BUTTON_LEFT)
		if (x >= GetAbsX() && x <= GetAbsX() + GetWidth() && y >= GetAbsY() && y <= GetAbsY() + GetHeight())
			_state = OTIUM_BUTTON_STATE_ACTIVE;
}

void Button::OnMouseUp(int32 x, int32 y, int32 button)
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

void Button::OnMouseMove(int32 x, int32 y)
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

void Button::OnRender()
{
	GetManager()->RenderCopy(GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), GetSrcX(_state), GetSrcY(_state), GetSrcWidth(), GetSrcHeight());
}
}