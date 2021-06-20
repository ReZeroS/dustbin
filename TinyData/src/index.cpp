#include <fstream>
#include <iostream>

#include "index.h"



void Index::createIndex(std::string& indexName, std::string& tableName, std::vector<std::string>& fields){
    std::ofstream indexWriter("index", std::ios::app);
    indexWriter << indexName << " " << tableName;
    int len = fields.size();
    for(int i = 0; i < len; ++i){
        indexWriter << " " << fields[i];
    }
    indexWriter << std::endl;
    indexWriter.close();


}


void Index::helpIndex(std::string indexName){
    std::ifstream indexReader("index", std::ios::in | std::ios::out);

    std::string s;
    std::getline(indexReader, s);
    while(std::getline(indexReader, s)){
        std::string name = s.substr(0, s.find_first_of(" "));

        if(name == indexName){
            std::string command = s.substr(s.find_first_of(" "));
            std::cout << ":"<< command << std::endl;
            break;
        }
    }

    return ;
}
