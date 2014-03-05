#ifndef BALL_H_
#define BALL_H_

#include "Common/Vector.h"

struct Ball {
	enum Type
		: int
		{
			CREATE, MOVE, DESTROY
	};

	Ball();
	Ball(int colour_);
	Ball(Type type_, Position position_, int colour_);

	Vector getCurrentPosition();
	void setCurrentPosition(const Position& currentPosition);
	Vector getStartPosition();
	void setStartPosition(Vector startPosition);
	void resetMoveVector();
	int getColour() const;
	int getId() const;
	float getV0x() const;
	float getV0y() const;
	float getV0z() const;
	bool wasInitialized() const;
	Vector getMoveVector();
	void setMoveVector(const Vector& newVector);
	void init();

	Type getType() const {
		return m_type;
	}

	void setType(Type type) {
		this->m_type = type;
	}

	float getFrameCount() const {
		return m_frameCount;
	}

	void updateFrameCount(float frameCount = 0.35f) {
		m_frameCount += frameCount;
	}

private:
	static int NextId;
	int m_id;
	int m_colour;
	Type m_type;
	Vector m_moveVector;
	Position m_position;
	Position m_startPosition;
	bool m_wasInitialized;
	float m_v0x;
	float m_v0y;
	float m_v0z;
	float m_frameCount;
};

inline Vector Ball::getCurrentPosition() {
	return m_position;
}

inline void Ball::setCurrentPosition(const Position& currentPosition) {
	m_position = currentPosition;
}

inline Vector Ball::getStartPosition() {
	return m_startPosition;
}

inline void Ball::setStartPosition(Vector startPosition) {
	m_startPosition = startPosition;
}

inline void Ball::resetMoveVector() {
//    m_moveVector = Vector
//    { 0, 0, 0 };
	m_wasInitialized = false;
}

inline float Ball::getV0x() const {
	return m_v0x;
}

inline float Ball::getV0y() const {
	return m_v0y;
}

inline float Ball::getV0z() const {
	return m_v0z;
}

inline bool Ball::wasInitialized() const {
	return m_wasInitialized;
}

inline Vector Ball::getMoveVector() {
	return m_moveVector;
}

inline void Ball::setMoveVector(const Vector& newVector) {
	if (Type::DESTROY == m_type) {
		m_moveVector = newVector;
		init();
	}
}

inline int Ball::getColour() const {
	return m_colour;
}

// todo ballprovider tworzy Ball z danym kolorem, wywalic position z player data, dodac ball do playera

inline int Ball::getId() const {
	return m_id;
}

#endif /* BALL_H_ */
