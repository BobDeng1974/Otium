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
#ifndef OTIUM_H
#define OTIUM_H

typedef unsigned char uint8;
typedef char int8;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;
typedef int int32;
typedef unsigned long long uint64;
typedef long long int64;
typedef float float32;
typedef double float64;

#include <string>
#include <vector>
#include <map>

#define OTIUM_MOUSE_BUTTON_LEFT   0
#define OTIUM_MOUSE_BUTTON_MIDDLE 1
#define OTIUM_MOUSE_BUTTON_RIGHT  2

#define OTIUM_KEY_UNKNOWN 0

#define OTIUM_KEY_A 4
#define OTIUM_KEY_B 5
#define OTIUM_KEY_C 6
#define OTIUM_KEY_D 7
#define OTIUM_KEY_E 8
#define OTIUM_KEY_F 9
#define OTIUM_KEY_G 10
#define OTIUM_KEY_H 11
#define OTIUM_KEY_I 12
#define OTIUM_KEY_J 13
#define OTIUM_KEY_K 14
#define OTIUM_KEY_L 15
#define OTIUM_KEY_M 16
#define OTIUM_KEY_N 17
#define OTIUM_KEY_O 18
#define OTIUM_KEY_P 19
#define OTIUM_KEY_Q 20
#define OTIUM_KEY_R 21
#define OTIUM_KEY_S 22
#define OTIUM_KEY_T 23
#define OTIUM_KEY_U 24
#define OTIUM_KEY_V 25
#define OTIUM_KEY_W 26
#define OTIUM_KEY_X 27
#define OTIUM_KEY_Y 28
#define OTIUM_KEY_Z 29

#define OTIUM_KEY_1 30
#define OTIUM_KEY_2 31
#define OTIUM_KEY_3 32
#define OTIUM_KEY_4 33
#define OTIUM_KEY_5 34
#define OTIUM_KEY_6 35
#define OTIUM_KEY_7 36
#define OTIUM_KEY_8 37
#define OTIUM_KEY_9 38
#define OTIUM_KEY_0 39

#define OTIUM_KEY_RETURN 40
#define OTIUM_KEY_ESCAPE 41
#define OTIUM_KEY_BACKSPACE 42
#define OTIUM_KEY_TAB 43
#define OTIUM_KEY_SPACE 44

#define OTIUM_KEY_MINUS 45
#define OTIUM_KEY_EQUALS 46
#define OTIUM_KEY_LEFTBRACKET 47
#define OTIUM_KEY_RIGHTBRACKET 48
#define OTIUM_KEY_BACKSLASH 49 

#define OTIUM_KEY_COMMA 54
#define OTIUM_KEY_PERIOD 55
#define OTIUM_KEY_SLASH 56

#define OTIUM_KEY_CAPSLOCK 57

#define OTIUM_KEY_F1 58
#define OTIUM_KEY_F2 59
#define OTIUM_KEY_F3 60
#define OTIUM_KEY_F4 61
#define OTIUM_KEY_F5 62
#define OTIUM_KEY_F6 63
#define OTIUM_KEY_F7 64
#define OTIUM_KEY_F8 65
#define OTIUM_KEY_F9 66
#define OTIUM_KEY_F10 67
#define OTIUM_KEY_F11 68
#define OTIUM_KEY_F12 69

#define OTIUM_KEY_PRINTSCREEN 70
#define OTIUM_KEY_SCROLLLOCK 71
#define OTIUM_KEY_PAUSE 72
#define OTIUM_KEY_INSERT 73 

#define OTIUM_KEY_HOME 74
#define OTIUM_KEY_PAGEUP 75
#define OTIUM_KEY_DELETE 76
#define OTIUM_KEY_END 77
#define OTIUM_KEY_PAGEDOWN 78
#define OTIUM_KEY_RIGHT 79
#define OTIUM_KEY_LEFT 80
#define OTIUM_KEY_DOWN 81
#define OTIUM_KEY_UP 82

#define OTIUM_KEY_NUMLOCKCLEAR 83

#define OTIUM_KEY_KP_DIVIDE 84
#define OTIUM_KEY_KP_MULTIPLY 85
#define OTIUM_KEY_KP_MINUS 86
#define OTIUM_KEY_KP_PLUS 87
#define OTIUM_KEY_KP_ENTER 88
#define OTIUM_KEY_KP_1 89
#define OTIUM_KEY_KP_2 90
#define OTIUM_KEY_KP_3 91
#define OTIUM_KEY_KP_4 92
#define OTIUM_KEY_KP_5 93
#define OTIUM_KEY_KP_6 94
#define OTIUM_KEY_KP_7 95
#define OTIUM_KEY_KP_8 96
#define OTIUM_KEY_KP_9 97
#define OTIUM_KEY_KP_0 98
#define OTIUM_KEY_KP_PERIOD 99

#define OTIUM_KEY_LCTRL 224
#define OTIUM_KEY_LSHIFT 225
#define OTIUM_KEY_LALT 226
#define OTIUM_KEY_LGUI 227
#define OTIUM_KEY_RCTRL 228
#define OTIUM_KEY_RSHIFT 229
#define OTIUM_KEY_RALT 230 
#define OTIUM_KEY_RGUI 231 

#include "fastdelegate/FastDelegate.h"

#include "Utilities.h"
#include "Renderer.h"
#include "Widget.h"
#include "Label.h"
#include "Button.h"

#endif