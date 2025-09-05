#include "playerP.hpp"
#include "log.hpp"


PlayerP::PlayerP(const Vector2& pos, const Properties& playerProperties, const Properties& defaultPlayerProperties, LevelScene* scene)
	:Player(pos, playerProperties, defaultPlayerProperties, scene)
{
}

PlayerP::~PlayerP()
{
}

void PlayerP::Shoot()
{
	Log::Success("P SHOOTS");
}
