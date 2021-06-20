#include <regex>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>



#include "util.h"
#include "field.h"
#include "rogex.h"
#include "sqlmain.h"
#include "optimize.h"



void Optimize::reItem(std::string commands, std::string& table, std::string& aimField, std::string& caseField, std::string& caseValue){
    std::regex regexSelect("\\s*select\\s+(\\w+)\\s+from\\s+(\\w+)\\s+where\\s+(\\w+)\\s+=\\s+(\\.+)\\s*", std::regex::icase);
    std::smatch sm;
    std::regex_match(commands, sm, regexSelect);
    table = sm[2];
    aimField = sm[1];
    caseField = sm[3];
    caseValue = sm[4];
    return ;
}


void Optimize::getItems(std::string tableName, std::vector<std::vector<Item>>& items){
    std::vector<Field> fieldDesc;
    std::string descLocation = Sqlmain::DBRoot + "/" + tableName + ".tiny";
    Util::readFieldDesc(fieldDesc, descLocation);
//
    int position = 0;
    std::vector<int> fieldBox;
    int fieldCount = fieldDesc.size();
    for(int i = 0; i < fieldCount; ++i){
//        std::cout << fieldDesc[i].getName() << std::endl;
        fieldBox.push_back(position);
        fieldBox.push_back(fieldDesc[i].getSize());
//        std::cout << "Box:" << position << "#" << fieldDesc[i].getSize() << std::endl;
        position += fieldDesc[i].getSize();
//  true: std::cout << "#" << fieldDesc[i].getName() << "#" << fieldDesc[i].getSize() << "#" << std::endl;
    }




    std::string dataLocation = Sqlmain::DBRoot + "/" + tableName + ".data";
    std::ifstream dataRead(dataLocation, std::ios::in | std::ios::binary | std::ios::out);

    int cursor = 0;
    int readCount = fieldBox.size();//3
    while(dataRead.peek() != EOF){
        std::vector<Item> row;
        for(int i = 0; i < readCount;){
//            std::cout << cursor << "#" << cursor + fieldBox[i] << std::endl;
            //redirect the aimed column
            dataRead.seekg(cursor + fieldBox[i], dataRead.beg);
            char *value = new char[fieldBox[i+1]];
            dataRead.read(value, fieldBox[i+1]);
            if(value == NULL){
                std::cout << "Memory has been overflowed !!!" << std::endl;
            }
//            std::cout << std::left << std::setw(fieldBox[i+1]) << value << " |" ;
            Item item(tableName, fieldDesc[i/2].getName(), value);


//            std::cout << cursor << "%" << fieldBox[i] << "%" << strlen(value) << std::endl;
            i += 2;
//            std::cout << "I::::" << i << std::endl;
            row.push_back(item);

            delete []value;
        }
        items.push_back(row);

        //redirect new row
        cursor += position;
        dataRead.seekg(cursor, dataRead.beg);
//        std::cout << std::endl;
    }

    return ;


}


//                1               2                   3                   4
// select\\s+(\\w+)\\s+from\\s+(\\w+)\\s+where\\s+(\\w+)\\s+in\\s*\\((\\.+)\\)



void Optimize::getIt(std::string commands){
    std::smatch parent;
    std::regex_match(commands, parent, Sqlmain::O_SELECT_FROM);
    std::smatch child;
    std::regex_match(std::string(parent[4]), child, Sqlmain::SELECT_FROM);


//    std::cout << "Parent: " << "#" << parent[1] << "#" << parent[2]  << "#" << parent[3] << "#" << std::endl;
//    std::cout << "Child: " << "#" << child[1] << "#"<< child[2] << "#" << std::endl;


    std::string table = child[2];
    std::string aimField = child[1];

    std::vector<std::vector<Item>> items;
    std::vector<Item> result;

    getItems(table, items);
    for(auto row : items){
        for(auto item : row){
            if(item.table == table && item.name == aimField){
                result.push_back(item);
            }
//            std::cout << item.table << "#" << item.name << "#" << item.value << "#" << std::endl;
        }
    }



//                1               2                   3                   4
// select\\s+(\\w+)\\s+from\\s+(\\w+)\\s+where\\s+(\\w+)\\s+in\\s*\\((\\.+)\\)
    std::string parentTable = parent[2];
    std::string parentAimField = parent[1];
    std::string parentCaseField = parent[3];
//    std::vector<std::vector<Item>> answer;
    std::vector<Item> answer;

    std::vector<std::vector<Item>> answers;
    getItems(parent[2], answers);

    std::cout << "Parent:" << parentTable << "#" << parentAimField << "#" << parentCaseField << std::endl;
    for(auto row : answers){
        Item aim;
        bool condition = false;
        for(auto item : row){
//            std::cout << "[" << item.table << "]" << item.name << "|" << item.value << std::endl;
            if(item.table == parentTable && item.name == parentAimField){
                aim = item;
            }
            if(item.table == parentTable && item.name == parentCaseField  && item.value == result[0].value){
                condition = true;
            }
        }

        if(condition){
            answer.push_back(aim);
        }

    }

    int len = answer.size();
    std::cout << "+-----+" << std::endl;
    for(int i = 0; i < len; ++i){
        std::cout << "+" << answer[i].value << "+" << std::endl;
    }
    std::cout << "+-----+" << std::endl;

    return ;
}





//            sm[1]:aimField    sm[2]:table    sm[3]:caseField    sm[4]:caseValue   sm[5]
//select\\s+(\\w+)\\s+from\\s+(\\w+)\\s+where\\s+(\\w+)\\s+=\\s+(\\.+?)\\((\\.+)\\)

//maps init with the whole table
//void Optimize::getIt(std::string commands, std::vector<std::vector<Item>>& items, bool& flag){
//    if(std::regex_match(commands, Sqlmain::O_SELECT_FROM) ){
//        std::smatch sm;
//        std::regex_match(commands, sm, Sqlmain::O_SELECT_FROM);
//        getIt(sm[5], items, flag);
//    }
//
//
//    std::string table, aimField, caseField, caseValue;
//    reItem(commands, table, aimField, caseField, caseValue);
//    if(flag){
//        flag = false;
//        getItems(table, items);
//    }
//
//    std::vector<std::vector<Item>> result;
//    for(auto row : items){
//        bool condition = false;
//        for(auto item : row){
//            if(item.table == table && item.name == caseField && item.value == caseValue){
//                condition = true;
//            }
//        }
//        if(condition){
//            result.push_back(row);
//        }
//    }
//
//
//
//    items = result;
//
//    return ;
//}
