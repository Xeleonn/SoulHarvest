#include "Player.h"
#include <iostream>
#include <string>

Player::Player()
{
}

Player::~Player()
{
}

// Gives souls to the player
void Player::addSouls(float amt)
{
	data.soulsOwned += amt;
}

// Takes away souls from the player
void Player::subtractSouls(float amt)
{
	data.soulsOwned -= amt;
}

// Multiplies the amount of souls the player has
void Player::multiplySouls(float mult)
{
	data.soulsOwned *= mult;
}