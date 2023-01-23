#pragma once

#include "interfaceObjects.h"

class menuClass : public interfaceObjects
{
public:/*const*/ enum btnsEnum
	{
		settingBtn,
		aboutBtn,
		statBtn,
		cancelGame,
		quitBtn,
	};
private:
	short positionStartX = settingGGame::gSizes.winWIDTH / 2 - settingGGame::menuSetting.btnW / 2;
	short positionStartY = 50;
	std::vector< btnsStruct>btnsV = {
		{"ÍÎÂÀß ÈÃÐÀ", {positionStartX,settingGGame::gSizes.menuHeaderHeight+ positionStartY, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
		{"ÎÁ ÈÃÐÅ", {positionStartX,settingGGame::gSizes.menuHeaderHeight+ positionStartY*2, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
		{"ÑÒÀÒÈÑÒÈÊÀ", {positionStartX,settingGGame::gSizes.menuHeaderHeight+ positionStartY * 3, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
		{"ÎÒÌÅÍÀ", {positionStartX, settingGGame::gSizes.menuHeaderHeight+positionStartY * 4, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
		{"ÂÛÕÎÄ", {positionStartX,settingGGame::gSizes.menuHeaderHeight+positionStartY * 5, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
	};
	SDL_Rect menuRect = { settingGGame::menuSetting.pading20, settingGGame::gSizes.menuHeaderHeight + settingGGame::menuSetting.pading20 ,
		settingGGame::gSizes.winWIDTH - 2 * settingGGame::menuSetting.pading20,
		settingGGame::gSizes.winHEIGHT - settingGGame::gSizes.menuHeaderHeight - 2 * settingGGame::menuSetting.pading20 };
	
public:
	menuClass(SDL_Surface* bgImg, SDL_Surface* btnImg, TTF_Font* font) :
		interfaceObjects(bgImg, btnImg, font) {
		this->btns = this->btnsV;
		this->objRect = this->menuRect;
	}
	~menuClass()
	{

	}
	void blit() {
		this->blitBg();
		this->blitBtns();
		SDL_UpdateWindowSurface(settingGGame::win);
	}
};

