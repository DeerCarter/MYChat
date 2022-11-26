#ifndef USER_H
#define USER_H

#include <string>

class User {
    User(int ID = -1, std::string nm = "", std::string psw = "", std::string st = "offline")
    :id(ID), name(nm), password(psw), state(st){

    }
    void setId(int id) {
        this->id = id;
    }
    void setName(int Name) {
        this->name = Name;
    }
    void setPwd(int pwd) {
        this->password = pwd;
    }
    void setState(int st) {
        this->state = st;
    }
    int getID() const {
        return id;
    }
    std::string getName() const {
        return this->name;
    }
    std::string getPasswd() const {
        return this->password;
    }
    std::string getState() const {
        return this->state;
    }
private:
    int id;
    std::string name;
    std::string password;
    std::string state;
};

#endif