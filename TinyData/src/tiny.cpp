#include <iostream>
#include <fstream>

#include <direct.h>

#include "tiny.h"
#include "sqlmain.h"


Tiny::Tiny()
{
    //ctor
}

Tiny::~Tiny()
{
    //dtor
}

void Tiny::createDatabase(std::string name){
    int isExist = _mkdir(name.c_str());
    if(!isExist){
        std::cout << "The database " << name << " has been created." << std::endl;
    } else {
        std::cout << "Please check the permission or whether the directory has been existed." << std::endl;
    }
    std::ofstream out("DATABASE", std::ios::app | std::ios::binary);
    out << name  << ";";
    out.close();
}

void Tiny::dropDB(std::string dbName){
    if(dbName.size() < 1){
        std::cout << "Sorry, your input does not match the rule." << std::endl;
    }
    if(!rmdir(dbName.c_str())){
        std::cout << "The database has been deleted." << std::endl;
    } else {
        std::cout << "Sorry, the database not exist or you do not have the authorization. " << std::endl;
    }
}

void Tiny::dropTable(std::string table){
    std::string descLocation = Sqlmain::DBRoot + "/" + table + ".tiny";
    std::string dataLocation = Sqlmain::DBRoot + "/" + table + ".data";
    if(remove(descLocation.c_str()) | remove(dataLocation.c_str())){
        std::cout << "You can not delete the table for some reasons." << std::endl;
    } else {
        std::cout << "Successfully delete it." << std::endl;
    }
}

void Tiny::deleteTable(std::string table){
    std::string location = Sqlmain::DBRoot + "/" + table + ".data";

    std::ofstream del(location);
    if(!del){
        std::cout << "The table does not exist." << std::endl;
    } else {
        del.close();
    }
}
