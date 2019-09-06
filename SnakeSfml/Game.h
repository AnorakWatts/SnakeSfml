#include <iostream>
#include<SFML/Graphics.hpp>
#include <windows.h>
using namespace sf;

class Game
{
public:
	Game(RenderWindow& window, Texture& Texttture) : SnakeW(window), Textture(Texttture)
	{
		srand(time(NULL));
		SN.Head = new PointSnake;
		FMap = nullptr;
		Fruitsp.setTexture(Textture); Fruitsp.setTextureRect(IntRect(18, 0, 18, 18));
		Snakesp.setTexture(Textture); Snakesp.setTextureRect(IntRect(36, 0, 18, 18));
		SHeadsp.setTexture(Textture); SHeadsp.setTextureRect(IntRect(72, 0, 18, 18));
		Feldsp.setTexture(Textture); Feldsp.setTextureRect(IntRect(54, 0, 18, 18));
		Wallsp.setTexture(Textture); Wallsp.setTextureRect(IntRect(0, 0, 18, 18));
	}
	~Game(){}

	void PPlay(int tailllen,FILE*Map)
	{
		SN.mv = Stop;
		SN.Head->Prev = nullptr;
		Score = 0;
		taillen = tailllen;

		Font font;
		font.loadFromFile("data/CyrilicOld.ttf");
		SScore.setFont(font);
		SScore.setPosition(0, 0);
		SScore.setStyle(sf::Text::Bold | sf::Text::Underlined);
		SScore.setOutlineColor(Color::Blue);
		SScore.setFillColor(Color::Blue);
		SScore.setString("Score: " + std::to_string(Score));
		MapLoad(Map);
		Build();
		MakeNewFrut();
		while (SnakeW.isOpen())
		{
			while (!GameOver)
			{
				sf::Event event;
				while (SnakeW.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
					{
						SnakeW.close();
						return;
					}
				}
				Graphics();
				if ((SN.Head->x == Fruit.x) && (SN.Head->y == Fruit.y))
					Eat();
				Control();
				Move();
				if (WAAAAATHQMWAAAAAAAAAAALQM(SN.Head->x, SN.Head->y, FMap))
				{
					GameOver = 1;
				}
				CutTail();
				EndOfMapQM();
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					Sleep(20);
				}
				else
					Sleep(60);
			}

			SScore.setString("Game Over Score: " + std::to_string(Score));
			SScore.setCharacterSize(50);
			SScore.setPosition(weig / 2, hei / 2);
				SnakeW.clear();
				for (int i = 0; i < hei; i++)
				{
					for (int j = 0; j < weig; j++)
					{
						Feldsp.setPosition(j * 18, i * 18);  SnakeW.draw(Feldsp);
					}
				}
				DrawMap(FMap);
				DrawSnake(SN.EndTail);
				SHeadsp.setPosition(SN.Head->x * 18, SN.Head->y * 18); SnakeW.draw(SHeadsp);
				Fruitsp.setPosition(Fruit.x * 18, Fruit.y * 18); SnakeW.draw(Fruitsp);
				SnakeW.draw(SScore);
				SnakeW.display();
				Sleep(3000);
				SnakeW.close();
			
		}
	}

private:
	bool CutQM = 0;
	bool GameOver = 0;
	struct PointMap
	{
		PointMap* Parent;
		PointMap* XY;
		PointMap* Xy;
		PointMap* xY;
		PointMap* xy;
		int x;
		int y;

		PointMap()
		{
			x = 0;
			y = 0;
			Xy = nullptr;
			xY = nullptr;
			XY = nullptr;
			xy = nullptr;
		}
	};

	struct PointSnake
	{
		int x;
		int y;
		PointSnake* Prev;
		PointSnake()
		{
			x = 0; y = 0;
		}
	};

	enum EDirections { Stop = 0, Left, Right, Up, Down };

	struct Snake
	{
		PointSnake* Head, * EndTail;
		EDirections mv;
	};

	struct Fruittt
	{
		int x, y;
	};

	Fruittt Fruit;
	Snake SN;
	PointMap* FMap;
	int weig, hei;
	RenderWindow& SnakeW;
	Texture& Textture;
	Sprite Fruitsp;
	Sprite Snakesp;
	Sprite SHeadsp;
	Sprite Feldsp;
	Sprite Wallsp;
	Text SScore;
	int Score;
	int taillen;
	
	void AddToMap(PointMap* F, PointMap* P) 
	{
	
		if ((P->x >= F->x) && (P->y >= F->y))
		{
			if (F->XY != nullptr)
			{
				AddToMap(F->XY, P);
			}
			else
			{
				F->XY = P;
				P->Parent = F;
				return;
			}
		}

		else if ((P->x < F->x) && (P->y >= F->y))
		{
			if (F->xY != nullptr)
			{
				AddToMap(F->xY, P);
			}
			else
			{
				F->xY = P;
				P->Parent = F;
				return;
			}
		}

		else if ((P->x < F->x) && (P->y < F->y))
		{
			if (F->xy != nullptr)
			{
				AddToMap(F->xy, P);
			}
			else
			{
				F->xy = P;
				P->Parent = F;
				return;
			}
		}

		else if ((P->x >= F->x) && (P->y < F->y))
		{
			if (F->Xy != nullptr)
			{
				AddToMap(F->Xy, P);
			}
			else
			{
				F->Xy = P;
				P->Parent = F;
				return;
			}
		}
	}

	void MapLoad(FILE* F)
	{
		int c = 0;
		int x = 0, y = 0;
		rewind(F);
		fscanf_s(F, "%d", &weig);
		fscanf_s(F, "%d", &hei);

		while ((fscanf_s(F, "%d", &c) != EOF))
		{
			fscanf_s(F, "%d", &x);
			fscanf_s(F, "%d", &y);
			PointMap* NNew = new PointMap();
			NNew->x = x;
			NNew->y = y;
			if (FMap == nullptr)
			{
				FMap = NNew;
			}
			else
				AddToMap(FMap, NNew);

		}
	}

	bool WAAAAATHQMWAAAAAAAAAAALQM(int x, int y,PointMap*F)
	{
		if ((x >= F->x) && (y >= F->y))
		{
			if (F->XY != nullptr)
			{
				if ((x == F->x) && (y == F->y))
					return 1;
				else
				{
					return WAAAAATHQMWAAAAAAAAAAALQM(x, y, F->XY);
				}
			}
			if ((x == F->x) && (y == F->y))
				return 1;
			return 0;
		}

		if ((x < F->x) && (y >= F->y))
		{
			if (F->xY != nullptr)
			{
				return WAAAAATHQMWAAAAAAAAAAALQM(x, y, F->xY);
			}
			return 0;
		}

		if ((x < F->x) && (y < F->y))
		{
			if (F->xy != nullptr)
			{
				return WAAAAATHQMWAAAAAAAAAAALQM(x, y, F->xy);
			}
			return 0;
		}

		if ((x >= F->x) && (y < F->y))
		{
			if (F->Xy != nullptr)
			{
				return WAAAAATHQMWAAAAAAAAAAALQM(x, y, F->Xy);
			}
			return 0;
		}
	}

	void MakeNewFrut()
	{
		int x, y;
		x = (rand() % weig);
		y = (rand() % hei);
		while (WAAAAATHQMWAAAAAAAAAAALQM(x, y, FMap))
		{
			x = (rand() % weig);
			y = (rand() % hei);
		}
		Fruit.x = x;
		Fruit.y = y;
		if (WAAAAATHQMWAAAAAAAAAAALQM(x-1,y,FMap)||WAAAAATHQMWAAAAAAAAAAALQM(x+1,y,FMap)||WAAAAATHQMWAAAAAAAAAAALQM(x,y+1,FMap)||WAAAAATHQMWAAAAAAAAAAALQM(x,y-1,FMap))
		{
			MakeNewFrut();
		}
	}
	
	void EndOfMapQM()
	{
		if (SN.Head->x == weig)
			SN.Head->x = -1;
		else if (SN.Head->x == -2)
			SN.Head->x = weig;
		else if (SN.Head->y == hei)
			SN.Head->y = -1;
		else if (SN.Head->y == -2)
			SN.Head->y = hei;
		
	}

	void Move()
	{
		if (SN.mv != Stop)
		{
			PointSnake* S;
			S = SN.EndTail;
			while (S->Prev != nullptr)
			{
				S->x = S->Prev->x;
				S->y = S->Prev->y;
				S = S->Prev;
			}
			switch (SN.mv)
			{
			case Left:
				SN.Head->x--;
				break;
			case Right:
				SN.Head->x++;
				break;
			case Up:
				SN.Head->y--;
				break;
			case Down:
				SN.Head->y++;
				break;
			}
		}
	}

	void Eat()
	{
		PointSnake* NNew = new PointSnake;
		NNew->Prev = SN.EndTail;
		SN.EndTail = NNew;
		MakeNewFrut();
		Score += 10;
		SScore.setString("Score: " + std::to_string(Score));
	}

	void CutTail()
	{

		PointSnake* S, * SS, * SSS;
		S = SN.EndTail;
		SS = S;
		while (S != SN.Head)
		{
			if ((S->x == SN.Head->x) && (S->y == SN.Head->y))
			{
				SN.EndTail = S;
				break;
			}
			S = S->Prev;
		}
		if (S != SN.Head)
		{
			if (CutQM == 1)
			{
				while (SS != S)
				{
					SSS = SS->Prev;
					delete SS;
					SS = SSS;
					Score -= 10;
				}
			}
			else GameOver = 1;
		}
	}
		

	void Control()
	{
		if (Keyboard::isKeyPressed(Keyboard::Left)) { if ((SN.mv != Right) && (SN.mv != Stop))SN.mv = Left; }
		else if (Keyboard::isKeyPressed(Keyboard::Right)) { if (SN.mv != Left) SN.mv = Right; }
		else if (Keyboard::isKeyPressed(Keyboard::Up)) { if (SN.mv != Down)SN.mv = Up; }
		else if (Keyboard::isKeyPressed(Keyboard::Down)) { if (SN.mv != Up)SN.mv = Down; }
		else if (Keyboard::isKeyPressed(Keyboard::P)) { SN.mv = Stop; }
		else if (Keyboard::isKeyPressed(Keyboard::C)) { CutQM = !CutQM; Beep(250, 250); }
	}

	void Build()
	{
		SN.Head->x = weig / 2;
		SN.Head->y = hei / 2;

		PointSnake* NNew = new PointSnake;
		NNew->x = SN.Head->x - 1;
		NNew->y = SN.Head->y;
		NNew->Prev = SN.Head;
		SN.EndTail = NNew;

		for (int i=2; i <= taillen; i++)
		{
			PointSnake* NNew = new PointSnake;
			NNew->x = SN.Head->x - i;
			NNew->y = SN.Head->y;
			NNew->Prev = SN.EndTail;
			SN.EndTail = NNew;
		}
		SN.mv = Right;
		Move();
		SN.mv = Stop;
	}

	void DrawMap(PointMap*FMMap)
	{
		if (FMMap == nullptr)
			return;
		Wallsp.setPosition(FMMap->x * 18, FMMap->y * 18); SnakeW.draw(Wallsp);
		DrawMap(FMMap->xY);
		DrawMap(FMMap->Xy);
		DrawMap(FMMap->xy);
		DrawMap(FMMap->XY);
	}

	void DrawSnake(PointSnake* ETT)
{
	PointSnake* ET = ETT;
	int i = 0;
	while (i != 1)
	{
		if ((ET == nullptr) || (ET == SN.Head))
			return;
		Snakesp.setPosition(ET->x * 18, ET->y * 18);
		SnakeW.draw(Snakesp);
		ET=ET->Prev;
	}
}
	
	void Graphics()
	{
		Vector2f targetSize(15, 15);
		Snakesp.setScale(
			targetSize.x / Snakesp.getLocalBounds().width,
			targetSize.y / Snakesp.getLocalBounds().height);
		SnakeW.clear();
		for (int i = 0; i < hei; i++)
		{
			for (int j = 0; j < weig; j++)
			{
				Feldsp.setPosition(j * 18, i * 18);  SnakeW.draw(Feldsp);
			}
		}
		DrawMap(FMap);
		DrawSnake(SN.EndTail);
		SHeadsp.setPosition(SN.Head->x * 18, SN.Head->y * 18); SnakeW.draw(SHeadsp);
		Fruitsp.setPosition(Fruit.x * 18, Fruit.y * 18); SnakeW.draw(Fruitsp);
		SnakeW.draw(SScore);
		SnakeW.display();
	}
	
};
