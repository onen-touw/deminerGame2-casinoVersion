#pragma once

#include<iostream>
#include<vector>
#include<SDL.h>
#include<SDL_image.h>

enum gameImages
{
	cell, 
	openCell,
	cellBombTip,
	cellStrengeTip,
	cellEmptyTip,
	

	gameImgTOTAL
};
struct hardnesSettings
{

	int hardSizeHeight = 30;
	int hardSizeWidth = 40;

	int normalSizeHeight = 20;
	int normalSizeWidth = 25;

	int easySizeHeight = 10;
	int easySizeWigth = 15;

	int bombParametr = 6;
	int tipBombParametr = 8;
	int tipStrangeParametr = 8;
	int tipEmptyParametr = 8;
} ;

struct gameSizes
{
	int cellSize = 50;		//px
	int fieldHEIGHT = 10;	//cells
	int fieldWIDTH = 15;	//cells

	int menuHeaderHeight = 100;

	int winWIDTH = fieldWIDTH * cellSize;	//px
	int winHEIGHT = fieldHEIGHT *cellSize + menuHeaderHeight;	//px
	
} ;

struct cellValue
{
	int x = 0;
	int y = 0;
	int i = 0;
	int j = 0;
	bool bomb = false;		// бомба
	bool open = false;		//открыто 
	bool tipStrange = false;		//подсказка
	bool tipWithBomb = false;	//100% Бомба
	bool tipEmptyCell = false;	//100% ничего нет
	bool hadSmth = false;
};



struct direction_
{
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;

	void stay() {
		up = false;
		down = false;
		right = false;
		left = false;
	}
};

struct Coords
{
	unsigned i =0;
	unsigned j = 0;
};

struct CharacterValues
{
	enum img
	{
		character,
		characterSteps,

		imgCount
	};
	unsigned healthPoint = 2;
	//direction_ direction;
	///bonuses
};

enum hardnesSettingsEnum
{
	easy,
	normal,
	hard
};

struct menuSettings
{
	int menuPaddingTop = 30;
	SDL_Rect menuOpenBtnCoords = {30, menuPaddingTop, 40, 40 };
	int cropHeightImgBtn = 150;
	int heightImgBtn = 95;
	int widthImgBtns = 300;
	const int menu2LvlPunctsCount = 2; ///about, settings
	enum menuImg
	{
		hearts,
		numbers,
		headerAndBG,
		menuOpenBtn,
		menuFirstLvlBtns,
		menuSettingsBtns,
		redSwitch,
		yellowSwitch,
		rootBtn,

		imgMenuTOTAL
	};
	enum menu2lvlPuncts
	{
		goTo1lvl,
		settingsP,
		aboutP
	};
	enum rootBtn
	{
		accept,
		cancel,
		rootTOTAL
	};
	enum menuPuncts
	{
		settingsBtn,
		about,
		quitBtn,
		cancelBtn,

		menuPunctsTOTAL
	};
	enum menuSettingPuncts
	{
		easySetting = 0,
		normalSetting,
		hardSetting,

		menuSettingPunctsTOTAL
	};
};

namespace settingGGame {
	extern SDL_Window* win;
	extern SDL_Surface* Surface;
	extern gameSizes gSizes;
	extern hardnesSettings hardSetting;
	extern CharacterValues charctData;
	extern menuSettings menuSetting;
	//extern std::string path
}
