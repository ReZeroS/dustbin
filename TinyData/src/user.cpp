#include <cstring>

#include "user.h"

void User::setSelect(bool key){
    pSelect = key;
}

void User::setDelete(bool key){
    pDelete = key;
}

void User::setInsert(bool key){
    pInsert = key;
}



void User::setUpdate(bool key){
    pUpdate = key;
}




bool User::getSelect(){
    return pSelect;
}

bool User::getDelete(){
    return pDelete;
}

bool User::getInsert(){
    return pInsert;
}



bool User::getUpdate(){
    return pUpdate;
}



void User::setUsername(std::string name){
    strcpy(userName, name.c_str());
}

void User::setPassword(std::string passwd){
    strcpy(passWord, passwd.c_str());
}


std::string User::getUsername(){
    return userName;
}

std::string User::getPassword(){
    return passWord;
}
