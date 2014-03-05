#include "Room/BallProvider.h"
#include <vector>
#include <algorithm>

BallProvider::BallProvider(const unsigned int &poolSize) :
                ABallProvider(poolSize)
{
    // TODO Auto-generated constructor stub

}

BallProvider::~BallProvider()
{
    // TODO Auto-generated destructor stub
}

bool BallProvider::registerBall(int& ballColor)
{

    if (POOL_SIZE > m_colorsInUse.size())
    {
        int colorIdx = m_colorsInUse.size();
        m_colorsInUse.push_back(colorIdx);
        std::sort(m_colorsInUse.begin(), m_colorsInUse.end());
        ballColor = BALL_COLLORS[colorIdx];
        return true;
    }
    else
        return false;
}

void BallProvider::unregisterBall(int& ballColor)
{
    std::vector<int>::iterator ballToUnregister;

    if (m_colorsInUse.end() != (ballToUnregister = getBallPointer(ballColor)))
    {

        m_colorsInUse.erase(ballToUnregister);
        std::sort(m_colorsInUse.begin(), m_colorsInUse.end());
    }
}

std::vector<int>::iterator BallProvider::getBallPointer(const int& ballColor)
{

    std::vector<int>::iterator ballIterator;
    int ballID = getBallID(ballColor);

    for (ballIterator = m_colorsInUse.begin();
            ballIterator <= m_colorsInUse.end(); ballIterator++)
    {
        if (*ballIterator == ballID)
            break;
    }
    return ballIterator;
}

int BallProvider::getBallID(const int& ballColor) const
{

    unsigned int ballIterator;
    for (ballIterator = 0; ballIterator < POOL_SIZE; ballIterator++)
    {
        if (BALL_COLLORS[ballIterator] == ballColor)
            break;
    }

    if (POOL_SIZE == ballIterator)
    {
        ballIterator = -1; //-> error
    }

    return ballIterator;
}
