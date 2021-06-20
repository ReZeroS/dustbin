#ifndef TINY_H
#define TINY_H

#include <string>

class Tiny
{
    public:
        Tiny();
        virtual ~Tiny();

        //Database handle command
        static void createDatabase(std::string result);

        static void dropDB(std::string dbName);

        static void dropTable(std::string table);

        static void deleteTable(std::string table);

        static void helpDatabase();




    private:
};

#endif // TINY_H
