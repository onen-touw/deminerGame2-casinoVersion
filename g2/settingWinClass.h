#pragma once

#include "interfaceObjects.h"

class settingWinClass : public interfaceObjects
{


public: enum btnsEnum
{
	easy,
	normal,
	hard,
	apply,
	cancel,
};
private:
	short positionStartX = settingGGame::gSizes.winWIDTH / 2 - settingGGame::menuSetting.btnW / 2;
	short positionStartY = 50;
	std::vector< btnsStruct>btnsV = {
		{"ËÅÃÊÎ", {positionStartX,settingGGame::gSizes.menuHeaderHeight+ positionStartY, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
		{"ÍÎÐÌÀËÜÍÎ", {positionStartX,settingGGame::gSizes.menuHeaderHeight + positionStartY * 2, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
		{"ÑËÎÆÍÎ", {positionStartX,settingGGame::gSizes.menuHeaderHeight + positionStartY * 3, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
		{"ÏÐÈÍßÒÜ", {positionStartX,settingGGame::gSizes.menuHeaderHeight + positionStartY * 5, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
		{"ÎÒÌÅÍÀ", {positionStartX,settingGGame::gSizes.menuHeaderHeight + positionStartY * 6, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
	};
	SDL_Rect menuRect = { settingGGame::menuSetting.pading20, settingGGame::gSizes.menuHeaderHeight + settingGGame::menuSetting.pading20 ,
		settingGGame::gSizes.winWIDTH - 2 * settingGGame::menuSetting.pading20,
		settingGGame::gSizes.winHEIGHT - settingGGame::gSizes.menuHeaderHeight - 2 * settingGGame::menuSetting.pading20 };
	

	short tempHardness = settingGGame::hardnes;

	SDL_Surface* switchImg = nullptr;

	SDL_Rect switchRect = { int(positionStartX - 1.5 * settingGGame::menuSetting.btnH),
		(tempHardness + 1) * positionStartY + settingGGame::gSizes.menuHeaderHeight,
		settingGGame::menuSetting.btnH,settingGGame::menuSetting.btnH };

public:
	settingWinClass(SDL_Surface* bgImg, SDL_Surface* btnImg,SDL_Surface* switchImg, TTF_Font* font) :
		interfaceObjects(bgImg, btnImg, font) {
		this->btns = this->btnsV;
		this->objRect = this->menuRect;
		this->switchImg = switchImg;
	}
	~settingWinClass()
	{
		SDL_FreeSurface(this->switchImg);
	}

	void changeHardness(int i) {
		this->tempHardness = i;
		this->blit();
		SDL_UpdateWindowSurface(settingGGame::win);
	}
	void applyHardness() {
		settingGGame::hardnes= this->tempHardness;
	}
	void resetHardness() {
		this->tempHardness = settingGGame::hardnes;
	}

	void blit() {
		this->blitBg();
		this->blitBtns();
		this->switchRect.y = (tempHardness + 1) * positionStartY + settingGGame::gSizes.menuHeaderHeight;
		SDL_BlitScaled(this->switchImg, NULL, settingGGame::Surface, &switchRect);
		SDL_UpdateWindowSurface(settingGGame::win);
	}

};

