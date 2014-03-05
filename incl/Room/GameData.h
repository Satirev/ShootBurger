#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include <vector>
#include "Room/ScoreData.h"
#include "Room/TargetData.h"
#include "Room/BallData.h"
#include "Room/EndGameData.h"
#include "Common/Ball.h"

class GameData
{
public:
    GameData();

    void addScore(ScoreData score);
    void addTarget(TargetData target);
    void addBall(Ball ball);
    void setEndGame(EndGameData endGame);

    const std::vector<ScoreData>& getScores() const;
    const std::vector<TargetData>& getTargets() const;
    const std::vector<Ball>& getBalls() const;
    const EndGameData getEndGame() const;
    bool isEndGame() const;

private:
    std::vector<ScoreData> m_scores;
    std::vector<TargetData> m_targets;
    std::vector<Ball> m_balls;
    EndGameData m_endGame;
    bool m_isEndGame;
};

#endif /* GAMEDATA_H_ */
