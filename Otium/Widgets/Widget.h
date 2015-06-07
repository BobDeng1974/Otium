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
#ifndef OTIUM_WIDGET_H
#define OITUM_WIDGET_H

namespace Otium
{

class Widget
{
OTIUM_DECL_INTERNAL_ID(Widget);

private:
	ID _id;
	Position _absX;
	Position _absY;
	Position _x;
	Position _y;
	Size _w;
	Size _h;
	uint8 _align; /* Align must be simple type due to compile error of enumerator */ 

	std::vector<Widget*> _children;
	Widget* _parent;

	bool _needUpdate;

public:

public:
	Widget(const char* id)
		: _parent(0), _needUpdate(false), _align(ALIGN_LEFT | ALIGN_TOP)
	{
		_id = GetStringHashCode(id);
	}

	virtual ~Widget()
	{
		for (uint32 i = 0; i < _children.size(); i++)
			delete _children[i];
	}

	void Widget::CalcAlignment(Position* x, Position* y)
	{
		if ((_align & (ALIGN_RIGHT | ALIGN_LEFT)) == (ALIGN_RIGHT | ALIGN_LEFT))
			*x -= static_cast<Position>(_w / static_cast<Size>(2));
		else if ((_align & ALIGN_RIGHT) != 0)
			*x -= static_cast<Position>(_w);

		if ((_align & (ALIGN_BOTTOM | ALIGN_TOP)) == (ALIGN_BOTTOM | ALIGN_TOP))
			*y -= static_cast<Position>(_h / static_cast<Size>(2));
		else if ((_align & ALIGN_BOTTOM) != 0)
			*y -= static_cast<Position>(_h);
	}

	void Widget::CalcAbsPosition(Position* x, Position* y)
	{
		if (_parent)
			_parent->CalcAbsPosition(x, y);

		*x += _x;
		*y += _y;

		CalcAlignment(x, y);
	}

	void MouseMoveEvent(Position x, Position y)
	{
		OnMouseMoveEvent(x, y);

		for (uint32 i = 0; i < _children.size(); i++)
			_children[i]->MouseMoveEvent(x, y);
	}
	virtual void OnMouseMoveEvent(Position x, Position y) { }

	void MouseButtonEvent(Position x, Position y, MouseButton button, bool down)
	{
		if (In(x, y))
		{
			// Check x and y is in bounding box of parent (if exist)
			if (!GetParent() || GetParent()->In(x, y))
			{
				if (down)
				{
					SetFocus(this);

					OnMouseButtonEvent(x, y, button, down);
				}
			}
		}

		if (!down)
			OnMouseButtonEvent(x, y, button, down);

		for (uint32 i = 0; i < _children.size(); i++)
			_children[i]->MouseButtonEvent(x, y, button, down);
	}
	virtual void OnMouseButtonEvent(Position x, Position y, MouseButton button, bool down) { }

	// UTF32
	void TextInputEvent(Codepoint codepoint)
	{
		OnTextInputEvent(codepoint);

		for (uint32 i = 0; i < _children.size(); i++)
			_children[i]->TextInputEvent(codepoint);
	}
	virtual void OnTextInputEvent(Codepoint codepoint) { }

	// UTF8
	void TextInputEvent(const char* codepoint)
	{
		Codepoint unicode;
		UTF8toUTF32(&unicode, codepoint);
		TextInputEvent(unicode);
	}

	void KeyEvent(Key key, bool down)
	{
		OnKeyEvent(key, down);

		for (uint32 i = 0; i < _children.size(); i++)
			_children[i]->KeyEvent(key, down);
	}
	virtual void OnKeyEvent(Key key, bool down) { }

	virtual void OnGetFocusEvent() { }

	void Update(Time deltaTime)
	{
		bool updated = false;
		if (_needUpdate)
		{
			Position lastAbsX = _absX, lastAbsY = _absY;

			_absX = _absY = 0;
			CalcAbsPosition(&_absX, &_absY);

			updated = lastAbsX != _absX || lastAbsY != _absY;

			_needUpdate = false;
		}

		OnUpdate(deltaTime);

		for (uint32 i = 0; i < _children.size(); i++)
		{
			_children[i]->_needUpdate |= updated;

			_children[i]->Update(deltaTime);
		}
	}
	virtual void OnUpdate(Time deltaTime) { }

	void Render()
	{
		OnRender();

		for (uint32 i = 0; i < _children.size(); i++)
			_children[i]->Render();

		OnPostRender();
	}
	virtual void OnRender() { }
	virtual void OnPostRender() { }

	template<typename T>
	T* FindChild(ID id)
	{
		for (uint32 i = 0; i < _children.size(); i++)
		{
			if (_children[i]->_id == id)
				return static_cast<T*>(_children[i]);

			T* child = _children[i]->FindChild<T>(id);
			if (child)
				return child;
		}

		return 0;
	}

	template<typename T>
	T* FindChild(const char* id)
	{
		ID hash = GetStringHashCode(id);
		return FindChild<T>(hash);
	}

	template<typename T>
	T* AddChild(const char* name)
	{
		T* widget = new T(name);
		widget->_parent = this;
		_children.push_back(widget);
		return widget;
	}

	void RemoveChild(Widget* widget)
	{
		for (uint32 i = 0; i < _children.size(); i++)
		{
			if (_children[i] == widget)
			{
				delete _children[i];
				return;
			}

			_children[i]->RemoveChild(widget);
		}
	}

	void RemoveChild(ID id)
	{
		for (uint32 i = 0; i < _children.size(); i++)
		{
			if (_children[i]->_id == id)
			{
				delete _children[i];
				return;
			}

			_children[i]->RemoveChild(id);
		}
	}

	void RemoveChild(const char* id)
	{
		ID hash = GetStringHashCode(id);
		RemoveChild(id);
	}

	inline Position GetAbsX() const { return _absX; }

	inline Position GetAbsY() const { return _absY; }

	inline Position GetX() const { return _x; }

	inline Position GetY() const { return _y; }

	inline Size GetWidth() const { return _w; }

	inline Size GetHeight() const { return _h; }

	inline uint8 GetAlignment() const { return _align; }

	inline Widget* GetParent() const { return _parent; }

	inline uint32 GetChildrenCount() const { return _children.size(); }

	inline Widget* GetChild(uint32 i) const { return _children[i]; }

	inline bool In(Position x, Position y) const { return x > GetAbsX() && x < GetAbsX() + GetWidth() && y > GetAbsY() && y < GetAbsY() + GetHeight(); }

	inline void SetX(Position x) { _x = x; _needUpdate = true; }

	inline void SetY(Position y) { _y = y; _needUpdate = true; }

	inline void SetWidth(Size w) { _w = w; _needUpdate = true; }

	inline void SetHeight(Size h)  { _h = h; _needUpdate = true; }

	inline void SetDestination(Position x, Position y, Size w, Size h) { _x = x; _y = y; _w = w; _h = h; _needUpdate = true; }

	inline void SetAlignment(uint8 align) { _align = align; }

	/**
		Return focused widget.
	*/
	static Widget*& GetFocus()
	{
		static Widget* focus = 0;

		return focus;
	}

	inline static void SetFocus(Widget* widget)
	{
		GetFocus() = widget;

		if (widget)
			widget->OnGetFocusEvent();
	}

	inline static bool IsFocus(Widget* widget)
	{
		return GetFocus() == widget;
	}
};

}

#endif