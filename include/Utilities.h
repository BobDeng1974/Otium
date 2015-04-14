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
#ifndef OTIUM_UTILITIES_H
#define OTIUM_UTILITIES_H

namespace Otium
{
#define OTIUM_INIT(ns) ns::Widget* ns::Widget::Focus = 0;

#define OTIUM_WIDGET_INIT(name) { static uint32 type = GetHashCode(name); SetType(type); }

#define OTIUM_COLOR_ENCODE(r, g, b) (r) | (g << 8) | (b << 16)
#define OTIUM_COLOR_ENCODE_ALPHA(r, g, b, a) OTIUM_COLOR_ENCODE(r, g, b) | (a << 24)

#define OTIUM_COLOR_DECODE(color, r, g, b) r = (uint8)(color & 0xFF); g = (uint8)((color >> 8) & 0xFF); b = (uint8)((color >> 16) & 0xFF);
#define OTIUM_COLOR_DECODE_ALPHA(color, r, g, b, a) OTIUM_COLOR_DECODE(color, r, g, b) a = (uint8)((color >> 24) & 0xFF);

#define OTIUM_FONT_ID(name, size) (name #size)

uint32 GetHashCode(const char* string);

}

#endif