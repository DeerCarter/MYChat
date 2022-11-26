#include "ChatService.hpp"
#include "Public.hpp"
#include "muduo/base/Logging.h"

ChatService *ChatService::instance()
{
    static ChatService service;
    return &service;
}

// 注册消息以及对应的Handler回调函数
ChatService::ChatService()
{
    msgHandler.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
    msgHandler.insert({REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});
}

MsgHandler ChatService::getHandler(int msgType)
{
    // 没找到 返回一个默认的处理函数，记录错误日志
    if (msgHandler.find(msgType) == msgHandler.end()) {
        
        return [=](const TcpConnectionPtr &conn, json &js, Timestamp time){
            LOG_ERROR << "msgType : " << msgType << "  not find!";
        };
    }
    return msgHandler[msgType];
}

void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "do login service!";
}

// 处理注册业务
void ChatService::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "do reg service";
}
