//
// Created by kristof on 9/14/26.
//

#include <utility>

#include "include/WebSocketServer.hpp"

WebSocketServer::WebSocketServer(const int port, std::string key_file, std::string cert_file)
    : key_file_(std::move(key_file)), cert_file_(std::move(cert_file)),
      app_({
        .key_file_name = key_file_.c_str(),
        .cert_file_name = cert_file_.c_str(),
      }),
      port_(port) {
    setup_routes();
}

void WebSocketServer::setup_routes() {
    app_.ws<SocketData>(
        "/*",
        {
            .open = [this](auto *ws) { this->on_open(ws); },
            .message = [this](auto *ws, std::string_view msg, uWS::OpCode op_code) {
                this->on_message(ws, msg, op_code);
            },
            .close = [this](auto *ws, int code, std::string_view msg) {
                this->on_close(ws, code, msg);
            }
        }
    );

    app_.get("/health", [](auto *res, auto *req) {
        res->writeStatus("200 OK")
            ->writeHeader("Content-Type", "application/json")
            ->end(R"({"status":"healthy"})");
    });
}

void WebSocketServer::on_open(WebSocket *ws) {
    auto *data = ws->getUserData();

    data->user_id = std::to_string(reinterpret_cast<uintptr_t>(ws));
    data->connected_at = std::chrono::system_clock::now().time_since_epoch().count();

    std::cout << "New connection: " << data->user_id << "\n";

    ws->send(R"({"event":"connected","message":"Welcome!"})", uWS::OpCode::TEXT);
}

void WebSocketServer::on_message(WebSocket *ws, const std::string_view message,
                                 const uWS::OpCode op_code) {
    const auto *data = ws->getUserData();

    std::cout << "[->] Message from " << data->user_id << ": " << message
              << "\n";

    // Echo it back
    ws->send(message, op_code);
}

void WebSocketServer::on_close(WebSocket *ws, int code,
                               std::string_view message) {
    const auto *data = ws->getUserData();

    std::cout << "[-] " << data->user_id << " disconnected\n";
}

void WebSocketServer::run() {
    app_.listen(port_, [this](auto *socket) {
        if (socket) {
            std::cout << "\nWebSocket server listening on port " << port_ << "\n";
            std::cout << "WSS endpoint: wss://localhost:" << port_ << "\n";
            std::cout << "Health check: https://localhost:" << port_ << "/health\n\n";
        }
        else {
            std::cerr << "WebSocket server failed to listen on port " << port_ << "\n";
            return;
        }
    })
    .run();
}