/*
Author: Mohammad Adnaan
Class: ECE6122
Last Date Modified: 24 Oct , 2021
Description:
main file to start the program
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include<chrono>
#include "elements.h"
#include <SFML/Audio.hpp>
#include<array>
using namespace std;


int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 950), "Buzzy's Revenge!!!" , sf::Style::Close| sf::Style::Resize);

	array<sf::SoundBuffer, 9> soundEffectBuffer;
	array<sf::Sound, 9> gameSound;
	loadSound(soundEffectBuffer, gameSound);

	int restart = 1;
	int levelRecreate = 1;
	bool first = true;

	while (restart || levelRecreate)
	{
		if (!first)
		{		
			chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
			if (!levelRecreate)
			{
				gameSound[7].play();
			}
			
			while (1)
			{
				chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
				chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
				if (time_span.count() > 2)
				{
					break;
				}
			}
		}

		if (levelRecreate && !restart)
		{
			gameSound[6].play();
		}

		initializer(window,restart, levelRecreate, soundEffectBuffer, gameSound);
		first = false;
	}
	

	return 0;

}


void loadSound(array<sf::SoundBuffer, 9>& soundEffectBuffer, array<sf::Sound, 9>& gameSound)
{
	//loading sounds
	//0.launch 1.regular collision 2.evil collision 3.unicorn collision 4.insect collision 5.out of window 6.level recreated 7.game over 

	for (int i = 0; i < 9; i++)
	{
		soundEffectBuffer[i].loadFromFile("sound/sound"+to_string(i)+ ".wav");
		gameSound[i].setBuffer(soundEffectBuffer[i]);
	}

}