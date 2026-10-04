//
// Created by kristof on 9/16/26.
//

#include "include/Game.hpp"
#define PORT (7000)

Game::Game() : webSocketServer(PORT, "../certs/key.pem", "../certs/cert.pem", dispatcher_),
               is_running(false) {
    updateInterval = std::chrono::milliseconds(1000 / 60);
}

Game::~Game() {
    stop();
}

void Game::start() {
    if (is_running) return;

    is_running = true;
    game_loop_thread = std::thread(&Game::game_loop, this);

    std::cout << "[Game] Game loop started" << std::endl;
}

void Game::stop() {
    if (!is_running) return;

    is_running = false;

    game_loop_thread.join();
}