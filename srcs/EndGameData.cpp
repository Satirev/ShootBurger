#include "Room/EndGameData.h"

EndGameData::EndGameData() :
                playerName(""), score(0)
{
}

EndGameData::EndGameData(const std::string& playerName_, int score_) :
                playerName(playerName_), score(score_)
{
}
