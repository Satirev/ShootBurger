#include "Room/GameData.h"

GameData::GameData() :
                m_isEndGame(false)
{
}

void GameData::addScore(ScoreData score)
{
    m_scores.push_back(score);
}

void GameData::addTarget(TargetData target)
{
    m_targets.push_back(target);
}

void GameData::addBall(Ball ball)
{
    m_balls.push_back(ball);
}

void GameData::setEndGame(EndGameData endGame)
{
    m_endGame = endGame;
    m_isEndGame = true;
}

const std::vector<ScoreData>& GameData::getScores() const
{
    return m_scores;
}

const std::vector<TargetData>& GameData::getTargets() const
{
    return m_targets;
}

const std::vector<Ball>& GameData::getBalls() const
{
    return m_balls;
}

const EndGameData GameData::getEndGame() const
{
    return m_endGame;
}

bool GameData::isEndGame() const
{
    return m_isEndGame;
}
