#include "ChatServer.hpp"

#include <functional>
using namespace std;
using namespace placeholders;

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : chatServer(loop, listenAddr, nameArg), entLoop(loop)
{
    // 注册连接回调函数
    chatServer.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    // 注册消息回调函数
    chatServer.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    // 设置线程数量
    chatServer.setThreadNum(4);
}

void ChatServer::start()
{
    chatServer.start();
}

// 连接监听函数
void ChatServer::onConnection(const TcpConnectionPtr &)
{
    
}

// 读写事件监听函数
void ChatServer::onMessage(const TcpConnectionPtr &,
                           Buffer *,
                           Timestamp)
{

}