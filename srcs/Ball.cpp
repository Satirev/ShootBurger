#include "Common/Ball.h"
#include <cmath>
#include <boost/math/constants/constants.hpp>

#include <iostream>

int Ball::NextId = 1;

Ball::Ball() :
                m_id(Ball::NextId++), m_colour(-1), m_type(Ball::DESTROY),
                m_position(-1, -1, -1), m_wasInitialized(false)
{
}

Ball::Ball(int colour_) :
                m_id(Ball::NextId++), m_colour(colour_), m_type(Ball::DESTROY),
                m_position(-1, -1, -1), m_wasInitialized(false)
{
}

Ball::Ball(Ball::Type type_, Position position_, int colour_) :
                m_id(Ball::NextId++), m_colour(colour_), m_type(type_),
                m_position(position_), m_wasInitialized(false)
{
}

void Ball::init()
{
    m_startPosition = m_moveVector;
    m_position = m_moveVector;
    m_frameCount = 0;
    const float pi = boost::math::constants::pi<float>();
    float theta = std::atan(static_cast<float>(m_position.y) / m_position.z)
            * (180.0f / pi);
    float angle = std::atan(static_cast<float>(m_position.x) / m_position.z)
            * (180.0f / pi);

    float velocity = m_moveVector.getModulus();
    std::cout << "theta = " << theta << std::endl;
    m_v0x = velocity * std::sin(angle * pi / 180);
    m_v0y = velocity * std::sin(theta * pi / 180);
    m_v0z = velocity * std::cos(theta * pi / 180);

    m_wasInitialized = true;
    m_type = Type::CREATE;

    std::cout << "Move vector: "<< m_position;

}
