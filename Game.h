#pragma once
#include <time.h>
#include<iostream>
#include<fstream>
#include<string>

class WordStr {
	std::string word;
	std::fstream file;
	int* intWord;
	int sizeIntWord;
public:
	WordStr();
	int getSize() const { return sizeIntWord; }
	int& operator[](int index) const { return intWord[index]; }
};

class Game {
private:
	int wGallows; // Ширина текстуры виселицы
	int wLetter; // ширина буквы
	int hLetter; // высота буквы
	int* gridLogic;
	int* gridView;
	int** alphabet;
	bool WIN;
	bool DEFEAT;
	int sizeWord;
	int countDefeat;
public:
	Game();
	~Game();
	int getWidthLetter();
	int getHeightLetter();
	int getGridLogic(int index);
	int& getGridView(int index);
	int getAlphabet(int index1, int index2);
	void setAlphabet(int index1, int index2, int value);
	bool getWIN();
	bool setWIN();
	int getWidthGallows();
	int& setWidthGallows(int num);
	Game& resetGame();
	int& setGridLogic(const WordStr& word);
	int getSize() { return sizeWord; }
	bool getDefeat();
	bool setDefeat();
	Game& operator=(const Game& game);
};