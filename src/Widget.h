#ifndef OTIUM_WIDGET_H
#define OITUM_WIDGET_H

namespace Otium
{

class Widget;

typedef fastdelegate::FastDelegate3<Widget*, Position, Position> ClickEvent;

class Widget
{
public:
	enum Alignment : int32
	{
		ALIGN_LEFT     = 0x01,
		ALIGN_RIGHT    = 0x02,
		ALIGN_TOP      = 0x04,
		ALIGN_BOTTOM   = 0x08,

		ALIGN_CENTER_X = ALIGN_LEFT | ALIGN_RIGHT,
		ALIGN_CENTER_Y = ALIGN_TOP | ALIGN_BOTTOM,

		ALIGN_CENTER   = ALIGN_CENTER_X | ALIGN_CENTER_Y
	};

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
	ClickEvent Click;

public:
	Widget()
		: _parent(0), _needUpdate(false), _align(ALIGN_LEFT | ALIGN_TOP)
	{
	}

	virtual ~Widget()
	{
		for (uint32 i = 0; i < _children.size(); i++)
			delete _children[i];
	}

	void Widget::CalcAbsPosition(Position* x, Position* y)
	{
		if (_parent)
			_parent->CalcAbsPosition(x, y);

		*x += _x;
		*y += _y;

		if ((_align & (ALIGN_RIGHT | ALIGN_LEFT)) == (ALIGN_RIGHT | ALIGN_LEFT))
			*x -= static_cast<Position>(_w / static_cast<Size>(2));
		else if ((_align & ALIGN_RIGHT) != 0)
			*x -= static_cast<Position>(_w);

		if ((_align & (ALIGN_BOTTOM | ALIGN_TOP)) == (ALIGN_BOTTOM | ALIGN_TOP))
			*y -= static_cast<Position>(_h / static_cast<Size>(2));
		else if ((_align & ALIGN_BOTTOM) != 0)
			*y -= static_cast<Position>(_h);
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
		if (down && In(x, y))
			Widget::GetFocus() = this;

		OnMouseButtonEvent(x, y, button, down);

		for (uint32 i = 0; i < _children.size(); i++)
			_children[i]->MouseButtonEvent(x, y, button, down);
	}
	virtual void OnMouseButtonEvent(Position x, Position y, MouseButton button, bool down) { }

	void TextInputEvent(const char* text)
	{
		OnTextInputEvent(text);

		for (uint32 i = 0; i < _children.size(); i++)
			_children[i]->TextInputEvent(text);
	}
	virtual void OnTextInputEvent(const char* text) { }

	void KeyEvent(Key key, bool down)
	{
		OnKeyEvent(key, down);

		for (uint32 i = 0; i < _children.size(); i++)
			_children[i]->KeyEvent(key, down);
	}
	virtual void OnKeyEvent(Key key, bool down) { }

	void Update(Time deltaTime)
	{
		if (_needUpdate)
		{
			_absX = _absY = 0;
			CalcAbsPosition(&_absX, &_absY);
			_needUpdate = false;
		}

		OnUpdate(deltaTime);

		for (uint32 i = 0; i < _children.size(); i++)
			_children[i]->Update(deltaTime);
	}
	virtual void OnUpdate(Time deltaTime) { }

	void Render()
	{
		OnRender();

		for (uint32 i = 0; i < _children.size(); i++)
			_children[i]->Render();
	}
	virtual void OnRender() { }

	template<typename T>
	T* FindChild(ID id)
	{
		for (uint32 i = 0; i < _children.size(); i++)
		{
			if (_children[i]->_id == id)
				return _children[i];

			T* child = _children[i]->FindChild<T>(id);
			if (child)
				return child;
		}

		return 0;
	}

	template<typename T>
	T* FindChild(const char* id)
	{
		ID hash;
		OTIUM_STRING_HASH_CODE(id, hash);
		return FindChild<T>(hash);
	}

	template<typename T>
	T* AddChild(const char* fileName)
	{
		T* widget = new T();
		OTIUM_STRING_HASH_CODE(fileName, widget->_id);
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
		ID hash;
		OTIUM_STRING_HASH_CODE(id, hash);
		RemoveChild(id);
	}

	inline Position GetAbsX() const { return _absX; }

	inline Position GetAbsY() const { return _absY; }

	inline Position GetX() const { return _x; }

	inline Position GetY() const { return _y; }

	inline Size GetWidth() const { return _w; }

	inline Size GetHeight() const { return _h; }

	inline uint8 GetAlignment() const { return _align; }

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
};

}

#endif