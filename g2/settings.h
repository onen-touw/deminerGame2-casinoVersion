#pragma once

#include<iostream>
#include<vector>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>


///==========
struct btnsStruct
{
	std::string btnText = "";
	SDL_Rect rect = { 0,0,0,0 };
};
struct menuSettings
{
	short btnH = 45, btnW = 150;
	short pading20 = 20; 
	enum menuState
	{
		close,
		mainMenuWindow,
		load,
		setting,
		about
	};
};
//struct winSettings
//{
//	const short header = 70;
//	const short winH = 600;
//	const short winW = 600;
//	const short winTopBorder = 31;
//
//	SDL_Window* win = nullptr;
//	SDL_Surface* surface = nullptr;
//};
///==========



enum gameImages
{
	cell,
	openCell,
	cellBombTip,
	cellStrengeTip,
	cellEmptyTip,
	finish,

	gameImgTOTAL
};
struct hardnesSettings
{

	int hardSizeHeight = 18;
	int hardSizeWidth = 25;

	int normalSizeHeight = 16;
	int normalSizeWidth = 20;

	int easySizeHeight = 10;
	int easySizeWigth = 15;

	int bombParametr = 6;
	int tipBombParametr = 8;
	int tipStrangeParametr = 8;
	int tipEmptyParametr = 8;
};

struct gameSizes
{
	int cellSize = 50;		//px
	int fieldHEIGHT = 10;	//cells
	int fieldWIDTH = 15;	//cells

	int menuHeaderHeight = 100;

	int winWIDTH = fieldWIDTH * cellSize;	//px
	int winHEIGHT = fieldHEIGHT * cellSize + menuHeaderHeight;	//px

};

struct cellValue
{
	int x = 0;
	int y = 0;
	int i = 0;
	int j = 0;
	bool bomb = false;		// áîìáà
	bool open = false;		//îòêðûòî 
	bool tipStrange = false;		//ïîäñêàçêà
	bool tipWithBomb = false;	//100% Áîìáà
	bool tipEmptyCell = false;	//100% íè÷åãî íåò
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
	unsigned i = 0;
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
};

enum hardnesSettingsEnum
{
	easy,
	normal,
	hard
};

struct headerSettings
{
	int menuPaddingTop = 30;
	SDL_Rect menuOpenBtnCoords = { 30, menuPaddingTop, 40, 40 };

	enum headerImg
	{
		headerAndBG,
		hearts,
		numbers,
		menuOpenBtn,

		imgMenuTOTAL
	};
};

namespace settingGGame {
	extern SDL_Window* win;
	extern SDL_Surface* Surface;
	extern gameSizes gSizes;
	extern hardnesSettings hardSetting;
	extern CharacterValues charctData;
	extern headerSettings headerSetting;
	extern menuSettings menuSetting;
	extern int hardnes;
	//extern std::string path
}