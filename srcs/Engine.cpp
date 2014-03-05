#include "Room/Engine.h"
#include "Room/PlayerData.h"
#include <algorithm>
#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include "Room/Rules.h"

Engine::Engine(Rules rules, Vector mapSize, float gravity) :
                m_rules(rules), m_mapSize(mapSize), m_gravity(gravity),
                m_targetsCount(5), m_ballRadius(100),
                m_targetRadius(200)
{
}

void Engine::handleTargets(GameData& gameData)
{
    const size_t currentTargetsCount = m_targets.size();
    if (currentTargetsCount < m_targetsCount)
    {
        for (size_t i = 0; i < m_targetsCount - currentTargetsCount; i++)
        {
            TargetData newTarget(TargetType::CREATE, findFreePosition());
            m_targets.push_back(newTarget);
            gameData.addTarget(newTarget);
        }
    }

    /*
     if(rules & Rules::DYNAMIC_TARGET)
     {
     // TODO:
     // compute next position for target		
     }
     */
}

int Engine::randSign() const
{
    struct timeval start;
    gettimeofday(&start, NULL);

    return (start.tv_usec % 2) ? -1 : 1;
}

Position Engine::findFreePosition()
{
    Position newPos;
    bool done = true;
    do
    {
        done = true;

        int sign = randSign();
        int rand_x = sign
                * (std::rand() % (m_mapSize.x / 2 - m_targetRadius)
                        + m_targetRadius);
        usleep(std::rand() % 5);
        sign = randSign();
        int rand_y = sign
                * (std::rand() % (m_mapSize.y / 2 - m_targetRadius)
                        + m_targetRadius);

        newPos = Position
        { rand_x, rand_y, std::rand() % 4000
                + 4000 };

        for (auto& i : m_targets)
        {
            if ((std::abs(i.position.x - newPos.x) < 2 * m_targetRadius)
                    && (std::abs(i.position.y - newPos.y) < 2 * m_targetRadius)
                    && (i.position.z == newPos.z))
            {
                done = false;
                break;
            }
        }

    } while (!done);
    return newPos;
}

bool Engine::checkIfBallIsOutOfMap(Position position)
{
    return (position.x > m_mapSize.x / 2 || position.x < -m_mapSize.x / 2)
            || position.y < -m_mapSize.y / 2
            || (position.z > m_mapSize.z);
}

bool Engine::checkCollision(Position position,
        std::vector<TargetData>::iterator& hitTarget)
{
    for (std::vector<TargetData>::iterator target = m_targets.begin();
            target != m_targets.end(); target++)
    {
        Position targetPosition = target->position;
        if ((std::abs(targetPosition.z - position.z)
                <= m_ballRadius + m_targetRadius)
                && (std::abs(targetPosition.x - position.x)
                        <= m_ballRadius + m_targetRadius)
                && (std::abs(targetPosition.y - position.y)
                        <= m_ballRadius + m_targetRadius))
        {
            hitTarget = target;
            return true;
        }
    }
    hitTarget = m_targets.end();
    return false;
}

void Engine::makeMove(PlayerData& player, GameData& gameData)
{
    Ball& playerBall = player.getBall();

    if (!playerBall.wasInitialized())
    {
        return;
    }

    Position position = playerBall.getCurrentPosition();
    Position startPosition = playerBall.getStartPosition();
    position.x = startPosition.x + playerBall.getV0x() * playerBall.getFrameCount();
    position.y = -1
            * (startPosition.y
                    - (playerBall.getV0y() * playerBall.getFrameCount()
                            - (1.0f / 2 * m_gravity
                                    * (std::pow(playerBall.getFrameCount(), 2)))));
    position.z = (startPosition.z + playerBall.getV0z() * playerBall.getFrameCount());

     if(checkIfBallIsOutOfMap(position))
     {
         playerBall.setType(Ball::DESTROY);
	 gameData.addBall(playerBall);
	 playerBall.resetMoveVector();
	 return ;
     }

     playerBall.setCurrentPosition(position);
     playerBall.setType(Ball::MOVE);
     gameData.addBall(playerBall);

     if(checkIfBallIsOutOfMap(position))
     {
		 playerBall.setType(Ball::DESTROY);
		 gameData.addBall(playerBall);
		 playerBall.resetMoveVector();
     }
     else
     {
		 std::vector<TargetData>::iterator hitTarget = m_targets.end();
		 if(checkCollision(position, hitTarget))
		 {
			 hitTarget->type = TargetType::DESTROY;
			 gameData.addTarget(*hitTarget);
			 m_targets.erase(hitTarget);
			 player.updateScore();
			 ScoreData sd = {player.getName(),player.getScore()};
			 gameData.addScore(sd);
			 playerBall.setType(Ball::DESTROY);
			 gameData.addBall(playerBall);
			 playerBall.resetMoveVector();
		 }
     }

    playerBall.updateFrameCount();
}
