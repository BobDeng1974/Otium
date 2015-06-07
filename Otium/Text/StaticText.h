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
#ifndef OTIUM_STATIC_TEXT_H
#define OTIUM_STATIC_TEXT_H

#ifndef OTIUM_NO_STATIC_TEXT

namespace Otium
{

class StaticText : public IText
{
private:
	Image _image;

protected:
	void OnStringChanged()
	{
		// nothing to do here
	}

public:
	StaticText()
		: _image(nullptr)
	{

	}

	virtual ~StaticText()
	{
		if (_image)
			IManager::Get()->FreeImage(_image);
	}

	void Render(Position x, Position y)
	{
		IManager* manager = IManager::Get();
		if (IsNeedUpdate())
		{
			if (_image)
			{
				manager->FreeImage(_image);
				_image = nullptr;
			}

			if (GetFont())
			{
				if (GetPasswordChar() != 0)
				{
					std::basic_string<Codepoint> password;
					UpdatePassword(password);
					_image = manager->Write(GetFont(), &password[0], GetColor()); 
				}
				else
					_image = manager->Write(GetFont(), GetString(), GetColor()); 
			}
			
			if (_image)
			{
				SrcSize w, h;
				manager->ReadImageSize(_image, &w, &h);

				UpdateOffsets(w, h);
			}

			SetNeedUpdate(false);
		}

		if (_image)
		{
			SrcSize w, h;
			manager->ReadImageSize(_image, &w, &h);

			manager->RenderImage(_image, x + GetOffsetX(), y + GetOffsetY(), static_cast<Size>(w), static_cast<Size>(h), static_cast<SrcPosition>(0), static_cast<SrcPosition>(0), w, h);
		}
	}
	
	void Measure(SrcSize* width, SrcSize* height)
	{
		if (width || height)
		{
			if (_image)
				IManager::Get()->ReadImageSize(_image, width, height);
			else
			{
				if (width)  *width = 0;
				if (height) *height = 0;
			}
		}
	}

	inline Image GetImage() const { return _image; }
};
typedef StaticText Text;

}

#endif

#endif