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

		return success;
	}

	void rebuildWin(int gameLvl) {

		/*this->gSize.fieldHEIGHT = settingGGame::hardSetting.;
		this->gSize.fieldWIDTH = ;
		this->gSize.winHEIGHT = ;
		this->gSize.winWIDTH = ;*/

		SDL_FreeSurface(settingGGame::Surface);
		SDL_DestroyWindow(settingGGame::win);

		settingGGame::win = SDL_CreateWindow("DeminerGame", 100, 100,
			settingGGame::gSizes.winWIDTH, settingGGame::gSizes.winHEIGHT,
			SDL_WINDOW_SHOWN);
		settingGGame::Surface = SDL_GetWindowSurface(settingGGame::win);
	}

};

