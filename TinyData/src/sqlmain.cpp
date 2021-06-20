#include <regex>
#include <string>
#include <iostream>


#include "item.h"
#include "tiny.h"
#include "util.h"
#include "view.h"
#include "index.h"
#include "rogex.h"
#include "control.h"
#include "sqlmain.h"
#include "optimize.h"







void Sqlmain::analyze(std::string commands){




    //re compile
    std::cout << "Analyzing: " << std::endl;
    //Use DB
    if (std::regex_match(commands, USE_DB)){
        std::cout << "Using the Database... " << std::endl;
        std::string result = Rogex::reUseDB(commands);
        Sqlmain::DBRoot = result;
        std::cout << "Now you use the database: " << result << std::endl;
        return ;
    }

    //view
    //pending
    if(std::regex_match(commands, Sqlmain::CREATE_VIEW)){
        std::string viewName, command;
        Rogex::createView(commands, viewName, command);
        View::createView(viewName, command);
        std::cout << "The view has been created." << std::endl;
        return ;
    }
    if(std::regex_match(commands, Sqlmain::HELP_VIEW)){
        std::string viewName = Rogex::helpView(commands);
        View::helpView(viewName);

        return ;
    }


    //index
    //pending
    if(std::regex_match(commands, Sqlmain::CREATE_INDEX)){
        std::string indexName, tableName;
        std::vector<std::string> fields;
        Rogex::createIndex(commands, indexName, tableName, fields);
        std::cout << ":" << indexName << ":" << tableName << ":";
        Index::createIndex(indexName, tableName, fields);
        std::cout << "The index has been created." << std::endl;
        return ;
    }
    if(std::regex_match(commands, Sqlmain::HELP_INDEX)){
        std::string indexName;
        indexName = Rogex::helpIndex(commands);
        Index::helpIndex(indexName);
        std::cout << "Show you the index." << std::endl;
        return ;
    }






    //pending
    if(std::regex_match(commands, Sqlmain::HELP_DB)){
        Control::showUsers();
        std::cout << std::endl;
        std::cout << "The View:" << std::endl;
        View::showView();
        return ;
    }
    //true
    if (std::regex_match(commands, DROP_DB)){
        std::string status = Rogex::reDropDB(commands);
        Tiny::dropDB(status);
        std::cout << "The database has been dropped." << std::endl;
        return ;
    }
    //true
    if(std::regex_match(commands, CREATE_DB)){
        std::cout << "Creating db..." << std::endl;
        std::string result = Rogex::reCreateDB(commands);
        Tiny::createDatabase(result);
        return ;
    }


    //true
    if(std::regex_match(commands, Sqlmain::reGrant)){
        std::vector<std::string> result = Rogex::Grant(commands);
        Control::Grant(result);
        std::cout << "The user has been authorized." << std::endl;
        return ;
    }
    //true
    if(std::regex_match(commands, Sqlmain::reRevoke)){
        std::vector<std::string> result = Rogex::Revoke(commands);
        Control::Revoke(result);
        std::cout << "The user has been authorized away." << std::endl;
        return ;
    }
    //true
    if(std::regex_match(commands, Sqlmain::reCreateUser)){
        std::string name = Rogex::createUser(commands);
        std::cout << "User: " << name << std::endl;
        bool flag = Control::createUser(name);
        if(flag){
            std::cout << "The user: " << name << " has been created." << std::endl;
        } else {
            std::cout << "The instruction has been executed failed." << std::endl;
        }
        return ;
    }



    //

     //true
    if(Sqlmain::DBRoot == "default"){
        std::cout << "Sorry, you do not choose the database." << std::endl;
        return ;
    }
    //true
    if (std::regex_match(commands, CREATE_TABLE)){
        std::cout << "Creating the table" << std::endl;
        std::vector<std::string> result = Rogex::reCreateTable(commands);
        Util::createTable(result);
        std::cout << "The table has been created." << std::endl;
        return ;

    }//true
    //true
    if (std::regex_match(commands, Sqlmain::O_INERT_INTO)){
        if(!Control::Ainsert){
            std::cout << "Sorry, you do not have the authorization: Insert" << std::endl;
            return ;
        }
        std::vector<std::vector<std::string>> tuples = Rogex::reOInsert(commands);
        int tupleSize = tuples.size();
        for(int i = 0; i < tupleSize; ++i){
            Util::insertValue(tuples[i]);
        }
//        std::cout << "Value has been stored" << std::endl;
        return ;
    }
    //true
    if (std::regex_match(commands, DELETE_DATA)){
        if(!Control::Adelete){
            std::cout << "Sorry, you do not have the authorization: DELETE" << std::endl;
            return ;
        }

        std::vector<std::string> result = Rogex::reDeleteData(commands);
        Util::deleteData(result);
        std::cout << "The data you pointed has been deleted." << std::endl;
        return ;
    }//true
    //true
    if (std::regex_match(commands, SELECT_FROM)){
        if(!Control::Aselect){
            std::cout << "Sorry, you do not have the authorization: SELECTE" << std::endl;
            return ;
        }

        std::vector<std::string> result = Rogex::reSelect(commands);
        Util::selectData(result);
        return ;
    }
    //true
    if (std::regex_match(commands, UPDATE_DATA)){
        std::cout << "Updating: " << std::endl;
        if(!Control::Aupdate){
            std::cout << "Sorry, you do not have the authorization: UPDATE" << std::endl;
            return ;
        }

        std::vector<std::string> result = Rogex::reUpdateData(commands);
        Util::updateData(result);
        return ;
    }
    //true
    if (std::regex_match(commands, DROP_TABLE)){
        std::string status = Rogex::reDropTable(commands);
        Tiny::dropTable(status);
        std::cout << "The table has been dropped." << std::endl;
        return ;
    }
    //true
    if (std::regex_match(commands, DEL_TABLE)){
        std::string status = Rogex::reDeleteTable(commands);
        Tiny::deleteTable(status);
        std::cout << "The table has been delete." << std::endl;
        return ;
    }
    //true
    if (std::regex_match(commands, Sqlmain::HELP_TABLE)){
        std::string table = Rogex::reHelpTable(commands);
        Util::helpTable(table);
        return ;
    }


    if (std::regex_match(commands, Sqlmain::O_SELECT_FROM)){
//        bool readFile = true;
        std::cout << "Selecting..." << std::endl;
//        std::vector<std::vector<Item>> items;
//        Optimize::readItems(location, items);
//        Optimize::getIt(commands, items, readFile);
        Optimize::getIt(commands);
        return ;

    }





    std::cout << "Error: Please check your syntax." << std::endl;
    return ;


//    if (std::regex_match(commands, "\\s*help\\s+view\\s+(\\w+)\\s*")){
//
//
//    }
//    else if (std::regex_match(commands, "\\s*help\\s+index\\s+(\\w+)\\s*")){
//
//
//    }
//

}

