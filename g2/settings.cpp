#include"settings.h"

namespace settingGGame {
	SDL_Window* win = nullptr;
	SDL_Surface* Surface = nullptr;
	gameSizes gSizes;
	hardnesSettings hardSetting;
	CharacterValues charctData;
	headerSettings headerSetting;
	menuSettings menuSetting;

	int hardnes = hardnesSettingsEnum::easy;
}