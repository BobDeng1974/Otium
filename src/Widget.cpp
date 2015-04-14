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
Widget* Widget::_FindChild(uint32 id)
{
	for (uint32 i = 0; i < _children.size(); ++i)
	{
		if (_children[i]->_id == id)
			return _children[i];

		Widget* widget = _children[i]->_FindChild(id);

		if (widget)
			return widget;
	}
	return 0;
}

Widget::Widget()
	: _parent(0), _x(0), _y(0), _width(0), _height(0), _absX(0), _absY(0), _needUpdate(false)
{
}

Widget::~Widget()
{
	for (uint32 i = 0; i < _children.size(); ++i)
		delete _children[i];
}

void Widget::MouseDown(int32 x, int32 y, int32 button)
{
	if (In(x, y))
		_focus = true;
	else
		_focus = false;

	OnMouseDown(x, y, button);

	for (uint32 i = 0; i < _children.size(); ++i)
		_children[i]->MouseDown(x, y, button);
}

void Widget::MouseUp(int32 x, int32 y, int32 button)
{
	OnMouseUp(x, y, button);

	for (uint32 i = 0; i < _children.size(); ++i)
		_children[i]->MouseUp(x, y, button);
}

void Widget::MouseMove(int32 x, int32 y)
{
	OnMouseMove(x, y);

	for (uint32 i = 0; i < _children.size(); ++i)
		_children[i]->MouseMove(x, y);
}

void Widget::KeyDown(int32 key)
{
	OnKeyDown(key);

	for (uint32 i = 0; i < _children.size(); ++i)
		_children[i]->KeyDown(key);
}

void Widget::KeyUp(int32 key)
{
	OnKeyUp(key);

	for (uint32 i = 0; i < _children.size(); ++i)
		_children[i]->KeyUp(key);
}

void Widget::TextInput(char* text)
{
	OnTextInput(text);

	for (uint32 i = 0; i < _children.size(); ++i)
		_children[i]->TextInput(text);
}

void Widget::CalcAbsPosition(int32* x, int32* y)
{
	if (_parent)
		_parent->CalcAbsPosition(x, y);

	*x += _x;
	*y += _y;
}

void Widget::Update(float32 deltaTime)
{
	if (_needUpdate)
	{
		_absX = _absY = 0;
		CalcAbsPosition(&_absX, &_absY);
		OnPositionChange(_absX, _absY);
		_needUpdate = false;
	}

	OnUpdate(deltaTime);

	for (uint32 i = 0; i < _children.size(); ++i)
		_children[i]->Update(deltaTime);
}

void Widget::Render()
{
	OnRender();

	for (uint32 i = 0; i < _children.size(); ++i)
		_children[i]->Render();
}

}