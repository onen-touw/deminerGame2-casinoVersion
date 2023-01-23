#pragma once

#include"baseGameClass.h"
#include"fieldClass.h"
#include"Character.h"
#include"menuClass.h"

#include"headerClass.h"
#include"aboutWinClass.h"
#include"settingWinClass.h"
#include"statisticWinClass.h"

#include"saveClass.h"
#include"fontClass.h"

class gameplayClass
{
private:
	baseGameClass bcTest;
	fieldClass fTest;
	headerClass header;
	Character characterTest;
	saveClass save;

	bool game = true;
	bool firstStep = false;
	bool gameResult = false;
	int menuFlag = settingGGame::menuSetting.close;

	int cursor_X = 0, cursor_Y = 0;

public:
	gameplayClass() {
		//bcTest.initModuls();
		fTest.setImgVectSize(gameImages::gameImgTOTAL);
		fTest.loadImg("./images/gameImages/justCell.png", gameImages::cell);
		fTest.loadImg("./images/gameImages/emptyTip.png", gameImages::cellEmptyTip);
		fTest.loadImg("./images/gameImages/openCell.png", gameImages::openCell);
		fTest.loadImg("./images/gameImages/strangeTip.png", gameImages::cellStrengeTip);
		fTest.loadImg("./images/gameImages/bombTip.png", gameImages::cellBombTip);
		fTest.loadImg("./images/gameImages/finish.png", gameImages::finish);

		header.setImgVectSize(settingGGame::headerSetting.headerImg::imgMenuTOTAL);
		header.loadImg("./images/headerImges/pinkMenuBG.png", settingGGame::headerSetting.headerImg::headerAndBG);
		header.loadImg("./images/headerImges/numbers_red.png", settingGGame::headerSetting.headerImg::numbers);
		header.loadImg("./images/headerImges/hearts.png", settingGGame::headerSetting.headerImg::hearts);
		header.loadImg("./images/headerImges/menuOpenBtn.png", settingGGame::headerSetting.headerImg::menuOpenBtn);


		characterTest.setImgVectSize(settingGGame::charctData.img::imgCount);
		characterTest.loadImg("./images/gameImages/character.png", settingGGame::charctData.img::character);
	}

	~gameplayClass()
	{

	}

	void generateGame() {
		bcTest.rebuildWin();
		fTest.clearField();
		fTest.setGameSettings();
		fTest.generateFieldMatrix();
		fTest.randomGenerationBombsTips();
		fTest.debug();

		header.resetTimerAndCounter();
		header.blitMenuHeaderFunctional();

		fTest.blitField();

		characterTest.characterResetPositon();
		characterTest.blitCharacter(fTest.getFiledVector());
		characterTest.setHP();

		SDL_UpdateWindowSurface(settingGGame::win);


		this->firstStep = false;
		this->gameResult = false;
	}

	void step() {
		if (!firstStep)
		{
			std::cout << "fStep\n";
			header.setGTime();
			firstStep = true;
		}
		header.increaseStepCount();

		fTest.blitField();
		characterTest.blitCharacter(fTest.getFiledVector());

		header.blitStepCounter();
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
			header.blitHP(characterTest.getHP());
			SDL_UpdateWindowSurface(settingGGame::win);
		}
		if (characterTest.checkWin(fTest.getFiledVector()))
		{
			std::cout << "WIN WIN WIN WIN WIN\n";


			save.openResult();
			save.saveResult(settingGGame::hardnes, header.getTime(), header.getSteps());
			gameResult = true;

		}
	}

	int startGame() {


		fontClass font;
		imagesClass img;
		SDL_Event event;

		menuClass menu(img.loadOneImg("./images/menuImges/mainBg.png"), img.loadOneImg("./images/menuImges/btnBg.png"), font.getFont());
		aboutWinClass aboutWin = aboutWinClass(img.loadOneImg("./images/menuImges/mainBg.png"), img.loadOneImg("./images/menuImges/btnBg.png"), font.getFont());
		settingWinClass settingWin = settingWinClass(img.loadOneImg("./images/menuImges/mainBg.png"), 
			img.loadOneImg("./images/menuImges/btnBg.png"), img.loadOneImg("./images/menuImges/switch.png"), font.getFont());
		statisticWinClass statisticWin = statisticWinClass(img.loadOneImg("./images/menuImges/mainBg.png"), img.loadOneImg("./images/menuImges/btnBg.png"), font.getFont());

		generateGame();

			while (SDL_PollEvent(&event) || game)
			{
				if (!gameResult)
				{
					header.gTimer();
					header.blitGTime();
				}

				if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP)
				{
					SDL_GetMouseState(&cursor_X, &cursor_Y);
					if (header.checkOpenBtn(cursor_X, cursor_Y) && this->menuFlag == settingGGame::menuSetting.close)
					{
						std::cout << "menuOPen\n";
						this->menuFlag = settingGGame::menuSetting.mainMenuWindow;
						menu.blit();
					}
					else if (this->menuFlag == settingGGame::menuSetting.mainMenuWindow)
					{
						switch (menu.checkButtonClick(this->cursor_X, this->cursor_Y)) {
						case menu.btnsEnum::settingBtn:
							this->menuFlag = settingGGame::menuSetting.setting;
							settingWin.blit();
							break;
						case menu.btnsEnum::aboutBtn:
							this->menuFlag = settingGGame::menuSetting.about;
							aboutWin.blit();
							break;
						case menu.btnsEnum::statBtn:
							this->menuFlag = settingGGame::menuSetting.statistic;
							save.openResult();
							statisticWin.loadStatistic(save.getStat());
							statisticWin.blit();
							break;
						case menu.btnsEnum::cancelGame:
							this->menuFlag = settingGGame::menuSetting.close;
							fTest.blitField();
							characterTest.blitCharacter(fTest.getFiledVector());
							header.blitStepCounter();
							SDL_UpdateWindowSurface(settingGGame::win);
							break;
						case menu.btnsEnum::quitBtn:
							return 0;
							break;

						default:
							break;
						}
					}
					else if (this->menuFlag == settingGGame::menuSetting.about)
					{
						if (aboutWin.checkButtonClick(this->cursor_X, this->cursor_Y) == aboutWin.cancelBtn)
						{
							std::cout << "aboutWin::buttons::cancel\n";
							this->menuFlag = settingGGame::menuSetting.mainMenuWindow;
							menu.blit();
						}
					}
					else if (this->menuFlag == settingGGame::menuSetting.setting)
					{
						switch (settingWin.checkButtonClick(this->cursor_X, this->cursor_Y))
						{
						case settingWin.btnsEnum::easy:
							std::cout << "setting::buttons::easy\n";
							settingWin.changeHardness(settingWin.btnsEnum::easy);
							break;
						case settingWin.btnsEnum::normal:
							std::cout << "setting::buttons::normal\n";
							settingWin.changeHardness(settingWin.btnsEnum::normal);
							break;
						case settingWin.btnsEnum::hard:
							std::cout << "setting::buttons::hard\n";
							settingWin.changeHardness(settingWin.btnsEnum::hard);
							break;
						case settingWin.btnsEnum::apply:
							std::cout << "setting::buttons::apply\n";
							this->menuFlag = settingGGame::menuSetting.close;
							settingWin.applyHardness();

							this->generateGame();

							/*fTest.blitField();
							characterTest.blitCharacter(fTest.getFiledVector());*/

							//SDL_UpdateWindowSurface(settingGGame::win);
							break;
						case settingWin.btnsEnum::cancel:
							std::cout << "setting::buttons::cancel\n";
							settingWin.resetHardness();
							this->menuFlag = settingGGame::menuSetting.mainMenuWindow;
							menu.blit();

							break;


						default:
							break;
						}
					}

					else if (this->menuFlag = settingGGame::menuSetting.statistic)
					{
						if (statisticWin.checkButtonClick(this->cursor_X, this->cursor_Y) == statisticWin.cancelBtn)
						{
							std::cout << "statisticWin::buttons::cancel\n";
							this->menuFlag = settingGGame::menuSetting.mainMenuWindow;
							menu.blit();
						}
					}
				}

				if (event.type == SDL_QUIT)//отслеживание закрытия окна через кнопку "Крест"
				{
					game = false;
				}

				if (characterTest.getHP() && !gameResult)
				{
					if (this->menuFlag == settingGGame::menuSetting.close)
					{
					if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN /*&& !menu.getMenuFlag()*/)
					{
						fTest.setOpenCell(characterTest.getCharacterPosition());
						if (!characterTest.transmit({ false, true, false, false }, fTest.getFiledVector()))
						{
							/*if (!firstStep)
							{
								std::cout << "fStep\n";


								header.setGTime();
								firstStep = true;
							}
							header.increaseStepCount();

							fTest.blitField();
							characterTest.blitCharacter(fTest.getFiledVector());
							header.blitStepCounter();
							SDL_UpdateWindowSurface(settingGGame::win);

							if (characterTest.checkBobm(fTest.getFiledVector()))
							{
								std::cout << "bomb\n";
								fTest.demineBomb(characterTest.getCharacterPosition());

								if (!characterTest.decreaseHP()) {
									std::cout << "you are Loser\n";
									gameResult = true;
								}
								header.blitHP(characterTest.getHP());
								SDL_UpdateWindowSurface(settingGGame::win);
							}
							if (characterTest.checkWin(fTest.getFiledVector()))
							{
								std::cout << "WIN WIN WIN WIN WIN\n";
								/// TODO: saving if it's necessary for this work(???)
								gameResult = true;
							}*/
							this->step();
						}
					}
					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT/* && *//*!menu.getMenuFlag()*/)
					{

						fTest.setOpenCell(characterTest.getCharacterPosition());
						if (!characterTest.transmit({ false, false, true,false }, fTest.getFiledVector()))
						{
							/*if (!firstStep)
							{
								std::cout << "fStep\n";
								header.setGTime();
								firstStep = true;
							}
							header.increaseStepCount();

							fTest.blitField();
							characterTest.blitCharacter(fTest.getFiledVector());

							header.blitStepCounter();
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
								header.blitHP(characterTest.getHP());
								SDL_UpdateWindowSurface(settingGGame::win);
							}
							if (characterTest.checkWin(fTest.getFiledVector()))
							{
								std::cout << "WIN WIN WIN WIN WIN\n";
								gameResult = true;

							}*/
							this->step();
						}

					}
					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP /*&& !menu.getMenuFlag()*/)
					{


						fTest.setOpenCell(characterTest.getCharacterPosition());
						if (!characterTest.transmit({ true,false,false,false }, fTest.getFiledVector()))
						{
							//if (!firstStep)
							//{
							//	std::cout << "fStep\n";

							//	/*menu.increaseStepCount();
							//	menu.blitStepCounter();*/
							//	header.setGTime();
							//	firstStep = true;
							//}
							//header.increaseStepCount();

							//fTest.blitField();
							//characterTest.blitCharacter(fTest.getFiledVector());
							//header.blitStepCounter();

							//SDL_UpdateWindowSurface(settingGGame::win);

							//if (characterTest.checkBobm(fTest.getFiledVector()))
							//{
							//	std::cout << "bomb\n";
							//	fTest.demineBomb(characterTest.getCharacterPosition());
							//	if (characterTest.decreaseHP()) {

							//	}
							//	else
							//	{
							//		std::cout << "you are Loser\n";
							//		gameResult = true;
							//	}
							//	header.blitHP(characterTest.getHP());
							//	SDL_UpdateWindowSurface(settingGGame::win);
							//}
							//if (characterTest.checkWin(fTest.getFiledVector()))
							//{
							//	std::cout << "WIN WIN WIN WIN WIN\n";
							//	gameResult = true;

							this->step();
							}
						}
					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT /*&& !menu.getMenuFlag()*/)
					{

						fTest.setOpenCell(characterTest.getCharacterPosition());

						if (!characterTest.transmit({ false,false,false, true }, fTest.getFiledVector()))
						{
							
							this->step();
						}
					}
					}
				}
				SDL_Delay(1000 / 60);
			}
		return 0;
	}
};

