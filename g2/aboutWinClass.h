#pragma once

#include"interfaceObjects.h"

class aboutWinClass : public interfaceObjects
{
public:const short cancelBtn = 0;
private:
	short positionStartX = settingGGame::gSizes.winWIDTH / 2 - settingGGame::menuSetting.btnW / 2;
	short positionStartY = 50;
	std::vector< btnsStruct>btnsV = {
		{"ÎÒÌÅÍÀ", {positionStartX, positionStartY * 9, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
	};
	SDL_Rect menuRect = { settingGGame::menuSetting.pading20, settingGGame::gSizes.menuHeaderHeight + settingGGame::menuSetting.pading20 ,
		settingGGame::gSizes.winWIDTH - 2* settingGGame::menuSetting.pading20,
		settingGGame::gSizes.winHEIGHT - settingGGame::gSizes.menuHeaderHeight -2* settingGGame::menuSetting.pading20 };

	std::string text = "ÍÅÊËÀÑÑÈ×ÅÑÊÈÉ ÑÀÏÅÐ\n\n"
		"Ðàçðàáîòàë ñòóäåí ÁÃÒÓ \" Âîåíìåõ\" Êóðî÷êèí À.Ñ.  - À811Ñ\n\n"
		"Öåëü ñîçäàíèÿ ðàáîòû - êóðñîâàÿ ðàáîòà ñòóäåíòà\n";

public:
	aboutWinClass(SDL_Surface* bgImg, SDL_Surface* btnImg, TTF_Font* font) :
		interfaceObjects(bgImg, btnImg, font) {
		this->btns = this->btnsV;
		this->objRect = this->menuRect;
	}
	~aboutWinClass()
	{
		text.clear();
		btnsV.clear();
	}
	void blit() {
		this->blitWithTxt(this->text.c_str());
		this->blitBtns();
		SDL_UpdateWindowSurface(settingGGame::win);
	}

};

