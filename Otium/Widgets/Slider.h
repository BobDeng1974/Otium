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
#ifndef OTIUM_HSLIDER_H
#define OTIUM_HSLIDER_H

namespace Otium
{

template<Orientation o>
class Slider : public Widget
{
OTIUM_DECL_INTERNAL_ID(HSlider);

public:

private:
	SrcPosition _sx;
	SrcPosition _sy;
	SrcSize     _sw;
	SrcSize     _sh;
	
	SrcPosition _psx;
	SrcPosition _psy;
	SrcSize     _psw;
	SrcSize     _psh;

	int32 _value;
	int32 _minValue;
	int32 _maxValue;

	bool _pressed;

public:
	std::function<void(Widget*, int32)> ValueChange;

private:
	void SetValueBy(Position x);

public:
	Slider(const char* name)
		: Widget(name), _value(0), _minValue(0), _maxValue(100), _pressed(false)
	{
		
	}

	virtual ~Slider()
	{
	}
	
	/* override */
	void OnMouseMoveEvent(Position x, Position y);

	/* override */ 
	void OnMouseButtonEvent(Position x, Position y, MouseButton button, bool down);

	void OnRender();
	/* override 
	void OnRender()
	{
		IManager::Get()->Render(GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), GetSrcX(), GetSrcY(), GetSrcWidth(), GetSrcHeight());

		Position x = (static_cast<Position>(_value - _minValue) * static_cast<Position>(GetWidth()) / static_cast<Position>(_maxValue - _minValue));

		IManager::Get()->Render(GetAbsX() + x - static_cast<Position>(GetPtrSrcWidth()) / static_cast<Position>(2), GetAbsY() + static_cast<Position>(GetHeight()) / 2 - static_cast<Position>(GetPtrSrcHeight()) / 2, static_cast<Size>(GetPtrSrcWidth()), static_cast<Size>(GetPtrSrcHeight()), GetPtrSrcX(), GetPtrSrcY(), GetPtrSrcWidth(), GetPtrSrcHeight());
	}
	*/
	void SetValue(int32 value) 
	{ 
		int32 lastValue = _value;

		_value = value; 

		if (_value < _minValue)
			_value = _minValue;
		else if (_value > _maxValue)
			_value = _maxValue;

		if (lastValue != _value && ValueChange) 
			ValueChange(this, _value); 
	}

	inline SrcPosition GetSrcX() const { return _sx; }

	inline SrcPosition GetSrcY() const { return _sy; }

	inline SrcSize GetSrcWidth() const { return _sw; }

	inline SrcSize GetSrcHeight() const { return _sh; }

	inline SrcPosition GetPtrSrcX() const { return _psx; }

	inline SrcPosition GetPtrSrcY() const { return _psy; }

	inline SrcSize GetPtrSrcWidth() const { return _psw; }

	inline SrcSize GetPtrSrcHeight() const { return _psh; }

	inline int32 GetValue() const { return _value; }

	inline int32 GetMaxValue() const { return _maxValue; }

	inline int32 GetMinValue() const { return _minValue; }

	inline void SetSrcX(SrcPosition sx) { _sx = sx; }

	inline void SetSrcY(SrcPosition sy) { _sy = sy; }

	inline void SetSrcWidth(SrcSize sw) { _sw = sw; }

	inline void SetSrcHeight(SrcSize sh)  { _sh = sh; }
	
	inline void SetSource(SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh) { _sx = sx; _sy = sy; _sw = sw; _sh = sh; }

	inline void SetPtrSrcX(SrcPosition sx) { _psx = sx; }

	inline void SetPtrSrcY(SrcPosition sy) { _psy = sy; }

	inline void SetPtrSrcWidth(SrcSize sw) { _psw = sw; }

	inline void SetPtrSrcHeight(SrcSize sh)  { _psh = sh; }
	
	inline void SetPtrSource(SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh) { _psx = sx; _psy = sy; _psw = sw; _psh = sh; }

	inline void SetMaxValue(int32 value) { _maxValue = value; }

	inline void SetMinValue(int32 value) { _minValue = value; }
};


inline
void Slider<HORIZONTAL>::SetValueBy(Position x)
{
	SetValue(static_cast<int32>((x - GetAbsX()) * static_cast<Position>(_maxValue - _minValue) / static_cast<Position>(GetWidth()) + static_cast<Position>(_minValue))); 
}

inline
void Slider<HORIZONTAL>::OnMouseMoveEvent(Position x, Position y)
{
	if (_pressed)
		SetValueBy(x);
}

inline
void Slider<HORIZONTAL>::OnMouseButtonEvent(Position x, Position y, MouseButton button, bool down)
{
	if (down)
	{
		if (_pressed = In(x, y))
			SetValueBy(x);
	}
	else
		_pressed = false;
}

inline
void Slider<HORIZONTAL>::OnRender()
{
	IManager::Get()->Render(GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), GetSrcX(), GetSrcY(), GetSrcWidth(), GetSrcHeight());

	Position x = (static_cast<Position>(_value - _minValue) * static_cast<Position>(GetWidth()) / static_cast<Position>(_maxValue - _minValue));

	IManager::Get()->Render(GetAbsX() + x - static_cast<Position>(GetPtrSrcWidth()) / static_cast<Position>(2), GetAbsY() + static_cast<Position>(GetHeight()) / 2 - static_cast<Position>(GetPtrSrcHeight()) / 2, static_cast<Size>(GetPtrSrcWidth()), static_cast<Size>(GetPtrSrcHeight()), GetPtrSrcX(), GetPtrSrcY(), GetPtrSrcWidth(), GetPtrSrcHeight());
}

inline
void Slider<VERTICAL>::SetValueBy(Position y)
{
	SetValue(static_cast<int32>((y - GetAbsY()) * static_cast<Position>(_maxValue - _minValue) / static_cast<Position>(GetHeight()) + static_cast<Position>(_minValue))); 
}

inline
void Slider<VERTICAL>::OnMouseMoveEvent(Position x, Position y)
{
	if (_pressed)
		SetValueBy(y);
}

inline
void Slider<VERTICAL>::OnMouseButtonEvent(Position x, Position y, MouseButton button, bool down)
{
	if (down)
	{
		if (_pressed = In(x, y))
			SetValueBy(y);
	}
	else
		_pressed = false;
}

inline
void Slider<VERTICAL>::OnRender()
{
	IManager::Get()->Render(GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), GetSrcX(), GetSrcY(), GetSrcWidth(), GetSrcHeight());

	Position y = (static_cast<Position>(_value - _minValue) * static_cast<Position>(GetHeight()) / static_cast<Position>(_maxValue - _minValue));

	IManager::Get()->Render(GetAbsX() + static_cast<Position>(GetWidth()) / 2 - static_cast<Position>(GetPtrSrcWidth()) / 2, GetAbsY() + y - static_cast<Position>(GetPtrSrcHeight()) / static_cast<Position>(2), static_cast<Size>(GetPtrSrcWidth()), static_cast<Size>(GetPtrSrcHeight()), GetPtrSrcX(), GetPtrSrcY(), GetPtrSrcWidth(), GetPtrSrcHeight());
}


}

#endif