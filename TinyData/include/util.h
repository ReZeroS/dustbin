#ifndef UTIL_H
#define UTIL_H


#include <regex>
#include <string>
#include <vector>


#include "field.h"

class Util
{
    public:

        //File tools
        static std::string ReadAsString(std::string fileName);

        static void readFieldDesc(std::vector<Field>& fileds, std::string location);

        static void writeFieldDesc(std::vector<Field>& fileds, std::string location);

        //String handle tools
        static std::string& trim(std::string &s);

        static void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);

        static std::vector<std::string> SplitGroup(const std::string &s, const std::string& f, const std::string& e);


        //Table tools
        static void helpTable(std::string table);

        static void createTable(std::vector<std::string> result);


        static void insertValue(std::vector<std::string> values);

        static void deleteData(std::vector<std::string> result);

        static void selectData(std::vector<std::string> result);

        static void updateData(std::vector<std::string> result);



};

#endif // UTIL_H
