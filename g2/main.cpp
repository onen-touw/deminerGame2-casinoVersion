

#include"baseGameClass.h"
#include"fieldClass.h"
#include"Character.h"
#include"menuClass.h"

int main(int argc, char* argv[]) {
	baseGameClass bcTest;
	SDL_Event event;

	fieldClass fTest;
	fTest.setImgVectSize(gameImages::gameImgTOTAL);
	fTest.loadImg("./images/gameImages/justCell.png", gameImages::cell);
	fTest.loadImg("./images/gameImages/emptyTip.png", gameImages::cellEmptyTip);
	fTest.loadImg("./images/gameImages/openCell.png", gameImages::openCell);
	fTest.loadImg("./images/gameImages/strangeTip.png", gameImages::cellStrengeTip);
	fTest.loadImg("./images/gameImages/bombTip.png", gameImages::cellBombTip);


	fTest.setGameSettings(hardnesSettingsEnum::easy);
	fTest.generateFieldMatrix();
	fTest.randomGenerationBombsTips();
	fTest.debug();

	
	
	menuClass menu;
	menu.setImgVectSize(settingGGame::menuSetting.menuImg::imgMenuTOTAL);
	menu.loadImg("./images/menuImges/pinkMenuBG.png", settingGGame::menuSetting.menuImg::headerAndBG);
	menu.loadImg("./images/menuImges/numbers_red.png", settingGGame::menuSetting.menuImg::numbers);
	menu.loadImg("./images/menuImges/rBt.png", settingGGame::menuSetting.menuImg::redSwitch);
	menu.loadImg("./images/menuImges/yBt.png", settingGGame::menuSetting.menuImg::yellowSwitch);
	menu.loadImg("./images/menuImges/menuOpenBtn.png", settingGGame::menuSetting.menuImg::menuOpenBtn);
	menu.loadImg("./images/menuImges/hearts.png", settingGGame::menuSetting.menuImg::hearts);
	menu.loadImg("./images/menuImges/menuBtns.png", settingGGame::menuSetting.menuImg::menuFirstLvlBtns);
	menu.loadImg("./images/menuImges/settingBtns.png", settingGGame::menuSetting.menuImg::menuSettingsBtns);
	menu.blitMenuHeaderFunctional();
	


	std::cout << "\n";
	fTest.blitField();
	SDL_UpdateWindowSurface(settingGGame::win);

	Character characterTest;
	characterTest.setImgVectSize(settingGGame::charctData.img::imgCount);
	characterTest.loadImg("./images/gameImages/character.png", settingGGame::charctData.img::character);
	characterTest.loadImg("./images/gameImages/characterStep.png", settingGGame::charctData.img::characterSteps);
	characterTest.blitCharacter(fTest.getFiledVector());

	SDL_UpdateWindowSurface(settingGGame::win);

	direction_ direct;
	bool game = true;
	bool firstStep = false;
	bool gameResult = false;
	
	int cursor_X = 0, cursor_Y = 0;


	while (game) {

		while (SDL_PollEvent(&event) || game)
		{
			if (!gameResult)
			{
				menu.gTimer();
				menu.blitGTime();
			}
			else
			{
				/// TODO: reset timer
			}
			

			if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&cursor_X, &cursor_Y);
				if (menu.checkOpenBtn(cursor_X, cursor_Y) && !menu.getMenuFlag())
				{
					std::cout << "menuOPen\n";
					menu.blitWinMenu(false);
					menu.toggleMEnuFlag();
				}

				if (menu.getMenuFlag())
				{
					switch (menu.btnParse(cursor_X, cursor_Y, menu.getMenuBtnCoords()))
					{
					case settingGGame::menuSetting.menuPuncts::settingsBtn:
						menu.blitWinSettings(false);
						//menu.blitSettings();
						std::cout << "blitSettings\n";

						SDL_UpdateWindowSurface(settingGGame::win);
						
						break;
					case settingGGame::menuSetting.menuPuncts::about:
						//menu.blitAbout();
						std::cout << "blitAbout\n";
						break;
					case settingGGame::menuSetting.menuPuncts::quitBtn:
						//quit
						std::cout << "quit\n";

						break;
					case settingGGame::menuSetting.menuPuncts::cancelBtn:
						//closeMenu
						std::cout << "closeMenu\n";

						break;

					default:
						break;
					}
				}
			}

			

			if (event.type == SDL_QUIT)//отслеживание закрытия окна через кнопку "Крест"
			{
				game = false;
			}
			if (characterTest.getHP())
			{
				/// TODO: create common function for btn press

				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN && !menu.getMenuFlag())
				{
					fTest.setOpenCell(characterTest.getCharacterPosition());
					if (!characterTest.transmit({ false, true, false, false }, fTest.getFiledVector()))
					{
						if (!firstStep)
						{
							std::cout << "fStep\n";


							menu.setGTime();
							firstStep = true;
						}
						menu.increaseStepCount();

						fTest.blitField();
						characterTest.blitCharacter(fTest.getFiledVector());
						menu.blitStepCounter();
						SDL_UpdateWindowSurface(settingGGame::win);



						if (characterTest.checkBobm(fTest.getFiledVector()))
						{
							std::cout << "bomb\n";
							fTest.demineBomb(characterTest.getCharacterPosition());

							if (characterTest.decreaseHP()) {

							}
							else
							{
								std::cout << "you are Loser\n";
								/// TODO: saving if it's necessary for this work(???)

								gameResult = true;
							}
							menu.blitHP(characterTest.getHP());
							SDL_UpdateWindowSurface(settingGGame::win);
						}
						if (characterTest.checkWin(fTest.getFiledVector()))
						{
							std::cout << "WIN WIN WIN WIN WIN\n";
							/// TODO: saving if it's necessary for this work(???)

						}
					}
				}
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT && !menu.getMenuFlag())
				{
					
					fTest.setOpenCell(characterTest.getCharacterPosition());
					if (!characterTest.transmit({ false, false, true,false }, fTest.getFiledVector()))
					{
						if (!firstStep)
						{
							std::cout << "fStep\n";

							/*menu.increaseStepCount();
							menu.blitStepCounter();*/

							menu.setGTime();
							firstStep = true;
						}
						menu.increaseStepCount();

						fTest.blitField();
						characterTest.blitCharacter(fTest.getFiledVector());

						menu.blitStepCounter();
						SDL_UpdateWindowSurface(settingGGame::win);

						if (characterTest.checkBobm(fTest.getFiledVector()))
						{
							std::cout << "bomb\n";
							fTest.demineBomb(characterTest.getCharacterPosition());

							if (characterTest.decreaseHP()) {

							}
							else
							{
								std::cout << "you are Loser\n";
								gameResult = true;
							}
							menu.blitHP(characterTest.getHP());
							SDL_UpdateWindowSurface(settingGGame::win);
						}
						if (characterTest.checkWin(fTest.getFiledVector()))
						{
							std::cout << "WIN WIN WIN WIN WIN\n";
						}
					}

				}
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP && !menu.getMenuFlag())
				{
					

					fTest.setOpenCell(characterTest.getCharacterPosition());
					if (!characterTest.transmit({ true,false,false,false }, fTest.getFiledVector()))
					{
						if (!firstStep)
						{
							std::cout << "fStep\n";

							/*menu.increaseStepCount();
							menu.blitStepCounter();*/
							menu.setGTime();
							firstStep = true;
						}
						menu.increaseStepCount();

						fTest.blitField();
						characterTest.blitCharacter(fTest.getFiledVector());
						menu.blitStepCounter();

						SDL_UpdateWindowSurface(settingGGame::win);

						if (characterTest.checkBobm(fTest.getFiledVector()))
						{
							std::cout << "bomb\n";
							fTest.demineBomb(characterTest.getCharacterPosition());
							if (characterTest.decreaseHP()) {

							}
							else
							{
								std::cout << "you are Loser\n";
								gameResult = true;
							}
							menu.blitHP(characterTest.getHP());
							SDL_UpdateWindowSurface(settingGGame::win);
						}
						if (characterTest.checkWin(fTest.getFiledVector()))
						{
							std::cout << "WIN WIN WIN WIN WIN\n";
						}
					}
				}
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT && !menu.getMenuFlag())
				{
					
					fTest.setOpenCell(characterTest.getCharacterPosition());
					
					if (!characterTest.transmit({ false,false,false, true }, fTest.getFiledVector()))
					{
						if (!firstStep)
						{
							std::cout << "fStep\n";

							/*menu.increaseStepCount();
							menu.blitStepCounter();*/
							menu.setGTime();
							firstStep = true;
						}
						menu.increaseStepCount();


						fTest.blitField();
						characterTest.blitCharacter(fTest.getFiledVector());
						menu.blitStepCounter();

						SDL_UpdateWindowSurface(settingGGame::win);

						if (characterTest.checkBobm(fTest.getFiledVector()))
						{
							std::cout << "bomb\n";
							fTest.demineBomb(characterTest.getCharacterPosition());

							if (characterTest.decreaseHP()) {

							}
							else
							{
								std::cout << "you are Loser\n";
								gameResult = true;
							}
							menu.blitHP(characterTest.getHP());
							SDL_UpdateWindowSurface(settingGGame::win);
						}
						if (characterTest.checkWin(fTest.getFiledVector()))
						{
							std::cout << "WIN WIN WIN WIN WIN\n";
						}
					}
				}
			}

			SDL_Delay(1000 / 60);
		}
	}
	
	

	SDL_FreeSurface(settingGGame::Surface);
	SDL_DestroyWindow(settingGGame::win);

	SDL_Quit();
	IMG_Quit();

	return 0;
}