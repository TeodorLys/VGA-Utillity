#pragma once

#include <SFML\Graphics.hpp>

#define SKIN 220,183,124,255
#define EYES 0,125,187,255
#define MOUT 91,73,49,255
#define HAIR 158,152,59,255

class turbo {
public:
  sf::Uint8 turboBuddy[32 * 32 * 4] = { SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,HAIR,HAIR,HAIR,HAIR,HAIR,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,  //With Hair
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,HAIR,HAIR,HAIR,HAIR,HAIR,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,HAIR,HAIR,HAIR,HAIR,HAIR,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,HAIR,HAIR,HAIR,HAIR,HAIR,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,HAIR,HAIR,HAIR,HAIR,HAIR,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN, //skin only
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,EYES,EYES,EYES,EYES,EYES,EYES,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,EYES,EYES,EYES,EYES,EYES,EYES,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,EYES,EYES,EYES,EYES,EYES,EYES,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,EYES,EYES,EYES,EYES,EYES,EYES,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN, // with Eyes
										SKIN,SKIN,SKIN,SKIN,SKIN,EYES,EYES,EYES,EYES,EYES,EYES,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,EYES,EYES,EYES,EYES,EYES,EYES,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,EYES,EYES,EYES,EYES,EYES,EYES,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,EYES,EYES,EYES,EYES,EYES,EYES,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,EYES,EYES,EYES,EYES,EYES,EYES,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,EYES,EYES,EYES,EYES,EYES,EYES,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,EYES,EYES,EYES,EYES,EYES,EYES,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,EYES,EYES,EYES,EYES,EYES,EYES,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,//Skin only
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,SKIN,SKIN,SKIN,SKIN,SKIN, //With mouth
										SKIN,SKIN,SKIN,SKIN,SKIN,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,MOUT,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,
										SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN,SKIN };
};