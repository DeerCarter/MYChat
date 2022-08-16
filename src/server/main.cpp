#include <iostream>
#include "ChatServer.hpp"

int main() {
    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "odd's ChatServer");

    server.start();
    loop.loop();
    return 0;
}