//
// Created by kristof on 9/14/26.
//

#ifndef HEXARENASERVER_WEBSOCKETSERVER_HPP
#define HEXARENASERVER_WEBSOCKETSERVER_HPP
#include "App.h"
#include <string>

class WebSocketServer {
public:
    explicit WebSocketServer(int port, std::string key_file,
                             std::string cert_file);

    // Run the server (this blocks until shutdown)
    void run();

private:
    // Per-connection data- store whatever you need here
    struct SocketData {
        std::string user_id;
        uint64_t connected_at;
    };

    // Type aliases to keep our sanity
    constexpr static bool IS_USING_SSL = true;
    constexpr static bool IS_SERVER = true;
    using WebSocket = uWS::WebSocket<IS_USING_SSL, IS_SERVER, SocketData>;

    // The lifecycle callbacks
    void setup_routes();
    void on_listen(us_listen_socket_t *listen_socket);
    void on_open(WebSocket *ws);
    void on_message(WebSocket *ws, std::string_view message, uWS::OpCode op_code);
    void on_close(WebSocket *ws, int code, std::string_view message);

    // Member variables
    std::string key_file_;
    std::string cert_file_;
    uWS::SSLApp app_;
    int port_;
};

#endif //HEXARENASERVER_WEBSOCKETSERVER_HPP
