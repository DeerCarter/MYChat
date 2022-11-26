#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <unordered_map>
#include <functional>
#include <muduo/net/TcpConnection.h>

#include "json.hpp"
using namespace muduo;
using json = nlohmann::json;
using namespace muduo::net;

// 对应的事件处理函数有三个参数， 起个别名  声明函数对象
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp time)>;

// 单例模式 实现 聊天服务器的业务类  需要给msgid 映射 不同的事件回调函数
class ChatService
{
public:
    //
    static ChatService *instance();
    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 获取消息对应的处理函数
    MsgHandler getHandler(int msgType);

private:
    ChatService();
    // 存储消息id 和 对应的 业务处理函数
    std::unordered_map<int, MsgHandler> msgHandler;
};

#endif
