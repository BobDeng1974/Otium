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

/*
	Necessity is the mother of invention
*/
#ifndef OTIUM_H
#define OITUM_H

namespace Otium
{
/*
	Options for Otium, just define above include Otium one of defines below:

	#define OTIUM_NO_SCISSOR_TEST   
	#define OTIUM_NO_STATIC_TEXT  
*/

#define OTIUM_VERSION          0x000100

#ifndef OTIUM_DEFINED_SIMPLE_TYPES
typedef unsigned char      uint8;
typedef char               int8;
typedef unsigned short     uint16;
typedef short              int16;
typedef unsigned int       uint32;
typedef int                int32;
typedef unsigned long long uint64;
typedef long long          int64;
typedef float              float32;
typedef double             float64;
#endif

#ifndef OTIUM_DEFINED_TYPES
typedef uint32  ID;
typedef float32 Position;    /* should be signed */
typedef float32 Size;
typedef float32 SrcPosition; /* should be signed */
typedef float32 SrcSize;
typedef void*   Font;     /* nullable */
typedef uint8   FontSize;
typedef void*   Image;    /* nullable */
typedef uint32  Color;
typedef float32 Time;     /* must be floating point */
typedef uint32  Codepoint;
#endif

template<typename T>
inline ID GetStringHashCode(T& string)
{
	ID id = 2166136261U;                      
	for (uint32 i = 0; string[i]; ++i)         
	{                                       
		id ^= int(string[i]);              
		id *= 16777619U;                   
	}
	return id;
}

inline
uint32 UTF32toUTF8(Codepoint codepoint, char* result)
{
	char* ptr = result;
	if (codepoint <= 0x7F) 
	{
        *ptr++ = (char) codepoint;
    } 
	else if (codepoint <= 0x7FF) 
	{
        *ptr++ = 0xC0 | (char) ((codepoint >> 6) & 0x1F);
        *ptr++ = 0x80 | (char) (codepoint & 0x3F);
    } 
	else 
	{
        *ptr++ = 0xE0 | (char) ((codepoint >> 12) & 0x0F);
        *ptr++ = 0x80 | (char) ((codepoint >> 6) & 0x3F);
        *ptr++ = 0x80 | (char) (codepoint & 0x3F);
    }
	*ptr = 0;
	return ptr - result;
	/*
	char* ptr = result;
	if (codepoint < 0x80) *ptr++ = static_cast<char>(codepoint);
	else if (codepoint < 0x800) *ptr++ = 192 + codepoint / 64, *ptr++ = 128 + codepoint % 64;
	else if (codepoint - 0xd800u < 0x800) { result[0] = 0; }
	else if (codepoint < 0x10000) *ptr++ = 224 + codepoint / 4096, *ptr++ = 128 + codepoint / 64 % 64, *ptr++ = 128 + codepoint % 64;
	else if (codepoint < 0x110000) *ptr++ = 240 + codepoint/ 262144, *ptr++ = 128 + codepoint / 4096 % 64, *ptr++=128 + codepoint / 64 % 64, *ptr++ = 128 + codepoint % 64;
	else { result[0] = 0; }
	*ptr = 0;
	return ptr - result;
	*/
}

inline
uint32 UTF8toUTF32(Codepoint* codepoint, const char* text)
{
	if(!(text[0] & 0x80))      // 0xxxxxxx
	{
		*codepoint = (wchar_t)text[0];
		return 1;
	}
	else if((text[0] & 0xE0) == 0xC0)  // 110xxxxx
	{
		*codepoint = (wchar_t)(((text[0] & 0x1F) << 6) | (text[1] & 0x3F));
		return 2;
	}
	else if((text[0] & 0xF0) == 0xE0)  // 1110xxxx
	{
		*codepoint = (wchar_t)(((text[0] & 0x0F) << 12) | ((text[1] & 0x3F) << 6) | (text[2] & 0x3F));
		return 3;
	}
	return 0;
}

template<typename T>
inline void Swap(T& x, T& y)
{
	x ^= y;
	y ^= x;
	x ^= y;
}

#define OTIUM_DECODE_COLOR(c, r, g, b, a) \
	r = c & 0xFF;                         \
	g = (c >> 8) & 0xFF;                  \
	b = (c >> 16) & 0xFF;                 \
	a = (c >> 24) & 0xFF;                 

#define OTIUM_ENCODE_COLOR(r, g, b, a) (r | (g << 8) | (b << 16) | (a << 24))

/**
	Macro only for internal use. 
*/
#define OTIUM_DECL_INTERNAL_ID(name)      \
public: virtual ID GetInternalID() const  \
{                                         \
	static                                \
	ID id = GetStringHashCode(#name);     \
	return id;                            \
}

enum MouseButton
{
	MOUSE_BUTTON_LEFT = 0,
	MOUSE_BUTTON_MIDDLE,
	MOUSE_BUTTON_RIGHT,

	MOUSE_BUTTON_UNKNOWN
};

enum Key
{
    KEY_RETURN = 0,
    KEY_ESCAPE,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_SPACE,
    KEY_INSERT,
    KEY_HOME,
    KEY_PAGEUP,
    KEY_DELETE,
    KEY_END,
    KEY_PAGEDOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP,

	KEY_UNKNOWN
};

enum Alignment
{
	ALIGN_LEFT     = 0x01,
	ALIGN_RIGHT    = 0x02,
	ALIGN_TOP      = 0x04,
	ALIGN_BOTTOM   = 0x08,

	ALIGN_CENTER_X = ALIGN_LEFT | ALIGN_RIGHT,
	ALIGN_CENTER_Y = ALIGN_TOP | ALIGN_BOTTOM,

	ALIGN_CENTER   = ALIGN_CENTER_X | ALIGN_CENTER_Y
};

enum Orientation
{
	HORIZONTAL = 0, // ---
	VERTICAL   = 1  //  |
};

}

#include <functional>
#include <vector>
#include <string>
#include <memory>

#include "IManager.h"

#include "String.h"

#include "Text/IText.h"
#include "Text/StaticText.h"
#include "Text/DynamicText.h"

#include "Widgets/Widget.h"
#include "Widgets/Label.h"
#include "Widgets/Input.h"
#include "Widgets/Button.h"
#include "Widgets/CheckBox.h"
#include "Widgets/RadioButton.h"
#include "Widgets/Textbox.h"
#include "Widgets/Picture.h"
#include "Widgets/Slider.h"
#include "Widgets/Window.h"

#endif