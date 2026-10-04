//
// Created by kristof on 9/22/26.
//
#include "include/Dispatcher.hpp"

#include <iostream>

using json = nlohmann::json;

void Dispatcher::dispatch(uintptr_t client_id, std::string_view raw_message) {
    try {
        json parsed_message = json::parse(raw_message);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
}

bool Dispatcher::poll(ClientMessage& out_msg) {
    std::lock_guard<std::mutex> lock(queue_mutex);

    if (message_queue.empty()) {
        return false;
    }

    out_msg = message_queue.front();
    message_queue.pop();

    return true;
}
