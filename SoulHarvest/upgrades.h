#pragma once

class Upgrade
{
public:
    Upgrade();
    ~Upgrade();

    int amountOwned;
    int cost;
    float soulsPerSec;

    void addAmountOwned(float amt);
    void subtractAmountOwned(float amt);

private:

};