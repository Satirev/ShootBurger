#ifndef ENDGAMEDATA_H_
#define ENDGAMEDATA_H_

#include <string>

struct EndGameData
{
    EndGameData();
    EndGameData(const std::string& playerName, int score);

    std::string playerName;
    int score;
};

#endif /* ENDGAMEDATA_H_ */
