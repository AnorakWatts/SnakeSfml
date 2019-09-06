#include<iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include<ctime>
using namespace sf;
struct PointMap
{
	int x;
	int y;
};

enum EDirections { Stop = 0, Left, Right, Up, Down };

class Snake
{
public:
	Snake(int taille, int hei, int weig)
	{
		s = (PointMap*)malloc(sizeof(PointMap) * (hei * weig+taille));
		s[0].x = weig / 2;
		s[0].y = hei / 2;
		for (int i = 1; i <= taille; i++)
		{
			s[i].y = s[0].y;
			s[i].x = s[0].x + i;
		}
		TAillen = taille;
		BaseTaillen = taille;
		mv = Stop;
		Mhei = hei;
		Mwei = weig;
	}
	~Snake()
	{
		TAillen = 0;
		mv = Stop;
	}

	void Movemv()
	{
		Move(mv);
	}

	void Move(EDirections mv)
	{
		if (mv != Stop)
		{
			for (int i = TAillen + 1; i >= 1; i--)
			{
				s[i].x = s[i - 1].x;
				s[i].y = s[i - 1].y;
			}
		}

		switch (mv)
		{
		case Left:
			s[0].x--;
			break;
		case Right:
			s[0].x++;
			break;
		case Up:
			s[0].y--;
			break;
		case Down:
			s[0].y++;
			break;
		}
	}

	void Eat()
	{
		TAillen += 1;
		Move(mv);
	}

	void End_Map()
	{
		switch (mv)
		{
		case Left:
			s[0].x = Mwei;
			break;
		case Right:
			s[0].x = 0;
			break;
		case Up:
			s[0].y = Mhei;
			break;
		case Down:
			s[0].y = 0;
			break;
		}
	}

	void Restart()
	{
		s[0].x = Mwei / 2;
		s[0].y = Mhei / 2;
		for (int i = 1; i <= BaseTaillen; i++)
		{
			s[i].y = s[0].y;
			s[i].x = s[0].x + i;
		}
		TAillen = BaseTaillen;
		mv = Stop;
	}

	void Control()
	{
		if (Keyboard::isKeyPressed(Keyboard::Left)) { if (mv != Right)mv = Left; }
		else if (Keyboard::isKeyPressed(Keyboard::Right)) { if ((mv != Left) && (mv != Stop))mv = Right; }
		else if (Keyboard::isKeyPressed(Keyboard::Up)) { if (mv != Down)mv = Up; }
		else if (Keyboard::isKeyPressed(Keyboard::Down)) { if (mv != Up)mv = Down; }
		else if (Keyboard::isKeyPressed(Keyboard::R)) { Restart(); }
		else if ((Keyboard::isKeyPressed(Keyboard::Left) && (Keyboard::isKeyPressed(Keyboard::Down)))) { if ((mv != Right) && (mv != Up))Move(Left); Move(Down); }
		else if ((Keyboard::isKeyPressed(Keyboard::Left) && (Keyboard::isKeyPressed(Keyboard::Up)))) { if ((mv != Right) && (mv != Down))Move(Left); Move(Up); }
		else if ((Keyboard::isKeyPressed(Keyboard::Right) && (Keyboard::isKeyPressed(Keyboard::Down)))) { if ((mv != Left) && (mv != Up))Move(Right); Move(Down); }
		else if ((Keyboard::isKeyPressed(Keyboard::Right) && (Keyboard::isKeyPressed(Keyboard::Up)))) { if ((mv != Left) && (mv != Down))Move(Right); Move(Up); }
		else if (Keyboard::isKeyPressed(Keyboard::P)) { mv = Stop; }
	}

	int TAillen;
	PointMap* s;
private:
	EDirections mv;
	int Mhei, Mwei, BaseTaillen;
};

PointMap fruit;

int Snake_Game(int hei, int weig, int taillen)
{
	int Score = 0;
	fruit.x = rand() % weig;
	fruit.y = rand() % hei;
	srand(time(0));
	Texture t1; t1.loadFromFile("images/SNAKE.png");
	Sprite Fruitsp; Fruitsp.setTexture(t1); Fruitsp.setTextureRect(IntRect(18, 0, 18, 18));
	Sprite Snakesp; Snakesp.setTexture(t1); Snakesp.setTextureRect(IntRect(36, 0, 18, 18));
	Sprite SHead; SHead.setTexture(t1); SHead.setTextureRect(IntRect(72, 0, 18, 18));
	Sprite Feldsp; Feldsp.setTexture(t1); Feldsp.setTextureRect(IntRect(54, 0, 18, 18));
	Sprite Wallsp; Wallsp.setTexture(t1); Wallsp.setTextureRect(IntRect(0, 0, 18, 18));
	Snake SN(taillen, hei, weig);
	RenderWindow SnakeW(VideoMode(18 * weig, 18 * hei), "Snake");
	while (SnakeW.isOpen())
	{
		sf::Event event;
		while (SnakeW.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				SnakeW.close();
			}
		}
		SN.Control();
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { SnakeW.close(); }
		SN.Movemv();
		if ((SN.s[0].x < 0) || (SN.s[0].y < 0) || (SN.s[0].x > weig) || (SN.s[0].y > hei))
			SN.End_Map();
		if ((SN.s[0].x == fruit.x) && (SN.s[0].y == fruit.y))
		{
			SN.Eat();
			fruit.x = rand() % weig;
			fruit.y = rand() % hei;
			Score += 10;

		}

		/////////////////Draw////////////////
		SnakeW.clear();
		for (int i = 0; i < hei; i++)
		{
			for (int j = 0; j < weig; j++)
			{
				Feldsp.setPosition(j * 18, i * 18);  SnakeW.draw(Feldsp);
			}
		}
		for (int i = 1; i < SN.TAillen + 1; i++)
		{
			if ((SN.s[0].x == SN.s[i].x) && (SN.s[0].y == SN.s[i].y))
			{
				SN.TAillen = i;
			}
			Snakesp.setPosition(SN.s[i].x * 18, SN.s[i].y * 18);  SnakeW.draw(Snakesp);
		}
		SHead.setPosition(SN.s[0].x * 18, SN.s[0].y * 18);  SnakeW.draw(SHead);
		Fruitsp.setPosition(fruit.x * 18, fruit.y * 18); SnakeW.draw(Fruitsp);
		SnakeW.display();
		Sleep(60);
	}
	return(Score);
}