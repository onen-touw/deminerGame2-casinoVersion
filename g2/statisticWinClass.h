#pragma once

#include"interfaceObjects.h"

class statisticWinClass : public interfaceObjects
{
public:const short cancelBtn = 0;
private:
	short positionStartX = settingGGame::gSizes.winWIDTH / 2 - settingGGame::menuSetting.btnW / 2;
	short positionStartY = 50;
	std::vector< btnsStruct>btnsV = {
		{"ОТМЕНА", {positionStartX, positionStartY * 9, settingGGame::menuSetting.btnW, settingGGame::menuSetting.btnH}},
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
		this->text = "Статистика:\n"
			"Время и шаги не связаны\n"
			"Легкий уровень:\n"
			"Лучшее время: "+ std::to_string(stat[0][0]) + ";    Наименьшее количество шагов: "+ std::to_string(stat[0][1]) + ";\n"
			"Средний уровень:\n"
			"Лучшее время: " + std::to_string(stat[1][0]) + ";    Наименьшее количество шагов: " + std::to_string(stat[1][1]) + ";\n"
			"Сложный уровень:\n"
			"Лучшее время: " + std::to_string(stat[2][0]) + ";    Наименьшее количество шагов: " + std::to_string(stat[2][1]) + ";\n"
			"ВОТЬ\n";
	}

	void blit() {
		this->blitWithTxt(this->text.c_str());
		this->blitBtns();
		SDL_UpdateWindowSurface(settingGGame::win);
	}

};

