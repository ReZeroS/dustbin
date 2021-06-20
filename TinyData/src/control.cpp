#include <fstream>
#include <iostream>
#include <iomanip>

#include <conio.h>

#include "control.h"

Control::Control()
{
    //ctor
}

Control::~Control()
{
    //dtor
}


void Control::readUsers(std::vector<User>& users){
    User user;
    std::ifstream userReader("userlist", std::ios::in | std::ios::binary);
//    userReader.read((char*)&user, sizeof(user));
    while(userReader.peek() != EOF)
    {
        userReader.read((char*)&user, sizeof(user));
        users.push_back(user);
    }
    userReader.close();
}


void Control::writeUsers(std::vector<User>& users){
    std::ofstream userWriter("userlist", std::ios::out | std::ios::binary | std::ios::trunc);

    int userCount = users.size();
    for(int i = 0; i < userCount; ++i)
    {
//        std::cout << "write: " << i << std::endl;
        userWriter.write((char*) &users[i], sizeof(users[i]));
    }
    std::cout << userCount << " rows has been affected." << std::endl;
    userWriter.close();
}


std::string Control::getPasswd()
{
    char c;
    std::string passwd;
    while ((c=getch()) != '\r')
    {
        passwd+=c;
        putchar('*');
    }
    return passwd;
}


bool Control::checkPermission(std::string name, std::string passwd){
    std::vector<User> userList;
    readUsers(userList);
    int len = userList.size();

//    std::cout << name << "#" << passwd << "#" << std::endl;

    for(int i = 0; i < len; ++i){
//        std::string username = userList[i].getUsername();
//        std::string password = userList[i].getPassword();
//        std::cout << username << "#" << password << "#" << std::endl;

        if(userList[i].getUsername() == name && userList[i].getPassword() == passwd){
//            if(userList[i].getSelect()){
//                std::cout << "Select " << std::endl;
//            }
            Control::Aselect = userList[i].getSelect();
            Control::Ainsert = userList[i].getInsert();
            Control::Aupdate = userList[i].getUpdate();
            Control::Adelete = userList[i].getDelete();
            return true;
        }
    }
    return false;
}


bool Control::createUser(std::string name){
    std::vector<User> userList;
    readUsers(userList);
    User user;
    user.setUsername(name);
    int listSize = userList.size();
    for(int i = 0; i < listSize; ++i){
        if(name == userList[i].getUsername()){
            std::cout << "The user name can not be duplicated." << std::endl;
            return false;
        }
    }
    std::cout << "Please input the password:";
    std::string passwd = getPasswd();
    user.setPassword(passwd);
    user.setDelete(false);
    user.setUpdate(false);
    user.setInsert(false);
    user.setSelect(false);
    userList.push_back(user);
    writeUsers(userList);
    return true;
}

void Control::Grant(std::vector<std::string> result){
    std::vector<User> userList;
    Control::readUsers(userList);
    int listLength = userList.size();

    for (int i = 0; i < listLength; ++i){
        if(userList[i].getUsername() == result[0]){
            int orderSize = result.size();
            for(int j = 1; j < orderSize; ++j){
                if(result[j] == "select"){
                    userList[i].setSelect(true);
                    continue;
                }
                if(result[j] == "insert"){
                    userList[i].setInsert(true);
                    continue;
                }
                if(result[j] == "update"){
                    userList[i].setUpdate(true);
                    continue;
                }
                if(result[j] == "delete"){
                    userList[i].setDelete(true);
                    continue;
                }
            }

        }
    }

    writeUsers(userList);

}

void Control::Revoke(std::vector<std::string> result){
    std::vector<User> userList;
    readUsers(userList);
    int listLength = userList.size();

    for (int i = 0; i < listLength; ++i){
        if(userList[i].getUsername() == result[0]){
            int orderSize = result.size();
            for(int j = 1; j < orderSize; ++j){
                if(result[j] == "select"){
                    userList[i].setSelect(false);
                    continue;
                }
                if(result[j] == "insert"){
                    userList[i].setInsert(false);
                    continue;
                }
                if(result[j] == "update"){
                    userList[i].setUpdate(false);
                    continue;
                }
                if(result[j] == "delete"){
                    userList[i].setDelete(false);
                    continue;
                }
            }

        }
    }
    writeUsers(userList);
}











void Control::showUsers(){
    std::vector<User> userList;
    readUsers(userList);
    int usersCount = userList.size();

    std::cout << "+---------------------------------------------+" << std::endl;
    std::cout << "+ Name    | Insert | Update | Delete | Select +" << std::endl;
    std::cout << "+---------------------------------------------+" << std::endl;

    for(int i = 0; i < usersCount; ++i){
        std::cout << "+ " ;
        std::cout << std::left << std::setw(8) << userList[i].getUsername();
        std::cout << "| ";
        if(userList[i].getInsert()){
            std::cout << std::left << std::setw(7) << "True";
        } else {
            std::cout << std::left << std::setw(7) << "False";
        }
        std::cout << "| ";
        if(userList[i].getUpdate()){
            std::cout << std::left << std::setw(7) << "True";
        } else {
            std::cout << std::left << std::setw(7) << "False";
        }
        std::cout << "| ";
        if(userList[i].getDelete()){
            std::cout << std::left << std::setw(7) << "True";
        } else {
            std::cout << std::left << std::setw(7) << "False";
        }
        std::cout << "| ";
        if(userList[i].getSelect()){
            std::cout << std::left << std::setw(7) << "True";
        } else {
            std::cout << std::left << std::setw(7) << "False";
        }
        std::cout << "+" << std::endl;
    }
    std::cout << "+---------------------------------------------+" << std::endl;

}


