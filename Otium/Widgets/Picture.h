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
#ifndef OTIUM_PICTURE_H
#define OTIUM_PICTURE_H

namespace Otium
{

class Picture : public Widget
{
OTIUM_DECL_INTERNAL_ID(Picture);
private:
	Image _image;

public:
	Picture(const char* name)
		: Widget(name), _image(0)
	{
	}

	virtual ~Picture()
	{
	}
	
	/* override */
	void OnRender()
	{
		if (_image)
			IManager::Get()->RenderImage(_image, GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), static_cast<SrcPosition>(0), static_cast<SrcPosition>(0), static_cast<SrcSize>(GetWidth()), static_cast<SrcSize>(GetHeight()));
	}

	inline void SetImage(Image image) { _image = image; }

	inline Image GetImage() const { return _image; }
};

}

#endif