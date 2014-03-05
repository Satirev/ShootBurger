#ifndef BALLDATA_H_
#define BALLDATA_H_

#include "Common/Vector.h"

struct BallData
{
    enum Type
    {
        UNKNOW, CREATE, DESTROY, MOVE
    };

    BallData();
    BallData(Type type, Position position, int colour);
    BallData(Position position, int colour);

    Position position;
    int colour;
    Type type;
};

#endif /* BALLDATA_H_ */
