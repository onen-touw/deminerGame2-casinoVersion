#pragma once

//#include"settings.h"
#include"imagesClass.h"
#include<string>


class menuClass : public imagesClass
{

private:
	bool menuFlag = false;
	Uint32 timer = 0;
	Uint32 timerPoint = 0;
	std::string gTime = "000";
	std::string timeTemp;
	std::string timeTemp2;

	unsigned stepCount = 0;
	std::string stepSCount = "000";
	std::string stepSTemp;

	std::vector<SDL_Rect> menuBtnCoords;

public:
	menuClass() {
		menuBtnCoords.resize(settingGGame::menuSetting.menuPuncts::menuPunctsTOTAL);
		SDL_Rect cr, mr;
		for (int i = 0; i < menuBtnCoords.size(); i++)
		{
			cr = {0, settingGGame::menuSetting.cropHeightImgBtn * i, 0, settingGGame::menuSetting.widthImgBtns};
			mr = {};
		}
	}
	~menuClass()
	{
		menuBtnCoords.clear();
	}

	bool getMenuFlag() { return menuFlag; }

	void toggleMEnuFlag() {
		if (menuFlag)
		{
			menuFlag = false;
		}
		else menuFlag = true;
	}

	///start timer point
	void setGTime() {
		timerPoint = SDL_GetTicks();
	}

	///счет времени
	Uint32 gTimer() {
		if (timerPoint != 0)
		{
			timer = ((SDL_GetTicks() - timerPoint) / 1000) /*+ timeFromSave*/;
			if (timer >= 999)
			{
				timer = 999;
			}
		}
		return timer;
	}
	
	///отрисовка таймера + оптимизация
	void blitGTime() {
		if (timer != 0)
		{
			timeTemp = std::to_string(timer);
			if (timeTemp.size() == 1)
			{
				gTime[2] = timeTemp[0];
			}
			else if (timeTemp.size() == 2)
			{
				gTime[1] = timeTemp[0];
				gTime[2] = timeTemp[1];
			}
			else
			{
				gTime = timeTemp;
			}
		}

		//оптимизация отрисовки
		if (gTime != timeTemp2)
		{
			timeTemp2 = gTime;
			for (int i = 0; i < gTime.size(); i++)
			{
				SDL_Rect motion_rect = { 200 + i * 30, settingGGame::menuSetting.menuPaddingTop , 30, 40 };
				SDL_Rect crop_rect = { 171 * (gTime[i] - '0'), 0 , 171, 300 };
				SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::numbers],
					&crop_rect, settingGGame::Surface, &motion_rect);
				SDL_UpdateWindowSurface(settingGGame::win);
			}
		}

	}

	bool checkOpenBtn(int x, int y) {
		if (x >= settingGGame::menuSetting.menuOpenBtnCoords.x &&
			x <= settingGGame::menuSetting.menuOpenBtnCoords.x + settingGGame::menuSetting.menuOpenBtnCoords.w &&
			y >= settingGGame::menuSetting.menuOpenBtnCoords.y &&
			y <= settingGGame::menuSetting.menuOpenBtnCoords.y + settingGGame::menuSetting.menuOpenBtnCoords.h)
		{
			return true;
		}
		else return false;
	}

	void blitHeader() {
		SDL_Rect mr = { 0, 0, settingGGame::gSizes.winWIDTH, settingGGame::gSizes.menuHeaderHeight };
		SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::headerAndBG],
			NULL, settingGGame::Surface, &mr);

		mr = settingGGame::menuSetting.menuOpenBtnCoords;
		SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::menuOpenBtn],
			NULL, settingGGame::Surface, &mr);
	}

	void blitHP(unsigned countHP) {
		SDL_Rect mr = { settingGGame::gSizes.winWIDTH - 100, settingGGame::menuSetting.menuPaddingTop, 40 * settingGGame::charctData.healthPoint , 40 };
		SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::headerAndBG],
			NULL, settingGGame::Surface, &mr);
		if (countHP > 0)
		{
			for (int i = 0; i < countHP; i++)
			{
				mr = { settingGGame::gSizes.winWIDTH - 100 + i * 40,settingGGame::menuSetting.menuPaddingTop, 40 , 40 };
				SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::hearts],
					NULL, settingGGame::Surface, &mr);
			}
		};
	} 

	void increaseStepCount() {
		this->stepCount++;
	}

	void blitStepCounter() {

		stepSTemp = std::to_string(stepCount);

		if (stepSTemp.size() == 1)
		{
			stepSCount[2] = stepSTemp[0];
		}
		else if (stepSTemp.size() == 2)
		{
			
			stepSCount[1] = stepSTemp[0];
			stepSCount[2] = stepSTemp[1];
		}
		else {
			stepSCount = stepSTemp;
		}

		for (int i = 0; i < stepSCount.size(); i++)
		{
			SDL_Rect mr = { 500 + i * 30, settingGGame::menuSetting.menuPaddingTop , 30, 40 };
			SDL_Rect cr = { 171 * (stepSCount[i] - '0'), 0 , 171, 300 };
			SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::numbers], &cr, settingGGame::Surface, &mr);

		}
		
	}

	void blitMenuHeaderFunctional() {
		blitHeader();
		blitHP(settingGGame::charctData.healthPoint);
		blitStepCounter();
		blitGTime();
	}

	///отрисовка окна "menu" (update - для единичного вызова в игровом цикле и обновления)
	///false - для первого вызова
	void blitWinMenu(bool update) {
		static int v = 0;
		std::cout << v << " vvv\n";
		if (v == 0 && !update)
		{
			SDL_Rect mr = { settingGGame::gSizes.winWIDTH / 2 - settingGGame::gSizes.winWIDTH / 4,
				settingGGame::menuSetting.menuPaddingTop + settingGGame::gSizes.menuHeaderHeight,
				settingGGame::gSizes.winWIDTH / 2,
				settingGGame::gSizes.winHEIGHT - settingGGame::gSizes.menuHeaderHeight -2* settingGGame::menuSetting.menuPaddingTop
			};
			SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::headerAndBG],
				NULL, settingGGame::Surface, &mr);
			SDL_UpdateWindowSurface(settingGGame::win);
			v++;

		}
		else if (v > 0 && !update)
		{
			return;
		}
		else if (v > 0 && update)
		{
			v = 0;
			return;
		}
	}



};

