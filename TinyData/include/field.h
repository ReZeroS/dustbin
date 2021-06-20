#ifndef FIELD_H
#define FIELD_H

#include <string>

class Field
{

    public:
//        Field();
//        virtual ~Field();
//        Field(int Id, std::string Name, std::string Type, int Len, bool NoIque, bool NoNull, bool PKey, std::string FKey, std::string Check);



//id, Name, Type, Len, NoIque, NoNull, bool PKey, string FKey, Check
        void setId(int _id);

        void setName(std::string _name);
        void setType(std::string _type);
        void setSize(int _len);
        void setNoique(bool _noIque);
        void setNoNull(bool _noNull);
        void setPKey(bool _pKey);
        void setFKey(std::string _fKey);
        void setCheck(std::string _check);




        int getId();

        std::string getName();
        std::string getType();
        int getSize();
        bool getNoique();
        bool getNonull();
        bool getPkey();
        std::string getFkey();
        std::string getCheck();







        void display();

        void outField();

        void inField();

    private:

//id, Name, Type, Len, NoIque, NoNull, bool PKey, string FKey, Check
        int id;
//    char name[20];
        char name[20];
        char type[20];
        int len;

        bool noIque;
        bool noNull;
        bool pKey;
        char fKey[40];

        char check[40];

};

#endif // FILED_H
