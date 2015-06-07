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
#ifndef OTIUM_TEST_FORM_H
#define OTIUM_TEST_FORM_H

namespace Otium
{

struct Form : public Widget
{
	Form(Size width, Size height)
		: Widget("ROOT")
	{
		SetDestination(0, 0, width, height);

		IManager* manager = IManager::Get();

		if (!manager)
			return;
		
		Window* wndTest = AddChild<Window>("wndTest");
		wndTest->SetSource(0, 130, 300, 270);
		wndTest->SetDestination(width / 2, height / 2, 300, 270);
		wndTest->SetAlignment(ALIGN_CENTER);
		wndTest->SetBorder(24);
		wndTest->GetText()->SetFont("../Data/verdana.ttf", 12);
		wndTest->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		wndTest->GetText()->SetString("Window");

		Button* btnTest = wndTest->AddChild<Button>("btnTest");
		btnTest->SetAlignment(ALIGN_CENTER);
		btnTest->SetDestination(150, 135, 71, 33);
		btnTest->SetSrcPosition(Button::STATE_DEFAULT, 0, 0);
		btnTest->SetSrcPosition(Button::STATE_HOVER, 0, 33);
		btnTest->SetSrcPosition(Button::STATE_ACTIVE, 0, 66);
		btnTest->SetSrcSize(71, 33);
		btnTest->GetText()->SetFont("../Data/verdana.ttf", 12);
		btnTest->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		btnTest->GetText()->SetString("Button");

		CheckBox* chkTest = wndTest->AddChild<CheckBox>("chkTest");
		chkTest->SetAlignment(ALIGN_CENTER);
		chkTest->SetDestination(150, 165, 16, 17);
		chkTest->SetSrcPosition(CheckBox::STATE_DEFAULT, 103, 0);
		chkTest->SetSrcPosition(CheckBox::STATE_ACTIVE,  119, 0);
		chkTest->SetSrcSize(16, 17);
		chkTest->GetText()->SetFont("../Data/verdana.ttf", 12);
		chkTest->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		chkTest->GetText()->SetString("CheckBox");

		RadioButton* radTest1 = wndTest->AddChild<RadioButton>("radTest1");
		radTest1->SetAlignment(ALIGN_CENTER);
		radTest1->SetDestination(20, 165, 16, 17);
		radTest1->SetSrcPosition(RadioButton::STATE_DEFAULT, 87, 0);
		radTest1->SetSrcPosition(RadioButton::STATE_ACTIVE,  71, 0);
		radTest1->SetSrcSize(16, 17);
		radTest1->GetText()->SetFont("../Data/verdana.ttf", 12);
		radTest1->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		radTest1->GetText()->SetString("RadioButton #1");
	
		RadioButton* radTest2 = wndTest->AddChild<RadioButton>("radTest2");
		radTest2->SetAlignment(ALIGN_CENTER);
		radTest2->SetDestination(20, 190, 16, 17);
		radTest2->SetSrcPosition(RadioButton::STATE_DEFAULT, 87, 0);
		radTest2->SetSrcPosition(RadioButton::STATE_ACTIVE,  71, 0);
		radTest2->SetSrcSize(16, 17);
		radTest2->GetText()->SetFont("../Data/verdana.ttf", 12);
		radTest2->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		radTest2->GetText()->SetString("RadioButton #2");

		Textbox* txtTest = wndTest->AddChild<Textbox>("txtTest");
		txtTest->SetAlignment(ALIGN_CENTER);
		txtTest->SetDestination(150, 60, 210, 31);
		txtTest->SetSource(0, 99, 210, 31);
		txtTest->GetText()->SetFont("../Data/verdana.ttf", 12);
		txtTest->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		txtTest->GetText()->SetString("Textbox");

		Textbox* txtTest2 = wndTest->AddChild<Textbox>("txtTest2");
		txtTest2->SetAlignment(ALIGN_CENTER);
		txtTest2->SetDestination(150, 100, 210, 31);
		txtTest2->SetSource(0, 99, 210, 31);
		txtTest2->GetText()->SetFont("../Data/verdana.ttf", 12);
		txtTest2->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		txtTest2->GetText()->SetString("Textbox2");
		txtTest2->GetText()->SetPasswordChar('*');

		Label* lblTest = wndTest->AddChild<Label>("lblTest");
		lblTest->SetDestination(150, 35, 0, 0);
		lblTest->GetText()->SetAlignment(ALIGN_CENTER);
		lblTest->GetText()->SetFont("../Data/verdana.ttf", 12);
		lblTest->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		lblTest->GetText()->SetString("Label");
	
		Slider<HORIZONTAL>* hsdTest = wndTest->AddChild<Slider<HORIZONTAL>>("hsdTest");
		hsdTest->SetDestination(150 - 116, 210, 232, 10);
		hsdTest->SetSource(71, 31, 232, 10);
		hsdTest->SetPtrSource(71, 41, 14, 15);
		hsdTest->SetMaxValue(300);

		Slider<VERTICAL>* vsdTest = wndTest->AddChild<Slider<VERTICAL>>("vsdTest");
		vsdTest->SetDestination(300 - 20, 30, 9, 232);
		vsdTest->SetSource(303, 32, 9, 232);
		vsdTest->SetPtrSource(71, 41, 14, 15);
		vsdTest->SetMaxValue(300);
	}
};

}

#endif