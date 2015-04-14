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
Textbox::Textbox()
	: _textOffset(0)
{
}

Textbox::~Textbox()
{
}

void Textbox::OnUpdate(float32 deltaTime)
{
		
}

void Textbox::OnRender()
{
	GetManager()->RenderCopy(GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), GetSrcX(), GetSrcY(), GetSrcWidth(), GetSrcHeight());

	_text.Render(_textOffset + GetAbsX(), GetAbsY() + GetSrcHeight() / 2 - _text.GetSrcHeight() / 2);

	if (IsFocus())
		GetManager()->RenderLine(_textOffset + GetAbsX() + _text.GetSrcWidth(), GetAbsY() + GetSrcHeight() / 2 - _text.GetSrcHeight() / 2,_textOffset + GetAbsX() +  _text.GetSrcWidth(), GetAbsY() + GetSrcHeight() / 2 + _text.GetSrcHeight() / 2);
}
}