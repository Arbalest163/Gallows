#include <SFML/Graphics.hpp>
#include"Game.h"
using namespace sf;


int main()
{
	srand(time(0));
	setlocale(0, "");
	Game game;
	game.setGridLogic(WordStr{});
	RenderWindow Gallows(VideoMode(1530, 1000), "The Gallows!", Style::Close);
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
					int x{ (pos.x - 810) / game.getWidthLetter() };
					int y{ (pos.y - 270) / game.getHeightLetter() };
					if (!game.getWIN() && !game.getDefeat()) {
						if (pos.x > 900 && pos.x < 1440 && pos.y > 360 && pos.y < 900) {
							if (pos.x > 1170 && pos.y > 810) continue;
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
								}
							} else game.setAlphabet(y, x, 68);
							
						}
					}
					else {
						if (pos.x > 1030 && pos.x < 1330 && pos.y > 670 && pos.y < 730) {
							game.resetGame();
							
						
						}
						if (pos.x > 1030 && pos.x < 1330 && pos.y > 745 && pos.y < 805) {
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
			
		}
		for (int i{ game.getSize() > 6 ? 900 : 950 }, j{ 1 }; j < game.getSize(); i += game.getWidthLetter(), j++) {
			lSprite.setTextureRect(IntRect(game.getGridView(j) * game.getWidthLetter(), 0,
				game.getWidthLetter(), game.getHeightLetter()));
			lSprite.setPosition(i, 150);
			Gallows.draw(lSprite);
		}
		if (game.getWIN()) {
			winSprite.setPosition(900, 250);
			Gallows.draw(winSprite);
			menuSprite.setPosition(970, 640);
			Gallows.draw(menuSprite);
		}
		if (game.getDefeat()) {
			loseSprite.setPosition(900, 250);
			Gallows.draw(loseSprite);
			menuSprite.setPosition(970, 640);
			Gallows.draw(menuSprite);
		
		}
		Gallows.display();

	}
	return 0;
}