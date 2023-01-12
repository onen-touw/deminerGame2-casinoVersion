#pragma once
#include"settings.h"
#include "imagesClass.h"


class fieldClass :
    public imagesClass/*, public baseGameClass*/
{
protected:

   
    unsigned int bombCount = 0;
    unsigned int tipBombCount = 0;
    unsigned int tipEmptyCellCount = 0;
    unsigned int tipStrangeCount = 0;

    int widthF = settingGGame::hardSetting.easySizeWigth;
    int heightF = settingGGame::hardSetting.easySizeHeight;

    std::vector<std::vector<cellValue>> fieldV;
    
   
public:
    ~fieldClass()
    {
        fieldV.clear();
    }

    fieldClass(){}

    std::vector<std::vector<cellValue>> getFiledVector() { return this->fieldV; }

    void generateFieldMatrix() {
        fieldV.resize(this->heightF);
        for (int k = 0; k < this->heightF; k++)
        {
            fieldV[k].resize(this->widthF);
        }

        int y = settingGGame::gSizes.menuHeaderHeight;
        for (int i = 0; i < fieldV.size(); i++)
        {
            int x = 0;
            for (int j = 0; j < fieldV[0].size(); j++)
            {
                fieldV[i][j].x = x;
                fieldV[i][j].y = y;
                x += settingGGame::gSizes.cellSize;

                fieldV[i][j].i = i;
                fieldV[i][j].j = j;

            }
            y += settingGGame::gSizes.cellSize;
        }
        fieldV[0][0].open = true;
    }

    void demineBomb(Coords pos) {
        this->fieldV[pos.i][pos.j].bomb = false;

    }

    void setOpenCell(Coords pos) {
        this->fieldV[pos.i][pos.j].open = true;
    }
    void clearField() {
        fieldV.clear();
    }
    void setGameSettings(/*int i*/) {
        switch (settingGGame::hardnes)
        {

        case hardnesSettingsEnum::easy:
            this->heightF = settingGGame::hardSetting.easySizeHeight;
            this->widthF = settingGGame::hardSetting.easySizeWigth;
            break;
        case hardnesSettingsEnum::normal:
            this->heightF = settingGGame::hardSetting.normalSizeHeight;
            this->widthF = settingGGame::hardSetting.normalSizeWidth;
            break;
        case hardnesSettingsEnum::hard:
            this->heightF = settingGGame::hardSetting.hardSizeHeight;
            this->widthF = settingGGame::hardSetting.hardSizeWidth;
            break;

        default:
            this->heightF = settingGGame::hardSetting.normalSizeHeight;
            this->widthF = settingGGame::hardSetting.normalSizeWidth;
            break;
        }
        this->bombCount = this->heightF * this->widthF / settingGGame::hardSetting.bombParametr;
        this->tipBombCount = this->heightF * this->widthF / settingGGame::hardSetting.tipBombParametr;
        this->tipStrangeCount = this->heightF * this->widthF / settingGGame::hardSetting.tipStrangeParametr;
        this->tipEmptyCellCount = this->heightF * this->widthF / settingGGame::hardSetting.tipEmptyParametr;


    }

    

    void randomGenerationBombsTips() {
        int h = this->heightF;
        int w = this->widthF- 2;
        srand(time(0));
        for (int i = 0; i < this->bombCount; i++)
        {
            int x = rand() % h;
            int y = rand() % w +1;
            if (fieldV[x][y].hadSmth)
            {
                i--;
            }
            else
            {
                fieldV[x][y].bomb = true;
                fieldV[x][y].hadSmth = true;
            }
        }

        ///TODO::подсказка 100% бомба 
        for (int i = 0; i < this->tipBombCount; i++)
        {
            int x = rand() % h;
            int y = rand() % w + 1;
            if (fieldV[x][y].hadSmth)
            {
                if (fieldV[x][y].bomb)
                {
                    fieldV[x][y].tipWithBomb = true;
                    fieldV[x][y].hadSmth = true;
                }
                else
                {
                    i--;
                }
                
            }
            else
            {
                i--;
            }
        }
        for (int i = 0; i < this->tipEmptyCellCount; i++)
        {
            int x = rand() % h;
            int y = rand() % w + 1;
            if (fieldV[x][y].hadSmth)
            {
                i--;
            }
            else
            {
                fieldV[x][y].tipEmptyCell = true;
                fieldV[x][y].hadSmth = true;
            }
        }
        for (int i = 0; i < this->tipStrangeCount; i++)
        {
            int x = rand() % h;
            int y = rand() % w + 1;
            fieldV[x][y].tipStrange = true;
            fieldV[x][y].hadSmth = true;
        }
    }

    void debug() {
        for (int i = 0; i < this->heightF; i++)
        {
            for (int j = 0; j < this->widthF; j++)
            {
                if (!fieldV[i][j].hadSmth)
                {
                    std::cout << 0 << " ";
                }
                else
                {
                    if (fieldV[i][j].bomb)
                    {
                        std::cout << "b ";
                    }
                    else if (fieldV[i][j].tipEmptyCell)
                    {
                        std::cout << "e ";
                    }
                    else if (fieldV[i][j].tipStrange)
                    {
                        std::cout << "s ";
                    }
                    else if (fieldV[i][j].tipWithBomb)
                    {
                        std::cout << "t ";
                    }
                }
            }
            std::cout << "\n";
        }
    }

    void blit(int i, int j, int numberImage) {
        SDL_Rect motR = { fieldV[i][j].x, fieldV[i][j].y,  settingGGame::gSizes.cellSize,  settingGGame::gSizes.cellSize};
        SDL_BlitScaled(images[numberImage], NULL, settingGGame::Surface , &motR);
    }


    void blitField() {
        for (int i = 0; i < this->heightF; i++)
        {
            for (int j = 0; j < this->widthF; j++)
            {
                if (fieldV[i][j].open)
                {
                    this->blit(i, j, gameImages::openCell);
                }
                else
                {
                    if (!fieldV[i][j].hadSmth)
                    {
                        this->blit(i, j, gameImages::cell);
                    }
                    else
                    {
                        if (fieldV[i][j].tipWithBomb)
                        {
                            this->blit(i, j, gameImages::cellBombTip);
                        }
                        else if (fieldV[i][j].tipStrange)
                        {
                            this->blit(i, j, gameImages::cellStrengeTip);
                        }
                        else if (fieldV[i][j].tipEmptyCell)
                        {
                            this->blit(i, j, gameImages::cellEmptyTip);
                        }
                        else
                        {
                            this->blit(i, j, gameImages::cell);
                        }
                    }
                }
            }
        }
    }


    

    void tempBlit() {
        for (int i = 0; i < fieldV.size(); i++)
        {
            for (int j = 0; j < fieldV[0].size(); j++)
            {
                std::cout << fieldV[i][j].x + settingGGame::gSizes.cellSize << " " << fieldV[i][j].y + settingGGame::gSizes.cellSize << " = ";
                blit(i, j, gameImages::openCell);
            }
            std::cout << "\n";
        }
    }


};

