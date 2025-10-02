#pragma once

class Upgrade
{
public:
    Upgrade();
    ~Upgrade();

    int amountOwned;
    int cost;
    int soulsPerSec;

    Upgrade(int baseCost, int baseSoulsPerSec);

private:

};