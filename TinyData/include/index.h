#ifndef INDEX_H
#define INDEX_H


#include <string>
#include <vector>


class Index
{
    public:

        static void createIndex(std::string& indexName, std::string& tableName, std::vector<std::string>& fields);

        static void helpIndex(std::string indexName);

};

#endif // INDEX_H
