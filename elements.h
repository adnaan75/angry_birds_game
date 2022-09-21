/*
Author: Mohammad Adnaan
Class: ECE6122
Last Date Modified: 24 Oct , 2021
Description:
header file containing all global function definitions, object definition 
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include<array>
#include <time.h>
#include <algorithm> 
#include <random>  
using namespace std;
class Power
{
public:
	int velocity;
	int minimumVelocity, maximumVelocity;
	sf::RectangleShape powerBar;
	sf::RectangleShape velocityBar;
	Power(sf::RenderWindow& window)
	{
		minimumVelocity = 5;
		maximumVelocity = 100;
		velocity = minimumVelocity;
		powerBar.setSize(sf::Vector2f(375.0f, 30.0f));
		velocityBar.setSize(sf::Vector2f((float)(375*velocity/maximumVelocity), 30.0f));
		powerBar.setPosition(146.0f, window.getSize().y - 74.0f);
		velocityBar.setPosition(146.0f, window.getSize().y - 74.0f);
		powerBar.setOutlineColor(sf::Color::Magenta);
		
		powerBar.setFillColor(sf::Color::Transparent);
		velocityBar.setFillColor(sf::Color::Red);
		powerBar.setOutlineThickness(2);
	}
	void setVelocityBar();
	int increasePower();
	int decreasePower();
	int resetPower();
};


class Bee
{
public:
	float angle, minimumAngle,maximumAngle,defaultAngle;
	sf::Texture beeTexture;
	sf::RectangleShape beeStrike;
	float rotationRate =1;
	Bee()
	{
		defaultAngle = 0;//-20;
		angle = defaultAngle;
		minimumAngle = -80;
		maximumAngle = 50;
		
		beeStrike.setSize(sf::Vector2f(75.0f, 75.0f));
	}
	void increaseAngle();
	void decreaseAngle();
	void resetAngle();
	void beeMove(int& velocity,float& launchAngle);
	void bindBee(sf::RectangleShape& beeStrike, sf::Texture& beeTexture);
};


class BeeLife
{
public:
	int life, minimumLife, maximumLife;
	sf::RectangleShape beelife;
	sf::Texture lifeTexture;
	BeeLife(sf::RenderWindow& window)
	{
		
		minimumLife = 0;
		maximumLife = 5;
		life = maximumLife;
		beelife.setScale(0.9f, 0.9f);
		beelife.setSize(sf::Vector2f(50.0f, 50.0f));
		lifeTexture.loadFromFile("graphics/buzzy life.png");
		beelife.setTexture(&lifeTexture);
		showLife(beelife, window);
	}
	int increaseLife();
	int decreaseLife();
	int resetLife();
	void showLife(sf::RectangleShape& beelife, sf::RenderWindow& window);
};

class AllText
{
public:
	sf::Text lifeText;
	sf::Text title;
	sf::Text hint;
	sf::Text creator;
	sf::Text power;
	sf::Text score;
	sf::Text over;
	sf::Text recreated;

	sf::Font font;
	
	int scoreValue;

	AllText(sf::RenderWindow& window)
	{
		font.loadFromFile("fonts/KOMIKAP_.ttf");
		lifeText.setFont(font);
		lifeText.setString("LIVES ");
		lifeText.setFillColor(sf::Color::White);
		lifeText.setCharacterSize(25);
		lifeText.setPosition(sf::Vector2f(10.0f, 15.0f));

		title.setFont(font);
		title.setString("Buzzy's Revenge");
		title.setFillColor(sf::Color::Red);
		title.setCharacterSize(50);
		title.setPosition(sf::Vector2f(window.getSize().x / 3 +40, window.getSize().y / 6));


		recreated.setFont(font);
		recreated.setString("Level Recreated");
		recreated.setFillColor(sf::Color::Red);
		recreated.setCharacterSize(50);
		recreated.setPosition(sf::Vector2f(window.getSize().x / 3 + 40, window.getSize().y / 6));

		over.setFont(font);
		over.setString("Game Over");
		over.setFillColor(sf::Color::Red);
		over.setCharacterSize(80);
		over.setPosition(sf::Vector2f(window.getSize().x / 3 + 40, window.getSize().y / 5));

		hint.setFont(font);
		hint.setString("Press enter to restart game \n        press esc to exit \n    Press Space to Powerup \n Press up/down arrow to aim");
		hint.setFillColor(sf::Color::White);
		hint.setCharacterSize(40);
		hint.setPosition(sf::Vector2f(window.getSize().x /4 +50 , window.getSize().y / 4 +30));

		creator.setFont(font);
		creator.setString("    Created by\nMohammad Adnaan");
		creator.setFillColor(sf::Color::White);
		creator.setCharacterSize(25);
		creator.setPosition(sf::Vector2f(window.getSize().x / 2 - 160, window.getSize().y / 2 + 100));

		power.setFont(font);
		power.setString("Power");
		power.setFillColor(sf::Color::White);
		power.setCharacterSize(35);
		power.setPosition(sf::Vector2f(10.0f, window.getSize().y- 80.0f));



		scoreValue = 99;
		score.setFont(font);
		score.setString("Score: "+ std::to_string(scoreValue));
		score.setFillColor(sf::Color::White);
		score.setCharacterSize(30);
		score.setPosition(sf::Vector2f(window.getSize().x-250.0f, 10.0f));
	}

	void scoreSet(int value);
	
};


class Insect
{
public:
	sf::RectangleShape fly;
	sf::Texture flyTexture;
	Insect(sf::RenderWindow& window)
	{
		
		fly.setScale(-1.0f, 1.0f);
		fly.setSize(sf::Vector2f(80.0f,60.0f));
		fly.setOrigin(fly.getSize().x / 2, fly.getSize().y / 2);
		flyTexture.loadFromFile("graphics/insect.png");
		fly.setTexture(&flyTexture);
		fly.setPosition( 1460.0f, 130.0f);
	}
	void locationUpdate(sf::RenderWindow& window);
};

class ColumnArrange
{
public:
	float iconSize = 80;
	array<sf::RectangleShape,5> icons1;
	array<sf::RectangleShape, 5> icons2;
	array<sf::Texture, 5> texture1;
	array<sf::Texture, 5> texture2;
	
	array<char, 2> evil;
	array<char, 5> column1,column2;
	array<char, 8> temp;


	array<float, 5> rotation1, rotation2;
	array<float, 5> translate1, translate2;
	array<float, 5> totalTranslate1, totalTranslate2;
	int unicornHit = 0;
	int unicornRow = 0;
	int unicornColumn = 0;
	ColumnArrange()
	{
		unsigned int seed = (unsigned)time(NULL);
		srand(seed);
		temp = {'U','B','C','D','F','M','P','S'};
		evil={ 'V','T' };
		shuffle(evil.begin(), evil.end(), default_random_engine(seed));
		shuffle(temp.begin(), temp.end(), default_random_engine(seed));
		for (int i = 0; i < 4; i++)
		{
			column1[i] = temp[i];
			column2[i] = temp[i + 4];
		}
		column1[4] = evil[0];
		column2[4] = evil[1];
		shuffle(column1.begin(), column1.end(), default_random_engine(rand() % 99));
		shuffle(column2.begin(), column2.end(), default_random_engine(rand() % 99));


		

		for (int i = 0; i < 5; i++)
		{

			if (column1[i] == 'U')
			{
				unicornColumn = 1;
				unicornRow = i;
			}
			if (column2[i] == 'U')
			{
				unicornColumn = 2;
				unicornRow = i;
			}

			rotation1[i] = 0;
			translate1[i] = 0;
			totalTranslate1[i] = 0;

			rotation2[i] = 0;
			translate2[i] = 0;
			totalTranslate2[i] = 0;

			icons1[i].setScale(1.0f, 1.0f);
			icons1[i].setSize(sf::Vector2f(iconSize, iconSize));
			icons1[i].setOrigin(icons1[i].getSize().x / 2, icons1[i].getSize().y / 2);
			icons1[i].setPosition(1360.0f, i*100+290.0f);
			icons1[i].rotate(rotation1[i]);
			icons1[i].move(sf::Vector2f(0, translate1[i]));

			icons2[i].setScale(1.0f, 1.0f);
			icons2[i].setSize(sf::Vector2f(iconSize, iconSize));
			icons2[i].setOrigin(icons2[i].getSize().x / 2, icons2[i].getSize().y / 2);
			icons2[i].setPosition(1480.0f, i * 100 + 290.0f);
			icons2[i].rotate(rotation2[i]);
			icons2[i].move(sf::Vector2f(0, translate2[i]));

		}

	}
	void arrangeIcons(sf::RenderWindow& window);
	void moveIcon(sf::RenderWindow& window);
};

void loadSound(array<sf::SoundBuffer, 9>& soundEffectBuffer, array<sf::Sound, 9>& gameSound);
void initializer(sf::RenderWindow& window,int& restart, int& levelRecreate, array<sf::SoundBuffer, 9>& soundEffectBuffer, array<sf::Sound, 9>& gameSound);
sf::Sprite setBackground(sf::RenderWindow& window, sf::Texture& windowTexture);
char collision( Bee& jacket, ColumnArrange& columns, Insect& roach,int& columnNumber,int& columnPosition);
void collisionImpact(char& collisonElement, sf::RenderWindow& window, Bee& jacket, ColumnArrange& columns, Insect& roach, AllText& text, int& columnNumber, int& columnPosition, BeeLife& lifeNumber, array<sf::SoundBuffer, 9>& soundEffectBuffer, array<sf::Sound, 9>& gameSound);