/*
Author: Mohammad Adnaan
Class: ECE6122
Last Date Modified: 24 Oct , 2021
Description:
functions related to collision detection and its impacts
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include<array>
#include <algorithm>
#include "elements.h"
using namespace std;

extern int clearRow;

char collision(Bee& jacket, ColumnArrange& columns, Insect& roach, int& columnNumber, int& columnPosition)
{
	//detects if any collision occurs and with which object

	sf::Vector2f beeCenter = jacket.beeStrike.getPosition();
	sf::Vector2f insectCenter = roach.fly.getPosition();
	array<float, 5> distanceColumn1, distanceColumn2;

	float insectCollisionDistance = jacket.beeStrike.getSize().y / 2 + roach.fly.getSize().y / 2;
	float animalCollisionDistance = columns.icons1[0].getSize().x / 2 + columns.icons1[0].getSize().x / 2;
	float distanceFromInsect = sqrt(pow((beeCenter.x - insectCenter.x), 2) + pow((beeCenter.y - insectCenter.y), 2));

	if (distanceFromInsect < insectCollisionDistance)
	{
		columnNumber = 0;
		columnPosition = 0;
		return 'I';
	}

	for (int i = 0; i < 5; i++)
	{
		distanceColumn1[i] = sqrt(pow((beeCenter.x - columns.icons1[i].getPosition().x), 2) + pow((beeCenter.y - columns.icons1[i].getPosition().y), 2));
		distanceColumn2[i] = sqrt(pow((beeCenter.x - columns.icons2[i].getPosition().x), 2) + pow((beeCenter.y - columns.icons2[i].getPosition().y), 2));

	}

	auto minimum1 = std::min_element(std::begin(distanceColumn1), std::end(distanceColumn1));
	auto minimum2 = std::min_element(std::begin(distanceColumn2), std::end(distanceColumn2));
	if (*minimum1 <= *minimum2 && (*minimum1 < animalCollisionDistance))
	{
		for (int i = 0; i < 5; i++)
		{
			if (distanceColumn1[i] == *minimum1)
			{
				columnNumber = 1;
				if (columns.unicornHit && (columns.unicornColumn == 1) && (i < columns.unicornRow))
				{
					columnPosition = i;
					return columns.column1[i+1];
				}
				else
				{
					columnPosition = i;
					return columns.column1[i];
				}
				
			}
		}
	}
	else if((*minimum2 < animalCollisionDistance))
	{
		for (int i = 0; i < 5; i++)
		{
			if (distanceColumn2[i] == *minimum2)
			{
				columnNumber = 2;
				if (columns.unicornHit && (columns.unicornColumn == 2) && (i < columns.unicornRow))
				{
					columnPosition = i ;
					return columns.column2[i + 1];
				}
				else
				{
					columnPosition = i;
					return columns.column2[i];
				}
			}
		}
	}
	return 'N';
}


void collisionImpact(char& collisonElement, sf::RenderWindow& window, Bee& jacket, ColumnArrange& columns, Insect& roach, AllText& text, int& columnNumber, int& columnPosition, BeeLife& lifeNumber, array<sf::SoundBuffer, 9>& soundEffectBuffer, array<sf::Sound, 9>& gameSound)
{
	//makes decision based on collided object

	int scoreUpdate = 0;
	switch (collisonElement)
	{
	case 'I':
		gameSound[4].play();
		scoreUpdate = text.scoreValue +75;
		text.scoreSet(scoreUpdate);
		roach.fly.setPosition(sf::Vector2f(window.getSize().x+1000,- 1000));
		jacket.beeStrike.setPosition(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000));

		break;

	case 'U':
		gameSound[3].play();
		lifeNumber.increaseLife();
		if (columnNumber == 1)
		{
			columns.icons1[columnPosition].setPosition(sf::Vector2f(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000)));
		}
		else
		{
			columns.icons2[columnPosition].setPosition(sf::Vector2f(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000)));
		}

		if (columnPosition > 0 && columnNumber == 1)
		{
			for (int i = 0; i < columnPosition; i++)
			{
				columns.translate1[i] = 0.5;
				columns.column1[columnPosition - i] = columns.column1[columnPosition - i - 1];
				
			}
			columns.unicornHit = 1;
			columns.column1[0] = 'N';
			for (auto& x : columns.column1) cout << x << endl;
		}
		else if (columnPosition > 0 && columnNumber == 2)
		{
			for (int i = 0; i < columnPosition; i++)
			{
				columns.translate2[i] = 0.5;

				columns.column2[columnPosition-i] = columns.column2[columnPosition-i-1];
				
			}
			columns.unicornHit = 1;
			columns.column2[0] = 'N';
		}

		jacket.beeStrike.setPosition(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000));
		break;

	case 'B':
		gameSound[1].play();
		lifeNumber.decreaseLife();
		if (columnNumber == 1)
		{
			columns.rotation1[columnPosition] = 0.5;
			columns.translate1[columnPosition] = 0.5;
		}
		else
		{
			columns.rotation2[columnPosition] = 0.5;
			columns.translate2[columnPosition] = 0.5;
		}
		jacket.beeStrike.setPosition(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000));
		break;
	case 'C':
		gameSound[1].play();
		lifeNumber.decreaseLife();
		if (columnNumber == 1)
		{
			columns.rotation1[columnPosition] = 0.5;
			columns.translate1[columnPosition] = 0.5;
		}
		else
		{
			columns.rotation2[columnPosition] = 0.5;
			columns.translate2[columnPosition] = 0.5;
		}
		jacket.beeStrike.setPosition(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000));
		break;

	case 'D':
		gameSound[1].play();
		lifeNumber.decreaseLife();
		if (columnNumber == 1)
		{
			columns.rotation1[columnPosition] = 0.5;
			columns.translate1[columnPosition] = 0.5;
		}
		else
		{
			columns.rotation2[columnPosition] = 0.5;
			columns.translate2[columnPosition] = 0.5;
		}
		jacket.beeStrike.setPosition(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000));
		break;
	case 'F':
		gameSound[1].play();
		lifeNumber.decreaseLife();
		if (columnNumber == 1)
		{
			columns.rotation1[columnPosition] = 0.5;
			columns.translate1[columnPosition] = 0.5;
		}
		else
		{
			columns.rotation2[columnPosition] = 0.5;
			columns.translate2[columnPosition] = 0.5;
		}
		jacket.beeStrike.setPosition(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000));
		break;

	case 'M':
		gameSound[1].play();
		lifeNumber.decreaseLife();
		if (columnNumber == 1)
		{
			columns.rotation1[columnPosition] = 0.5;
			columns.translate1[columnPosition] = 0.5;
		}
		else
		{
			columns.rotation2[columnPosition] = 0.5;
			columns.translate2[columnPosition] = 0.5;
		}
		jacket.beeStrike.setPosition(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000));
		break;

	case 'P':
		gameSound[1].play();
		lifeNumber.decreaseLife();
		if (columnNumber == 1)
		{
			columns.rotation1[columnPosition] = 0.5;
			columns.translate1[columnPosition] = 0.5;
		}
		else
		{
			columns.rotation2[columnPosition] = 0.5;
			columns.translate2[columnPosition] = 0.5;
		}
		jacket.beeStrike.setPosition(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000));
		break;

	case 'S':
		gameSound[1].play();
		lifeNumber.decreaseLife();
		if (columnNumber == 1)
		{
			columns.rotation1[columnPosition] = 0.5;
			columns.translate1[columnPosition] = 0.5;
		}
		else
		{
			columns.rotation2[columnPosition] = 0.5;
			columns.translate2[columnPosition] = 0.5;
		}
		jacket.beeStrike.setPosition(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000));
		break;

	case 'V':
		gameSound[2].play();
		scoreUpdate = text.scoreValue + 25;
		text.scoreSet(scoreUpdate);
		if (columnNumber == 1)
		{
			for (int i = 0; i < 5; i++)
			{
				columns.rotation1[i]=0.5;
				columns.translate1[i] = 0.5;
			}

		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				columns.rotation2[i] = 0.5;
				columns.translate2[i] = 0.5;
			}
		}
		jacket.beeStrike.setPosition(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000));
		clearRow++;
		break;

	case 'T':
		gameSound[2].play();
		scoreUpdate = text.scoreValue + 25;
		text.scoreSet(scoreUpdate);
		if (columnNumber == 1)
		{
			for (int i = 0; i < 5; i++)
			{
				columns.rotation1[i] = 0.5;
				columns.translate1[i] = 0.5;
			}

		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				columns.rotation2[i] = 0.5;
				columns.translate2[i] = 0.5;
			}
		}

		jacket.beeStrike.setPosition(sf::Vector2f(window.getSize().x + 1000, window.getSize().y + 1000));
		clearRow++;

		break;
	}

}