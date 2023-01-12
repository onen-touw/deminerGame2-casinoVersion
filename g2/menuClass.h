#pragma once

//#include"settings.h"
#include"imagesClass.h"
#include<string>



class menuClass : public imagesClass
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

	std::vector<SDL_Rect> menuBtnCoords;

	std::vector<SDL_Rect> settingBtnCoords;
	std::vector<SDL_Rect> settingSwitchCoords;
	std::vector<SDL_Rect> rootBtnCoords;

	int tempHardnesSetting = settingGGame::hardnes;

public:
	menuClass() {
		menuBtnCoords.resize(settingGGame::menuSetting.menuPuncts::menuPunctsTOTAL);
		SDL_Rect mr;
		for (int i = 0; i < menuBtnCoords.size(); i++)
		{
			
			mr = { settingGGame::gSizes.winWIDTH / 2 -  settingGGame::menuSetting.widthImgBtns / 2,
				(settingGGame::menuSetting.heightImgBtn+5)* i+settingGGame::menuSetting.menuPaddingTop*2 + settingGGame::gSizes.menuHeaderHeight,
				settingGGame::menuSetting.widthImgBtns,
				settingGGame::menuSetting.heightImgBtn
			};
			menuBtnCoords[i] = mr;
		}
		settingBtnCoords.resize(settingGGame::menuSetting.menuSettingPuncts::menuSettingPunctsTOTAL);
		settingSwitchCoords.resize(settingGGame::menuSetting.menuSettingPuncts::menuSettingPunctsTOTAL);
		for (int i = 0; i < settingBtnCoords.size(); i++)
		{
			mr = { settingGGame::gSizes.winWIDTH / 2 - settingGGame::menuSetting.widthImgBtns / 2 + 100,
				(settingGGame::menuSetting.heightImgBtn+5) * i + settingGGame::menuSetting.menuPaddingTop * 2 + settingGGame::gSizes.menuHeaderHeight,
				settingGGame::menuSetting.widthImgBtns-100,
				settingGGame::menuSetting.heightImgBtn };
			settingBtnCoords[i] = mr;

			mr = { settingGGame::gSizes.winWIDTH / 2 - settingGGame::menuSetting.widthImgBtns / 2 - 20,
				(settingGGame::menuSetting.heightImgBtn + 5) * i + settingGGame::menuSetting.menuPaddingTop * 2 + settingGGame::gSizes.menuHeaderHeight,
				settingGGame::menuSetting.heightImgBtn, 
				settingGGame::menuSetting.heightImgBtn
			};
			settingSwitchCoords[i] = mr;
		}
		rootBtnCoords.resize(settingGGame::menuSetting.rootTOTAL);
		for (int i = 0; i < settingGGame::menuSetting.rootTOTAL; i++) {
			mr = { settingGGame::gSizes.winWIDTH / 2 - settingGGame::menuSetting.widthImgBtns / 2 + settingGGame::menuSetting.widthImgBtns / 2 * i,
			500,
			settingGGame::menuSetting.widthImgBtns / 2,
			settingGGame::menuSetting.heightImgBtn / 2
			};
			rootBtnCoords[i] = mr;
		}
	}
	~menuClass()
	{
		menuBtnCoords.clear();
		settingBtnCoords.clear();
		settingSwitchCoords.clear();
		rootBtnCoords.clear();
	}

	std::vector<SDL_Rect>getSettingBtnsCoords() { return this->settingBtnCoords; }
	std::vector<SDL_Rect>getRootBtnsCoords() { return this->rootBtnCoords; }

	void changeHardnesSetting(int i) {
		if (i == 0)
		{
			this->tempHardnesSetting = settingGGame::hardnes;

		}
		else
		{
			this->tempHardnesSetting = i;

		}
		std::cout << this->tempHardnesSetting << "\n";
	}

	void blitRedSwich(int i) {
		for (int i = 0; i < settingBtnCoords.size(); i++)
		{
			SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::yellowSwitch], NULL, settingGGame::Surface, &settingSwitchCoords[i]);

		}
		SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::redSwitch], NULL, settingGGame::Surface, &settingSwitchCoords[i]);
	}

	void blitRootBtn(int i) {
		SDL_Rect cr;
		 cr = {0,  settingGGame::menuSetting.cropHeightImgBtn * i,
					settingGGame::menuSetting.widthImgBtns,
					settingGGame::menuSetting.cropHeightImgBtn 
		 };
		 SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::rootBtn], &cr, settingGGame::Surface, &rootBtnCoords[i]);
	}

	int btnParse(int x, int y, std::vector<SDL_Rect>vect) {
		for (int i = 0; i < vect.size(); i++)
		{
			if (x>= vect[i].x && x<= vect[i].x+vect[i].w && y >= vect[i].y && y <= vect[i].y + vect[i].h)
			{
				return i;
			}
		}
		return -1;
	}

	bool getMenuFlag() { return menuFlag; }
	int getMenu2Lvl() { return this->menu2Lvl; }
	void goTo1Lvl() { this->menu2Lvl = settingGGame::menuSetting.menu2lvlPuncts::goTo1lvl; }

	std::vector<SDL_Rect> getMenuBtnCoords() { return this->menuBtnCoords; }

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

	void blitMenuBG() {
		SDL_Rect mr = { settingGGame::gSizes.winWIDTH / 2 - settingGGame::gSizes.winWIDTH / 4,
				settingGGame::menuSetting.menuPaddingTop + settingGGame::gSizes.menuHeaderHeight,
				settingGGame::gSizes.winWIDTH / 2,
				settingGGame::gSizes.winHEIGHT - settingGGame::gSizes.menuHeaderHeight - 2 * settingGGame::menuSetting.menuPaddingTop
		};
		SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::headerAndBG],
			NULL, settingGGame::Surface, &mr);
	}

	///отрисовка окна "menu" (update - для единичного вызова в игровом цикле и обновления)
	void blitWinMenu(bool update) {
		static int v = 0;
		std::cout << v << " vvv\n";
		if (v == 0 && !update)
		{
			blitMenuBG();

			for (int i = 0; i < menuBtnCoords.size(); i++)
			{
				SDL_Rect mr = { 0, settingGGame::menuSetting.cropHeightImgBtn * i,
					settingGGame::menuSetting.widthImgBtns,
					settingGGame::menuSetting.cropHeightImgBtn
				};
				SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::menuFirstLvlBtns], 
					&mr, settingGGame::Surface, &menuBtnCoords[i]);

			}
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

	void setNewHardnessSetting() {
		settingGGame::hardnes = this->tempHardnesSetting;
		std::cout << settingGGame::hardnes << " << newGAme\n";
	}

	void blitWinSettings(bool update) {

		static int v = 0;
		std::cout << v << " vvv\n";
		if (v == 0 && !update)
		{
			menu2Lvl = settingGGame::menuSetting.menu2lvlPuncts::settingsP;
			blitMenuBG();

			for (int i = 0; i < settingBtnCoords.size(); i++)
			{
				SDL_Rect cr = { 0, settingGGame::menuSetting.cropHeightImgBtn * i,
					settingGGame::menuSetting.widthImgBtns,
					settingGGame::menuSetting.cropHeightImgBtn
				};
				SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::menuSettingsBtns],
				&cr, settingGGame::Surface, &settingBtnCoords[i]);

				//SDL_BlitScaled(images[settingGGame::menuSetting.menuImg::yellowSwitch], NULL, settingGGame::Surface, &settingSwitchCoords[i]);
			}

			this->blitRedSwich(this->tempHardnesSetting);
			blitRootBtn(settingGGame::menuSetting.rootBtn::accept);
			blitRootBtn(settingGGame::menuSetting.rootBtn::cancel);
			std::cout << "settings\n";
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

	void blitWinAbout(bool update) {

		static int v = 0;
		std::cout << v << " vvv\n";
		if (v == 0 && !update)
		{
			menu2Lvl = settingGGame::menuSetting.menu2lvlPuncts::aboutP;

			blitMenuBG();
			blitRootBtn(settingGGame::menuSetting.rootBtn::cancel);
			std::cout << "About\n";
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

