//
// Created by kristof on 9/16/26.
//

#ifndef HEXARENASERVER_GAME_HPP
#define HEXARENASERVER_GAME_HPP

#include "Player.hpp"
#include "Map.hpp"
#include "WebSocketServer.hpp"

class Game {
public:

private:
    Map map;
    std::vector<Player> players;
    WebSocketServer webSocketServer;
    std::chrono::steady_clock::time_point lastUpdate;
    std::chrono::steady_clock::duration updateInterval;
};

#endif //HEXARENASERVER_GAME_HPP
