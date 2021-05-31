#include"Game.h"
WordStr::WordStr() {
	/*std::fstream file;
	file.open("Word.txt", std::fstream::in | std::fstream::out);*/
	m_size = 6;
	m_word = new int[m_size] {0, 19, 13, 16, 3, 16};
}

Game& Game::operator=(const Game& game) {
	wGallows = game.wGallows;
	wLetter = game.wLetter;
	hLetter = game.hLetter;
	size = game.size;
	countDefeat = game.countDefeat;
	gridLogic = game.gridLogic;
	gridView = game.gridView;
	WIN = game.WIN;
	DEFEAT = game.DEFEAT;
	/*for (int i{ 0 }; i < size; ++i) {
		gridLogic[i] = game.gridLogic[i];
		gridView[i] = game.gridView[i];
	}*/
	alphabet = new int* [8];
	for (int i{ 0 }; i < 8; ++i)
		alphabet[i] = new int[8]{ 0 };
	for (int i{ 0 }; i < 8; ++i)
		for (int j{ 1 }; j < 8; ++j) {
			alphabet[i][j] = game.alphabet[i][j];
		}
	return *this;
}

Game::Game() {
	wGallows = 0;
	wLetter = 90;
	hLetter = 90;
	size = 0;
	countDefeat = 11;
	gridLogic = nullptr;
	gridView = nullptr;
	WIN = false;
	DEFEAT = false;
	for (int i{ 0 }; i < size; ++i) {
		gridLogic[i] = 0;
		gridView[i] = 0;
	}
	alphabet = new int* [8];
	for (int i{ 0 }; i < 8; ++i)
		alphabet[i] = new int[8]{ 0 };
	for (int i{ 1 }, letter{ 1 }; i < 7; ++i)
		for (int j{ 1 }; j < 7 && letter < 34; ++j, letter++) {
			alphabet[i][j] = letter;
		}
}
Game::~Game() {
	for (int i{ 0 }; i < 8; ++i)
		delete[] alphabet[i];
	delete[]alphabet;
	delete[]gridView;
	delete[]gridLogic;
}
Game& Game::resetGame() {
	Game tmp;
	*this = tmp;
	return *this;

}
int Game::getWidthLetter() { return wLetter; }
int Game::getHeightLetter() { return hLetter; }
int Game::getGridLogic(int index) { return gridLogic[index]; }
int& Game::getGridView(int index) { return gridView[index]; }
int Game::getAlphabet(int index_1, int index_2) { return alphabet[index_1][index_2]; }
bool Game::getWIN() { setWIN(); return WIN; }
bool Game::setWIN() {
	for (int i{ 1 }; i < size; ++i)
		if (gridLogic[i] != gridView[i]) {
			return false;
		}
	WIN = true;
	return WIN;
}
bool Game::getDefeat() { return DEFEAT; }
bool Game::setDefeat() { --countDefeat; if (!countDefeat)DEFEAT = true;  return DEFEAT; }
int Game::getWidthGallows() { return wGallows; }
int& Game::setWidthGallows(int num) { return wGallows += num; }
int& Game::setGridLogic(WordStr & word) {
	size = word.getSize();
	gridLogic = new int[size];
	gridView = new int[size] {0};
	for (int i{ 0 }; i < size; ++i) {
		gridLogic[i] = word[i];
	}
	return *gridLogic;
}