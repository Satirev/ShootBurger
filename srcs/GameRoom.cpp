#include "Common/Vector.h"
#include "Common/GameType.h"
#include "Common/Client.h"
#include "Room/Rules.h"
#include "Room/GameRoom.h"
#include "Room/Game.h"
#include "Room/EndGameData.h"
#include "Room/BallProvider.h"
#include "Json/JsonProvider.h"
#include <vector>
#include <string>
#include <unistd.h>

GameRoom::GameRoom(const RoomConfigurator &roomConfig, const std::string &name) :
		ROOM_CONFIG(roomConfig), ROOM_NAME(name), m_gameStatus(STOPPED), m_currentGame(
				nullptr) {
	m_balls = new BallProvider(ROOM_CONFIG.maxPlayers);
}

void GameRoom::shoot(const Client *client, const Vector& vector) {
	if (PLAYING == m_gameStatus) {
		PlayerData * pd = nullptr;
		for (auto &player : m_players) {
			if (client == player.getClient()) {
				player.setMoveVector(vector);
				pd = &player;
			}
		}
		if (pd != nullptr) {
			for (auto &player : m_players) {
				player.getClient()->Notify(JSON_NOTIFY::INTERVAL,
						json::JsonProvider::MakeInterval(0,
								std::vector < Ball > (1, pd->getBall())));
			}

		}
	}
}

GameRoom::~GameRoom() {
// TODO Auto-generated destructor stub
	delete m_balls;
}

bool GameRoom::isPlayerInRoom(const std::string& name) const {
	bool result = false;
	for (auto &player : m_players) {
		if (player.getName() == name) {
			result = true;
			break;
		}
	}
	return result;
}

std::string GameRoom::createPlayerName(const std::string &playerName) const {
	std::string createdName = playerName;
	int numToAppend = 0;

	for (auto &player : m_players) {
		createdName = playerName;
		while (player.getName() == playerName && isPlayerInRoom(createdName)) {
			numToAppend++;
			createdName = playerName;
			createdName.append(" ").append(std::to_string(numToAppend));
		}
	}
	return createdName;
}

bool GameRoom::addPlayer(const std::string& name, Client * client) {
	int color;
	if (STOPPED == m_gameStatus) {
		if (ROOM_CONFIG.maxPlayers <= m_players.size()) {
			return false;
		}

		std::string playerName = createPlayerName(name);

		if (m_balls->registerBall(color)) {
			PlayerData newPlayer(client, color, playerName);
			m_players.push_back(newPlayer);
		}
		Player answer;
		answer.name = playerName;
		answer.color = static_cast<int>(color);
		client->Notify(JSON_NOTIFY::HELLO_RESPONE,
				json::JsonProvider::MakeHelloRespone(answer));

		return true;
	} else {
		return false;
	}
}

void GameRoom::removePlayer(Client* client) {

	std::unique_lock < std::mutex > lock(m_mutex);
	for (std::vector<PlayerData>::iterator player = m_players.begin();
			player < m_players.end(); player++) {

		int ballColor = player->getBall().getColour();
		m_balls->unregisterBall(ballColor);

		if (client == player->getClient()) {
			m_players.erase(player);
		}
	}
}

void GameRoom::play() {
	Run();
}

void GameRoom::unreadyPlayers() {
	for (auto& player : m_players) {
		player.setReady(false);
	}
}

void GameRoom::waitForGameBegin() {

	while (1) {
		usleep(100);
		if (isGameRoomReady())
			break;
	}
}

void GameRoom::initGame() {
	m_currentGame = new Game(GameKind::TIME, m_players, ROOM_CONFIG.rules,
			ROOM_CONFIG.mapSize);

	std::vector<Player> players;
	for (auto &player : m_players) {
		players.push_back(player.getPlayerStruct());
	}

	for (auto &player : m_players) {
		player.getClient()->Notify(JSON_NOTIFY::INIT_GAME,
				json::JsonProvider::MakeInitGame(0, ROOM_CONFIG.mapSize,
						players, ROOM_CONFIG.type));
	}
}

bool GameRoom::isGameRoomReady() {
	bool result = true;
	if (m_players.size() < 1) {
		result = false;
	} else {
		for (auto &player : m_players) {
			if (!(result = player.isReady())) {
				break;
			}
		}
	}
	return result;
}

void GameRoom::startGame(int startGameDelay) {
	for (auto& player : m_players) {
		player.getClient()->Notify(JSON_NOTIFY::START_GAME,
				json::JsonProvider::MakeStartGame(startGameDelay));
	}
	sleep(startGameDelay);
}

void GameRoom::Task() {
	m_gameStatus = STOPPED;
	int startGameDelay = 5;

	while (1) {
		switch (m_gameStatus) {
		case STOPPED:
			if (isGameRoomReady()) {
				unreadyPlayers();
				initGame();
				waitForGameBegin();
				m_gameStatus = PLAYING;
				break;
			}
			usleep(500); //0,5s
			break;
		case PLAYING:
			startGame(startGameDelay);
			unreadyPlayers();

			while (!m_currentGame->isEndGame()) {
				std::unique_lock < std::mutex > lock(m_mutex);
				m_currentGame->nextMove();
				if ( 0 == m_players.size()) {
					break; //no players to play
				}
				usleep(17000); //0,02s
			}
			endGame();
			break;
		};

	}
}

void GameRoom::stop() {
	Halt();
}

void GameRoom::toggleReady(const Client* client) {
	if (STOPPED == m_gameStatus) {
		for (auto &player : m_players) {
			if (client == player.getClient()) {
				if (!player.isReady()) {
					player.setReady(true);
				} else {
					player.setReady(false);
				}
			}
		}
	}
}

void GameRoom::endGame() {
	EndGameData edg = m_currentGame->getWinner();

	delete m_currentGame;
	m_currentGame = nullptr;
	m_gameStatus = STOPPED;
//unready
	for (auto &player : m_players) {
		player.getClient()->Notify(JSON_NOTIFY::END_GAME,
				json::JsonProvider::MakeEndGame(edg.playerName, edg.score));
		player.setReady(false);
		player.clearScore();
		int ballColor = player.getBall().getColour();
		m_balls->unregisterBall(ballColor);
	}
	m_players.clear();
}
