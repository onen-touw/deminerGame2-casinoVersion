#pragma once

//#include"settings.h"
#include"imagesClass.h"
#include<string>



class headerClass : public imagesClass
{

private:
	bool menuFlag = false;
	int menu2Lvl = 0;

	Uint32 timer = 0;
	Uint32 timerPoint = 0;
	std::string gTime = "000";
	std::string timeTemp;
	std::string timeTemp2;

	unsigned stepCount = 0;
	std::string stepSCount = "000";
	std::string stepSTemp;

	int tempHardnesSetting = settingGGame::hardnes;

public:
	headerClass() {

	}
	~headerClass()
	{
	
	}

	void resetTimerAndCounter() {
		this->timer = 0;
		this->timerPoint = 0;

		this->stepCount = 0;
		this-> gTime = "000";
		this->stepSCount = "000";
	}

	///start timer point
	void setGTime() {
		timerPoint = SDL_GetTicks();
	}

	int getTime() { return this->timer; }
	int getSteps() { return this->stepCount; }

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
				SDL_Rect motion_rect = { 200 + i * 30, settingGGame::headerSetting.menuPaddingTop , 30, 40 };
				SDL_Rect crop_rect = { 171 * (gTime[i] - '0'), 0 , 171, 300 };
				SDL_BlitScaled(images[settingGGame::headerSetting.headerImg::numbers],
					&crop_rect, settingGGame::Surface, &motion_rect);
				SDL_UpdateWindowSurface(settingGGame::win);
			}
		}

	}

	bool checkOpenBtn(int x, int y) {
		if (x >= settingGGame::headerSetting.menuOpenBtnCoords.x &&
			x <= settingGGame::headerSetting.menuOpenBtnCoords.x + settingGGame::headerSetting.menuOpenBtnCoords.w &&
			y >= settingGGame::headerSetting.menuOpenBtnCoords.y &&
			y <= settingGGame::headerSetting.menuOpenBtnCoords.y + settingGGame::headerSetting.menuOpenBtnCoords.h)
		{
			return true;
		}
		else return false;
	}

	void blitHeader() {
		SDL_Rect mr = { 0, 0, settingGGame::gSizes.winWIDTH, settingGGame::gSizes.menuHeaderHeight };
		SDL_BlitScaled(images[settingGGame::headerSetting.headerImg::headerAndBG],
			NULL, settingGGame::Surface, &mr);

		mr = settingGGame::headerSetting.menuOpenBtnCoords;
		SDL_BlitScaled(images[settingGGame::headerSetting.headerImg::menuOpenBtn],
			NULL, settingGGame::Surface, &mr);
	}

	void blitHP(unsigned countHP) {
		SDL_Rect mr = { settingGGame::gSizes.winWIDTH - 100, settingGGame::headerSetting.menuPaddingTop, 40 * settingGGame::charctData.healthPoint , 40 };
		SDL_BlitScaled(images[settingGGame::headerSetting.headerImg::headerAndBG],
			NULL, settingGGame::Surface, &mr);
		if (countHP > 0)
		{
			for (int i = 0; i < countHP; i++)
			{
				mr = { settingGGame::gSizes.winWIDTH - 100 + i * 40,settingGGame::headerSetting.menuPaddingTop, 40 , 40 };
				SDL_BlitScaled(images[settingGGame::headerSetting.headerImg::hearts],
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
			SDL_Rect mr = { 500 + i * 30, settingGGame::headerSetting.menuPaddingTop , 30, 40 };
			SDL_Rect cr = { 171 * (stepSCount[i] - '0'), 0 , 171, 300 };
			SDL_BlitScaled(images[settingGGame::headerSetting.headerImg::numbers], &cr, settingGGame::Surface, &mr);

		}
		
	}

	void blitMenuHeaderFunctional() {
		blitHeader();
		blitHP(settingGGame::charctData.healthPoint);
		blitStepCounter();
		blitGTime();
	}

	//void blitMenuBG() {
	//	SDL_Rect mr = { settingGGame::gSizes.winWIDTH / 2 - settingGGame::gSizes.winWIDTH / 4,
	//			settingGGame::menuSetting.menuPaddingTop + settingGGame::gSizes.menuHeaderHeight,
	//			settingGGame::gSizes.winWIDTH / 2,
	//			settingGGame::gSizes.winHEIGHT - settingGGame::gSizes.menuHeaderHeight - 2 * settingGGame::menuSetting.menuPaddingTop
	//	};
	//	SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::headerAndBG],
	//		NULL, settingGGame::Surface, &mr);
	//}

	/////отрисовка окна "menu" (update - для единичного вызова в игровом цикле и обновления)
	//void blitWinMenu(bool update) {
	//	static int v = 0;
	//	std::cout << v << " vvv\n";
	//	if (v == 0 && !update)
	//	{
	//		blitMenuBG();

	//		for (int i = 0; i < menuBtnCoords.size(); i++)
	//		{
	//			SDL_Rect mr = { 0, settingGGame::menuSetting.cropHeightImgBtn * i,
	//				settingGGame::menuSetting.widthImgBtns,
	//				settingGGame::menuSetting.cropHeightImgBtn
	//			};
	//			SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::menuFirstLvlBtns], 
	//				&mr, settingGGame::Surface, &menuBtnCoords[i]);

	//		}
	//		SDL_UpdateWindowSurface(settingGGame::win);

	//		v++;

	//	}
	//	else if (v > 0 && !update)
	//	{
	//		return;
	//	}
	//	else if (v > 0 && update)
	//	{
	//		v = 0;
	//		return;
	//	}
	//}

	//void setNewHardnessSetting() {
	//	settingGGame::hardnes = this->tempHardnesSetting;
	//	std::cout << settingGGame::hardnes << " << newGAme\n";
	//}

	//void blitWinSettings(bool update) {

	//	static int v = 0;
	//	std::cout << v << " vvv\n";
	//	if (v == 0 && !update)
	//	{
	//		menu2Lvl = settingGGame::menuSetting.menu2lvlPuncts::settingsP;
	//		blitMenuBG();

	//		for (int i = 0; i < settingBtnCoords.size(); i++)
	//		{
	//			SDL_Rect cr = { 0, settingGGame::menuSetting.cropHeightImgBtn * i,
	//				settingGGame::menuSetting.widthImgBtns,
	//				settingGGame::menuSetting.cropHeightImgBtn
	//			};
	//			SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::menuSettingsBtns],
	//			&cr, settingGGame::Surface, &settingBtnCoords[i]);

	//			//SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::yellowSwitch], NULL, settingGGame::Surface, &settingSwitchCoords[i]);
	//		}

	//		this->blitRedSwich(this->tempHardnesSetting);
	//		blitRootBtn(settingGGame::menuSetting.rootBtn::accept);
	//		blitRootBtn(settingGGame::menuSetting.rootBtn::cancel);
	//		std::cout << "settings\n";
	//		v++;
	//	}
	//	else if (v > 0 && !update)
	//	{
	//		return;
	//	}
	//	else if (v > 0 && update)
	//	{
	//		v = 0;
	//		return;
	//	}
	//}

	//void blitWinAbout(bool update) {

	//	static int v = 0;
	//	std::cout << v << " vvv\n";
	//	if (v == 0 && !update)
	//	{
	//		menu2Lvl = settingGGame::menuSetting.menu2lvlPuncts::aboutP;

	//		blitMenuBG();
	//		blitRootBtn(settingGGame::menuSetting.rootBtn::cancel);
	//		std::cout << "About\n";
	//		v++;
	//	}
	//	else if (v > 0 && !update)
	//	{
	//		return;
	//	}
	//	else if (v > 0 && update)
	//	{
	//		v = 0;
	//		return;
	//	}
	//}


};

