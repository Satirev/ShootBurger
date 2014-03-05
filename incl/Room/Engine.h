#ifndef ENGINE_H_
#define ENGINE_H_

#include "PlayerData.h"
#include "Common/Vector.h"
#include "Room/TargetData.h"
#include "Room/GameData.h"
#include "Room/Rules.h"

class Engine
{
public:
    Engine(Rules rules, Vector mapSize, float gravity);
    void makeMove(PlayerData &player, GameData& gameData);
    void handleTargets(GameData& gameData);

private:
    Position findFreePosition();
    bool checkIfBallIsOutOfMap(Position position);
    bool checkCollision(Position position,
            std::vector<TargetData>::iterator& hitTarget);
    int randSign() const;

private:
    Rules m_rules;
    const Vector m_mapSize;
    const float m_gravity;
    std::vector<TargetData> m_targets;
    const size_t m_targetsCount;
    const int m_ballRadius;
    const int m_targetRadius;
};

#endif /* ENGINE_H_ */
