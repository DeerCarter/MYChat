#include "UserModel.hpp"
#include "db.h"
#include <iostream>
using namespace std;

bool UserModel::insert(User &user) {
    // 1. 组装sql语句
    char sql[1024] = {};
    sprintf(sql, "insert into User(name, password, state) values('%s', '%s', '%s')",
            user.getName().c_str(), user.getPasswd().c_str(), user.getState().c_str());

    MySQL mysql;
    if (mysql.connect()) {
        if (mysql.update(sql)) {
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}