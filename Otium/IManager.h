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

	/**
		Return Font size
	*/
	virtual FontSize GetFontSize(Font font) = 0;

	/**
		This method should read size of image. If 'width' or 'height' is zero then dont read it parameter.
	*/
	virtual void ReadImageSize(Image image, SrcSize* width, SrcSize* height) = 0;

	/**
		Free allocated IMAGE.
	*/
	virtual void FreeImage(Image image) = 0;

#ifndef OTIUM_NO_STATIC_TEXT
	/*
		Methods available when IManager support PRERENDERED text.
	*/

	/**
		Create and return IMAGE with rendered text.
	*/
	virtual Image Write(Font font, const Codepoint* string, Color color) = 0;
#else
	/*
		Methods available when IManager doesn't support PRERENDERED text.
	*/

	virtual void MeasureText(Font font, const Codepoint* string, SrcSize* width, SrcSize* height) = 0;

	virtual void RenderText(Font font, const Codepoint* string, Position x, Position y, Color color) = 0;
#endif

	virtual void GetGlyphAdvance(Font font, Codepoint codepoint, Size* advance) = 0;

	virtual void GetGlyphKerning(Font font, Codepoint first, Codepoint second, Size* kerning) = 0;

	/**
		RenderImage(SKIN, x, y, w, h, sx, sy, sw, sh);
	*/	
	virtual void Render(Position x, Position y, Size w, Size h, SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh) = 0;

	/**
		Render image to screen with specifed destination and source.
	*/
	virtual void RenderImage(Image image, Position x, Position y, Size w, Size h, SrcPosition sx, SrcPosition sy, SrcSize sw, SrcSize sh) = 0;

	virtual void RenderLine(Position x1, Position y1, Position x2, Position y2, Color color) = 0;

#ifndef OTIUM_NO_SCISSOR_TEST
	/**
		Push CURRENT scissor box (wherever you want) and set NEW scissor box.
		If CURRENT scissor box is dont exist push EMPTY box.

		Example:
		if (ScissorIsEnabled())
			_scissor_boxes.push_back(GetCurrentScissorBox());
		else
			_scissor_boxes.push_back(Rectangle(0, 0, 0, 0));
		SetNewScissorBox(Rectangle(x, y, w, h));
	*/
	virtual void PushClipRect(Position x, Position y, Size w, Size h) = 0;

	/**
		Pop LATEST scissor box and set it scissor box.
		If LATEST scissor box is EMPTY then disable scissor test(or set scissor box at viewport rect).

		Example:
		Rectangle rect = _scissor_boxes.back();
		if (rect.w > 0 && rect.h > && h)
			SetNewScissorBox(rect);
		else
		    DisableScissorBox();
	*/
	virtual void PopClipRect() = 0;
#endif

	virtual Color EncodeColor(uint8 r, uint8 g, uint8 b, uint8 a) = 0;

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