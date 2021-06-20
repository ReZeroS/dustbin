#ifndef USER_H
#define USER_H

#include <string>

class User
{
    public:
        void setSelect(bool key);
        void setDelete(bool key);
        void setInsert(bool key);
        void setUpdate(bool key);


        bool getSelect();
        bool getDelete();
        bool getInsert();
        bool getUpdate();

        void setUsername(std::string name);
        void setPassword(std::string passwd);

        std::string getUsername();
        std::string getPassword();

    private:

        char userName[20];
        char passWord[20];

        bool pSelect;
        bool pDelete;
        bool pInsert;
        bool pUpdate;




};

#endif // USER_H
