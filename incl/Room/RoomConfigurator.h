/*
 * RoomConfigurator.h
 *
 *  Created on: Sep 24, 2013
 *      Author: matt
 */

#ifndef ROOMCONFIGURATOR_H_
#define ROOMCONFIGURATOR_H_

#include "Common/GameType.h"
#include "Common/Vector.h"
#include "Room/Rules.h"

struct RoomConfigurator
{
    Vector mapSize;
    GameType type;
    Rules rules;
    unsigned int maxPlayers;
};

#endif /* ROOMCONFIGURATOR_H_ */
