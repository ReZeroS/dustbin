#ifndef OPTIMIZE_H
#define OPTIMIZE_H

#include <string>
#include <vector>

#include "item.h"

class Optimize
{
    public:

        static void getIt(std::string commands);

//        static void getIt(std::string commands, std::vector<std::vector<Item>>& items, bool& flag);

        static void getItems(std::string tableName, std::vector<std::vector<Item>>& items);

//        static void reSelect(std::string commands, std::string& table, bool flag);

        static void reItem(std::string commands, std::string& table, std::string& aimField, std::string& caseField, std::string& caseValue);

};

#endif // OPTIMIZE_H
