#include "Upgrades.h"
#include <iostream>

Upgrade::Upgrade()
{
}

Upgrade::~Upgrade()
{
}

// Adds to the owned amount of an upgrade
void Upgrade::addAmountOwned(float amt)
{
	amountOwned += amt;
}

// Subtracts from the owned amount of an upgrade
void Upgrade::subtractAmountOwned(float amt)
{
	amountOwned -= amt;
}