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
#ifndef OTIUM_TEXTBOX_H
#define OTIUM_TEXTBOX_H

namespace Otium
{
class Textbox : public Widget
{
private:
	int32 _srcX;
	int32 _srcY;
	int32 _srcWidth;
	int32 _srcHeight;

	Text _text;
	int32 _textOffset;

public:
	Textbox();

	virtual ~Textbox();

	void OnUpdate(float32 deltaTime);

	void OnRender();

	inline void SetSrcX(int32 srcX) { _srcX = srcX; }
	inline void SetSrcY(int32 srcY) { _srcY = srcY; }
	inline void SetSrcWidth(int32 srcWidth) { _srcWidth = srcWidth; }
	inline void SetSrcHeight(int32 srcHeight) { _srcHeight = srcHeight; }
	inline void SetSource(int32 srcX, int32 srcY, int32 srcWidth, int32 srcHeight) { SetSrcX(srcX); SetSrcY(srcY); SetSrcWidth(srcWidth); SetSrcHeight(srcHeight); }
	inline void SetTextOffset(int32 offset) { _textOffset = offset; }

	inline int32 GetSrcX() const { return _srcX; }
	inline int32 GetSrcY() const { return _srcY; }
	inline int32 GetSrcWidth() const { return _srcWidth; }
	inline int32 GetSrcHeight() const { return _srcHeight; }
	inline int32 GetTextOffset() const { return _textOffset; }

	inline Text* GetText() { return &_text; }
};
}

#endif