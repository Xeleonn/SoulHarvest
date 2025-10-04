#include "Player.h"
#include <iostream>
#include <string>

Player::Player()
{
}

Player::~Player()
{
}

void Player::addSouls(float amt)
{
	data.soulsOwned += amt;
}

void Player::subtractSouls(float amt)
{
	data.soulsOwned -= amt;
}

void Player::multiplySouls(float mult)
{
	data.soulsOwned *= mult;
}