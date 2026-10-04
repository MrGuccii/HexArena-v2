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
    Game();
    ~Game();

    void start();
    void stop();
private:
    void game_loop();

    Map map;
    std::vector<Player> players;
    Dispatcher dispatcher_;
    WebSocketServer webSocketServer;

    // Thread handling
    std::thread game_loop_thread;
    std::atomic<bool> is_running;

    // Timing
    std::chrono::steady_clock::time_point lastUpdate;
    std::chrono::steady_clock::duration updateInterval;
};

#endif //HEXARENASERVER_GAME_HPP
