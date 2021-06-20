#ifndef GLOBAL_H
#define GLOBAL_H

#include <cstdio>
#include <conio.h>

class Global
{
    public:
        Global();
        virtual ~Global();


        static void HelloWorld();
        static std::string getPasswd();
        static int checkPermission(std::string name, std::string passwd);

        static void showDatabases();


    protected:

    private:
};

#endif // GLOBAL_H
