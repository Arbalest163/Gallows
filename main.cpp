#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int main()
{
	setlocale(0, "");
	RenderWindow Gallows(VideoMode(1542, 1000), "The Gallows!");
	Texture gallowsTexture;
	gallowsTexture.loadFromFile("C:\\SFML-2.5.1\\Gallows\\GallowsTexture.png");
	Sprite g(gallowsTexture);
	Texture ramka;
	ramka.loadFromFile("C:\\SFML-2.5.1\\Gallows\\Ramka.png");
	Sprite r(ramka);
	Texture letters;
	letters.loadFromFile("C:\\SFML-2.5.1\\Gallows\\letters.png");
	Sprite l(letters);
	int wG = 800; // Ширина текстуры виселицы
	int wL = 90; // ширина буквы
	int hL = 90; // высота буквы
	int gridLogic[6][6]{0};
	int gridView[6][6]{0};
	std::string word("CЛОВО");
	RectangleShape rectangle(Vector2f(540.f, 540.f));
	rectangle.move(900, 400);
	rectangle.setFillColor(Color::Red);
	int count{ 800 };
	while (Gallows.isOpen())
	{
		Vector2i pos = Mouse::getPosition(Gallows);
		int x = pos.x / wL;
		int y = pos.y / hL;
		Event event;
		Gallows.clear(Color::White);
		r.setPosition(800,0);
		l.setPosition(900, 400);
		
		while (Gallows.pollEvent(event))
		{
			if (event.type == Event::Closed)
				Gallows.close();
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left) {
					if(pos.x > 900 && pos.x<1440 && pos.y > 400 && pos.y < 940)
					count += wG;
				}
		}
		g.setTextureRect(IntRect(count, 0, 800, 1000));
		g.setPosition(0, 0);
		Gallows.draw(rectangle);
		Gallows.draw(g);
		Gallows.draw(r);
		Gallows.draw(l);
		
		Gallows.display();

	}
	return 0;
}