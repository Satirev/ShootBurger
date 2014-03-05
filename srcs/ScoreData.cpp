#include "Room/ScoreData.h"

ScoreData::ScoreData() :
                playerName(""), score(0)
{
}

ScoreData::ScoreData(const std::string& playerName_) :
                playerName(playerName_), score(0)
{
}

ScoreData::ScoreData(const std::string& playerName_, int score_) :
                playerName(playerName_), score(score_)
{
}
