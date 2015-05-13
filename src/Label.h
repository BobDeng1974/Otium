#ifndef OTIUM_LABEL_H
#define OTIUM_LABEL_H

namespace Otium
{

class Label : public Widget
{
private:
	Text _text;

public:
	Label()
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