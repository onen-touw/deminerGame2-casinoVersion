#pragma once

#include"settings.h"

class baseGameClass
{
protected:

public:

	~baseGameClass()
	{

	}

	baseGameClass()
	{
		initModuls();
	}

	bool initModuls() {
		bool success = true;

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			success = false;
		}
		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags)) {
			std::cout << "Can't init image: " << IMG_GetError() << std::endl;
			success = false;
		}
		
		settingGGame::win = SDL_CreateWindow("DeminerGame", 100, 100, 
			settingGGame::gSizes.winWIDTH, settingGGame::gSizes.winHEIGHT, SDL_WINDOW_SHOWN);
		
		if (settingGGame::win == NULL) {
			std::cout << "Can't create window: " << SDL_GetError() << std::endl;
			success = false;
		}
		settingGGame::Surface = SDL_GetWindowSurface(settingGGame::win);

		if (TTF_Init() != 0)
		{
			std::cout << "problem::ttfInit\n";
			success = false;
		}

		return success;
	}

	void rebuildWin() {//+

		SDL_FreeSurface(settingGGame::Surface);
		SDL_DestroyWindow(settingGGame::win);

		switch (settingGGame::hardnes)
		{
		case hardnesSettingsEnum::easy:
			settingGGame::gSizes.winWIDTH = settingGGame::hardSetting.easySizeWigth * settingGGame::gSizes.cellSize;
			settingGGame::gSizes.winHEIGHT = settingGGame::hardSetting.easySizeHeight * settingGGame::gSizes.cellSize;
			break;
		case hardnesSettingsEnum::normal:
			settingGGame::gSizes.winWIDTH = settingGGame::hardSetting.normalSizeWidth * settingGGame::gSizes.cellSize;
			settingGGame::gSizes.winHEIGHT = settingGGame::hardSetting.normalSizeHeight * settingGGame::gSizes.cellSize;
			break;
		case hardnesSettingsEnum::hard:
			settingGGame::gSizes.winWIDTH = settingGGame::hardSetting.hardSizeWidth * settingGGame::gSizes.cellSize;
			settingGGame::gSizes.winHEIGHT = settingGGame::hardSetting.hardSizeHeight * settingGGame::gSizes.cellSize;
			break;

		default:
			break;
		}
		settingGGame::gSizes.winHEIGHT +=settingGGame::gSizes.menuHeaderHeight;
		std::cout << settingGGame::gSizes.winWIDTH << "x" << settingGGame::gSizes.winHEIGHT << "\n";
		settingGGame::win = SDL_CreateWindow("DeminerGame", 100, 100,
			settingGGame::gSizes.winWIDTH, settingGGame::gSizes.winHEIGHT,
			SDL_WINDOW_SHOWN);
		settingGGame::Surface = SDL_GetWindowSurface(settingGGame::win);
	}

};

