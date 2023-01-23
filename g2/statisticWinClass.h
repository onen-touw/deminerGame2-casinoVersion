#pragma once

#include"interfaceObjects.h"

class statisticWinClass : public interfaceObjects
{
public:const short cancelBtn = 0;
private:
	short positionStartX = settingGGame::gSizes.winWIDTH / 2 - settingGGame::menuSetting.btnW / 2;
	short positionStartY = 50;
	std::vector< btnsStruct>btnsV = {
		{"������", {positionStartX, positionStartY * 9, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
	};
	SDL_Rect menuRect = { settingGGame::menuSetting.pading20, settingGGame::gSizes.menuHeaderHeight + settingGGame::menuSetting.pading20 ,
		settingGGame::gSizes.winWIDTH - 2 * settingGGame::menuSetting.pading20,
		settingGGame::gSizes.winHEIGHT - settingGGame::gSizes.menuHeaderHeight - 2 * settingGGame::menuSetting.pading20 };

	std::string text = "";

public:
	statisticWinClass(SDL_Surface* bgImg, SDL_Surface* btnImg, TTF_Font* font) :
		interfaceObjects(bgImg, btnImg, font) {
		this->btns = this->btnsV;
		this->objRect = this->menuRect;
	}
	~statisticWinClass()
	{
		this->text.clear();
		this->btnsV.clear();
	}

	void loadStatistic(std::vector<std::vector<int>> stat) {
		this->text = "����������:\n"
			"����� � ���� �� �������\n"
			"������ �������:\n"
			"������ �����: "+ std::to_string(stat[0][0]) + ";    ���������� ���������� �����: "+ std::to_string(stat[0][1]) + ";\n"
			"������� �������:\n"
			"������ �����: " + std::to_string(stat[1][0]) + ";    ���������� ���������� �����: " + std::to_string(stat[1][1]) + ";\n"
			"������� �������:\n"
			"������ �����: " + std::to_string(stat[2][0]) + ";    ���������� ���������� �����: " + std::to_string(stat[2][1]) + ";\n"
			"����\n";
	}

	void blit() {
		this->blitWithTxt(this->text.c_str());
		this->blitBtns();
		SDL_UpdateWindowSurface(settingGGame::win);
	}

};

