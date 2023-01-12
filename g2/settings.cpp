#include"settings.h"

namespace settingGGame {
	SDL_Window* win = nullptr;
	SDL_Surface* Surface = nullptr;
	gameSizes gSizes;
	hardnesSettings hardSetting;
	CharacterValues charctData;
	menuSettings menuSetting;
	int hardnes = hardnesSettingsEnum::easy;
}