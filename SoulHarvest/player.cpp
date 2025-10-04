#include "Player.h"
#include <iostream>
#include <string>

Player::Player()
{
}

Player::~Player()
{
}

void Player::incrementSouls(int amt)
{
	data.soulsOwned += amt;
}