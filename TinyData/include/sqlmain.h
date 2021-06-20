#ifndef SQLMAIN_H
#define SQLMAIN_H

#include <regex>
#include <string>


class Sqlmain
{
    public:

        static std::string DBRoot;



        static void analyze(std::string commands);





        static const std::regex O_INERT_INTO;

        static const std::regex O_SELECT_FROM;













        static const std::regex HELP_DB;


        static const std::regex CREATE_DB;

        static const std::regex USE_DB;

        static const std::regex CREATE_TABLE;

        static const std::regex INSERT_INTO;

        static const std::regex DELETE_DATA;

        static const std::regex SELECT_FROM;

        static const std::regex UPDATE_DATA;

        static const std::regex DROP_DB;

        static const std::regex DROP_TABLE;

        static const std::regex DEL_TABLE;

        static const std::regex HELP_TABLE;

        static const std::regex reField;

        static const std::regex rePrimaryKey;

        static const std::regex reForeignKey;



        static const std::regex reGrant;

        static const std::regex reRevoke;

        static const std::regex reCreateUser;




        static const std::regex HELP_VIEW;

        static const std::regex CREATE_VIEW;


        //
        static const std::regex CREATE_INDEX;

        static const std::regex HELP_INDEX;




    protected:

    private:
};

#endif // SQLMAIN_H
