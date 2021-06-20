#include <regex>
#include <vector>
#include <string>
#include <iostream>


#include "util.h"
#include "field.h"
#include "global.h"
#include "control.h"
#include "sqlmain.h"




std::string Sqlmain::DBRoot = "default";
bool Control::Aselect = false;
bool Control::Ainsert = false;
bool Control::Adelete = false;
bool Control::Aupdate = false;

/*************************************************
Function: // SQL Regex Pattern

*************************************************/


const std::regex Sqlmain::CREATE_DB = std::regex("\\s*create\\s+database\\s+(\\w+?)\\s*", std::regex::icase);

const std::regex Sqlmain::USE_DB = std::regex("\\s*use\\s+(\\w+?)\\s*", std::regex::icase);
/*
\\s*create\\s+table\\s+(\\w+)\\s*\\(((.|\\s)+)\\)\\s*
\\s*create\\s+table\\s+(\\w+)\\s*\\((.+)\\)\\s*
*/

//main
const std::regex Sqlmain::CREATE_TABLE = std::regex("\\s*create\\s+table\\s+(\\w+)\\s*\\(((.|\\s)+)\\)\\s*", std::regex::icase);

const std::regex Sqlmain::INSERT_INTO = std::regex("\\s*insert\\s+into\\s+(\\w+)\\s+values\\((.+)\\)\\s*", std::regex::icase);

const std::regex Sqlmain::DELETE_DATA = std::regex("\\s*delete\\s+from\\s+(\\w+)\\s+where\\s+(\\w+)\\s*=\\s*(.*)\\s*", std::regex::icase);

const std::regex Sqlmain::SELECT_FROM = std::regex("\\s*select\\s+(.+)\\s+from\\s+(\\w+)\\s*", std::regex::icase);

const std::regex Sqlmain::UPDATE_DATA = std::regex("\\s*update\\s+(\\w+)\\s+set\\s+(\\w+)\\s*=\\s*(.+)\\s+where\\s+(\\w+)\\s*=\\s*(.+)\\s*", std::regex::icase);



//branch
const std::regex Sqlmain::DROP_DB = std::regex("\\s*drop\\s+database\\s+(\\w+)\\s*", std::regex::icase);

const std::regex Sqlmain::DROP_TABLE = std::regex("\\s*drop\\s+table\\s+(\\w+)\\s*", std::regex::icase);

const std::regex Sqlmain::DEL_TABLE = std::regex("\\s*delete\\s+from\\s+(\\w+)\\s*", std::regex::icase);

const std::regex Sqlmain::HELP_TABLE = std::regex("\\s*help\\s+table\\s+(\\w+)\\s*", std::regex::icase);



/**************************************/
/**the primary and some little tools**/
/************************************/
const std::regex Sqlmain::reField = std::regex("\\s*(\\w+)\\s+(\\w+?)\\((\\w+?)\\)(.*)", std::regex::icase);

const std::regex Sqlmain::rePrimaryKey = std::regex("\\s*primary\\s+key\\s+\\((\\w+?)\\)\\s*", std::regex::icase);

const std::regex Sqlmain::reForeignKey = std::regex("\\s*foreign\\s+key\\s+\\((\\w+)\\)\\s+references\\s+(\\w+)\\((\\w+)\\)\\s*", std::regex::icase);


/************************************/
/**the user grant permission **/
/**********************************/

const std::regex Sqlmain::reGrant = std::regex("\\s*grant\\s+(\\w+)\\s+(.*)\\s*", std::regex::icase);
const std::regex Sqlmain::reRevoke = std::regex("\\s*revoke\\s+(\\w+)\\s+(.*)\\s*", std::regex::icase);

const std::regex Sqlmain::reCreateUser = std::regex("\\s*create\\s+user\\s+(\\w+)\\s*", std::regex::icase);


const std::regex Sqlmain::HELP_DB = std::regex("\\s*help\\s+database\\s*", std::regex::icase);



/*************************/
/**Optimized**/
/************************/
const std::regex Sqlmain::O_INERT_INTO = std::regex("\\s*insert\\s+into\\s+(\\w+)\\s+values(.+)\\s*", std::regex::icase);

//const std::regex Sqlmain::O_SELECT_FROM = std::regex("\\s*select\\s+(\\w+)\\s+from\\s+(\\w+)\\s+where\\s+(\\w+)\\s+=\\s+(\\.+?)\\((\\.+)\\)\\s*", std::regex::icase);


const std::regex Sqlmain::O_SELECT_FROM = std::regex("\\s*select\\s+(\\w+)\\s+from\\s+(\\w+)\\s+where\\s+(\\w+)\\s+in\\s*\\((.+)\\)\\s*", std::regex::icase);

//const std::regex Sqlmain::O_SELECT_FROM_CHILD = std::regex("\\s*select");


/*************************/
/**View**/
/************************/

const std::regex Sqlmain::CREATE_VIEW = std::regex("\\s*create\\s+view\\s+(\\w+)\\s+as\\s*(.+)\\s*", std::regex::icase);

const std::regex Sqlmain::HELP_VIEW = std::regex("\\s*help\\s+view\\s+(\\w+)\\s*", std::regex::icase);


/*********************/
/**Index**/
/***************/

const std::regex Sqlmain::CREATE_INDEX = std::regex("\\s*create\\s+index\\s+(\\w+)\\s+on\\s+(\\w+)\\s*\\((.+)\\)\\s*", std::regex::icase);

const std::regex Sqlmain::HELP_INDEX = std::regex("\\s*help\\s+index\\s+(\\w+)\\s*", std::regex::icase);





//tinydata -u root -p
//int (int argc, char* argv[]){
int main(){

/***************************
Unlock the code segment
***************************/
//
    std::cout << "Please input your user name:";
    std::string username;
    std::cin >> username;
    std::cout << "Please input your password:";
    std::string password = Control::getPasswd();
    bool check = Control::checkPermission(username, password);
    if(check){
        Global::HelloWorld();
        while(1){
            std::cout << "TinyData>";
            std::string commands;
            std::getline(std::cin, commands, ';');
//                commands = Sqlmain::sqlState(commands);
            Sqlmain::analyze(commands);
        }
    } else {
        std::cout << "Sorry,  you may not have the authorization to execute the system." << std::endl;

    }
    return 0;
}
