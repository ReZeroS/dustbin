#include <iostream>
#include <cstring>        // for strcpy(), strcat()
#include <io.h>

#include "util.h"
#include "global.h"




void Global::HelloWorld(){
    std::cout << std::endl;
    std::cout
            <<  "Welcome to tiny data, all of the operations as follows: \n"
            <<  "1. Create table : CREATE TABLE tableName(fieldName FIELD(Len), field2(Len)); \n"
            <<  "2. Select attribute : SELECT field1, field2 FROM tableName [WHERE] (condition) \n"
            <<  "3. Insert attribute : INSERT INTO VALUES (value1, value2) \n"
            <<  "4. Delete attribute : DELETE FROM tableName WHERE (condition) \n"
            <<  "5. Update attribute : UPDATE student SET field = value WHERE field = value \n"
            <<  "6. Grant user: Grant user_name operation, ... \n"
            <<  "7. Revoke user: Grant user_name operation, ... \n"
            <<  "8. Create user: Create user, then input the password, default(no permission) \n"
            <<  "9. Help table tableName. \n"
            <<  "10.Help database \n"
            << std::endl;
}


std::string Global::getPasswd()
{
    char c;
    std::string passwd;
    while ((c=getch()) != '\r')
    {
        passwd+=c;
        putchar('*');
    }
    return passwd;
}


int Global::checkPermission(std::string name, std::string passwd){
    std::string content = Util::ReadAsString("passwd");
    std::vector<std::string> userList;
    Util::SplitString(content, userList, ";");
    int len = userList.size();
    for(int i = 1; i < len; ++i){
        int index = userList[i].find("&");
        std::string username = userList[i].substr(0, index-1);
        std::string password = userList[i].substr(index+1, userList.size());
        if(username==name && password == passwd){
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}


void Global::showDatabases()
{
    char dir[200];
    std::cout << "Enter a directory: ";
    std::cin.getline(dir, 200);

    char dirNew[200];
    strcpy(dirNew, dir);
    strcat(dirNew, "\\*.*");    // 在目录后面加上"\\*.*"进行第一次搜索

    intptr_t handle;
    _finddata_t findData;

    handle = _findfirst(dirNew, &findData);
    if (handle == -1)        // 检查是否成功
        return;

    do
    {
        if (findData.attrib & _A_SUBDIR)
        {
            if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
                continue;

            std::cout << findData.name << "\t<dir>\n";

            // 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
            strcpy(dirNew, dir);
            strcat(dirNew, "\\");
            strcat(dirNew, findData.name);

//            listFiles(dirNew);
        }
        else
            std::cout << findData.name << "\t" << findData.size << " bytes.\n";
    } while (_findnext(handle, &findData) == 0);

    _findclose(handle);    // 关闭搜索句柄
    return ;
}




