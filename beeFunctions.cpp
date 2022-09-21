/*
Author: Mohammad Adnaan
Class: ECE6122
Last Date Modified: 24 Oct , 2021
Description:
functions related to bee movement and buzzy movement
*/

#include <iostream>
#include "elements.h"
#include "math.h"
void Bee::increaseAngle()
{
	//increases launch angle
	if (angle > minimumAngle )
	{
		beeStrike.rotate(-rotationRate);
		angle = angle - rotationRate;
	}
	
}
void Bee::decreaseAngle()
{
	//decreases launch angle
	if (angle < maximumAngle)
	{
		beeStrike.rotate(rotationRate);
		angle =angle + rotationRate;
	}
	
}

void Bee::resetAngle()
{
	//resets launch angle to zero 
	angle = defaultAngle;
	beeStrike.setRotation(angle);
}

void Bee::beeMove(int& velocity,float& launchAngle)
{
	//calculates trajectory of buzzy

	float x=0, y=0;
	
	x = (std::sqrt(velocity)/12.0)*std::abs(std::cos(launchAngle*3.1416/180));
	y = x* (std::tan(-launchAngle * 3.1416 / 180))  - ((1/x) *(2*beeStrike.getPosition().x-x-60))/8000;
	beeStrike.move(sf::Vector2f(x, -y)); 
	beeStrike.setRotation(-std::atan(y/x)*180/3.1416);
}

void Bee::bindBee(sf::RectangleShape& beeStrike, sf::Texture& beeTexture)
{
	// display the buzy at calculated position

	beeStrike.setPosition(60.0f, 475.0f);
	beeStrike.setScale(2.5f, 1.0f);
	beeStrike.setRotation(angle);

	beeTexture.loadFromFile("graphics/smallbuzzy.png");
	beeStrike.setTexture(&beeTexture);
	beeStrike.setOrigin(beeStrike.getSize().x / 2, beeStrike.getSize().y / 2);
}

/////////////////

int BeeLife::increaseLife()
{
	//increases buzzy life
	if (life < maximumLife)
	{
		life++; 
	}
	return life;
}
int BeeLife::decreaseLife()
{
	//decreases buzzy life
	if (life > minimumLife)
	{
		life--;
	}
	return life;
}

int BeeLife::resetLife()
{
	//resets buzzy life to zero
	life = maximumLife;
	return life;
}

void BeeLife::showLife(sf::RectangleShape& beelife, sf::RenderWindow& window)
{
	//display buzzy lives
	for (int i = 0; i < life; i++)
	{
		
		beelife.setPosition((float) i*55+100.0f, 10.0f);
		window.draw(beelife);
	}
	

	
}


void Insect::locationUpdate(sf::RenderWindow& window)
{
	//updates the location of bee
	if (fly.getPosition().x < 0 && fly.getPosition().y > 0)
	{
		fly.setPosition(sf::Vector2f(window.getSize().x, 130.0f));
	}
	float y = .08* std::sin(fly.getPosition().x*.01);
	//std::cout << y <<std::endl;
	fly.move(sf::Vector2f(-0.2f,y));
}