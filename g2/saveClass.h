#pragma once

#include"settings.h"
#include<fstream>


class saveClass
{

private:

	std::vector<std::vector<int>>statMatrix;
	short colum = 2, lines = 3;
	std::string tempStr = "";
	std::string tempStr2 = "";
public:
	saveClass() {
		this->statMatrix.resize(this->lines);
		for (int i = 0; i < this->statMatrix.size(); i++)
		{
			this->statMatrix[i].resize(this->colum);
		}
	}

	void openResult() {
	
		std::ifstream file("save/data.txt");
		if (file.is_open()) {
			for (int i = 0; i < lines; i++)
			{
				std::getline(file, tempStr);
				int k = 0, j = 0;
				while (tempStr[k] != '\0')
				{
					if (tempStr[k] != '/')
					{
						tempStr2.append(1, tempStr[k]);
					}
					else
					{
						statMatrix[i][j] = (atoi(tempStr2.c_str()));
						tempStr2.clear();
						j++;
					}
					k++;
				}
			}
		}

		for (int i = 0; i < this->statMatrix.size(); i++)
		{
			for (int j = 0; j < this->statMatrix[0].size(); j++)
			{
				std::cout << this->statMatrix[i][j] << " ";

			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}


	std::vector<std::vector<int>>getStat() { return this->statMatrix; }

	void saveResult(int hardness, int time, int steps) {
		std::ofstream file("save/data.txt", std::ios::out);

		if (file.is_open()) {
			if (time < this->statMatrix[hardness][0] || this->statMatrix[hardness][0] == 0)
			{
				this->statMatrix[hardness][0] = time;
			}
			if (steps < this->statMatrix[hardness][1] || this->statMatrix[hardness][1] == 0)
			{
				this->statMatrix[hardness][1] = steps;

			}
			for (int i = 0; i < this->statMatrix.size(); i++)
			{
				for (int j = 0; j < this->statMatrix[0].size(); j++)
				{
					file << this->statMatrix[i][j] << "/";
				}
				file << "\n";
			}
		}
		file.close();
	}

	~saveClass()
	{
		this->statMatrix.clear();
		this->tempStr.clear();
		this->tempStr2.clear();
	}

};

