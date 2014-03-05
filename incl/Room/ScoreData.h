#ifndef SCOREDATA_H_
#define SCOREDATA_H_

#include <string>
#include "Common/Vector.h"

struct ScoreData
{
    ScoreData();
    ScoreData(const std::string& playerName);
    ScoreData(const std::string& playerName, int score);

    std::string playerName;
    int score;
};

#endif /* SCOREDATA_H_ */
