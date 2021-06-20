#include <iostream>
#include <fstream>
#include <cstring>
#include <typeinfo>

#include "field.h"



void Field::display(){
    std::cout << "#####################################################" << std::endl;
    std::cout << id << len << name << type << pKey << fKey << check << std::endl;
    std::cout << typeid(id).name() << std::endl;
    std::cout << typeid(name).name() << std::endl;
    std::cout << typeid(len).name() << std::endl;
    std::cout << typeid(type).name() << std::endl;
    std::cout << typeid(noIque).name() << std::endl;
    std::cout << typeid(noNull).name() << std::endl;
    std::cout << typeid(pKey).name() << std::endl;
    std::cout << typeid(fKey).name() << std::endl;
    std::cout << typeid(check).name() << std::endl;
    std::cout << "#####################################################" << std::endl;
    std::cout << "#####################################################" << std::endl;
    std::cout << sizeof(id) << std::endl;
    std::cout << sizeof(name) << std::endl;
    std::cout << sizeof(len) << std::endl;
    std::cout << sizeof(type) << std::endl;
    std::cout << sizeof(noIque) << std::endl;
    std::cout << sizeof(noNull) << std::endl;
    std::cout << sizeof(pKey) << std::endl;
    std::cout << sizeof(fKey) << std::endl;
    std::cout << sizeof(check) << std::endl;
    std::cout << "#####################################################" << std::endl;
}

/*
set method
*/
void Field::setId(int _id){
    id = _id;
}

void Field::setName(std::string _name){
//    name = new char[_name.size()];
    strcpy(name, (char*)_name.c_str());
}

void Field::setType(std::string _type){
//    type = new char[_type.size()];
    strcpy(type, (char*)_type.c_str());
}
void Field::setSize(int _len){
    len = _len;
}

void Field::setNoique(bool _noIque){
    noIque = _noIque;
}

void Field::setNoNull(bool _noNull){
    noNull = _noNull;
}

void Field::setPKey(bool _pKey){
    pKey = _pKey;
}

void Field::setFKey(std::string _fKey){
//    fKey = new char[_fKey.size()];
    strcpy(fKey, (char*)_fKey.c_str());
}

void Field::setCheck(std::string _check){
//    check = new char[_check.size()];
    strcpy(check, (char*)_check.c_str());
}




/*
get method¡£
*/

int Field::getId(){
    return id;
}

std::string Field::getName(){
    return name;
}

std::string Field::getType(){
    return type;
}

int Field::getSize(){
    return len;
}

bool Field::getNoique(){
    return noIque;
}

bool Field::getNonull(){
    return noNull;
}

bool Field::getPkey(){
    return pKey;
}
std::string Field::getFkey(){
    return fKey;
}

std::string Field::getCheck(){
    return check;
}


