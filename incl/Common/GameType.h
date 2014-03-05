#ifndef GAMETYPE_H_
#define GAMETYPE_H_

struct GameType
{
    int id;
    int value;
};

enum GameKind
    : int
    {
        TIME = 0, HITS
};

#endif /* GAMETYPE_H_ */
