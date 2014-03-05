#ifndef JSONTYPES_H_
#define JSONTYPES_H_

enum JSON_NOTIFY
{
    HELLO_RESPONE, INIT_GAME, START_GAME, END_GAME, INTERVAL, TARGET, SCORE
};

enum TargetType
    : int
    {
        CREATE = 1, MOVE, DESTROY, NONE
};

#endif /* JSONTYPES_H_ */
