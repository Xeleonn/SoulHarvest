#pragma once
#include <iostream>

class Player
{
public:
	Player();
	~Player();

	struct PlayerData {
		std::string name;
		int soulsOwned;
		int currentLevel;
		int totalUpgradesOwned;
		int totalSoulsSpent;
		int totalSoulsEarned;
	};
	PlayerData data;

	void incrementSouls(int amt);
};