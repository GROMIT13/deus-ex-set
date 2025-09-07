#pragma once
#include "raylib.h"
#include "sprite.hpp"
#include <unordered_map>

class Scene;

enum class SpriteName
{
	TEST16 = 0,
	TEST32,
	TEST64,
	TEST128,
	TEST256,
	ALEPH,
	ALEPH_BIG,
	AND,
	BIG_SUM,
	DELTA,
	EUQIVALENT,
	EXIISTS,
	FOR_ALL,
	FUNCTION,
	HERMIT,
	IMPLICATION,
	IN,
	INCLUSION,
	INFINITY_SYMBOL,
	INJECTIVE_FUNCTION,
	INTEGRAL,
	INTEGRAL_MIRROR,
	NATURAL_8,
	ORDER,
	PI_SYMBOL,
	PI_SMALL_SYMBOL,
	SIGMA,
	SIGMA_SMALL,
	SUM, 
	SURJECTIVE,
	UNDERSCORE_0,
	UNDERSCORE_1,
	UNDERSCORE_2,
	UNDERSCORE_3,
	UNDERSCORE_4,
	UNDERSCORE_5,
	UNDERSCORE_6,
	UNDERSCORE_7,
	UNDERSCORE_8,
	UNDERSCORE_9,
	NUMBER_0,
	NUMBER_1,
	NUMBER_2,
	NUMBER_3,
	NUMBER_4,
	NUMBER_5,
	NUMBER_6,
	NUMBER_7,
	NUMBER_8,
	NUMBER_9,
	MENU_SELECT_TEXT,
	PLAYER_SELECT_TEXT,
	QUIT_TEXT,
	START_TEXT,
	TITLE_TEXT,

	LAST //This sprite does not exist, it's here for iterating over sprites
};

class SpriteManager
{
public:
	SpriteManager();
	void LoadSprite(SpriteName spriteName);
	void LoadAllSprites();
	void UnloadSprite(SpriteName spriteName);
	void DrawSprite(SpriteName spriteName, const Vector2& pos, float rotation, Color color) const;
	void DrawSprite(SpriteName spriteName, const Vector2& pos, float rotation, Color color, Scene* scene) const;
	const char* GetSpriteFileName(SpriteName spriteName) const;
	~SpriteManager();

private:
	std::unordered_map<SpriteName, Sprite> sprites;
	std::unordered_map<SpriteName, const char*> spriteNames = {
		   {SpriteName::TEST16, "test16.png"},
		   {SpriteName::TEST32, "test32.png"},
		   {SpriteName::TEST64, "test64.png"},
		   {SpriteName::TEST128, "test128.png"},
		   {SpriteName::TEST256, "test256.png"},
		   {SpriteName::ALEPH, "aleph.png"},
		   {SpriteName::ALEPH_BIG, "aleph_big.png"},
		   {SpriteName::AND, "and.png"},
		   {SpriteName::BIG_SUM, "big_sum.png"},
		   {SpriteName::DELTA, "delta.png"},
		   {SpriteName::EUQIVALENT, "equivalent.png"},
		   {SpriteName::EXIISTS, "exists.png"},
		   {SpriteName::FOR_ALL, "for_all.png"},
		   {SpriteName::FUNCTION, "function.png"},
		   {SpriteName::HERMIT, "hermit.png"},
		   {SpriteName::IMPLICATION, "implication.png"},
		   {SpriteName::IN, "in.png"},
		   {SpriteName::INCLUSION, "inclusion.png"},
		   {SpriteName::INFINITY_SYMBOL, "infinity.png"},
		   {SpriteName::INJECTIVE_FUNCTION, "injective.png"},
		   {SpriteName::INTEGRAL, "integral.png"},
		   {SpriteName::INTEGRAL_MIRROR, "integral_mirror.png"},
		   {SpriteName::NATURAL_8, "natural8.png"},
		   {SpriteName::ORDER, "order.png"},
		   {SpriteName::PI_SYMBOL, "pi.png"},
		   {SpriteName::PI_SMALL_SYMBOL, "pi_small.png"},
		   {SpriteName::SIGMA, "sigma.png"},
		   {SpriteName::SIGMA_SMALL, "sigma_small.png"},
		   {SpriteName::SUM, "sum.png"},
		   {SpriteName::SURJECTIVE, "surjective.png"},
		   {SpriteName::UNDERSCORE_0, "underscore_0.png"},
		   {SpriteName::UNDERSCORE_1, "underscore_1.png"},
		   {SpriteName::UNDERSCORE_2, "underscore_2.png"},
		   {SpriteName::UNDERSCORE_3, "underscore_3.png"},
		   {SpriteName::UNDERSCORE_4, "underscore_4.png"},
		   {SpriteName::UNDERSCORE_5, "underscore_5.png"},
		   {SpriteName::UNDERSCORE_6, "underscore_6.png"},
		   {SpriteName::UNDERSCORE_7, "underscore_7.png"},
		   {SpriteName::UNDERSCORE_8, "underscore_8.png"},
		   {SpriteName::UNDERSCORE_9, "underscore_9.png"},
		   {SpriteName::NUMBER_0, "0.png"},
		   {SpriteName::NUMBER_1, "1.png"},
		   {SpriteName::NUMBER_2, "2.png"},
		   {SpriteName::NUMBER_3, "3.png"},
		   {SpriteName::NUMBER_4, "4.png"},
		   {SpriteName::NUMBER_5, "5.png"},
		   {SpriteName::NUMBER_6, "6.png"},
		   {SpriteName::NUMBER_7, "7.png"},
		   {SpriteName::NUMBER_8, "8.png"},
		   {SpriteName::NUMBER_9, "9.png"},
		   {SpriteName::MENU_SELECT_TEXT, "menu_select.png"},
		   {SpriteName::PLAYER_SELECT_TEXT, "player_select.png"},
		   {SpriteName::QUIT_TEXT, "quit.png"},
		   {SpriteName::START_TEXT, "start.png"},
		   {SpriteName::TITLE_TEXT, "title.png"}
	};
};
