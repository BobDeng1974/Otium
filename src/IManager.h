#ifndef OTIUM_MANAGER_H
#define OTIUM_MANAGER_H

namespace Otium
{

class IManager
{
public:
	/**
		This method should get font if exist and load it from file if not exist.
	*/
	virtual Font GetFont(const char* name, FontSize size) = 0;

	virtual FontSize GetFontSize(Font font) = 0;

	/**
		This method should read size of image. If 'width' or 'height' is zero then dont read it parameter.
	*/
	virtual void ReadImageSize(Image image, SrcSize* width, SrcSize* height) = 0;

	virtual void FreeImage(Image image) = 0;

	virtual Image Write(Font font, const char* string, Color color) = 0;

	virtual void Render(Position x, Position y, Size w, Size h, SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh) = 0;

	virtual void RenderImage(Image image, Position x, Position y, Size w, Size h, SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh) = 0;

	virtual void RenderLine(Position x1, Position y1, Position x2, Position y2, Color color) = 0;

	static IManager*& Get()
	{
		static IManager* instance = 0;

		return instance;
	}

	static void Set(IManager* manager)
	{
		Get() = manager; // ^^
	}
};

}

#endif