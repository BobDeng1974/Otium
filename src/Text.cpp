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

Text::Text()
	: _font(0), _needRedraw(false), _image(0), _color(OTIUM_COLOR_ENCODE_ALPHA(255, 255, 255, 255))
{
}

Text::~Text()
{
	if (_image)
		GetManager()->FreeImage(_image);
}

void Text::Render(int32 x, int32 y)
{
	if (_needRedraw)
	{
		if (_image)
			GetManager()->FreeImage(_image);

		if (_text.size() > 0)
			_image = GetManager()->RenderFont(_font, _text.c_str(), 256, _color, &_srcWidth, &_srcHeight);
		else
		{
			_image = 0;
			_srcWidth = 0;
		}

		_needRedraw = false;
	}

	if (_image)
		GetManager()->RenderImage(_image, x, y, _srcWidth, _srcHeight, 0, 0, _srcWidth, _srcHeight);
}

}