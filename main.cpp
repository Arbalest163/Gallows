#include <SFML/Graphics.hpp>
#include"Game.h"
#include<sstream>
using namespace sf;


int main()
{
	srand(time(0));
	//setlocale(0, "");
	Font font;
	font.loadFromFile("Font.ttf");
	Text text("", font, 50);
	Text textClock("", font, 50);
	Text ClockStop;
	text.setFillColor(Color::Black);
	textClock.setFillColor(Color::Black);
	Clock clock;
	text.setPosition(1510, 150);
	textClock.setPosition(1510, 80);
	Game game;
	game.setGridLogic(WordStr{});
	RenderWindow Gallows(VideoMode(1920, 1000), "The Gallows!", Style::Close);
	Texture gallowsTexture;
	gallowsTexture.loadFromFile("GallowsTexture.png");
	Sprite gallowsSprite(gallowsTexture);
	Texture frame;
	frame.loadFromFile("Ramka.png");
	Sprite frameSprite(frame);
	Texture letters;
	letters.loadFromFile("letterstr.png");
	Sprite lSprite(letters);
	Texture win;
	win.loadFromFile("win.png");
	Sprite winSprite(win);
	Texture lose;
	lose.loadFromFile("lose.png");
	Sprite loseSprite(lose);
	Texture menu;
	menu.loadFromFile("menu.png");
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
					int x{ (pos.x - 790) / game.getWidthLetter() };
					int y{ (pos.y - 270) / game.getHeightLetter() };
					if (!game.getWIN() && !game.getDefeat()) {
						if (pos.x > 880 && pos.x < 1420 && pos.y > 360 && pos.y < 900) {
							if (pos.x > 1150 && pos.y > 810) continue;
							bool flag{ false };
							for (int k{ 1 }; k < game.getSize(); k++) {
								if (game.getAlphabet(y, x) == game.getGridLogic(k)) {
									game.getGridView(k) = game.getGridLogic(k);
									flag = true;
								} 
							}
							if (!flag) {
								if (!game.getWIN() && !game.getDefeat() && game.getAlphabet(y, x) < 34) {
									game.setAlphabet(y, x, 34);
									game.setWidthGallows(800);
									game.setDefeat();
									game.setCountLetters()--;
								}
							} else game.setAlphabet(y, x, 68);
							
						}
					}
					else {
						if (pos.x > 1010 && pos.x < 1310 && pos.y > 670 && pos.y < 730) {
							game.resetGame();
							
						
						}
						if (pos.x > 1010 && pos.x < 1310 && pos.y > 745 && pos.y < 805) {
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
		std::ostringstream countLetters;
		std::ostringstream countClock;
		countLetters << game.getCountLetters();
		int time{ static_cast<int>(clock.getElapsedTime().asSeconds()) };
		countClock << time;
		text.setString(L"Попытки:" + countLetters.str());
		textClock.setString(L"Время:" + countClock.str());
		Gallows.draw(text);
		if (!game.getWIN() && !game.getDefeat()) {
			ClockStop = textClock;
			Gallows.draw(textClock);
		}
		else {
			Gallows.draw(ClockStop);
			clock.restart();
		}
		if (!game.getWIN()&&!game.getDefeat()) {
			for (int i{ 360 }, h{ 1 }; h < 7; i += game.getHeightLetter(), h++) {
				for (int j{ 880 }, w{ 1 }; w < 7; j += game.getWidthLetter(), w++) {
					if (i == 810 && w > 3) continue;
					lSprite.setTextureRect(IntRect(game.getAlphabet(h,w) * game.getWidthLetter(), 0, 
													game.getWidthLetter(), game.getHeightLetter()));
					lSprite.setPosition(j, i);
					Gallows.draw(lSprite);
				}
			}
			
		}
		for (int i{ game.getSize() > 6 ? 870 : 920 }, j{ 1 }; j < game.getSize(); i += game.getWidthLetter(), j++) {
			lSprite.setTextureRect(IntRect(game.getGridView(j) * game.getWidthLetter(), 0,
				game.getWidthLetter(), game.getHeightLetter()));
			lSprite.setPosition(i, 150);
			Gallows.draw(lSprite);
		}
		if (game.getWIN()) {
			winSprite.setPosition(880, 250);
			Gallows.draw(winSprite);
			menuSprite.setPosition(950, 640);
			Gallows.draw(menuSprite);
		}
		if (game.getDefeat()) {
			loseSprite.setPosition(880, 250);
			Gallows.draw(loseSprite);
			menuSprite.setPosition(950, 640);
			Gallows.draw(menuSprite);
		
		}
		
		Gallows.display();

	}
	return 0;
}