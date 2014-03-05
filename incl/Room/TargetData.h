#ifndef TARGETDATA_H_
#define TARGETDATA_H_

#include "Json/JsonTypes.h"
#include "Common/Vector.h"

struct TargetData
{
    TargetData();
    TargetData(Position position);
    TargetData(TargetType type, Position position);

    int id;
    Position position;
    TargetType type;

private:
    static int NextId;

};

#endif /* TARGETDATA_H_ */
