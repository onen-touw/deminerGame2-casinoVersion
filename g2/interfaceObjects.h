#pragma once

#include"settings.h" 


class interfaceObjects
{
protected:
	short pading = 20; // px
	short btnTextPading = 5; //px

	SDL_Rect objRect = { 0,0,0,0 };
	TTF_Font* font = nullptr;
	SDL_Surface* bgImg = nullptr;
	SDL_Surface* btnImg = nullptr;
	std::vector<btnsStruct> btns = {};


public:

	interfaceObjects() {}

	interfaceObjects(SDL_Surface* bgImg, SDL_Surface* btnImg,  TTF_Font* font, std::vector<btnsStruct>btns, SDL_Rect objRect={0,0,0,0}) {
		this->bgImg = bgImg;
		this->btnImg = btnImg;
		this->objRect = objRect;
		this->font = font;
		this->btns = btns;
	}

	interfaceObjects(SDL_Surface* bgImg, SDL_Surface* btnImg, TTF_Font* font) {
		this->bgImg = bgImg;
		this->btnImg = btnImg;
		this->font = font;
	}

	interfaceObjects(SDL_Surface* bgImg,  TTF_Font* font, SDL_Rect objRect = { 0,0,0,0 }) {
		this->bgImg = bgImg;
		this->font = font;
		this->objRect = objRect;
	}

	~interfaceObjects()
	{
		this->btns.clear();
		SDL_FreeSurface(this->bgImg);
		SDL_FreeSurface(this->btnImg);
		//TTF_CloseFont(this->font);
	}

	void blitBg() {
		if (this->bgImg == nullptr)
		{
			std::cout << "interfaceObjects::error-image is empty\n";
			return;
		}
		SDL_BlitScaled(this->bgImg, NULL, settingGGame::Surface, &this->objRect );
	}

	/////notUsed
	//void blitBg(SDL_Surface* img, SDL_Rect objRect) {
	//	std::cout << this->objRect.x << " " << this->objRect.w << "\n";
	//	SDL_BlitScaled(img, NULL, settingGGame::Surface, &objRect );
	//}

	///notUsed
	void blitWithTxt(const char* text, SDL_Color color = {0,0,0}) {
		if (this->bgImg == nullptr)
		{
			std::cout << "interfaceObjects::error-image is empty\n";
			return;
		}
		SDL_BlitScaled(this->bgImg, NULL, settingGGame::Surface, &this->objRect);
		SDL_Rect tempRect = { this->objRect.x + this->pading, this->objRect.y + this->pading,
			this->objRect.w - 2 * pading, this->objRect.h - 2 * pading };
		SDL_Surface* tempSurf = TTF_RenderText_Blended_Wrapped(this->font, text, color, tempRect.w);
		SDL_BlitSurface(tempSurf, NULL, settingGGame::Surface, &tempRect);
		SDL_FreeSurface(tempSurf);
	}

	/*void blitWithTxt(SDL_Surface* img, const char* text, SDL_Rect objRect, SDL_Color color = { 0,0,0 }) {
		SDL_BlitScaled(img, NULL, gameSettings::winSetting.surface, &objRect);

		SDL_Rect tempRect = { objRect.x + this->pading, objRect.y + this->pading,
			objRect.w - 2 * pading, objRect.h - 2 * pading };
		if (this->font == nullptr)
		{
			std::cout << "error\n";
		}
		SDL_Surface* tempSurf = TTF_RenderText_Blended_Wrapped(this->font, text, color, tempRect.w);
		SDL_BlitSurface(tempSurf, NULL, gameSettings::winSetting.surface, &tempRect);
		SDL_UpdateWindowSurface(gameSettings::winSetting.win);
		SDL_FreeSurface(tempSurf);
	}*/

	SDL_Rect getRect() { return this->objRect; }

	void blitWithTextCenter(SDL_Surface* img, const char* text, SDL_Rect objRect, SDL_Color color = { 0,0,0 }){
		SDL_BlitScaled(img, NULL, settingGGame::Surface, &objRect);
		SDL_Surface* tempSurf = TTF_RenderText_Solid(this->font, text, color);
		SDL_Rect tempRect = { objRect.x + (objRect.w - tempSurf->w) / 2,objRect.y + (objRect.h - tempSurf->h) / 2,0,0 };
		if (this->font == nullptr)
		{
			std::cout << "error\n";
		}
		SDL_BlitSurface(tempSurf, NULL, settingGGame::Surface, &tempRect);
		SDL_FreeSurface(tempSurf);
	}

	void blitWithTextCenter(const char* text, SDL_Color color = { 0,0,0 }) {
		SDL_BlitScaled(this->bgImg, NULL, settingGGame::Surface, &this->objRect);
		SDL_Surface* tempSurf = TTF_RenderText_Solid(this->font, text, color);
		SDL_Rect tempRect = { this->objRect.x + (this->objRect.w - tempSurf->w) / 2,this->objRect.y + (this->objRect.h - tempSurf->h) / 2,0,0 };
		if (this->font == nullptr)
		{
			std::cout << "error\n";
		}
		SDL_BlitSurface(tempSurf, NULL, settingGGame::Surface, &tempRect);
		SDL_FreeSurface(tempSurf);
	}


	void blitBtns() {
		if (this->btns.size() > 0)
		{
			for (int i = 0; i < btns.size(); i++)
			{
				this->blitWithTextCenter(this->btnImg, this->btns[i].btnText.c_str(), this->btns[i].rect);
			}
		}
		else std::cout << "btnManager:: 0 btns for blit\n";
	}

	int checkButtonClick(int x, int y) {
		if (this->btns.size() > 0)
		{
			for (int i = 0; i < this->btns.size(); i++)
			{
				if (x >= this->btns[i].rect.x && x <= this->btns[i].rect.x + this->btns[i].rect.w
					&& y >= this->btns[i].rect.y && y <= this->btns[i].rect.y + this->btns[i].rect.h)
				{
					return i;
				}
			}
		}
		else std::cout << "btnManager:: 0 btns for checking\n";
		return -1;
	}
};

