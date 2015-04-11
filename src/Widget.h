#ifndef OTIUM_WIDGET_H
#define OTIUM_WIDGET_H

namespace Otium
{
class Widget;

// lukasz.wojtowicz.88@o2.pl

typedef fastdelegate::FastDelegate3<Widget*, int32, int32> OnClickEvent;

class Widget
{
private:
	uint32 _id;

	int32 _absX;
	int32 _absY;

	int32 _x;
	int32 _y;
	int32 _width;
	int32 _height;

	uint8 _align;

	bool _needUpdate;

	std::vector<Widget*> _children;
	Widget* _parent;

public:
	OnClickEvent OnClick;

private:
	Widget* _GetChild(uint32 id)
	{
		for (uint32 i = 0; i < _children.size(); ++i)
		{
			if (_children[i]->_id == id)
				return _children[i];

			Widget* widget = _children[i]->_GetChild(id);

			if (widget)
				return widget;
		}
		return 0;
	}

public:
	Widget()
		: _parent(0), _x(0), _y(0), _width(0), _height(0), _absX(0), _absY(0), _needUpdate(false)
	{
	}

	virtual ~Widget()
	{
		for (uint32 i = 0; i < _children.size(); ++i)
			delete _children[i];
	}

	template<typename T>
	T* GetChild(const char* id)
	{
		uint32 hash;
		OTIUM_HASH_CODE(hash, id);
		return static_cast<T*>(_GetChild(hash));
	}

	template<typename T>
	T* AddChild(const char* id)
	{
		T* t = new T();
		OTIUM_HASH_CODE(t->_id, id);
		t->_parent = this;
		_children.push_back(t);
		return t;
	}

	void MouseDown(int32 x, int32 y, int32 button)
	{
		OnMouseDown(x, y, button);

		for (uint32 i = 0; i < _children.size(); ++i)
			_children[i]->MouseDown(x, y, button);
	}
	virtual void OnMouseDown(int32 x, int32 y, int32 button) { }

	void MouseUp(int32 x, int32 y, int32 button)
	{
		OnMouseUp(x, y, button);

		for (uint32 i = 0; i < _children.size(); ++i)
			_children[i]->MouseUp(x, y, button);
	}
	virtual void OnMouseUp(int32 x, int32 y, int32 button) { }

	void MouseMove(int32 x, int32 y)
	{
		OnMouseMove(x, y);

		for (uint32 i = 0; i < _children.size(); ++i)
			_children[i]->MouseMove(x, y);
	}
	virtual void OnMouseMove(int32 x, int32 y) { }

	void KeyDown(int32 key)
	{
		OnKeyDown(key);

		for (uint32 i = 0; i < _children.size(); ++i)
			_children[i]->KeyDown(key);
	}
	virtual void OnKeyDown(int32 key) { }

	void KeyUp(int32 key)
	{
		OnKeyUp(key);

		for (uint32 i = 0; i < _children.size(); ++i)
			_children[i]->KeyUp(key);
	}
	virtual void OnKeyUp(int32 key) { }

	void TextInput(char* text)
	{
		OnTextInput(text);

		for (uint32 i = 0; i < _children.size(); ++i)
			_children[i]->TextInput(text);
	}
	virtual void OnTextInput(char* text) { }

	void Release(Renderer* renderer)
	{
		OnRelease(renderer);

		for (uint32 i = 0; i < _children.size(); ++i)
			_children[i]->Release(renderer);
	}
	virtual void OnRelease(Renderer* renderer) { }

	/*
		@param x On start must be 0
		@param y On start must be 0
	*/
	virtual void CalcAbsPosition(int32* x, int32* y)
	{
		if (_parent)
			_parent->CalcAbsPosition(x, y);

		*x += _x;
		*y += _y;
	}

	void Render(Renderer* renderer)
	{
		if (_needUpdate)
		{
			_absX = _absY = 0;
			CalcAbsPosition(&_absX, &_absY);
			_needUpdate = false;
		}

		OnRender(renderer);

		for (uint32 i = 0; i < _children.size(); ++i)
			_children[i]->Render(renderer);
	}
	virtual void OnRender(Renderer* renderer) { }

	inline void SetX(int32 x) { _x = x; _needUpdate = true; }
	inline void SetY(int32 y) { _y = y; _needUpdate = true; }
	inline void SetWidth(int32 width) { _width = width; }
	inline void SetHeight(int32 height) { _height = height; }
	inline void SetSize(int32 width, int32 height) { SetWidth(width); SetHeight(height); }
	inline void SetPosition(int32 x, int32 y) { _x = x; _y = y; _needUpdate = true; }
	inline void SetDestination(int32 x, int32 y, int32 width, int32 height) { SetPosition(x, y); SetSize(width, height); }

	inline uint32 GetID() const { return _id; }
	inline int32 GetAbsX() const { return _absX; }
	inline int32 GetAbsY() const { return _absY; }
	inline int32 GetX() const { return _x; }
	inline int32 GetY() const { return _y; }
	inline int32 GetWidth() const { return _width; }
	inline int32 GetHeight() const { return _height; }
};
}

#endif