/*
Author: Mohammad Adnaan
Class: ECE6122
Last Date Modified: 24 Oct , 2021
Description:
function related to velocity calculation of buzzy
*/

#include <iostream>
#include "elements.h"

int Power::increasePower()
{
	//increases power
	if (velocity < maximumVelocity)
	{
		velocity++;
	}
	return velocity;
}
int Power::decreasePower()
{
	//decreases power
	if (velocity > minimumVelocity )
	{
		velocity--;
	}
	return velocity;
}

int Power::resetPower()
{
	// resets to initial default power
	velocity= minimumVelocity;
	return velocity;
}

void Power::setVelocityBar()
{
	//display power bar
	velocityBar.setSize(sf::Vector2f((float)(375 * velocity / maximumVelocity), 30.0f));
}