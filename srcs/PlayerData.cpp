#include "Common/Player.h"
#include "Common/Vector.h"
#include "Room/PlayerData.h"

PlayerData::PlayerData(Client * client, int &ballColour,
        const std::string &name) :
                m_client(client), m_ball(ballColour), m_ready(false), m_score(0)
{
    m_name = name;
}

PlayerData::~PlayerData()
{
    // TODO Auto-generated destructor stub
}
