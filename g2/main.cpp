
#include"gameplayClass.h"		

int main(int argc, char* argv[]) {


	gameplayClass game;

	game.startGame();

	SDL_FreeSurface(settingGGame::Surface);
	SDL_DestroyWindow(settingGGame::win);

	SDL_Quit();
	IMG_Quit();

	return 0;
}