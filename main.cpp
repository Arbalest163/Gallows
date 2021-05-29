#include <SFML/Graphics.hpp>
#include <time.h>
#include<iostream>
#include<fstream>
using namespace sf;

struct WordStr {
	int* m_word;
	int m_size;
public:
	WordStr();
	int getSize() { return m_size; }
	int& operator[](int index) { return m_word[index]; }
};

WordStr::WordStr() {
	/*std::fstream file;
	file.open("Word.txt", std::fstream::in | std::fstream::out);*/
	m_size = 6;
	m_word = new int[m_size] {0, 19, 13, 16, 3, 16};
}
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
Game& Game::operator=(const Game& game) {
	wGallows = game.wGallows;
	wLetter = game.wLetter;
	hLetter = game.hLetter;
	size = game.size;
	countDefeat = game.countDefeat;
	gridLogic = new int[size];
	gridView = new int[size];
	WIN = game.WIN;
	DEFEAT = game.DEFEAT;
	for (int i{ 0 }; i < size; ++i) {
		gridLogic[i] = game.gridLogic[i];
		gridView[i] = game.gridView[i];
	}
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
	size = 6;
	countDefeat = 11;
	gridLogic = new int[size];
	gridView = new int[size];
	WIN = false;
	DEFEAT = false;
	for (int i{ 0 }; i < size; ++i) {
		gridLogic[i] = 0;
		gridView[i] = 0;
	}
	alphabet = new int* [8];
	for (int i{ 0 }; i < 8; ++i)
		alphabet[i] = new int[8]{0};
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
bool Game::setDefeat() { --countDefeat; if(!countDefeat)DEFEAT = true;  return DEFEAT; }
int Game::getWidthGallows() { return wGallows; }
int& Game::setWidthGallows(int num) {  return wGallows += num; }
int& Game::setGridLogic(WordStr& word) { 
	for (int i{ 0 }; i < word.getSize(); ++i) {
		gridLogic[i] = word[i];
	}
	return *gridLogic; }

int main()
{
	setlocale(0, "");
	Game game;
	WordStr word;
	game.setGridLogic(word);
	RenderWindow Gallows(VideoMode(1530, 990), "The Gallows!");
	Texture gallowsTexture;
	gallowsTexture.loadFromFile("C:\\SFML-2.5.1\\Gallows\\GallowsTexture.png");
	Sprite gallowsSprite(gallowsTexture);
	Texture frame;
	frame.loadFromFile("C:\\SFML-2.5.1\\Gallows\\Ramka.png");
	Sprite frameSprite(frame);
	Texture letters;
	letters.loadFromFile("C:\\SFML-2.5.1\\Gallows\\letterstr.png");
	Sprite lSprite(letters);
	Texture win;
	win.loadFromFile("C:\\SFML-2.5.1\\Gallows\\win.png");
	Sprite winSprite(win);
	Texture lose;
	lose.loadFromFile("C:\\SFML-2.5.1\\Gallows\\lose.png");
	Sprite loseSprite(lose);
	Texture menu;
	menu.loadFromFile("C:\\SFML-2.5.1\\Gallows\\menu.png");
	Sprite menuSprite(menu);
	while (Gallows.isOpen())
	{
		Vector2i pos = Mouse::getPosition(Gallows);
		Event event;
		//std::cout << x << "   " << y << std::endl; // отладка координат
		while (Gallows.pollEvent(event))
		{
			if (event.type == Event::Closed)
				Gallows.close();
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left) {
					int x{ 0 };
					int y{ 0 };
					if (!game.getWIN() && !game.getDefeat()) {
						if (pos.x > 900 && pos.x < 1440 && pos.y > 360 && pos.y < 900) {
							x = (pos.x - 810) / game.getWidthLetter();
							y = (pos.y - 270) / game.getHeightLetter();
							if (pos.x > 1170 && pos.y > 810) continue;
							bool flag{ false };
							for (int k{ 1 }; k < 6; k++) {
								if (game.getAlphabet(y, x) == game.getGridLogic(k)) {
									game.getGridView(k) = game.getGridLogic(k);
									flag = true;
								}
							}
							if (!flag)
								if (!game.getWIN() && !game.getDefeat()) {
									game.setWidthGallows(800);
									game.setDefeat();
								}
						}
					}
					else {
						if (pos.x > 1030 && pos.x < 1330 && pos.y > 570 && pos.y < 630) {
							game.resetGame();
							game.setGridLogic(word);
						
						}
						if (pos.x > 1030 && pos.x < 1330 && pos.y > 645 && pos.y < 705) {
							Gallows.close();
						}
					
					}
				}
		}
		Gallows.clear(Color::White);
		gallowsSprite.setTextureRect(IntRect(game.getWidthGallows(), 0, 800, 1000));
		gallowsSprite.setPosition(0, 0);
		Gallows.draw(gallowsSprite);
		frameSprite.setPosition(800, 0);
		Gallows.draw(frameSprite);
		if (!game.getWIN()&&!game.getDefeat()) {
			for (int i{ 360 }, h{ 1 }; h < 7; i += game.getHeightLetter(), h++) {
				for (int j{ 900 }, w{ 1 }; w < 7; j += game.getWidthLetter(), w++) {
					if (i == 810 && w > 3) continue;
					lSprite.setTextureRect(IntRect(game.getAlphabet(h,w) * game.getWidthLetter(), 0, 
													game.getWidthLetter(), game.getHeightLetter()));
					lSprite.setPosition(j, i);
					Gallows.draw(lSprite);
				}
			}
			for (int i{ 950 }, j{ 1 }; j < game.getSize(); i += game.getWidthLetter(), j++) {
				lSprite.setTextureRect(IntRect(game.getGridView(j) * game.getWidthLetter(), 0, 
												game.getWidthLetter(), game.getHeightLetter()));
				lSprite.setPosition(i, 150);
				Gallows.draw(lSprite);
			}
		}
		if (game.getWIN()) {
			winSprite.setPosition(900, 150);
			Gallows.draw(winSprite);
			menuSprite.setPosition(970, 540);
			Gallows.draw(menuSprite);
		}
		if (game.getDefeat()) {
			loseSprite.setPosition(900, 150);
			Gallows.draw(loseSprite);
			menuSprite.setPosition(970, 540);
			Gallows.draw(menuSprite);
		
		}
		Gallows.display();

	}
	return 0;
}