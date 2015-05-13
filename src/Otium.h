/*
	Necessity is the mother of invention
*/
#ifndef OTIUM_H
#define OITUM_H

namespace Otium
{

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
typedef float32 Time;
#endif

#define OTIUM_STRING_HASH_CODE(string, val) \
	val = 2166136261U;                      \
	for (uint32 i = 0; string[i]; ++i)      \
	{                                       \
		val ^= uint32(string[i]);           \
		val *= 16777619U;                   \
	}

#define OTIUM_DECODE_COLOR(c, r, g, b, a) \
	r = c & 0xFF;                         \
	g = (c >> 8) & 0xFF;                  \
	b = (c >> 16) & 0xFF;                 \
	a = (c >> 24) & 0xFF;                 

#define OTIUM_ENCODE_COLOR(r, g, b, a) (r | (g << 8) | (b << 16) | (a << 24))

enum MouseButton
{
	MOUSE_BUTTON_LEFT = 0,
	MOUSE_BUTTON_MIDDLE,
	MOUSE_BUTTON_RIGHT
};

enum Key
{
	KEY_UNKNOWN = 0,
    KEY_RETURN,
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
    KEY_UP
};


}

#include "FastDelegate/FastDelegate.h"

#include <vector>
#include <string>

#include "IManager.h"
#include "Widget.h"
#include "Text.h"
#include "Label.h"
#include "Button.h"
#include "Textbox.h"
#include "Picture.h"

#endif