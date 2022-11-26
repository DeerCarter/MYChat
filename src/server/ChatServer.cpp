#include "ChatServer.hpp"
#include <string>
#include <functional>

#include "json.hpp"
#include "ChatService.hpp"
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

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
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    // 客户端断开连接
    if (!conn->connected())
    {
        conn->shutdown();
    }
}

// 读写事件监听函数
void ChatServer::onMessage(const TcpConnectionPtr & conn,
                           Buffer *buffer,
                           Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    // 反序列化为json
    json js = json::parse(buf);
    // 根据收到的不同的消息标识  调用不同的方法
    // 这里 需要将网络模块和业务模块的代码解耦， 不能直接if else
    // 利用回调的思想 通过json里的msgID 获取 业务handler，来调用不同的函数
    // 还有一种是基于抽象类来实现
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    // 调用已经绑定好的事件处理函数，执行相应的业务处理
    msgHandler(conn, js, time);
}