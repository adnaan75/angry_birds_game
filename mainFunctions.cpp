/*
Author: Mohammad Adnaan
Class: ECE6122
Last Date Modified: 24 Oct , 2021
Description:
main initializer which create all objects and coordinate game activities
*/

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include<array>
#include <string.h>
#include "elements.h"
using namespace std;

int clearRow = 0, onGoing=0;


void initializer(sf::RenderWindow &window, int& restart, int& levelRecreate, array<sf::SoundBuffer, 9>& soundEffectBuffer, array<sf::Sound, 9>& gameSound)
{
	// main initialize , loads all objects , runs the game
	sf::Clock clock;
	bool clockReset = false;
	restart = 0;
	levelRecreate = 0;
	clearRow = 0;
	ColumnArrange columns;
	columns.arrangeIcons(window);

	Power powerBar(window);
	int velocity = 0;
	float launchAngle = 0;
	Bee jacket;
	BeeLife lifeNumber(window);
	AllText text(window);
	Insect roach(window);

	sf::Texture windowTexture;
	sf::Sprite background = setBackground(window, windowTexture);
	jacket.bindBee(jacket.beeStrike, jacket.beeTexture);

	bool start = false;
	bool firstTime = true;
	bool shoot = false;
	bool collided = false;
	bool spacePress = false;
	int scoreValue = 55;
	int columnNumber = 0, columnPosition = 0;
	char collisonElement = '0';
	bool acceptInput = true;
	if (onGoing)
	{
		if (firstTime)
		{
			start = true;
			scoreValue = 0;
			text.scoreSet(scoreValue);
			cout << start << endl;
		}
		firstTime = false;
	}



	while (window.isOpen())
	{

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (evnt.type == sf::Event::Resized)
			{
				cout << evnt.size.height << "  " << evnt.size.width << endl;
			}
			else if (evnt.type == sf::Event::KeyPressed )
			{
				switch (evnt.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Enter:
					if (firstTime)
					{
						start = true;
						scoreValue = 0;
						text.scoreSet(scoreValue);
						gameSound[6].play();
					}
					firstTime = false;
					break;
				case sf::Keyboard::Space:
					if (start && !shoot)
					{
						acceptInput = false;
						if (!spacePress)
						{
							gameSound[8].play();
						}
						
						spacePress = true;
						powerBar.increasePower();
						powerBar.setVelocityBar();
					}
					break;
				case sf::Keyboard::Up:
					if (start && !shoot && !spacePress)
					{
						jacket.increaseAngle();
					}

					break;
				case sf::Keyboard::Down:
					if (start && !shoot && !spacePress)
					{
						jacket.decreaseAngle();

					}

					break;
				}
			}
			else if (evnt.type == sf::Event::KeyReleased)
			{
				if (evnt.key.code == sf::Keyboard::Space && start && !shoot)
				{
					shoot = true;
					collided = false;
					spacePress = false;
					velocity=powerBar.velocity;
					launchAngle = jacket.angle;
					powerBar.resetPower();
					gameSound[8].stop();
					gameSound[0].play();
					acceptInput = true;
					
				}
				
			}
		}
		
		
		window.clear();
		
		window.draw(background);
		if (shoot)
		{
			jacket.beeMove(velocity, launchAngle);
		}
		if ((jacket.beeStrike.getPosition().x > window.getSize().x) || (jacket.beeStrike.getPosition().x < 0) || (jacket.beeStrike.getPosition().y > window.getSize().y) || (jacket.beeStrike.getPosition().y < 0))
		{
			shoot = false;
			jacket.resetAngle();
			powerBar.setVelocityBar();
			jacket.bindBee(jacket.beeStrike, jacket.beeTexture);
			
			if (collisonElement == 'N')
			{
				lifeNumber.decreaseLife();
				if (lifeNumber.life > 0)
				{
					gameSound[5].play();
				}
				
			}

		}

		if (clearRow == 2)
		{
			sf::Time time1 = clock.restart();
			clockReset = true;
			clearRow = 0;
			
		}
		if (clockReset)
		{
			sf::Time time1 = clock.getElapsedTime();
			window.draw(text.recreated);
			if (time1.asSeconds() > 1.2)
			{
				clockReset = false;
				levelRecreate = 1;
				onGoing = 1;
				break;
			}
		}

		
		window.draw(jacket.beeStrike);
		window.draw(powerBar.powerBar);
		window.draw(powerBar.velocityBar);
		window.draw(text.lifeText);
		window.draw(text.power);
		window.draw(text.score);
		lifeNumber.showLife(lifeNumber.beelife,window);
		columns.moveIcon(window);
		window.draw(roach.fly);
		for (int i = 0; i < 5; i++)
		{
			window.draw(columns.icons1[i]);
			window.draw(columns.icons2[i]);
		}

		if (start)
		{
			roach.locationUpdate(window);
		}
		if (!start)
		{
			window.draw(text.title);
			window.draw(text.hint);
			window.draw(text.creator);
		}
		
		if (shoot)
		{
			collisonElement = collision(jacket, columns, roach, columnNumber, columnPosition);
			if (collisonElement != 'N' && !collided)
			{
				shoot = false;
				collided = true;
				collisionImpact(collisonElement, window, jacket, columns, roach, text, columnNumber, columnPosition, lifeNumber, soundEffectBuffer, gameSound);
			}

		}
		if (lifeNumber.life == 0)
		{
			
			window.draw(text.over);
		}
		window.display();
		if (lifeNumber.life == 0)
		{
			onGoing = 0;
			restart = 1;
			break;
		}
	}
}


sf::Sprite setBackground(sf::RenderWindow& window, sf::Texture& windowTexture)
{
	//sets background of window
	sf::Sprite background;
	windowTexture.loadFromFile("graphics/background.png");
	background.setTexture(windowTexture);
	sf::Vector2u textureSize = windowTexture.getSize();
	sf::Vector2u windowSize = window.getSize();
	background.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
	return background;
}


void AllText::scoreSet(int value)
{
	//updates score
	score.setString("Score: " + std::to_string(value));
	scoreValue = value;
}