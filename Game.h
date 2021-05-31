#pragma once
class Slova {
public:
	int word_1[6];

};
class WordStr {
	int* m_word;
	int m_size;
public:
	WordStr();
	int getSize() { return m_size; }
	int& operator[](int index) { return m_word[index]; }
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
	int size = 6;
	int countDefeat;
public:
	Game();
	~Game();
	int getWidthLetter();
	int getHeightLetter();
	int getGridLogic(int index);
	int& getGridView(int index);
	int getAlphabet(int index1, int index2);
	bool getWIN();
	bool setWIN();
	int getWidthGallows();
	int& setWidthGallows(int num);
	Game& resetGame();
	int& setGridLogic(WordStr& word);
	int getSize() { return size; }
	bool getDefeat();
	bool setDefeat();
	Game& operator=(const Game& game);
};