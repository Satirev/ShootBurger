#include "Room/TargetData.h"

int TargetData::NextId = 1;

TargetData::TargetData() :
                id(TargetData::NextId++), position(-1, -1, -1),
                type(TargetType::CREATE)
{
}

TargetData::TargetData(Position position_) :
                id(TargetData::NextId++), position(position_),
                type(TargetType::CREATE)
{
}

TargetData::TargetData(TargetType type_, Position position_) :
                id(TargetData::NextId++), position(position_), type(type_)
{
}

