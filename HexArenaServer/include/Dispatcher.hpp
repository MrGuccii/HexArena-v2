//
// Created by kristof on 9/22/26.
//

#ifndef HEXARENASERVER_DISPATCHER_HPP
#define HEXARENASERVER_DISPATCHER_HPP

#include <cstdint>
#include <mutex>
#include <queue>
#include <string_view>

#include <nlohmann/json.hpp>

enum ClientAction {
    Unknown = 0,
    Move = 1,
    Ping = 2,
};

struct ClientMessage {
    uintptr_t client_id = 0;
    ClientAction action = Unknown;
    nlohmann::json payload = {};
};

class Dispatcher {
public:
    void dispatch(uintptr_t client_id, std::string_view raw_message);

    bool poll(ClientMessage& out_msg);

private:
    ClientAction parse_action(std::string_view action_str, const nlohmann::json& json);

    std::queue<ClientMessage> message_queue;
    std::mutex queue_mutex;
};

#endif //HEXARENASERVER_DISPATCHER_HPP
