#include <regex>
#include <iostream>


#include "util.h"
#include "rogex.h"
#include "sqlmain.h"



Rogex::Rogex()
{
    //ctor
}

Rogex::~Rogex()
{
    //dtor
}



std::string Rogex::reCreateDB(std::string commands)
{
    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::regex_match(commands, sm, Sqlmain::CREATE_DB);
    return sm[1];
}

std::string Rogex::reUseDB(std::string commands)
{
    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::regex_match(commands,sm, Sqlmain::USE_DB);
    return sm[1];
}

std::vector<std::string> Rogex::reCreateTable(std::string commands)
{

    std::smatch sm;
    std::vector<std::string> vec;
        // same as std::match_results<string::const_iterator> sm;
    std::regex_match(commands, sm, Sqlmain::CREATE_TABLE);

    //sm[1] table name
    //sm[2] All filed
//    std::cout << sm[1] << std::endl;
//    std::cout << sm[2] << std::endl;
    Util::SplitString(sm[2], vec, ",");
    int vecSize = vec.size();
    for(int i = 0; i < vecSize; ++i){
        Util::trim(vec[i]);
    }
    vec.insert(vec.begin(), sm[1]);
//    vecSize += 1;
//    for(int i = 0; i < vecSize; ++i){
//        std::cout << vec[i] << std::endl;
//    }
    return vec;
}

std::vector<std::string> Rogex::reInsert(std::string commands)
{

    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::regex_match(commands, sm, Sqlmain::INSERT_INTO);
    std::vector<std::string> vec;
    sm[1];
    Util::SplitString(sm[2], vec, ",");
    int vecSize = vec.size();
    for(int i = 0; i < vecSize; ++i){
        Util::trim(vec[i]);
    }
    vec.insert(vec.end(), sm[1]);
    /*add the "" value item which does not have value into the vector*/


    return vec;
}



std::vector<std::string> Rogex::reSelect(std::string commands)
{
    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::vector<std::string> vec;
    std::regex_match(commands, sm, Sqlmain::SELECT_FROM);
//    sm[1]//fileds
//    sm[2]//tablename
    std::string filedGroup = sm[1];
    Util::SplitString(filedGroup, vec, ",");
    vec.insert(vec.begin(), sm[2]);
    int vecSize = vec.size();
    for(int i = 0; i < vecSize; ++i){
        vec[i] = Util::trim(vec[i]);
//        std::cout  << "#" << vec[i] << "#";
    }
//    std::cout << std::endl;

    return vec;
}

std::vector<std::string> Rogex::reDeleteData(std::string commands){
    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::vector<std::string> vec;
    std::regex_match(commands, sm, Sqlmain::DELETE_DATA);
    vec.push_back(sm[1]);//table name
    vec.push_back(sm[2]);//column name
    std::string value = sm[3];//column value
    Util::trim(value);
    if( (value[0] == '\'') && (value[value.size()-1] == '\'') ){
        value = value.substr(1, value.size() - 2);
    }
    vec.push_back(value);//the value
    return vec;
}

std::vector<std::string> Rogex::reUpdateData(std::string commands){
    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::vector<std::string> vec;
    std::regex_match(commands, sm, Sqlmain::UPDATE_DATA);
    //sm[2]: aim column, sm[3]: not filter value
    //sm[4]: case column, sm[5]: not filter case value

    //filter
    std::string value, caseValue;
    value = sm[3];
    caseValue = sm[5];
    Util::trim(value);
    Util::trim(caseValue);
    if( (value[0] == '\'') && (value[value.size()-1] == '\'') ){
        value = value.substr(1, value.size() - 2);
    }
    if( (caseValue[0] == '\'') && (caseValue[caseValue.size()-1] == '\'') ){
        caseValue = caseValue.substr(1, caseValue.size() - 2);
    }
    //vec[0]: table
    //vec[1]: aim column, vec[2]: aim value
    //vec[3]: case column, vec[4]: case value
    vec.push_back(sm[1]);
    vec.push_back(sm[2]);
    vec.push_back(value);
    vec.push_back(sm[4]);
    vec.push_back(caseValue);

    return vec;
}



std::vector<std::string> Rogex::Grant(std::string commands){
    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::vector<std::string> vec;
    std::regex_match(commands, sm, Sqlmain::reGrant);
    Util::SplitString(sm[2], vec, ",");
    int vecSize = vec.size();
    for(int i = 0; i < vecSize; ++i){
        Util::trim(vec[i]);
    }
    vec.insert(vec.begin(), sm[1]);
    return vec;
}




std::vector<std::string> Rogex::Revoke(std::string commands){
    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::vector<std::string> vec;
    std::regex_match(commands, sm, Sqlmain::reRevoke);
    Util::SplitString(sm[2], vec, ",");
    int vecSize = vec.size();
    for(int i = 0; i < vecSize; ++i){
        Util::trim(vec[i]);
    }
    vec.insert(vec.begin(), sm[1]);
    return vec;
}



std::string Rogex::reDropDB(std::string commands)
{
    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::regex_match(commands, sm, Sqlmain::DROP_DB);
//    std::cout << sm[1] << std::endl;
    return sm[1];
}


std::string Rogex::reDropTable(std::string commands)
{
    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::regex_match(commands, sm, Sqlmain::DROP_TABLE);
//    std::cout << sm[1] << std::endl;
    return sm[1];
}


std::string Rogex::reDeleteTable(std::string commands)
{
    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::regex_match(commands, sm, Sqlmain::DEL_TABLE);
    return sm[1];
}

std::string Rogex::reHelpTable(std::string commands){
    std::smatch sm;
    std::regex_match(commands, sm, Sqlmain::HELP_TABLE);
    return sm[1];
}

std::string Rogex::createUser(std::string commands){
    std::smatch sm;
    std::regex_match(commands, sm, Sqlmain::reCreateUser);
    return sm[1];
}








/*optimize*/

std::vector<std::vector<std::string>> Rogex::reOInsert(std::string commands){

    std::vector<std::string> groups;
    std::vector<std::vector<std::string>> vecs;

    std::smatch sm;
    std::regex_match(commands, sm, Sqlmain::O_INERT_INTO);

    groups = Util::SplitGroup(sm[2], "(", ")");
    int len = groups.size();

    for(int i = 0; i < len; ++i){
        std::vector<std::string> vec;
//        std::cout << "#" << groups[i] << "#" << std::endl;
        Util::SplitString(groups[i], vec, ",");
        int vecSize = vec.size();
        for(int i = 0; i < vecSize; ++i){
            Util::trim(vec[i]);
//            std::cout << "#" << vec[i] << "#" << std::endl;
        }
        vec.insert(vec.end(), sm[1]);
        vecs.push_back(vec);

    }
    return vecs;

}

void Rogex::createView(std::string commands, std::string& viewName, std::string& command){
    std::smatch sm;
    std::regex_match(commands, sm, Sqlmain::CREATE_VIEW);
    viewName = sm[1];
    command = sm[2];
    return ;
}


std::string Rogex::helpView(std::string commands){
    std::smatch sm;
    std::regex_match(commands, sm, Sqlmain::HELP_VIEW);
    return sm[1];
}



void Rogex::createIndex(std::string commands, std::string& indexName, std::string& tableName, std::vector<std::string>& fields){
    std::smatch sm;
    std::regex_match(commands, sm, Sqlmain::CREATE_INDEX);
    indexName = sm[1];
    tableName = sm[2];
    Util::SplitString(sm[3], fields, ",");
    int vecSize = fields.size();
    for(int i = 0; i < vecSize; ++i){
        Util::trim(fields[i]);
    }
    return ;
}

std::string Rogex::helpIndex(std::string commands){
    std::smatch sm;
    std::regex_match(commands, sm, Sqlmain::HELP_INDEX);
    return sm[1];
}


