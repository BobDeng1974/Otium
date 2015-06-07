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

struct Form : public Otium::Widget
{
	Form(Otium::Size width, Otium::Size height)
		: Otium::Widget("ROOT")
	{
		SetDestination(0, 0, width, height);

		Otium::IManager* manager = Otium::IManager::Get();

		if (!manager)
			return;
		
		Otium::Window* wndTest = AddChild<Otium::Window>("wndTest");
		wndTest->SetSource(0, 130, 300, 270);
		wndTest->SetDestination(width / 2, height / 2, 300, 270);
		wndTest->SetAlignment(Otium::ALIGN_CENTER);
		wndTest->SetBorder(24);
		wndTest->GetText()->SetFont("../Data/verdana.ttf", 12);
		wndTest->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		wndTest->GetText()->SetString("Window");

		Otium::Button* btnTest = wndTest->AddChild<Otium::Button>("btnTest");
		btnTest->SetAlignment(Otium::ALIGN_CENTER);
		btnTest->SetDestination(150, 135, 71, 33);
		btnTest->SetSrcPosition(Otium::Button::STATE_DEFAULT, 0, 0);
		btnTest->SetSrcPosition(Otium::Button::STATE_HOVER, 0, 33);
		btnTest->SetSrcPosition(Otium::Button::STATE_ACTIVE, 0, 66);
		btnTest->SetSrcSize(71, 33);
		btnTest->GetText()->SetFont("../Data/verdana.ttf", 12);
		btnTest->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		btnTest->GetText()->SetString("Button");

		Otium::CheckBox* chkTest = wndTest->AddChild<Otium::CheckBox>("chkTest");
		chkTest->SetAlignment(Otium::ALIGN_CENTER);
		chkTest->SetDestination(150, 165, 16, 17);
		chkTest->SetSrcPosition(Otium::CheckBox::STATE_DEFAULT, 103, 0);
		chkTest->SetSrcPosition(Otium::CheckBox::STATE_ACTIVE,  119, 0);
		chkTest->SetSrcSize(16, 17);
		chkTest->GetText()->SetFont("../Data/verdana.ttf", 12);
		chkTest->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		chkTest->GetText()->SetString("CheckBox");

		Otium::RadioButton* radTest1 = wndTest->AddChild<Otium::RadioButton>("radTest1");
		radTest1->SetAlignment(Otium::ALIGN_CENTER);
		radTest1->SetDestination(20, 165, 16, 17);
		radTest1->SetSrcPosition(Otium::RadioButton::STATE_DEFAULT, 87, 0);
		radTest1->SetSrcPosition(Otium::RadioButton::STATE_ACTIVE,  71, 0);
		radTest1->SetSrcSize(16, 17);
		radTest1->GetText()->SetFont("../Data/verdana.ttf", 12);
		radTest1->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		radTest1->GetText()->SetString("RadioButton #1");
	
		Otium::RadioButton* radTest2 = wndTest->AddChild<Otium::RadioButton>("radTest2");
		radTest2->SetAlignment(Otium::ALIGN_CENTER);
		radTest2->SetDestination(20, 190, 16, 17);
		radTest2->SetSrcPosition(Otium::RadioButton::STATE_DEFAULT, 87, 0);
		radTest2->SetSrcPosition(Otium::RadioButton::STATE_ACTIVE,  71, 0);
		radTest2->SetSrcSize(16, 17);
		radTest2->GetText()->SetFont("../Data/verdana.ttf", 12);
		radTest2->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		radTest2->GetText()->SetString("RadioButton #2");

		Otium::Textbox* txtTest = wndTest->AddChild<Otium::Textbox>("txtTest");
		txtTest->SetAlignment(Otium::ALIGN_CENTER);
		txtTest->SetDestination(150, 60, 210, 31);
		txtTest->SetSource(0, 99, 210, 31);
		txtTest->GetText()->SetFont("../Data/verdana.ttf", 12);
		txtTest->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		txtTest->GetText()->SetString("Textbox");

		Otium::Textbox* txtTest2 = wndTest->AddChild<Otium::Textbox>("txtTest2");
		txtTest2->SetAlignment(Otium::ALIGN_CENTER);
		txtTest2->SetDestination(150, 100, 210, 31);
		txtTest2->SetSource(0, 99, 210, 31);
		txtTest2->GetText()->SetFont("../Data/verdana.ttf", 12);
		txtTest2->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		txtTest2->GetText()->SetString("Textbox2");
		txtTest2->GetText()->SetPasswordChar('*');

		Otium::Label* lblTest = wndTest->AddChild<Otium::Label>("lblTest");
		lblTest->SetDestination(150, 35, 0, 0);
		lblTest->GetText()->SetAlignment(Otium::ALIGN_CENTER);
		lblTest->GetText()->SetFont("../Data/verdana.ttf", 12);
		lblTest->GetText()->SetColor(manager->EncodeColor(255, 255, 255, 255));
		lblTest->GetText()->SetString("Label");
	
		Otium::Slider<Otium::HORIZONTAL>* hsdTest = wndTest->AddChild<Otium::Slider<Otium::HORIZONTAL>>("hsdTest");
		hsdTest->SetDestination(150 - 116, 210, 232, 10);
		hsdTest->SetSource(71, 31, 232, 10);
		hsdTest->SetPtrSource(71, 41, 14, 15);
		hsdTest->SetMaxValue(300);

		Otium::Slider<Otium::VERTICAL>* vsdTest = wndTest->AddChild<Otium::Slider<Otium::VERTICAL>>("vsdTest");
		vsdTest->SetDestination(300 - 20, 30, 9, 232);
		vsdTest->SetSource(303, 32, 9, 232);
		vsdTest->SetPtrSource(71, 41, 14, 15);
		vsdTest->SetMaxValue(300);
	}
};

#endif