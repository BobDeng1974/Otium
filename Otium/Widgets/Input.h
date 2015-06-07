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
#ifndef OTIUM_INPUT_H
#define OTIUM_INPUT_H

namespace Otium
{


class Input : public Widget
{
OTIUM_DECL_INTERNAL_ID(Input);
public:
	std::function<void(Widget*, Position, Position)> Click;

private:
	Text* _text;

public:
	Input(const char* name)
		: Widget(name)
	{
		_text = new Text();
	}

	virtual ~Input()
	{
		delete _text;
	}

	inline Text* GetText() const { return _text; }
};

}

#endif