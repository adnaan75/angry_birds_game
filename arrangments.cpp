/*
Author: Mohammad Adnaan
Class: ECE6122
Last Date Modified: 24 Oct , 2021
Description:
functions related to arrangement of icons
*/
#include <iostream>
#include "elements.h"
#include <string.h>
#include <SFML/Graphics.hpp>

void ColumnArrange::arrangeIcons(sf::RenderWindow& window)
{
	// arrange the icons in two columns and display them

	for (int i=0; i<5;i++)
	{
		switch (column1[i])
		{
		case 'U':
			texture1[i].loadFromFile("graphics/angry_unicorn.png");
			icons1[i].setTexture(&texture1[i]);
			break;
		case 'B':
			texture1[i].loadFromFile("graphics/bunny.png");
			icons1[i].setTexture(&texture1[i]);
			break;
		case 'C':
			texture1[i].loadFromFile("graphics/chicken.png");
			icons1[i].setTexture(&texture1[i]);
			break;
		case 'D':
			texture1[i].loadFromFile("graphics/dog.png");
			icons1[i].setTexture(&texture1[i]);
			break;
		case 'F':
			texture1[i].loadFromFile("graphics/frog.png");
			icons1[i].setTexture(&texture1[i]);
			break;
		case 'V':
			texture1[i].loadFromFile("graphics/Georgia_Bulldogs_logo_dog_g.png");
			icons1[i].setTexture(&texture1[i]);
			break;
		case 'M':
			texture1[i].loadFromFile("graphics/mouse.png");
			icons1[i].setTexture(&texture1[i]);
			break;
		case 'P':
			texture1[i].loadFromFile("graphics/pig.png");
			icons1[i].setTexture(&texture1[i]);
			break;
		case 'S':
			texture1[i].loadFromFile("graphics/sheep.png");
			icons1[i].setTexture(&texture1[i]);
			break;
		case 'T':
			texture1[i].loadFromFile("graphics/tiger.png");
			icons1[i].setTexture(&texture1[i]);
			break;
		}
	}

	for (int i=0; i < 5; i++)
	{
		switch (column2[i])
		{
		case 'U':
			texture2[i].loadFromFile("graphics/angry_unicorn.png");
			icons2[i].setTexture(&texture2[i]);
			break;
		case 'B':
			texture2[i].loadFromFile("graphics/bunny.png");
			icons2[i].setTexture(&texture2[i]);
			break;
		case 'C':
			texture2[i].loadFromFile("graphics/chicken.png");
			icons2[i].setTexture(&texture2[i]);
			break;
		case 'D':
			texture2[i].loadFromFile("graphics/dog.png");
			icons2[i].setTexture(&texture2[i]);
			break;
		case 'F':
			texture2[i].loadFromFile("graphics/frog.png");
			icons2[i].setTexture(&texture2[i]);
			break;
		case 'V':
			texture2[i].loadFromFile("graphics/Georgia_Bulldogs_logo_dog_g.png");
			icons2[i].setTexture(&texture2[i]);
			break;
		case 'M':
			texture2[i].loadFromFile("graphics/mouse.png");
			icons2[i].setTexture(&texture2[i]);
			break;
		case 'P':
			texture2[i].loadFromFile("graphics/pig.png");
			icons2[i].setTexture(&texture2[i]);
			break;
		case 'S':
			texture2[i].loadFromFile("graphics/sheep.png");
			icons2[i].setTexture(&texture2[i]);
			break;
		case 'T':
			texture2[i].loadFromFile("graphics/tiger.png");
			icons2[i].setTexture(&texture2[i]);
			break;
		}
	}
}


void ColumnArrange::moveIcon(sf::RenderWindow& window)
{
	//controls the movements of icons in the column

	int rotationCount1= 0;
	int rotationCount2 = 0;
	for (int i = 0; i < 5; i++)
	{

		if (rotation1[i] < 0.0001 && translate1[i] != 0)
		{
			
			totalTranslate1[i] = totalTranslate1[i] + translate1[i];
			if (totalTranslate1[i] > 100)
			{
				translate1[i] = 0;
				totalTranslate1[i] = 0;
			}
		}
		if (rotation2[i] < 0.0001 && translate2[i] != 0)
		{
			
			totalTranslate2[i] = totalTranslate2[i] + translate2[i];
			if (totalTranslate2[i] > 100)
			{
				translate2[i] = 0;
				totalTranslate2[i] = 0;
			}
		}

		if (rotation1[i] > 0.001 )
		{
			rotationCount1++;
		}
		if (rotation2[i] > 0.001)
		{
			rotationCount2++;
		}


		icons1[i].rotate(rotation1[i]);
		icons1[i].move(sf::Vector2f(0, translate1[i]));

		icons2[i].rotate(rotation2[i]);
		icons2[i].move(sf::Vector2f(0, translate2[i]));

	}

	if ((rotationCount1 == 1))
	{
		for (int i = 0; i < 5; i++)
		{
			if (rotation1[i] > 0.001)
			{
				totalTranslate1[i] = totalTranslate1[i] + translate1[i];
				if (totalTranslate1[i] > window.getSize().y/1.5)
				{
					translate1[i] = 0;
					totalTranslate1[i] = 0;
					rotation1[i] = 0;
					icons1[i].setRotation(0);
					if (unicornHit && (unicornColumn == 1) && (i < unicornRow))
					{
						icons1[i].setPosition(1360.0f, (i+1) * 100 + 290.0f);
					}
					else
					{
						icons1[i].setPosition(1360.0f, i * 100 + 290.0f);
					}
					
				}
			}

		}
	}

	if ((rotationCount2 == 1))
	{
		for (int i = 0; i < 5; i++)
		{
			if (rotation2[i] > 0.001)
			{
				totalTranslate2[i] = totalTranslate2[i] + translate2[i];
				if (totalTranslate2[i] > window.getSize().y / 1.5)
				{
					translate2[i] = 0;
					totalTranslate2[i] = 0;
					rotation2[i] = 0;
					icons2[i].setRotation(0);
					if (unicornHit && (unicornColumn == 2) && (i < unicornRow))
					{
						icons2[i].setPosition(1480.0f, (i + 1) * 100 + 290.0f);
					}
					else
					{
						icons2[i].setPosition(1480.0f, i * 100 + 290.0f);
					}
					
				}
			}

		}
	}
}