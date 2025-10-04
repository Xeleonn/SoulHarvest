#pragma once
#include <iostream>

class Player
{
public:
	Player();
	~Player();

	struct PlayerData {
		std::string name;
		float soulsOwned;
		int currentLevel;
		float totalUpgradesOwned;
		float totalSoulsSpent;
		float totalSoulsEarned;
	};
	PlayerData data;

	void addSouls(float amt);
	void subtractSouls(float amt);
	void multiplySouls(float mult);
};