#include<iostream>
#include"Game.h"
#include"MapBuilder.h"
#include <stdio.h>
void Menu();
void Play(int taillen)
{
	int weig, hei;
	FILE* Map;
	fopen_s(&Map, "data/Maps/M.txt", "r");
	fscanf_s(Map, "%d", &weig);
	fscanf_s(Map, "%d", &hei);
	rewind(Map);
	RenderWindow SnakeW(VideoMode(18 * weig, 18 * hei), "Snake");
	Texture t1; t1.loadFromFile("data/SNAKE.png");
	Game GN(SnakeW, t1);
	GN.PPlay(taillen, Map);
	Menu();
}


void Menu()
{ 
	
	int x, y;
	RenderWindow MenuW(VideoMode(720, 480), "Menu");
	Texture T;
	T.loadFromFile("data/Menu.png");
	Sprite M;
	M.setTexture(T);
	M.setTextureRect(IntRect(0, 0, 720, 480));
	M.setPosition(0, 0);
	MenuW.draw(M);
	MenuW.display();
	while (MenuW.isOpen())
	{
		sf::Event event;
		while (MenuW.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				MenuW.close();
			}
		}
		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			x = (int)Mouse::getPosition(MenuW).x;
			y = (int)Mouse::getPosition(MenuW).y;

			if ((x >= 30) && (x <= 350) && (y >= 180) && (y <= 280))
			{
				MenuW.close();
				Play(1);
			}
			if ((x >= 30) && (x <= 350) && (y >= 300) && (y <= 400))
			{
				//MenuW.close;
				MapBuilder(40, 30);
			}
		}
	}
	
}


int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	Menu();
}