#ifndef OTIUM_PICTURE_H
#define OTIUM_PICTURE_H

namespace Otium
{

class Picture : public Widget
{
private:
	Image _image;

public:
	Picture()
		: _image(0)
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