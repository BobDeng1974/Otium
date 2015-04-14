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
#define OTIUM_WIDGET_H

namespace Otium
{
class Widget;

typedef fastdelegate::FastDelegate3<Widget*, int32, int32> OnClickEvent;

class Widget
{
private:
	uint32 _type;

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

	bool _focus;

public:
	OnClickEvent OnClick;

private:
	Widget* _FindChild(uint32 id);

protected:
	inline void SetType(uint32 type) { _type = type; }

public:
	Widget();

	virtual ~Widget();

	template<typename T>
	T* FindChild(const char* id)
	{
		return static_cast<T*>(_FindChild(GetHashCode(id)));
	}

	template<typename T>
	T* AddChild(const char* id)
	{
		T* t = new T();
		t->_id = GetHashCode(id);
		t->_parent = this;
		_children.push_back(t);
		return t;
	}

	void MouseDown(int32 x, int32 y, int32 button);

	virtual void OnMouseDown(int32 x, int32 y, int32 button) { }

	void MouseUp(int32 x, int32 y, int32 button);

	virtual void OnMouseUp(int32 x, int32 y, int32 button) { }

	void MouseMove(int32 x, int32 y);

	virtual void OnMouseMove(int32 x, int32 y) { }

	void KeyDown(int32 key);

	virtual void OnKeyDown(int32 key) { }

	void KeyUp(int32 key);

	virtual void OnKeyUp(int32 key) { }

	void TextInput(char* text);

	virtual void OnTextInput(char* text) { }

	/*
		@param x On start must be 0
		@param y On start must be 0
	*/
	void CalcAbsPosition(int32* x, int32* y);

	virtual void OnPositionChange(int32 x, int32 y) { }

	void Update(float32 deltaTime);

	virtual void OnUpdate(float32 deltaTime) { }

	void Render();

	virtual void OnRender() { }

	inline void SetX(int32 x) { _x = x; _needUpdate = true; }
	inline void SetY(int32 y) { _y = y; _needUpdate = true; }
	inline void SetWidth(int32 width) { _width = width; }
	inline void SetHeight(int32 height) { _height = height; }
	inline void SetSize(int32 width, int32 height) { SetWidth(width); SetHeight(height); }
	inline void SetPosition(int32 x, int32 y) { _x = x; _y = y; _needUpdate = true; }
	inline void SetDestination(int32 x, int32 y, int32 width, int32 height) { SetPosition(x, y); SetSize(width, height); }

	inline uint32 GetID() const { return _id; }
	inline Widget* GetParent() const { return _parent; }
	inline uint32 GetChildCount() const { return _children.size(); }
	inline int32 GetAbsX() const { return _absX; }
	inline int32 GetAbsY() const { return _absY; }
	inline int32 GetX() const { return _x; }
	inline int32 GetY() const { return _y; }
	inline int32 GetWidth() const { return _width; }
	inline int32 GetHeight() const { return _height; }
	inline bool IsFocus() const { return _focus; }
	inline bool In(int32 x, int32 y) const { return x >= GetAbsX() && x <= GetAbsX() + GetWidth() && y >= GetAbsY() && y <= GetAbsY() + GetHeight(); }
	inline uint32 GetType() const { return _type; }
	inline Widget* GetChild(uint32 i) { return _children[i]; }
};
}

#endif