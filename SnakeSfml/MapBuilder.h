#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include<ctime>
#include<fstream>

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


using namespace sf;
PointMap* Root;
Texture t1;
Sprite Wallsp;
Sprite Feldsp;


void AddToMap(PointMap* F, PointMap* P)
{
	if (P == nullptr)
		return;

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



bool WAAAAATHQMWAAAAAAAAAAALQM(int x, int y, PointMap* F)
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

void Delite_From_Map(int x, int y, PointMap* F)
{
	PointMap* xxyy;
	PointMap* XXyy;
	PointMap* xxYY;
	PointMap* XXYY;

	if ((x >= F->x) && (y >= F->y))
	{
		if ((x == F->x) && (y == F->y))
		{
			xxyy = F->xy;
			XXyy = F->Xy;
			XXYY = F->XY;
			xxYY = F->xY;
			if (F->Parent->XY == F)
			{
				F->Parent->XY = nullptr;
			}
			else if (F->Parent->Xy == F)
			{
				F->Parent->Xy = nullptr;
			}
			else if (F->Parent->xy == F)
			{
				F->Parent->xy = nullptr;
			}
			else if (F->Parent->xY == F)
			{
				F->Parent->xY = nullptr;
			}
			delete F;
			AddToMap(Root,xxyy);
			AddToMap(Root,XXyy);
			AddToMap(Root, xxYY);
			AddToMap(Root, XXYY);
			return;
		}
		else
			Delite_From_Map(x, y, F->XY);
	}

	else if ((x < F->x) && (y >= F->y))
	{
		Delite_From_Map(x,y,F->xY);
	}

	else if ((x < F->x) && (y < F->y))
	{
		Delite_From_Map(x, y, F->xy);
	}

	else if ((x >= F->x) && (y < F->y))
	{
		Delite_From_Map(x, y, F->Xy);
	}
}

void Writhe_to_File(std::ofstream& F, PointMap* RRoot)
{
	if (RRoot == nullptr)
		return;	
	F << -1 << " " << RRoot->x << " " << RRoot->y;
	Writhe_to_File(F, RRoot->xy);
	Writhe_to_File(F, RRoot->xY);
	Writhe_to_File(F, RRoot->Xy);
	Writhe_to_File(F, RRoot->XY);
}

void Save(int weig,int hei)
{
	std::ofstream F;
	F.open("data/Maps/M.txt");
	F << weig << " " << hei<<" ";
	Writhe_to_File(F, Root);
}


void DrawMap(PointMap* FMMap,RenderWindow &SnakeW)
{
	if (FMMap == nullptr)
		return;
	Wallsp.setPosition(FMMap->x * 18, FMMap->y * 18); 
	SnakeW.draw(Wallsp);
	DrawMap(FMMap->xY,SnakeW);
	DrawMap(FMMap->Xy,SnakeW);
	DrawMap(FMMap->xy,SnakeW);
	DrawMap(FMMap->XY,SnakeW);
}

void Draw(RenderWindow&SnakeW,int weig,int hei)
{
	SnakeW.clear();
	for (int i = 0; i < hei; i++)
	{
		for (int j = 0; j < weig; j++)
		{
			Feldsp.setPosition(j * 18, i * 18);  SnakeW.draw(Feldsp);
		}
	}
	DrawMap(Root, SnakeW);
}

void MapBuilder(int weig, int hei)
{
	int x, y,x0,x1,y0,y1;
	RenderWindow SnakeW(VideoMode(18 * weig, 18 * hei), "MapBuilder");
	Root = nullptr;
	t1.loadFromFile("data/SNAKE.png");
	Feldsp.setTexture(t1); Feldsp.setTextureRect(IntRect(54, 0, 18, 18));
	Wallsp.setTexture(t1); Wallsp.setTextureRect(IntRect(0, 0, 18, 18));
	Root = new PointMap;
	Root->x = -10; Root->y = -10;
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
		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			x = (int)Mouse::getPosition(SnakeW).x/18;
			y = (int)Mouse::getPosition(SnakeW).y/18;
			if (WAAAAATHQMWAAAAAAAAAAALQM(x, y, Root))
			{

				Delite_From_Map(x, y, Root);
			}
			else
			{
				PointMap* NNew = new PointMap;
				NNew->x = x; NNew->y = y;
				AddToMap(Root, NNew);
			}
			while (Mouse::isButtonPressed(Mouse::Button::Left))
			{
				Sleep(1);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			Save(weig, hei);
		}
		else if (Mouse::isButtonPressed(Mouse::Button::Right))
		{
			x0 = (int)Mouse::getPosition(SnakeW).x / 18;
			y0 = (int)Mouse::getPosition(SnakeW).y / 18;
			while (!(Mouse::isButtonPressed(Mouse::Button::Left)))
			{
				Sleep(1);
			}
			x1 = (int)Mouse::getPosition(SnakeW).x / 18;
			y1 = (int)Mouse::getPosition(SnakeW).y / 18;
			
			while (Mouse::isButtonPressed(Mouse::Button::Left))
			{
				Sleep(1);
			}

			if (x0 == x1)
			{
				if (y0 < y1)
				{
					for (int i = y0; i <= y1; i++)
					{
						PointMap* NNew = new PointMap;
						NNew->x = x0; NNew->y = i;
						AddToMap(Root, NNew);
					}
				}
				else if (y0 >= y1)
				{
					for (int i = y1; i <= y0; i++)
					{
						PointMap* NNew = new PointMap;
						NNew->x = x0; NNew->y = i;
						AddToMap(Root, NNew);
					}
				}
			}
			else if (y0 == y1)
			{
				if (x0 < x1)
				{
					for (int i = x0; i <= x1; i++)
					{
						PointMap* NNew = new PointMap;
						NNew->x = i; NNew->y = y0;
						AddToMap(Root, NNew);
					}
				}
				else if (x0 >= x1)
				{
					for (int i = x1; i <= x0; i++)
					{
						PointMap* NNew = new PointMap;
						NNew->x = i; NNew->y = y0;
						AddToMap(Root, NNew);
					}
				}
			}
			
		}
		Draw(SnakeW, weig, hei);
		SnakeW.display();
	}
	return;
}