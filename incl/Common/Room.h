#ifndef ROOM_H_
#define ROOM_H_

#include <string>

class Room
{
public:
    explicit Room(const std::string& roomName);
    ~Room();

private:
    std::string m_roomName;
};

#endif /* ROOM_H_ */
