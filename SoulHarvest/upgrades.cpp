#include <iostream>

class Upgrade
{
public:
    Upgrade();
    ~Upgrade();

    int amountOwned;
    int cost;
    int soulsPerSec;

    Upgrade(int baseCost, int baseSoulsPerSec)
    {
        cost = baseCost;
        soulsPerSec = baseSoulsPerSec;
    }

private:

};

Upgrade::Upgrade()
{
}

Upgrade::~Upgrade()
{
}