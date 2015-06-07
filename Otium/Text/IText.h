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
#ifndef OTIUM_TEXT_H
#define OTIUM_TEXT_H

namespace Otium
{

class IText
{
private:
	Font _font;

	std::basic_string<Codepoint> _string;

	Color _color;

	bool _needUpdate;

	uint8 _align;

	Position _ox;
	Position _oy;

	Codepoint _pass;

protected:
	void UpdateOffsets(SrcSize w, SrcSize h)
	{
		_ox = _oy = 0;
		if ((_align & (ALIGN_RIGHT | ALIGN_LEFT)) == (ALIGN_RIGHT | ALIGN_LEFT))
			_ox -= static_cast<Position>(w / static_cast<Size>(2));
		else if ((_align & ALIGN_RIGHT) != 0)
			_ox -= static_cast<Position>(w);

		if ((_align & (ALIGN_BOTTOM | ALIGN_TOP)) == (ALIGN_BOTTOM | ALIGN_TOP))
			_oy -= static_cast<Position>(h / static_cast<Size>(2));
		else if ((_align & ALIGN_BOTTOM) != 0)
			_oy -= static_cast<Position>(h);
	}

	virtual void OnStringChanged() = 0;

	inline void SetNeedUpdate(bool value) { _needUpdate = value; }

	inline bool IsNeedUpdate() const { return _needUpdate; }

	inline Position GetOffsetX() const { return _ox; }

	inline Position GetOffsetY() const { return _oy; }

public:
	IText()
		: _pass(0), _needUpdate(false), _font(0), _align(ALIGN_LEFT | ALIGN_TOP), _ox(static_cast<Position>(0)), _oy(static_cast<Position>(0))
	{

	}

	virtual ~IText()
	{
	}
	
	void UpdatePassword(std::basic_string<Codepoint>& password)
	{
		password.resize(_string.size());
		for (uint32 i = 0; i < _string.size(); i++)
			//if ((_string[i] & 0x80) == 0 || (_string[i] & 0xC0) == 0xC0)
				password[i] = _pass;
	}

	virtual void Render(Position x, Position y) = 0;

	virtual void Measure(SrcSize* width, SrcSize* height) = 0;

	void Pop()
	{
		if (!_string.empty())
		{	
			_string.pop_back();

			_needUpdate = true;
		}
	}

	/**
		@param string Text in UTF8
	*/
	void SetString(const char* string) 
	{ 
		_string.clear();
		while (*string)
		{
			Codepoint codepoint;
			string += UTF8toUTF32(&codepoint, string);
			_string.push_back(codepoint);
		}
		_needUpdate = true;
	}

	const Codepoint* GetString()
	{
		return &_string[0];
	}

	const char* GetCString() const 
	{
		static char string[1024];

		char* ptr = string;
		for (uint32 i = 0; i < _string.size(); i++)
		{
			ptr += UTF32toUTF8(_string[i], ptr);
		}

		return string; 
	}

	inline uint8 GetAlignment() const { return _align; }

	inline Font GetFont() const { return _font; }

	inline Color GetColor() const { return _color; }

	inline Codepoint GetPasswordChar() const { return _pass; }

	inline void SetColor(Color color) { _color = color; }

	inline void SetFont(const char* name, FontSize size) { _font = IManager::Get()->GetFont(name, size); }

	inline void SetAlignment(uint8 align) { _align = align; }

	inline void Add(uint32 codepoint) 
	{ 
		_string.push_back(codepoint);
		_needUpdate = true; 
	}

	inline void Add(const char* codepoint) 
	{ 
		Codepoint c;
		UTF8toUTF32(&c, codepoint);
		Add(c);
	}

	inline void Remove(uint32 index)
	{
		_string.erase(_string.begin() + index);

		_needUpdate = true;
	}

	inline void Insert(uint32 codepoint, uint32 index)
	{
		_string.insert(index, 1, codepoint);

		_needUpdate = true;
	}

	inline void SetPasswordChar(Codepoint c) { _pass = c; }

	inline uint32 GetLength() const { return _string.size(); }
};

}

#endif