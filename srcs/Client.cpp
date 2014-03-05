#include "Common/Client.h"
#include "Automata/AState.h"
#include "Automata/Uninitialized.h"
#include "Common/Dispatcher.h"

#include <iostream>

Client::Client(Lobby *lobby, Dispatcher *disp) :
                m_name(""), m_current_state(0), m_lobby(lobby), m_disp(disp)
{
    m_current_state = new Uninitialized(this);
}

Client::~Client()
{
    delete m_current_state;
}

void Client::ProcessRequest(const std::string &request)
{
    AState *next = 0;
    std::cout << "[CLIENT] " << this << ": ";
    next = m_current_state->Process(request);
    if (next != 0)
    {
        delete m_current_state;
        m_current_state = next;
    }
}

void Client::Notify(JSON_NOTIFY type, json::IJsonSerializable *obj)
{
    std::string parsed_answer;
    AState *next = m_current_state->Process(type, parsed_answer, obj);
    m_disp->PushOut(this, parsed_answer);
    if (next != 0)
    {
        delete m_current_state;
        m_current_state = next;
    }
    delete obj;
}

Lobby *Client::GetLobby()
{
    return m_lobby;
}
