#include "playerS.hpp"
#include "log.hpp"


PlayerS::PlayerS(const Vector2& pos, const Properties& playerProperties, const Properties& defaultPlayerProperties, LevelScene* scene)
	:Player(pos, playerProperties, defaultPlayerProperties, scene)
{
}

PlayerS::~PlayerS()
{
}

void PlayerS::Shoot()
{
	Log::Success("S SHOOTS");
}
