#include"Game.h"

WordStr::WordStr() {
	file.open("Word.txt", std::fstream::out | std::fstream::in);
	for (int i{ 0 }; i < rand()%5 + 1; ++i)
		file >> word;
	sizeIntWord = word.length() + 1;
	intWord = new int[sizeIntWord] {0};
	for (int j{ 0 }; j < sizeIntWord; j++) {
		word[j] -=5;
		if (word[j] == -88) *(intWord + j) = 7;
		else if(word[j] < -58) * (intWord + j + 1) = word[j] + 65;
		else *(intWord + j + 1) = word[j] + 66;
	}
}

Game& Game::operator=(const Game& game) {
	wGallows = game.wGallows;
	wLetter = game.wLetter;
	hLetter = game.hLetter;
	sizeWord = game.sizeWord;
	countDefeat = game.countDefeat;
	gridLogic = game.gridLogic;
	gridView = game.gridView;
	WIN = game.WIN;
	DEFEAT = game.DEFEAT;
	/*for (int i{ 0 }; i < sizeWord; ++i) {
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
	sizeWord = 0;
	countDefeat = 11;
	gridLogic = nullptr;
	gridView = nullptr;
	WIN = false;
	DEFEAT = false;
	/*for (int i{ 0 }; i < sizeWord; ++i) {
		gridLogic[i] = 0;
		gridView[i] = 0;
	}*/
	alphabet = new int* [8];
	for (int i{ 0 }; i < 8; ++i) {
		alphabet[i] = new int[8]{ 0 };
	}
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
	WordStr word;
	setGridLogic(word);
	return *this;

}
int Game::getWidthLetter() { return wLetter; }
int Game::getHeightLetter() { return hLetter; }
int Game::getGridLogic(int index) { return gridLogic[index]; }
int& Game::getGridView(int index) { return gridView[index]; }
int Game::getAlphabet(int index_1, int index_2) { return alphabet[index_1][index_2]; }
void Game::setAlphabet(int index_1, int index_2, int value) { alphabet[index_1][index_2]+=value; }
bool Game::getWIN() { setWIN(); return WIN; }
bool Game::setWIN() {
	for (int i{ 1 }; i < sizeWord; ++i)
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
int& Game::setGridLogic(const WordStr & word) {
	sizeWord = word.getSize();
	gridView = new int[sizeWord] {0};
	gridLogic = new int[sizeWord];
	for (int i{ 0 }; i < sizeWord; ++i) {
		gridLogic[i] = word[i];
	}
	return *gridLogic;
}