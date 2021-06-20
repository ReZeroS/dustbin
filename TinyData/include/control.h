#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include <string>

#include "user.h"

class Control
{
    public:
        Control();
        virtual ~Control();


        static void readUsers(std::vector<User>& users);
        static void writeUsers(std::vector<User>& users);

        static bool checkPermission(std::string name, std::string passwd);
        static std::string getPasswd();

        static bool createUser(std::string name);

        static void showUsers();

        static bool Aselect;
        static bool Ainsert;
        static bool Adelete;
        static bool Aupdate;

        static void Grant(std::vector<std::string> result);
        static void Revoke(std::vector<std::string> result);


};

#endif // CONTROL_H
