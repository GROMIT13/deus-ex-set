#pragma once

#include "player.hpp"

class PlayerP : public Player
{
public:
	PlayerP(const Vector2& pos, const Properties& playerProperties, const Properties& defaultPlayerProperties, LevelScene* scene);
	~PlayerP() override;
	void Shoot() override;
private:

};

