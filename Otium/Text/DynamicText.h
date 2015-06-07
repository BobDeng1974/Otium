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
#ifndef OTIUM_DYNAMIC_TEXT_H
#define OTIUM_DYNAMIC_TEXT_H

#ifdef OTIUM_NO_STATIC_TEXT

namespace Otium
{

class DynamicText : public IText
{
private:
	std::basic_string<Codepoint> _password;

protected:	
	void OnStringChanged()
	{
		UpdatePassword(_password);
	}

public:
	DynamicText()
	{

	}

	virtual ~DynamicText()
	{
	}

	void Render(Position x, Position y)
	{
		IManager* manager = IManager::Get();
		if (IsNeedUpdate())
		{
			UpdatePassword(_password);

			SrcSize w, h;
			//manager->MeasureText(GetFont(), GetString(), &w, 0);
			//h = static_cast<SrcSize>(IManager::Get()->GetFontSize(GetFont()));
			Measure(&w, &h);

			UpdateOffsets(w, h);

			SetNeedUpdate(false);
		}

		const Codepoint* text = (GetPasswordChar() != 0) ? &_password[0] : GetString();

		manager->RenderText(GetFont(), text, x + GetOffsetX(), y + GetOffsetY(), GetColor());
	}
	
	void Measure(SrcSize* width, SrcSize* height)
	{
		if (width || height)
			IManager::Get()->MeasureText(GetFont(), (GetPasswordChar() != 0) ? &_password[0] : GetString(), width, height);
	}
};
typedef DynamicText Text;

}

#endif

#endif