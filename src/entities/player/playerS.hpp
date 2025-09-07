#pragma once

#include "player.hpp"

class PlayerS : public Player
{
public:
	PlayerS(const Vector2& pos, const Properties& playerProperties, const Properties& defaultPlayerProperties, LevelScene* scene);
	~PlayerS();
	void Shoot() override;
private:

};
