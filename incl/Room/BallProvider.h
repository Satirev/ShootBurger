#ifndef BALLPROVIDER_H_
#define BALLPROVIDER_H_

#include "ABallProvider.h"

class BallProvider: public ABallProvider
{
public:
    BallProvider(const unsigned int &poolSize);
    virtual ~BallProvider();

    virtual bool registerBall(int & ball);
    virtual void unregisterBall(int & ball);

private:
    enum
    {
        MAX_NUM_BALLS = 8
    };
    const int BALL_COLLORS[MAX_NUM_BALLS] =
    { 0xCD3333, 0xD2691E, 0x6B4226, 0x7CFC00, 0xFF1493, 0xFFDEAD, 0xFFB90F,
            0x236B8E };

    int getBallID(const int& ballColor) const;
    std::vector<int>::iterator getBallPointer(const int& color);
    std::vector<int> m_colorsInUse;
};

#endif /* BALLPROVIDER_H_ */
