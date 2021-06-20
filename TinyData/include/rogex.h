#ifndef ROGEX_H
#define ROGEX_H

#include <string>
#include <vector>

class Rogex
{
    public:
        Rogex();
        virtual ~Rogex();

        static std::string reCreateDB(std::string commands);

        static std::string reUseDB(std::string commands);
        static std::vector<std::string> reCreateTable(std::string commands);

        static std::vector<std::string> reInsert(std::string commands);

        static std::vector<std::string> reSelect(std::string commands);

        static std::vector<std::string> reDeleteData(std::string commands);

        static std::vector<std::string> reUpdateData(std::string commands);



        static void reDelete(std::string commands);

        static std::string reDropDB(std::string commands);

        static std::string reDropTable(std::string commands);

        static std::string reDeleteTable(std::string commands);

        static std::string reHelpTable(std::string table);

        static void reFields(std::string commands);



        static std::vector<std::string> Grant(std::string commands);
        static std::vector<std::string> Revoke(std::string commands);
        static std::string createUser(std::string commands);

        static void createView(std::string commands, std::string& viewName, std::string& command);

        static std::string helpView(std::string commands);


//        static void re(std::string commands);

        static void createIndex(std::string commands, std::string& indexName, std::string& tableName, std::vector<std::string>& fields);

        static std::string helpIndex(std::string indexName);


//*optimize*//
        static std::vector<std::vector<std::string>> reOInsert(std::string commands);

        static void reOSelect(std::string& tableName, std::string& fieldName, std::string& condition);


        //view



};

#endif // ROGEX_H
