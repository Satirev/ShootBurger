#include "Room/BallData.h"

BallData::BallData() :
                position(-1, -1, -1), colour(-1), type(BallData::UNKNOW)
{
}

BallData::BallData(BallData::Type type_, Position position_, int colour_) :
                position(position_), colour(colour_), type(type_)
{
}

BallData::BallData(Position position_, int colour_) :
                position(position_), colour(colour_), type(BallData::UNKNOW)
{
}
