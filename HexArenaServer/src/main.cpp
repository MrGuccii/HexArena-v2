#include "include/WebSocketServer.hpp"
#include <iostream>

int main() {
    constexpr int PORT = 7000;

    try {
        WebSocketServer server(PORT, "../certs/key.pem", "../certs/cert.pem");
        server.run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}