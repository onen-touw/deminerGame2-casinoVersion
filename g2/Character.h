#pragma once
//#include"settings.h"
#include"imagesClass.h"
#include"fieldClass.h"

class Character : /*public imagesClass,*/ public fieldClass
{
private:
	unsigned i = 0;
	unsigned j = 0;
	unsigned healthPoint = 0;
	bool alive = true;

public:

	Character(){ 
		this->healthPoint = settingGGame::charctData.healthPoint;
	
	}
	~Character()
	{
	
	}

	void setPosition(unsigned i, unsigned j) {
		this->i = i;
		this->j = j;
	}

	///return false if HP = 0
	bool decreaseHP() { 
		this->healthPoint--;
		if (this->healthPoint == 0)
		{
			alive = false;
			return false;
		}
		return true;
		 
	}
	void increaseHP() {
		if (this->healthPoint <2)
		{
			this->healthPoint++;
		}
	}

	unsigned getHP() { return this->healthPoint; }


	void blitCharacter(std::vector<std::vector<cellValue>> field) {
		SDL_Rect mR = {field[this->i][this->j].x, field[this->i][this->j].y, settingGGame::gSizes.cellSize,settingGGame::gSizes.cellSize };
		SDL_BlitScaled(images[settingGGame::charctData.img::character], NULL, settingGGame::Surface, &mR);
	}

	Coords getCharacterPosition() { return{ i,j }; }

	bool transmit(direction_ direct, std::vector<std::vector<cellValue>> field) {
		if (direct.up)
		{
			if (i > 0)
			{
				std::cout << i << " " << j << "\n";
				--i;
				return false;
			}
			else
			{
				return true;
			}
		}
		else if (direct.down)
		{
			if (i < field.size() - 1) {
				++i;
				return false;
			}
			else
			{
				return true;
			}
		}
		else if (direct.left)
		{
			if (j > 0)
			{
				--j;
				return false;
			}
			else
			{
				return true;
			}
		}
		else if (direct.right)
		{
			if (j < field[0].size() - 1) {
				++j;
				return false;
			}
			else
			{
				return true;
			}
		}

		return false;

	}

	bool checkWalls(direction_ direct, std::vector<std::vector<cellValue>> field) {
		if (direct.up)
		{
			if (i == 0)
			{
				return true;
			}
		}
		else if (direct.down)
		{
			if (i == field.size() - 1) {
				return true;
			}
		}
		else if (direct.left)
		{
			if (j == 0)
			{
				return true;
			}
		}
		else if (direct.right)
		{
			if (j == field[0].size() - 1) {
				return true;
			}
		}
		return false;
	}

	bool checking(std::vector<std::vector<cellValue>> field) {
		if (field[i][j].bomb)
		{
			return true;
		}
		return false;
	}

};

