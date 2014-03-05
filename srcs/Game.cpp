#include "Room/Game.h"
using namespace json;

Game::Game(GameKind type, std::vector<PlayerData>& players, Rules rules,
        const Vector & mapSize) :
                m_players(players), m_rules(rules),
                m_engine(rules, mapSize, 9.81f), m_type(type),
                m_startTime(std::time(NULL)), m_currentTime(std::time(NULL)),
                m_gameTotalTime(5 * 60), m_gameTotalHits(5)
{
}

Game::~Game()
{
}

void Game::nextMove()
{
    GameData gameData;
    makeMove(gameData);
    notifyClients(gameData);
}

void Game::makeMove(GameData& gameData)
{
    std::random_shuffle(m_players.begin(), m_players.end());

    m_engine.handleTargets(gameData);

    for (auto& player : m_players)
    {
        m_engine.makeMove(player, gameData);
    }
}

void Game::notifyClients(const GameData& gameData)
{
    const std::vector<Ball> balls = gameData.getBalls();
    const std::vector<TargetData>& targets = gameData.getTargets();
    const std::vector<ScoreData>& scores = gameData.getScores();
    JsonProvider jsonProvider;

    for (auto& player : m_players)
    {
        Client* client = player.getClient();
        if (client != nullptr)
        {
            auto interval = jsonProvider.MakeInterval(
                    static_cast<int>(m_currentTime - m_startTime), balls);
            client->Notify(JSON_NOTIFY::INTERVAL, interval);

            for (size_t i = 0; i < targets.size(); i++)
            {
                auto target = jsonProvider.MakeTarget(targets[i].position,
                        targets[i].type, targets[i].id);

                client->Notify(JSON_NOTIFY::TARGET, target);
            }

            for (size_t i = 0; i < scores.size(); i++)
            {
                auto score = jsonProvider.MakeScore(scores[i].playerName,
                        scores[i].score);
                client->Notify(JSON_NOTIFY::SCORE, score);
            }
            	
            if(gameData.isEndGame())
            {
                EndGameData egd = gameData.getEndGame();
                auto end = 
                   jsonProvider.MakeEndGame(egd.playerName, egd.score);
                client->Notify(JSON_NOTIFY::END_GAME, end); 
            }	 
        }
    }
}

bool Game::isEndGame()
{
    switch (m_type)
    {
    case GameKind::TIME:
        m_currentTime = std::time(NULL);
        return ((m_currentTime - m_startTime) > m_gameTotalTime);

    case GameKind::HITS:
        return (std::find_if(m_players.begin(), m_players.end(),
                [&](PlayerData& playerData)->bool
                {
                    return m_gameTotalHits == playerData.getScore();
                }) != m_players.end());
    }
    return false;
}

EndGameData Game::getWinner() const
{
    auto player =
            std::max_element(m_players.cbegin(), m_players.cend(),
                    [&](const PlayerData& playerData1, const PlayerData& playerData2)->bool
                    {
                        return playerData1.getScore() < playerData2.getScore();
                    });
    EndGameData edg
    { player->getName(), player->getScore() };
    return edg;
}
