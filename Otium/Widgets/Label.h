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
#ifndef OTIUM_LABEL_H
#define OTIUM_LABEL_H

namespace Otium
{

class Label : public Widget
{
OTIUM_DECL_INTERNAL_ID(Label);

private:
	Text _text;

public:
	Label(const char* name)
		: Widget(name)
	{
	}

	virtual ~Label()
	{
	}
	
	/* override */
	void OnRender()
	{
		_text.Render(GetAbsX(), GetAbsY());
	}


	inline Text* GetText() { return &_text; }
};

}

#endif